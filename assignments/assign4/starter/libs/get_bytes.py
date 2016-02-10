#! /usr/bin/env python
from __future__ import print_function
import binascii, sys

# This program takes an decimal integer string as its first argument and outs
# the 32-bit little endian representation of the integer.

full_hex = "{0:0{1}x}".format(int(sys.argv[1]), 8)
hex_string = "".join([full_hex[i-2:i] for i in range(len(full_hex), 0, -2)])

# retrieve stdout as a binary file object. (compat. between python 2 and 3)
output = getattr(sys.stdout, 'buffer', sys.stdout)
output.write(binascii.unhexlify(hex_string))
