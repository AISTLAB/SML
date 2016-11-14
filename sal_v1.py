# coding:utf-8
# winxos 2016-11-15
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
    # after_code.append(["JMP", "main"])
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
        after_code.append(int(var_table[n]))
        var_table[n] = len(after_code) - 1
    print(var_table)
    print(label_table)
    print(after_code)
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
                if code[0] == "HALT":
                    pass
                else:
                    print("[waring] LINE % MISS OPERAND." % index)
        ml.append(operator * 100 + operand)
    print(ml)
    return ml


codes = open("sum.sal").read().split("\n")
translate(pretranslate(codes))
