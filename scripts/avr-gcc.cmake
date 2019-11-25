find_program(AVR-SIZE avr-size)
find_program(AVR-NM avr-nm)
find_program(AVR-UPLOAD avrdude)
find_program(AT_UPPLOAD atprogram.exe HINTS "C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\atbackend")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
            SUFFIX ".elf"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
        -O ihex
        -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures
        $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.hex
    COMMENT "OBJCOPY from ELF file into HEX file"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
        -j .eeprom
        --set-section-flags=.eeprom=alloc,load
        --change-section-lma .eeprom=0
        --no-change-warnings
        -O ihex     # should this be binary? atmel studio uses ihex
        $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.eep
    COMMENT "OBJCOPY from ELF file into EEPROM file"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -h -S $<TARGET_FILE:${PROJECT_NAME}> > $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.lss
    COMMENT "OBJCOPY from ELF file into LSS file"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    -O srec
    -R .eeprom  -R .fuse -R .lock -R .signature -R .user_signatures
    $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.srec
    COMMENT "OBJCOPY from ELF file into SREC file"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    -O binary
    -j .text -j .data
    $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.bin
    COMMENT "OBJCOPY from ELF file into BIN file"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${AVR-SIZE}
        $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Display binary size on the terminal"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${AVR-NM}
        -Crtd   #demangle, reverse sorted, use decimal numbers
        -l
        --size-sort
        -f sysv
        $<TARGET_FILE:${PROJECT_NAME}> > $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}_nmdump.txt
        COMMENT "Display binary size on the terminal"
)

add_custom_target(program_edbg
       COMMAND ${AT_UPPLOAD} -t edbg -i PDI -d ${CMAKE_SYSTEM_PROCESSOR} program -f $<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>
       DEPENDS ${PROJECT_NAME}
)
