/*
SIMPLE ASSEMBLY LANGUAGE v1
winxos 2016-11-13
*/
#define _CRT_SECURE_NO_WARNINGS
//up for cancel visual studio 15' warnings (C4996: unsafe scanf).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#define MAX_MEM 100
int MEM[MAX_MEM] = {0}, ADDER = 0; //ONLY MAX_MEN MEMORY, ONE REGISTER ADDER

enum
{
    INPUT = 10, PRINT, LOAD = 20, STORE, SET, ADD = 30, SUB, MUL, DIV, MOD,
    JMP = 40, JMPN, JMPZ, HALT = -1
};

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
    puts("SUPPORTED COMMAND:");
    puts("ls\t\t\t[list SML source codes]");
    puts("help | ? \t\t[help]");
    puts("load name.sml\t\t[load and run source code]");
    puts("input\t\t\t[open code input mode]");
    puts("exit\t\t\t[exit program]");
    puts("dump\t\t\t[show memories]");
    puts("\n");
}

void console()
{
    while (1)
    {
        printf("SML >");
        char buf[80] = {0};
        fgets(buf, 80, stdin);
        buf[strlen(buf) - 1] = 0;//remove \n
        char dst[10][80] = {0};
        int len = split(dst, buf, " ");
        if (0 == strcmp(dst[0], "ls"))
        {
            char path[2] = ".";
            if (-1 == dir(path, "*.sal"))
            {
                puts("NO .sal FILE FOUND ON CURRENT DIRECTORY.");
            }
        }
        else if (0 == strcmp(dst[0], "help") || 0 == strcmp(dst[0], "?"))
        {
            help();
        }
        else if (0 == strcmp(dst[0], "exit"))
        {
            puts("See you soon.");
            system("ping -n 3 127.1>nul");
            exit(0);
        }
        fflush(stdin);
        rewind(stdin); //
    }
}

int
main()
{
    printf("\tSimple Assembly Language Simulator v1.0\n");
    printf("\t\t\twinxos 2016/11/13\n\n\n");
    help();
    console();
    return 0;
}
