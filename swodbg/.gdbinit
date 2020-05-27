# connect to target
target remote localhost:2331
# reset target
monitor reset 0
monitor SWO EnableTarget 160000000 75000 1 0
# load image
load blink.elf
# load symbols
file blink.elf
# init regs
set $pc=0x20000000
set $sp=0x20010000
# it's ready for starting ...

