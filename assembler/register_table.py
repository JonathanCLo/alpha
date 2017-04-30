'''
Description: Maps register names to numbers
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f98/doc/alpha-guide.pdf
'''

REGS = dict()
REGS["0"] = 0
REGS["v0"] = 0
for i in range(0, 8): # temporaries 1-8
    REGS[str(i + 1)] = i + 1
    REGS["t" + str(i)] = i + 1
for i in range(0, 7): # callee saved 9-15
    REGS[str(i + 9)] = i + 9
    REGS["s" + str(i)] = i + 9
REGS["fp"] = 15 # frame pointer - also $15 and $s6
for i in range(0, 6): # integer arguments 0-5
    REGS[str(i + 16)] = i + 16
    REGS["a" + str(i)] = i + 16
for i in range(8, 12): # temporaries t8-t11
    REGS[str(i + 14)] = i + 14
    REGS["t" + str(i)] = i + 14
REGS["26"] = 26
REGS["ra"] = 26
REGS["27"] = 27
REGS["pv"] = 27 # address of current procedure
REGS["t12"] = 27 # temporary
REGS["28"] = 28 # reserved for assembler use
REGS["at"] = 28 # reserved for assembler use
REGS["29"] = 29
REGS["gp"] = 29 # global pointer
REGS["30"] = 30
REGS["sp"] = 30 # stack pointer
REGS["31"] = 31 # always zero
REGS["zero"] = 31
