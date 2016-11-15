# coding:utf-8
# SIMPLE ASSEMBLY LANGUAGE V1
# ASSEMBLY SAL FILE TO SAL FOR SML
# PYTHON 3.5
# winxos 2016-11-15
import glob
import sys, os

keywords = {"INPUT": 10, "PRINT": 11,
            "LOAD": 20, "STORE": 21, "SET": 22,
            "ADD": 30, "SUB": 31, "MUL": 32, "DIV": 33, "MOD": 34, "INC": 35, "DEC": 36, "NEG": 37,
            "JMP": 40, "JMPN": 41, "JMPZ": 42, "HALT": 43,
            "AND": 50, "OR": 51, "XOR": 52,
            "PUSH": 60, "POP": 61
            };
MAX_MEM = 100
var_table = {}
label_table = {}


def pretranslate(src_code):
    after_code = []
    for line in src_code:
        cmds = str(line).split()
        if len(cmds) > 0:
            if cmds[0] == "DIM":  # vars
                if len(cmds) == 2:
                    cmds.append("0")
                if len(cmds) > 2:
                    if cmds[1] in var_table:
                        print("[error] VAR %s ALREADY DEFINED." % cmds[1])
                        return
                    var_table[cmds[1]] = cmds[2]
            elif cmds[0].startswith("."):  # label
                if cmds[0] in label_table:
                    print("[error] LABEL %s ALREADY DEFINED." % cmds[0])
                    return
                label_table[cmds[0]] = len(after_code)
            elif cmds[0].startswith(";"):  # comment
                pass
            else:  # normal code
                after_code.append(cmds)

    for i, n in enumerate(var_table):
        after_code.append(var_table[n])
        var_table[n] = len(after_code) - 1
    return after_code


def translate(codes):
    ml = []
    for index, code in enumerate(codes):
        if index >= len(codes) - len(var_table):
            ml += (codes[-len(var_table):])
            break
        operator = keywords[code[0]]
        operand = 0
        if code[0] == "JMP" or code[0] == "JMPN" or code[0] == "JMPZ":
            if len(code) > 1:
                label = "." + code[1]
                if label in label_table:
                    operand = label_table[label]
                else:
                    print("[error] LABEL %S NOT FOUND." % code[1])
                    return;
            else:
                print("[waring] LINE % MISS LABEL." % index)
        else:
            if len(code) > 1:
                if code[1] in var_table:
                    operand = var_table[code[1]]
                else:
                    print("[error] VAR %s NOT FOUND." % code[1])
                    return;
            else:
                if code[0] == "HALT" or code[0] == "PUSH" or code[0] == "POP":
                    pass
                else:
                    print("[waring] LINE % MISS OPERAND." % index)
        ml.append("%02d%02d" % (operator, operand))
    return ("\n").join(ml)


def deal_sal(n):
    fn = str(n).split(".")[0] + ".sml"
    try:
        with open(n) as fi, open(fn, "w") as fo:
            fo.write(translate(pretranslate(fi.read().split("\n"))))
            print("[success] ASSEMBLY FILE %s TO %s" % (n, fn))
    except IOError as e:
        print("[error] %s" % str(e))


def console():
    print("WELCOME TO SIMPLE ASSEMBLER v1")
    print("\t\twinxos 2016-11-15")
    print("\n")
    print("ls\t\t[list .sal assembly file]")
    print("as file\t\t[assembly .sal file to .sml file]")
    print("exit\t\t[exit program]")
    while True:
        cmd = str(input("SAL >"))
        cmds = cmd.split(" ")
        if cmds[0] == "ls":
            print("\n".join(glob.glob(r"*.sal")))
        if cmds[0] == "as":
            deal_sal(cmds[1])
        if cmds[0] == "exit":
            sys.exit()


if __name__ == "__main__":
    if len(sys.argv) > 1:
        deal_sal(sys.argv[1])
    else:
        console()
