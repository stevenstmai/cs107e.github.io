from random import randint

print " A  S L"
for i in range(16):
    addr = randint(0,255)
    cacheaddr = addr&0x7
    print "%02X %X %X" % (addr, (cacheaddr>>1), (cacheaddr&1))
