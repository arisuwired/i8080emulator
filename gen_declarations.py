#!/bin/env python3

FILENAME = "instructions.c"
TYPE = "static unsigned"

if __name__ == "__main__":
    with open(FILENAME, "r") as f:
        lines = f.readlines()
    lines = filter(lambda x: x.startswith(TYPE), lines)
    decls = map(lambda x: x.rstrip().rstrip("{").rstrip() + ';', lines)
    print(*decls, sep="\n")
