keywords = {"INPUT": 10, "PRINT": 11,
            "LOAD": 20, "STORE": 21, "SET": 22,
            "ADD": 30,
            "JMP": 40,
            "AND": 50,
            "PUSH": 60,
            "HALT": -1};
MAX_MEM = 100
var_stack = {}
labels = {}


def pretranslate(src_code):
    after_code = []
    for line in src_code:
        cmds = str(line).split()
        if len(cmds) > 0:
            if cmds[0] == "DIM":
                if len(cmds) == 2:
                    cmds.append("0")
                if len(cmds) > 2:
                    if cmds[1] in var_stack:
                        print("VAR %s ALREADY DEFINED." % cmds[1])
                        return
                    var_stack[cmds[1]] = (MAX_MEM - 1 - len(var_stack), int(cmds[2]))
            if cmds[0].startswith("."):
                if cmds[0] in labels:
                    print("LABEL %s ALREADY DEFINED." % cmds[0])
                    return
                labels[cmds[0]] = len(after_code)
    return after_code
    print(var_stack)


codes = ["DIM A 10", "DIM B", ".start", "INPUT A", "PRINT A"]
pretranslate(codes)
