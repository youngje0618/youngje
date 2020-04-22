/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32153356 & 32181178
*	    Student name : Lee Young Je(YJ) & Kim Tae Yun(TY)
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include <stdbool.h>
#include "lab1_sched_types.h"

/*
 * you need to implement scheduler simlator test code.
 *
 */

int main(int argc, char *argv[]){
	PROCESS *p1=NULL;
	PROCESS *p2=NULL;
	PROCESS *p3=NULL;
	PROCESS *p4=NULL;
	PROCESS *ps1=NULL;
	PROCESS *ps2=NULL;
	int choice;
	bool flag=false;
	for(;;)
	{
		printf(">>Choose the scheduling algorithm.(FIFO:1, RR:2, MLFQ:3, Stride:4, Exit:Others)\n");
		printf("Answer: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
					printf(">FIFO-Result 1\n");
					p1=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p1);
					FIFO(p1);
					
					printf(">FIFO-Result 2\n");
					p2=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init2(p2);
					FIFO(p2);
					
					free(p1);
					free(p2);
					break;
			case 2:
					printf(">RR-Result 1-Time Quantum 1\n");
					p1=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p1);
					RR(p1,1);
					
					printf(">RR-Result 1-Time Quantum 4\n");
					p2=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p2);
					RR(p2,4);
					
					printf(">RR-Result 2-Time Quantum 1\n");
					p3=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p3);
					RR(p3,1);
					
					printf(">RR-Result 2-Time Quantum 2\n");
					p4=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p4);
					RR(p4,2);
					
					free(p1);
					free(p2);
					free(p3);
					free(p4);
					break;
			case 3:
					printf(">MLFQ-Result 1-Time Quantum 1\n");
					p1=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p1);
					MLFQ(p1,1);
					
					printf(">MLFQ-Result 1-Time Quantum 2^\n");
					p2=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init1(p2);
					MLFQ(p2,2);
					
					printf(">MLFQ-Result 2-Time Quantum 1\n");
					p3=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init2(p3);
					MLFQ(p3,1);
					
					printf(">MLFQ-Result 2-Time Quantum 2^\n");
					p4=(PROCESS*)malloc(sizeof(PROCESS)*5);
					Init2(p4);
					MLFQ(p4,2);
					
					free(p1);
					free(p2);
					free(p3);
					free(p4);
					break;
			case 4:
					printf(">Stride-Result 1\n");
					ps1=(PROCESS*)malloc(sizeof(PROCESS)*3);
					InitStride1(ps1);
					Stride(ps1);
					
					printf(">Stride-Result 2\n");
					ps2=(PROCESS*)malloc(sizeof(PROCESS)*3);
					InitStride2(ps2);
					Stride(ps2);
					
					free(ps1);
					free(ps2);
					break;
			default:
					flag=true;
					printf("Exit-Bye!\n");
					break;
		}
		if(flag==true)
		{
			break;
		}
	}
}
