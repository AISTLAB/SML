/*
SIMPLE MACHINE LANGUAGE v4
This version realize stack segment.
winxos 2016-11-14
*/
#define _CRT_SECURE_NO_WARNINGS
//up for cancel visual studio 15' warnings (C4996: unsafe scanf).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#define MAX_MEM 100
int MEM[MAX_MEM] = {0}, ADDER = 0; //ONLY MAX_MEN MEMORY, ONE REGISTER ADDER
#define MAX_STACK 30
int STACK[MAX_STACK] = {0};
enum
{
    INPUT = 10, PRINT, LOAD = 20, STORE, SET,
    ADD = 30, SUB, MUL, DIV, MOD, INC, DEC, NEG,
    JMP = 40, JMPN, JMPZ,
    AND = 50, OR, XOR,
    PUSH = 60, POP,
    HALT = -1
};

#define COLS 10
#define TITLE_FORMAT "%6X"
#define DATA_FORMAT "%6d"
#define COL_HEADER_FORMAT "\n%3d"

void dump() //Pretty Show Memory For Debugging
{
    int i;
    printf("\nADDER:%4d, MEMORY:\n%3s", ADDER, "");
    for (i = 0; i < COLS; i++)
    {
        printf(TITLE_FORMAT, i);
    }
    for (i = 0; i < MAX_MEM; i++)
    {
        if (i % COLS == 0)
        {
            printf(COL_HEADER_FORMAT, i / COLS);
        }
        printf(DATA_FORMAT, MEM[i]);
    }
    puts("\n");
}

void runSML() //
{
    int operand = 0, pcode = 0, pstack = 0;
    while (pcode < MAX_MEM)
    {
        int op = MEM[pcode] / 100;    //xxbb
        operand = MEM[pcode] % 100;
        switch (op)
        {
        case INPUT:printf("INPUT:");
            scanf("%d", &MEM[operand]);
            break;
        case PRINT:printf("%d ", MEM[operand]);
            break;
        case LOAD:ADDER = MEM[operand];
            break;
        case STORE:MEM[operand] = ADDER;
            break;
        case SET:ADDER = operand;
            break;
        case ADD:ADDER += MEM[operand];
            break;
        case SUB:ADDER -= MEM[operand];
            break;
        case MUL:ADDER *= MEM[operand];
            break;
        case DIV:ADDER /= MEM[operand];
            break;
        case MOD:ADDER %= MEM[operand];
            break;
        case INC:ADDER++;
            break;
        case DEC:ADDER--;
            break;
        case NEG:ADDER = -ADDER;
            break;
        case JMP:pcode = operand;
            break;
        case JMPN:ADDER < 0 ? pcode = operand : 0;
            break;
        case JMPZ:ADDER == 0 ? pcode = operand : 0;
            break;
        case AND:ADDER = ADDER & MEM[operand];
            break;
        case OR:ADDER = ADDER | MEM[operand];
            break;
        case XOR:ADDER = ADDER ^ MEM[operand];
            break;
        case PUSH:pstack < MAX_STACK ? STACK[pstack++] = ADDER : puts("STACK OVERFLOW.");
            break;
        case POP:pstack > 0 ? ADDER = STACK[--pstack] : puts("STACK EMPTY.");
            break;
        case HALT: pcode = MAX_MEM;
            break;
        default:break;
        }
        pcode++;
    }
    puts("HALT.");
    dump();
}

int input_code()
{
    printf("\nEnter -1 to end input.\n\n");
    int ct = 0, li = 0;
    memset(MEM, 0, sizeof(int) * MAX_MEM);
    while (ct != -1)
    {
        printf("%02d ? ", li);
        scanf("%d", &ct);
        MEM[li++] = ct;
    }
    return li - 1;
}

int dir(char path[], char filter[])//list files in path with filter
{
    struct _finddata_t fi;
    long handle;
    if ((handle = _findfirst(strcat(strcat(path, "\\"), filter), &fi)) == -1L)
    {
        return -1;
    }
    do
    {
        if (!(fi.attrib & _A_SUBDIR))//not directory
        {
            printf("%s\n", fi.name);
        }
    } while (_findnext(handle, &fi) == 0);
    _findclose(handle);
    return 0;
}

int split(char dst[][80], char *str, const char *spl)//for single line chars split to words
{
    int n = 0;
    char *result = NULL;
    result = strtok(str, spl);
    while (result != NULL)
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }
    return n;
}

int load_file(char file[80])//load .sml file to MEM
{
    FILE *fi;
    int i = 0;
    if (fi = fopen(file, "r"))
    {
        while (fscanf(fi, "%d", &MEM[i++]) != EOF);
    }
    else
    {
        printf("%s NOT FOUND.", file);
        return -1;
    }
    return 0;
}

void help()
{
    printf("THIS MACHINE HAVE %d(int)MEMORY, %d(int)STACK\n",MAX_MEM,MAX_STACK);
    puts("INSTRUCTION IS 4 DECIMAL DIGITS, FORMAT: AABB");
    puts("AA IS OPERATOR, BB IS OPERAND");
    puts("ONLY HAVE ONE REGISTER\n");
    puts("INSTRUCTIONS:");
    puts("\tINPUT:10\tPRINT:11\tLOAD:20\tSTORE:21\tSET:22");
    puts("\tADD:30\tSUB:31\tMUL:32\tDIV:33\tMOD:34\tINC:35\tDEC:36\tNEG:37");
    puts("\tJMP:40\tJMPN:41\tJMPZ:42");
    puts("\tAND:50\tOR:51\tXOR:52");
    puts("\tPUSH:60\tPOP:61");
    puts("\tHALT:-1\n");
    puts("THIS SHELL SUPPORTED COMMAND:");
    puts("ls\t\t\t[list SML source codes]");
    puts("help | ? \t\t[help]");
    puts("load name.sml\t\t[load and run source code]");
    puts("input\t\t\t[open code input mode]");
    puts("exit\t\t\t[exit program]");
    puts("dump\t\t\t[show memories]");
}

void console()
{
    char buf[80] = {0};
    while (1)
    {
        printf("SML >");
        fgets(buf, 80, stdin); //gets is not safe, attention: fgets include \n
        buf[strlen(buf) - 1] = 0;//remove \n
        char dst[10][80] = {0};
        split(dst, buf, " ");
        if (0 == strcmp(dst[0], "ls"))
        {
            char path[2] = ".";
            if (-1 == dir(path, "*.sml"))
            {
                puts("NO .sml FILE FOUND ON CURRENT DIRECTORY.");
            }
        }
        else if (0 == strcmp(dst[0], "help") || 0 == strcmp(dst[0], "?"))
        {
            help();
        }
        else if (0 == strcmp(dst[0], "load"))
        {
            if (!load_file(dst[1]))
                runSML();
        }
        else if (0 == strcmp(dst[0], "exit"))
        {
            puts("See you soon.");
            system("ping -n 3 127.1>nul");
            exit(0);
        }
        else if (0 == strcmp(dst[0], "input"))
        {
            if (input_code() > 0)
                runSML();
        }
        else if (0 == strcmp(dst[0], "dump"))
        {
            dump();
        }
        fflush(stdin);
        rewind(stdin); //
    }
}

int main()
{
    puts("\tSimple Machine Language Simulator v4.0");
    puts("\t\t\twinxos 2016/11/14\n");
    help();
    console();
    return 0;
}
