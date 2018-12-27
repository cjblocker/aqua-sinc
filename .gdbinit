set history file ~/.gdb_history
set history save on
set target-async on
set confirm off
set mem inaccessible-by-default off
target extended-remote /dev/cu.usbmodem7BAB88A81
monitor version
monitor jtag_scan
attach 1