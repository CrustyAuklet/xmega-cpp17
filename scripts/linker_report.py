#!/usr/bin/env python

from collections import OrderedDict
from os import path
import re
import os
import json

_columns = [ "Name", "Value", "Class", "Type", "Size", "Line", "Section", "Path"]
_class_code = { 'U':'Undefined named object', 'C':'Common', 'W':'Weak reference', 't':'Local function', 'T':'Global function', 'd':'Local data', 'D':'Global data', '?':'Unknown' }

# A Utility Function to find the common
# prefix between first and last strings
def commonPrefixUtil(str1, str2):
    n1 = len(str1)
    n2 = len(str2)
    result = ""

    # Compare str1 and str2
    j = 0
    i = 0
    while(i <= n1 - 1 and j <= n2 - 1):
        if (str1[i] != str2[j]):
            break
        result += (str1[i])
        i += 1
        j += 1
    return (result)


def parse_nm_sysv(nm_output):
    '''
    Parses the output of gcc NM command in sysv format.
    Be sure to run nm with the arguemnts: "-l -S -C -f sysv"
    '''
    sections = []
    for line in nm_output.split('\n'):
        if '|' in line:
            l = [x.strip() for x in re.split(r"(?<!operator)\||\t", line.strip())]
            # identify code from libc and mark appropriatly
            if len(l) == 7:
                l.append('./libc')
            elif 'libgcc' in l[7]:
                # libgcc files will have the path of the compiler's compiler. but end with a correct path
                l[7] = './libc' + l[7].split('libgcc')[-1]
            else:
                # normal path, make it absolute
                l[7] = path.abspath(l[7])
            # append section line to list
            sections.append(l)
    # find longest common prefix, not including system directories
    paths = [ x[7] for x in sections if 'libc' not in x[7] ]
    paths.sort(reverse=False)
    prefix = commonPrefixUtil(paths[1], paths[-1])
    # remove prefix from all paths and replace with './'
    for s in sections:
        s[7] = s[7][len(prefix):] if s[7].startswith(prefix) else s[7]
        split_test = s[7].split(':')
        # add line number back to position 5
        if len(split_test) > 1:
            s[7] = split_test[0]
            s[5] = split_test[1]
    # return list of parsed NM output
    return sections


def get_binary_name(nm_output):
    match = re.search(r'Symbols from (.+):', nm_output)
    if match:
        return os.path.split(match.group(1))[1]
    else:
        return 'ELF'


def splitall(path):
    allparts = []
    while 1:
        parts = os.path.split(path)
        if parts[0] == path:  # sentinel for absolute paths
            allparts.insert(0, parts[0])
            break
        elif parts[1] == path: # sentinel for relative paths
            allparts.insert(0, parts[1])
            break
        else:
            path = parts[0]
            allparts.insert(0, parts[1])
    return allparts


def add_node(root, node_path, node_size):
    node = root
    added = 0
    for p in splitall(node_path):
        if p == '.':
            # skip "this" directory dots
            continue
        children = node["children"]
        if p not in [x['name'] for x in children]:
            add = {"name": p, "children": []}
            children.append(add)
            added = 1
            node = children[-1]
        else:
            p_index = [x['name'] for x in children].index(p)
            node = children[p_index]
    if added:
        node.pop("children")
        node['size'] = node_size

def total_size(root):
    # TODO: Walk dict and sum up size
    return 10000

def make_ordered_dict(section_list, name, size_base=16):
    '''
    '''
    # parse output and store in dict
    root = OrderedDict({"name": name, "children": []})
    for section in section_list:
        try:
            node_size = int(section[4],size_base)
        except ValueError:
            # symbols without size have blank entries
            continue
        node_path = path.join(section[6], section[7], section[0])
        add_node(root, node_path, node_size)
    return root


def stringify_dict(root, minimize=false):
    s = "var linker_report = "
    if minimize:
        return s + json.dumps(dict(root), indent=None, separators=(',',':'))
    else:
        return + json.dumps(dict(root), indent=4)


def do_output(filename, size=None):
    f = open(filename).read()

    symbols = parse_nm_sysv(f)
    name = get_binary_name(f)

    root = make_ordered_dict(symbols, name)

    if size is not None:
        add_node(root, "Unused", size - total_size(root))

    fd = open("./scripts/html/linker-report.js","w")
    fd.write(stringify_dict(root))
    fd.truncate()

def main(binaries, output):
    op = ""
    for binary in binaries:
        # run nm command on binary
        cmd = [nm] + nm_opts.split() + [binary]
        print(" ".join(cmd))
        op += check_output(cmd).strip()
    root = parse_nm_output(op)
    output_to_file(output, root)


default_datafile = "linker-report.js"

if __name__ == '__main__':
    import argparse
    import webbrowser

    parser = argparse.ArgumentParser(
        description='Generate an interactive visualization of binary size'
        epilog=R'This program accepts the output of nm in sysv format. To get the proper information and run nm with at least the options "-l -S -C -f sysv')

    def output_arg(s):
        if path.isdir(s):
            s = path.join(s, default_datafile)
        return open(s, "wb")

    # specify arguments
    parser.add_argument('-i', '--input', type = str, required = True, nargs = '*',
                        help = 'path to the sysv formatted output of nm')
    parser.add_argument('-o', '--output', type = output_arg,
                        help = f'Path and name of output file. By default the outout will go to stdout'),
                        default = None)
    parser.add_argument('-b', '--browser', action='store_true',
                        help = 'launch the pie chart visualisation in a browser')
    parser.add_argument('-s', '--size', type = int,
                        help = 'Total size of device data segment. This will add an "Unused" segment for unused program space.')

    # get and validate arguments
    args = parser.parse_args()

    # parse input and write to output
    main(args.binary, args.output)

    # close output file
    output_fn = path.abspath(args.output.name)
    args.output.close()

    print("[INFO] data written to", output_fn)

    if args.browser:
        uri = "file://" + path.join(repo_root, "index.html")
        print("[INFO] opening in browser", uri)
        webbrowser.open(uri, new=2)
