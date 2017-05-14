'''
Description: Assembler; Converts nice assembly files into ALPHA binary
'''
import sys
from mnemonic_table import MNEM
from register_table import REGS

def isMemory(mnemonic):
    return mnemonic in ["LDA", "LDAH", "LDBU", "LDL", "LDWU", "STL",\
                    "STW", "RPCC"]
def isControl(mnemonic):
    return mnemonic in ["JMP", "JSR", "RET", "JSRC"]
def isBranch(mnemonic):
    return mnemonic in ["BEQ", "BGE", "BGT", "BLBC", "BLBS", "BLE", \
                    "BLT", "BNE", "BR", "BSR"]
def isPalcode(mnemonic):
    return mnemonic in ["PAL", "HALT", "NOOP"]
def isOperate(mnemonic):
    return mnemonic in ["ADDL", "S4ADDL", "S8ADDL", \
                    "CLTZ", "CTPOP", "CTTZ", \
                    "MULL", "SUBL", "S4SUBL", "S8SUBL", \
                    "AND", "BIC", "BIS", "EQV", "ORNOT", "XOR", \
                    "CMOVEQ", "CMOVGE", "CMOVGT", "CMOVLBS", "CMOVLE", "CMOVNE", "CMOVLT", \
                    "SLL", "SRA", "SRL", "CMPGBE", "EXTWL", \
                    "EXTLL", "EXTWH", "EXTLH", \
                    "INSWL", "INSLL", "INSWH", "INSLH", \
                    "MSKWL", "MSKLL", "MSKWH", "MSKLH", "SEXTW"]

def isLabel(mnemonic):
    return mnemonic.endswith(":")

class Instruction():
    targets = dict()
    addrnext = 0
    def __init__(self, string):
        self.raw_string = string
        self.comment = ""
        if ";" in self.raw_string:
            self.raw_string = string.split(";")[0].strip()
            self.comment = string.split(";")[1:]
        parts = [splits for splits in self.raw_string.split(" ") if splits is not ""]
        self.mnemonic = parts[0]
        if isMemory(self.mnemonic):
            # LDA $Ra $Rb 1234
            self.Format = "Memory"
            self.Ra = parts[1].strip("$")
            self.Rb = parts[2].strip("$")
            self.Disp = int(parts[3])
            self.Addr = Instruction.addrnext
            Instruction.addrnext += 1
        elif isBranch(self.mnemonic):
            # BEQ $Ra @Target
            self.Format = "Branch"
            self.Ra = parts[1].strip("$")
            self.Target = parts[2].strip("@")
            self.Addr = Instruction.addrnext
            Instruction.addrnext += 1
        elif isControl(self.mnemonic):
            self.Format = "Control"
            self.Target = parts[1].strip("@")
            self.Addr = Instruction.addrnext
            Instruction.addrnext += 1
        elif isOperate(self.mnemonic):
            # ADDL $Ra $Rb $Rc
            # ADDL $Ra 1234 $Rc
            self.Ra = parts[1].strip("$")
            if parts[2].startswith("$"):
                self.Rb = parts[2].strip("$")
            else:
                self.Li = int(parts[2])
            self.Rc = parts[3].strip("$")
            self.Format = "Operate"
            self.Addr = Instruction.addrnext
            Instruction.addrnext += 1
        elif isPalcode(self.mnemonic):
            # PAL HALT
            self.Format = "PALCode"
            if (len(parts) > 1 and isPalcode(parts[1])):
                self.PALCode = parts[1]
            else:
                self.PALCode = parts[0]
            self.Addr = Instruction.addrnext
            Instruction.addrnext += 1
        elif isLabel(self.mnemonic):
            # Target:
            self.Format = "Label"
            self.Label = parts[0].strip(":")
            Instruction.targets[self.Label] = Instruction.addrnext
            # Don't touch addrnext because not executable
        else:
            print(string, " - ", self.mnemonic)
        return

    def toBinary(self):
        result = ""
        if self.Format != "Label":
            result += "{0:b}".format(MNEM[self.mnemonic][0]).zfill(6)
        if self.Format == "Memory":
            result += "{0:b}".format(REGS[self.Ra]).zfill(5)
            result += "{0:b}".format(REGS[self.Rb]).zfill(5)
            if hasattr(self, "Disp"):
                result += "{0:b}".format(self.Disp).zfill(16)
            if MNEM[self.mnemonic][1] != None:
                result += "{0:b}".format(MNEM[self.mnemonic][1]).zfill(2)
            return result
        elif self.Format == "Branch":
            result += "{0:b}".format(REGS[self.Ra]).zfill(5)
            # figure out target
            target = Instruction.targets[self.Target]
            pc = self.Addr
            result += "{0:b}".format(target - pc).zfill(20)
            return result
        elif self.Format == "Control":
            result += "{0:b}".format(REGS["pv"]).zfill(5)
            result += "{0:b}".format(REGS["at"]).zfill(5) #jumps to address at at; need to remember to set at
            result += "{0:b}".format(MNEM[self.mnemonic][1]).zfill(2)
            result += "".zfill(15)
            return result
        elif self.Format == "Operate" and hasattr(self, "Li"): #literal 
            result += "{0:b}".format(REGS[self.Ra]).zfill(5)
            result += "{0:b}".format(self.Li).zfill(8)
            result += "1"
            result += "{0:b}".format(MNEM[self.mnemonic][1]).zfill(7)
            result += "{0:b}".format(REGS[self.Rc]).zfill(5)
            return result
        elif self.Format == "Operate" and hasattr(self, "Rb"): # register
            result += "{0:b}".format(REGS[self.Ra]).zfill(5)
            result += "{0:b}".format(REGS[self.Rb]).zfill(5)
            result += "000"
            result += "0"
            result += "{0:b}".format(MNEM[self.mnemonic][1]).zfill(7)
            result += "{0:b}".format(REGS[self.Rc]).zfill(5)
            return result
        elif self.Format == "PALCode":
            if self.PALCode == "HALT":
                result += "1".zfill(26)
            elif self.PALCode == "NOOP":
                result += "0".zfill(26)
            else:
                result += "10".zfill(26)
            return result
        return ""
def test():
    pass

def main():
    if len(sys.argv) < 2:
        test()
    else:
        _, inarg, outarg = sys.argv
        program = []
        with open(inarg, 'r') as infile:
            for line in infile:
                if (line.strip() == ""):
                    continue
                program.append(Instruction(line.strip()))
        with open(outarg, 'w') as outfile:
            accumulator = 0
            for instr in program:
                b = instr.toBinary()
                if b != "":
                    print(b)
                    print(instr.raw_string)
                    outfile.write(str(hex(accumulator))[2:] + " 1 ")
                    accumulator = accumulator + 4
                    outfile.write(str(hex(int(instr.toBinary(), 2)))[2:])
                    outfile.write("\n")
                    '''
                    one, two, three, four = b[24:32], b[16:23], b[8:15], b[0:7]
                    outfile.write(str(hex(int(four, 2)))[2:] + " ")
                    outfile.write(str(hex(int(three, 2)))[2:] + " ")
                    outfile.write(str(hex(int(two,2)))[2:] + " ")
                    outfile.write(str(hex(int(one, 2)))[2:] + "\n")
                    '''
            outfile.write("0\n")

if __name__ =="__main__":
    main()
