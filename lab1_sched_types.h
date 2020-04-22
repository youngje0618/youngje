/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32153356 & 32181178
*	    Student name : Lee Young Je(YJ) & Kim Tae Yun(TY)
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

#include <stdbool.h>

typedef struct process
{
	char Pid;
	int Arrive_time;
	int Service_time;
	int Remain_time;
	int Work_time;
	int Pass_value;
	int Ticket_value;
	float Stride_value;
	bool Finish;
	int check_first_insert;
}PROCESS;

typedef struct processQueueForMLFQ
{
	int Quantum;
	int Rear;
	int Front;
	int Priority;
	int List_index[5];
}PQUEUE;

void Init1(PROCESS* p); // for FIFO, RR, MLFQ

void Init2(PROCESS* p); // for FIFO, RR, MLFQ

void InitStride1(PROCESS* p); // for Stride

void InitStride2(PROCESS* p); // for Stride

int TotalTime(PROCESS* p); // for FIFO, RR, MLFQ

int CM(PROCESS* p); // for Stride

void FIFO(PROCESS* p); // by YJ

void RR(PROCESS* p,int quantum); // by TY

void MLFQ(PROCESS* p,int case); // by YJ

void Stride(PROCESS* p); // by TY

#endif /* LAB1_HEADER_H*/
