# AquaSinc

A small home-made aquarium controller built around an ARM Cortex M4 STM32f and a Raspberry Pi

## Reference

- 1Bitsy Pinout [ https://github.com/esden/1BitSy ]

## Parts
- 3.3V LDO [ https://www.arrow.com/en/products/mcp1703a-3302edb/microchip-technology ]
- Green Chip LED [ https://www.arrow.com/en/products/kpg-1608vgc-a/kingbright ]

## Dev Instructions for Black Magic Probe

Putting these here because I forget...

1. `$ arm-none-eabi-gdb src/main.elf` or `make debug`
    Upon start up of gdb, these should automatically be exectured from .gdbinit
    ```bash
    (gdb) set target-async on
    (gdb) set confirm off
    (gdb) set mem inaccessible-by-default off
    (gdb) target extended-remote /dev/cu.usbmodem7BAB88A81
    (gdb) monitor version
    (gdb) monitor swdp_scan
    (gdb) attach 1
    ```
2. Load the program from the connected computer with `load`
3. Use any of the following to debug
    * `run` - start or restart the program
    * `start` - run till the beginning of the main function, restart if needed
    * `Ctrl-C` - interrupt the program while running
    * `continue` - resume running after being stopped
    * `next` - run next line of program (but don't step into functions)
    * `step` - like next, but steps into a function
    * `finish` - run till you leave the current function
    * `list [line number]` - show 10 lines surrounding [line number], current line by default
    * `info locals` - print out local variables
    * `set variable <var_name>=<value>` - set variable _var_name_ to _value_
    * `break <line_number>` - set a breakpoint at _line_number_
    * `info breakpoints` - list current breakpoints
    * `disable breakpoints`
    * `delete breakpoints`
    * `watch <var_name>` - set a watchpoint on variable _var_name_
    * `print <expression>` - evaluates expression and prints it
    * `printf <format_string>,<var_name>` - place _var_name_ in the format string at points with %d,%s,etc
    * `commands ... end` - execute the given commands after the previously created watchpoint is changed. 
        Example:
        ```bash
        (gdb) watch blink_count
        (gdb) commands
        > printf "blink extend condition %d\n", blink_count^4
        > end
        ```
4. If you make changes to main.c, you can run make from within gdb, followed by `load`.
5. `quit` to exit gdb or `Ctrl-D`

