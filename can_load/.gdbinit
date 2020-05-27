# connect to target
target remote localhost:2331
# reset target
monitor reset 0
monitor SWO EnableTarget 160000000 75000 1 0
# loading symbols
file blink.elf
# it's ready for starting ...

