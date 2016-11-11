/*
SIMPLE MACHINE LANGUAGE v3
Change:
can load source file *.sml
each machine code per line
winxos 2016-11-11
*/
#define _CRT_SECURE_NO_WARNINGS
//up for cancel visual studio 15' warnings (C4996: unsafe scanf).
#include <stdio.h>
#include <string.h>
#include <io.h>

#define MAX_MEM 100
int MEM[MAX_MEM] = { 0 }, ADDER = 0; //ONLY MAX_MEN MEMORY, ONE REGISTER ADDER

enum { INPUT = 10, PRINT, LOAD = 20, STORE, ADD = 30, SUB, MUL, DIV, MOD, 
	JMP = 40, JMPN, JMPZ, HALT = -1 };

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
	int operand = 0, pt = 0;
	while (pt < MAX_MEM)
	{
		int op = (MEM[pt] / 100);	//xxbb
		operand = MEM[pt] % 100;
		switch (op)
		{
		case INPUT:printf("INPUT:"); scanf("%d", &MEM[operand]); break;
		case PRINT:printf("%d ", MEM[operand]); break;
		case LOAD:ADDER = MEM[operand]; break;
		case STORE:MEM[operand] = ADDER; break;
		case ADD:ADDER += MEM[operand]; break;
		case SUB:ADDER -= MEM[operand]; break;
		case MUL:ADDER *= MEM[operand]; break;
		case DIV:ADDER /= MEM[operand]; break;
		case JMP:pt = operand; break;
		case JMPN:ADDER < 0 ? pt = operand : 0; break;
		case JMPZ:ADDER == 0 ? pt = operand : 0; break;
		case HALT:printf("\nHALT\n"); pt = MAX_MEM; break;
		default:break;
		}
		pt++;
	}
	dump();
}
void input_code()
{
	printf("\nEnter -1 to end input.\n\n");
	int ct = 0, li = 0;
	memset(MEM, 0, sizeof(int)*MAX_MEM);
	while (ct != -1)
	{
		printf("%02d ? ", li);
		scanf("%d", &ct);
		MEM[li++] = ct;
	}
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
		if (!(fi.attrib&_A_SUBDIR))//not directory
		{
			printf("%s\n", fi.name);
		}
	} while (_findnext(handle, &fi) == 0);
	_findclose(handle);
	return 0;
}
int split(char dst[][80], char* str, const char* spl)//for single line chars split to words
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
void load_file(char file[80])//load .sml file to MEM
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
	}
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
	char path[2] = ".";
	while (1)
	{
		printf("SML >");
		char buf[80] = { 0 };
		gets_s(buf, 80);
		char dst[4][40] = { 0 };
		int len = split(dst, buf, " ");
		if (0 == strcmp(dst[0], "ls"))
		{
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
			load_file(dst[1]);
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
			input_code();
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
{	//2036,2137,0000,2035,3137,4133,2037,3036,2137,3136,2138,0000,2038,3136,3136,4129,2037,3338,3238,3137,4222,4024,0000,4031,0000,2038,3136,2138,4011,0000,1137,0000,4002,0000,4300,99,1,0,0,-1
	printf("\tSimple Machine Language Simulator v3.0\n");
	printf("\t\t\twinxos 2016/11/11\n\n\n");
	help();
	console();
	return 0;
}
