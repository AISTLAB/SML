/*
SIMPLE MACHINE LANGUAGE v2
Change:
	Refactor the code
	Optimize showMemory function
winxos 2016-11-08
*/
#define _CRT_SECURE_NO_WARNINGS
//¡ü for cancel visual studio 15' warnings (C4996: unsafe scanf).
#include <stdio.h>
#include <string.h>

#define MAX_MEM 100
int mem[MAX_MEM] = { 0 }, ADDER = 0; //ONLY MAX_MEN MEMORIES , ONE REGISTER ADDER

enum OPERATE { INPUT = 10, PRINT, LOAD = 20, STORE, ADD = 30, SUB, MUL, DIV, MOD, JMP = 40, JMPN, JMPZ, HALT = -1 } op;

#define COLS 10
#define TITLE_FORMAT "%6X"
#define DATA_FORMAT "%6d"
#define COL_HEADER_FORMAT "\n%3d"
void showMemory() //Pretty Show Memory For Debugging 
{
	int i;
	printf("\nMEMORY:\n%3s", "");
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
		printf(DATA_FORMAT, mem[i]);
	}
	puts("\n");
}
void runSML() //
{
	int addr = 0, pt = 0;
	while (pt < MAX_MEM)
	{
		op = (enum OPERATE)(mem[pt] / 100);	//xxbb
		addr = mem[pt] % 100;
		pt++;
		switch (op)
		{
		case INPUT:printf("INPUT:"); scanf("%d", &mem[addr]); break;
		case PRINT:printf("%d ", mem[addr]); break;
		case LOAD:ADDER = mem[addr]; break;
		case STORE:mem[addr] = ADDER; break;
		case ADD:ADDER += mem[addr]; break;
		case SUB:ADDER -= mem[addr]; break;
		case MUL:ADDER *= mem[addr]; break;
		case DIV:ADDER /= mem[addr]; break;
		case JMP:pt = addr; break;
		case JMPN:ADDER < 0 ? pt = addr : 0; break;
		case JMPZ:ADDER == 0 ? pt = addr : 0; break;
		case HALT:printf("\nHALT\n"); return;
		default:break;
		}
	}
}
void inputCode()
{
	printf("\nEnter -1 to end input.\n\n");
	int ct = 0, li = 0;
	memset(mem, 0, sizeof(int)*MAX_MEM);
	while (ct != -1)
	{
		printf("%02d ? ", li);
		scanf("%d", &ct);
		mem[li++] = ct;
	}
}
int main()
{	//2036,2137,0000,2035,3137,4133,2037,3036,2137,3136,2138,0000,2038,3136,3136,4129,2037,3338,3238,3137,4222,4024,0000,4031,0000,2038,3136,2138,4011,0000,1137,0000,4002,0000,4300,99,1,0,0,-1
	printf("\t\tSimpletron simulator.\n\n");
	printf("\t\t\tVersion 2.0\n\n");
	printf("\t\t\t\twinxos 2016/11/08\n\n\n");
	while (1)
	{
		inputCode();
		runSML();
		showMemory();
	}
	return 0;
}
