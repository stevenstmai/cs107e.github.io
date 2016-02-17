#! /usr/bin/env python
from __future__ import print_function
from subprocess import check_output
import sys, os

# This program computes and prints out the number of bytes needed to pad $2
# given that $2 is the .text section of the ARM ELF object file #1.

def get_addr(obj_file, symbol):
    nm_out = check_output(["arm-none-eabi-nm", obj_file]).decode("ascii").split('\n')
    for line in nm_out:
        [addr, _type, name] = line.split(" ")
        if name == symbol:
            return int(addr, 16)
    return None

obj_filename = sys.argv[1]
bin_filename = sys.argv[2]

stab_start = get_addr(obj_filename, "__stab_start__")
text_start = get_addr(obj_filename, "_start")
if not stab_start or not text_start:
    sys.exit(1)

bin_size = os.path.getsize(sys.argv[2])
padding = (stab_start - text_start) - bin_size
print(max(0, padding))
