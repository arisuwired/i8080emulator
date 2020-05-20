#!/bin/env python3

filename = "opcodes.h"

size_3 = ["SHLD", "LHLD", "STA", "LDA", "JNZ", "JMP", "CNZ", "JZ", "CZ",
        "CALL", "JNC", "CNC", "JC", "CC", "JPO", "CPO", "JPE", "CPE",
        "JP", "CP", "JM", "CM"]
str_default = """default:
    inst_fmt(dst, i, file_memory+i, inst_len, "--");
    break;"""
str_size_1 = """case {}:
    inst_fmt(dst, i, file_memory+i, inst_len, "{}");
    break;"""
str_size_2 = """case {}:
    arg = 0;
    inst_len = 2;
    arg = (file_memory+i)[1];
    inst_fmt(dst, i, file_memory+i, inst_len, "{}, $%x", arg);
    break;"""
str_size_2_2 = """case {}:
    arg = 0;
    inst_len = 2;
    arg = (file_memory+i)[1];
    inst_fmt(dst, i, file_memory+i, inst_len, "{} $%x", arg);
    break;"""
str_size_3 = """case {}:
    arg = 0;
    inst_len = 3;
    arg = (file_memory+i)[1];
    arg += (file_memory+i)[2] << 8;
    inst_fmt(dst, i, file_memory+i, inst_len, "{} $%x", arg);
    break;"""

if __name__ == "__main__":
    lines = []
    with open(filename, "r") as f:
        lines = f.readlines()
    lines = filter(lambda x: x.startswith("#define "), lines)
    lines = map(lambda x: x.split()[1], lines)
    lines = filter(lambda x: "OPCODE" in x, lines)
    lines = list(lines)[1:]
    print("switch (*(file_memory+i)) {")
    for macro in lines:
        splitted = macro.split("_")
        if "D8" in macro:
            if len(splitted) == 3:
                print(str_size_2_2.format(macro, splitted[1]))
                continue
            print(str_size_2.format(macro, splitted[1] + " " + splitted[2]))
        # instruction that are 3 bytes long but dont have a D16 in
        # their define name are a little bit different
        elif any(map(lambda x: x in macro, size_3)):
            print(str_size_3.format(macro, splitted[1]))
        elif "D16" in macro:
            print(str_size_3.format(macro, splitted[1] + " " + \
                    splitted[2] + ","))
        else:
            print(str_size_1.format(macro, splitted[1] + " " + \
                ", ".join(splitted[2:])))
    print(str_default)
    print("}")
