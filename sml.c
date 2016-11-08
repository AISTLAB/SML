/*
SML(simple machine language) simulator Simpletron DEMO.
Language Format: xxbb
The Lower 2 digits bb is memory address.
The Higher 2 digits xx is the operater.
Operators: READ, WRITE, LOAD, STORE, ADD, SUB, MUL, DIV, MOD, JMP, JMPN, JMPE, HALT
winxos 2012-11-04 
*/
#include <stdio.h>
#include <string.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define MUL 32
#define DIV 33
#define MOD 34
#define JMP 40
#define JMPN 41
#define JMPZ 42
#define HALT 43

#define MAX_MEM 100
int mem[MAX_MEM]={0},ADDER=0; //ONLY ONE REGISTER ADDER
void showMemory() //Pretty Show Memory For Debugging 
{         
	int i;
	printf("\nMEMORY:\n   ");
	for(i=0;i<10;i++) printf("%6d",i); 
	printf("\n  0");
	for(i=0;i<MAX_MEM;i++)
	{
		printf("%6d",mem[i]);
		if(i%10==9 && i!=MAX_MEM-1) printf("\n%3d",1+i/10);
	}	
	printf("\n");
}
void loadCode(int c[])
{
	int len=0;
	while(c[len++]!=-1);
	memset(mem,0,sizeof(int)*MAX_MEM);
	memcpy(mem,c,len*sizeof(int));	
}
void runSML() //
{
	int op=0,addr=0,*pt=mem;
	while(1)
	{
		op=*pt/100;	//xxbb
		addr=*pt%100;
		pt++;
		switch(op)
		{
			case READ:printf("input:");scanf("%d",&mem[addr]);break;
			case WRITE:printf("%d ",mem[addr]);break;
			case LOAD:ADDER=mem[addr];break;
			case STORE:mem[addr]=ADDER;break;
			case ADD:ADDER+=mem[addr];break;
			case SUB:ADDER-=mem[addr];break;
			case MUL:ADDER*=mem[addr];break;
			case DIV:ADDER/=mem[addr];break;
			case JMP:pt=mem+addr;break;
			case JMPN:ADDER<0?pt=mem+addr:0;break;
			case JMPZ:ADDER==0?pt=mem+addr:0;break;
			case HALT:printf("\nhalt");return;
			default:break;
		}
	}
}
int* inputCode()
{
	int buf[MAX_MEM];
	printf("Enter -1 to end input.\n\n");
	int ct=0,li=0;
	while(ct!=-1)
	{
		printf("%02d ? ",li);
		scanf("%d",&ct);
		buf[li++]=ct;
	}
	return buf;
}
int main()
{	//2036,2137,0000,2035,3137,4133,2037,3036,2137,3136,2138,0000,2038,3136,3136,4129,2037,3338,3238,3137,4222,4024,0000,4031,0000,2038,3136,2138,4011,0000,1137,0000,4002,0000,4300,99,1,0,0,-1
	printf("\t\tSimpletron simulator.\n\n");
	printf("\t\t\tVersion 1.0\n\n");
	printf("\t\t\t\twinxos 2012/11/05\n\n\n");
	while(1)
	{
		loadCode(inputCode()); //calculate the code length
		runSML();	
		showMemory();	
	}
	return 0;
} //end
