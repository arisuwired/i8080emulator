#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "_8080emulator.h"

#define FEOF -1
#define FERROR -2

int main(int argc, char *argv[]) {
    // length of a single instruction in bytes. can be between 1 and 3
    unsigned inst_len;
    // if no file specified use stdin
    FILE *fp = stdin;
    // where to begin reading the file
    size_t offset = 0;
    // how many bytes to read, if zero read to the end
    size_t length = 0;
    // verbose output
    bool verbose = false;
    // pointer to file content
    uint8_t *file;

    // buf for printing
    char line[1024];

    // helping variables
    size_t file_end;
    int file_length;

    // arguments processing
NEXT_ARG:
    while (--argc > 0) {
        if (*(++argv)[0] == '-') {
            while (*++argv[0]) {
                switch (*argv[0]) {
                case 'o':
                    if (isdigit(*++argv[0])) {
                        sscanf(argv[0], "%lu", &offset);
                    } else if (*argv[0] == '\0' && --argc > 0) {
                        if (sscanf(*++argv, "%lu", &offset) == 0) {
                            fprintf(stderr, "-o parameter is not a number\n");
                            exit(-1);
                        }
                    } else {
                        fprintf(stderr, "-o needs a number\n");
                        exit(-1);
                    }
                    goto NEXT_ARG;
                case 'l':
                    if (isdigit(*++argv[0])) {
                        sscanf(argv[0], "%lu", &length);
                    } else if (*argv[0] == '\0' && --argc > 0) {
                        if (sscanf(*++argv, "%lu", &length) == 0) {
                            fprintf(stderr, "-l parameter is not a number\n");
                            exit(-1);
                        }
                    } else {
                        fprintf(stderr, "-l needs a number\n");
                        exit(-1);
                    }
                    goto NEXT_ARG;
                case 'v':
                    verbose = true;
                    break;
                default:
                    fprintf(stderr, "bad argument: %s\n", argv[0]);
                    exit(-2);
                }
            }
        } else {
            fclose(fp);
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "couldn't open the %s file\n", *argv);
                exit(-3);
            }
        }
    }

    if (verbose) {
        printf("offset: 0x%lx\n", offset);
        printf("length: 0x%lx\n", length);
        printf("\n");
    }

    // file reading
    fseek(fp, 0L, SEEK_END);
    file_end = ftell(fp);
    fseek(fp, offset, SEEK_SET);
    if (length > 0)
        file_end = (file_end <= offset + length) ? file_end : offset + length;

    file_length = file_end - ftell(fp);
    if (file_length <= 0) {
        fprintf(stderr, "file is too short/offset address is too big\n");
        exit(-1);
    }
    file = (uint8_t *)malloc(file_length * sizeof(uint8_t));
    if (file == NULL) {
        fprintf(stderr, "couldn't allocate memory\n");
        exit(-1);
    }
    if (!fread(file, file_length, 1, fp)) {
        fprintf(stderr, "couldn't load the file\n");
    }
    // main loop for writing to line and printing
    for (size_t i = 0; i < file_length; i += inst_len) {
        inst_len = sprint_inst(file, i, line);
        printf("%s\n", line);
    }

    return 0;
}
