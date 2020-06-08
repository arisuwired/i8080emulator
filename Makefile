# gcc -DDEBUG -o emu _8080emulator.c translate_inst.c instructions.c interrupts.c -Wall -ggdb _8080state.c -DCPUDIAG -DSKIP_SPECIAL

OBJS = _8080emulator.c translate_inst.c instructions.c interrupts.c _8080state.c parts.c timer.c
OBJ_NAME = emu

CC = gcc
COMPILER_FLAGS = -Wall -ggdb -lSDL2

CPUDIAG_FLAGS = -DCPUDIAG -DSKIP_SPECIAL -DDEBUG

all: $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) $(COMPILER_FLAGS) #$(CPUDIAG_FLAGS)
