/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32153356 & 32181178
*	    Student name : Lee Young Je(YJ) & Kim Tae Yun(TY)
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
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

void Init1(PROCESS* p) // for FIFO, RR, MLFQ
{
	p[0].Pid='A';
	p[0].Arrive_time=0;
	p[0].Service_time=3;
	p[0].Remain_time=p[0].Service_time;
	p[0].Work_time=0;
	p[0].Finish=false;
	p[0].check_first_insert=0;
	p[1].Pid='B';
	p[1].Arrive_time=2;
	p[1].Service_time=6;
	p[1].Remain_time=p[1].Service_time;
	p[1].Work_time=0;
	p[1].Finish=false;
	p[1].check_first_insert=0;
	p[2].Pid='C';
	p[2].Arrive_time=4;
	p[2].Service_time=4;
	p[2].Remain_time=p[2].Service_time;
	p[2].Work_time=0;
	p[2].Finish=false;
	p[2].check_first_insert=0;
	p[3].Pid='D';
	p[3].Arrive_time=6;
	p[3].Service_time=5;
	p[3].Remain_time=p[3].Service_time;
	p[3].Work_time=0;
	p[3].Finish=false;
	p[3].check_first_insert=0;
	p[4].Pid='E';
	p[4].Arrive_time=8;
	p[4].Service_time=2;
	p[4].Remain_time=p[4].Service_time;
	p[4].Work_time=0;
	p[4].Finish=false;
	p[4].check_first_insert=0;
	for(int i=0;i<5;i++)
	{
		printf("process %c's Arrive time:%d, Service time:%d\n",p[i].Pid,p[i].Arrive_time,p[i].Service_time);
	}
}

void Init2(PROCESS* p) // for FIFO, RR, MLFQ
{
	p[0].Pid='A';
	p[0].Arrive_time=0;
	p[0].Service_time=2;
	p[0].Remain_time=p[0].Service_time;
	p[0].Work_time=0;
	p[0].Finish=false;
	p[0].check_first_insert=0;
	p[1].Pid='B';
	p[1].Arrive_time=4;
	p[1].Service_time=6;
	p[1].Remain_time=p[1].Service_time;
	p[1].Work_time=0;
	p[1].Finish=false;
	p[1].check_first_insert=0;
	p[2].Pid='C';
	p[2].Arrive_time=1;
	p[2].Service_time=3;
	p[2].Remain_time=p[2].Service_time;
	p[2].Work_time=0;
	p[2].Finish=false;
	p[2].check_first_insert=0;
	p[3].Pid='D';
	p[3].Arrive_time=9;
	p[3].Service_time=3;
	p[3].Remain_time=p[3].Service_time;
	p[3].Work_time=0;
	p[3].Finish=false;
	p[3].check_first_insert=0;
	p[4].Pid='E';
	p[4].Arrive_time=5;
	p[4].Service_time=5;
	p[4].Remain_time=p[4].Service_time;
	p[4].Work_time=0;
	p[4].Finish=false;
	p[4].check_first_insert=0;
	for(int i=0;i<5;i++)
	{
		printf("process %c's Arrive time:%d, Service time:%d\n",p[i].Pid,p[i].Arrive_time,p[i].Service_time);
	}
}

void InitStride1(PROCESS* p) // for Stride
{
	p[0].Pid='A';
	p[0].Pass_value=0;
	p[0].Ticket_value=100;
	p[0].Stride_value=(float)(1)/(p[0].Ticket_value);
	p[1].Pid='B';
	p[1].Pass_value=0;
	p[1].Ticket_value=50;
	p[1].Stride_value=(float)(1)/(p[1].Ticket_value);
	p[2].Pid='C';
	p[2].Pass_value=0;
	p[2].Ticket_value=250;
	p[2].Stride_value=(float)(1)/(p[2].Ticket_value);
	for(int i=0;i<3;i++)
	{
		printf("process %c's Ticket:%d\n",p[i].Pid,p[i].Ticket_value);
	}
}

void InitStride2(PROCESS* p) // for Stride
{
	p[0].Pid='A';
	p[0].Pass_value=0;
	p[0].Ticket_value=200;
	p[0].Stride_value=(float)(1)/(p[0].Ticket_value);
	p[1].Pid='B';
	p[1].Pass_value=0;
	p[1].Ticket_value=100;
	p[1].Stride_value=(float)(1)/(p[1].Ticket_value);
	p[2].Pid='C';
	p[2].Pass_value=0;
	p[2].Ticket_value=50;
	p[2].Stride_value=(float)(1)/(p[2].Ticket_value);
	for(int i=0;i<3;i++)
	{
		printf("process %c's Ticket:%d\n",p[i].Pid,p[i].Ticket_value);
	}
}

int TotalTime(PROCESS* p) // for FIFO, RR, MLFQ
{
	int Total_time=0;
	for(int i=0;i<5;i++)
	{
		Total_time+=p[i].Service_time;
	}
	return Total_time;
}

int CM(PROCESS* p) // for Stride
{
	int CM_value=1;
	for(int i=0;i<3;i++)
	{
		CM_value*=p[i].Ticket_value;
	}
	return CM_value;
}

void FIFO(PROCESS* p) // by YJ
{
	int time=0;
	int min;
	int min_index;
	int total_time=TotalTime(p);
	int **matrix=(int**)malloc(sizeof(int*)*5);
	for(int i=0;i<5;i++)
	{
		matrix[i]=(int*)malloc(sizeof(int)*total_time);
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			matrix[i][j]=0;
		}
	}
	for(int i=0;i<5;i++)
	{
		min=total_time;
		min_index=i;
		if(p[i].Finish==false)                      //processlist에 있는 실행된 process가 종료 되지 않았을때 
		{
			min=p[i].Arrive_time;
		}
		for(int j=0;j<5;j++)                       // 모든 processs  
		{
			if(i!=j)
			{
				if(min>p[j].Arrive_time&&p[j].Finish==false)
				{
					min=p[j].Arrive_time;
					min_index=j;
				}
			}
		}
		for(int j=p[min_index].Service_time;p[min_index].Remain_time>0;j--)    //실행시간이 모두 소요 될 동안 for문 반복
		{
			p[min_index].Finish=true;
			p[min_index].Remain_time--;
			matrix[min_index][time]=1;
			time++;
		}
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			if(matrix[i][j]==1)
			{
				printf("■ ");
			}
			else
			{
				printf("□ ");
			}
		}
		printf("\n");
	}
	for(int i=0;i<5;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void RR(PROCESS* p,int quantum) // by TY
{
	int time=0;
	int total_time=TotalTime(p);
	int queue_size=total_time+(total_time/quantum);
	int front=0;
	int rear=0;
	int fail;
	bool flag=false;
	int *queue=(int*)malloc(sizeof(int)*queue_size);
	int **matrix=(int**)malloc(sizeof(int*)*5);
	for(int i=0;i<5;i++)
	{
		matrix[i]=(int*)malloc(sizeof(int)*total_time);
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			matrix[i][j]=0;
		}
	}
	while(1)
	{
		fail=0;
		for(int i=0;i<5;i++)
		{
			if(p[i].Arrive_time==time)
			{
				queue[rear]=i;
				rear++;
				flag=true;
				break;
			}
			else
			{
				fail++;
				if(fail==5)
				{
					time++;
				}
			}
		}
		if(flag==true)
		{
			break;
		}
	}
	flag=false;
	while(1)
	{
		for(;;)
		{
			if(front<rear)
			{
				if(p[queue[front]].Remain_time<=quantum)
				{
					for(int j=p[queue[front]].Remain_time;j>0;j--)
					{
						matrix[queue[front]][time]=1;
						time++;
						for(int l=0;l<5;l++)
						{
							if(p[l].Arrive_time==time&&p[l].Finish==false)
							{
								queue[rear]=l;
								rear++;
							}
						}
					}
					p[queue[front]].Remain_time=0;
					p[queue[front]].Finish=true;
				}
				else
				{
					for(int j=0;j<quantum;j++)
					{
						matrix[queue[front]][time]=1;
						time++;
						for(int k=0;k<5;k++)
						{
							if(p[k].Arrive_time==time&&p[k].Finish==false)
							{
								queue[rear]=k;
								rear++;
							}
						}
						p[queue[front]].Remain_time--;
					}
				}
				if(p[queue[front]].Finish==false)
				{
					queue[rear]=queue[front];
					rear++;
				}
				front++;
			}
			if(time>=total_time)
			{
				flag=true;
				break;
			}
		}
		if(flag==true)
		{
			break;
		}
	}
	printf("Quantum:%d\n",quantum);
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			if(matrix[i][j]==1)
			{
				printf("■ ");
			}
			else
			{
				printf("□ ");
			}
		}
		printf("\n");
	}
	free(queue);
	for(int i=0;i<5;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void MLFQ(PROCESS* p,int case) // by YJ
{
	PQUEUE myQueue[4];
	int time=0;		
	int total_time=TotalTime(p);
	int **matrix=(int**)malloc(sizeof(int*)*5);
	int timequantum_1[4]={1,1,1,1};                //time_quantum case1
	int timequantum_2[4] = { 1,2,4,8 };            //time_quantum case2
	int num = 0;        //큐 안에 두 개 이상의 큐가 있는 지 확인할때 사용

	for(int i=0;i<5;i++)
	{
		matrix[i]=(int*)malloc(sizeof(int)*total_time);
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			matrix[i][j]=0;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(case==1)                //두 개의 time_quantum case가 존재하기 때문
		{
			myQueue[i].Quantum=timequantum_1[i];
		}
		else
		{
			myQueue[i].Quantum=timequantum_2[i];
		}
		myQueue[i].Front=0;
		myQueue[i].Rear=0;
	}
	
	while(1)          
	{
		for (int i = 0; i < 5; i++)                     
		{
			if (time >= p[i].Arrive_time)
			{
				if (p[i].check_first_insert ==0) {
					myQueue[0].List_index[myQueue[0].Rear] = i;
					myQueue[0].Rear++;
					num++;
					p[i].check_first_insert = 1;
				}				
			}			
		}

		int i = 0;

		while(1){   
			if (myQueue[i].Front < myQueue[i].Rear)          //queue에 process가 들어있음을 뜻함
			{
				if (num == 1) {        //총 한개의 process가 있을때 ==> 이때는 다음 큐로 내려가지 않음
					if (p[myQueue[i].List_index[myQueue[i].Front]].Remain_time)   //remain_time 이 남아 있을 때 실행
					{
						for (int k = 0; k < myQueue[i].Quantum; k++) {       //tim,e quantum만큼 반복

							p[myQueue[i].List_index[myQueue[i].Front]].Work_time++;
							p[myQueue[i].List_index[myQueue[i].Front]].Remain_time--;

							matrix[myQueue[i].List_index[myQueue[i].Front]][time] = 1;
							time++;
						}
							break;
					}
					else {                    //Remain_time을 모두 소비했을 경우  큐에서 제거
							myQueue[i].Front++;
							num--;
					}
				}

				else {     //두개 이상의 process 존재
					if (p[myQueue[i].List_index[myQueue[i].Front]].Work_time >= myQueue[i].Quantum) {    //실행된 시간이 time quantum보다 같거나 클 경우 다음큐로 이동 시킴
							int temp_index = myQueue[i].List_index[myQueue[i].Front];       
							if (i != 3)            //제일 최하 우선순위 큐가 아닐 경우(아래 큐로 바꾸기 위해)
							{
								myQueue[i + 1].List_index[myQueue[i + 1].Rear] = temp_index;
								p[myQueue[i].List_index[myQueue[i].Front]].Work_time = 0;     //큐에서 실행된 시간 초기화
								myQueue[i].Front++;
								myQueue[i + 1].Rear++;
							}  
							else{            //제일 최하 우선순위 큐 일 경우 ==> 이동 할 큐가 없어서 
								
									myQueue[i].List_index[myQueue[i].Rear] = temp_index;
									p[myQueue[i].List_index[myQueue[i].Front]].Work_time = 0;     //큐에서 실행된 시간 초기화
									myQueue[i].Front++;
									myQueue[i].Rear++;
								
							}

							if (myQueue[i].Front < myQueue[i].Rear)  //동일 큐에 다른 프로세스가 존재할 경우  
							{
								for (int k = 0; k < myQueue[i].Quantum; k++) {
									p[myQueue[i].List_index[myQueue[i].Front]].Work_time++;                   
									p[myQueue[i].List_index[myQueue[i].Front]].Remain_time--;
									matrix[myQueue[i].List_index[myQueue[i].Front]][time] = 1;
									time++;

									if (p[myQueue[i].List_index[myQueue[i].Front]].Remain_time == 0)    //실행 시간이 다 되었을 경우
									{
										myQueue[i].Front++;
										num--;
										break;
									}
									
								}
								break;
							}
							
					}

					else            //Work_time이 time_quantum보다 작을 때   ==> 즉, 다음 큐로 내려가지 않고 큐에 그대로 남아있음
					{
						
						if (p[myQueue[i].List_index[myQueue[i].Front]].Remain_time>0) {          //실행 시간이 남아있을 경우
							for (int k = 0; k < myQueue[i].Quantum; k++) {
								p[myQueue[i].List_index[myQueue[i].Front]].Work_time++;                
								p[myQueue[i].List_index[myQueue[i].Front]].Remain_time--;
								matrix[myQueue[i].List_index[myQueue[i].Front]][time] = 1;
								time++;     

								if (p[myQueue[i].List_index[myQueue[i].Front]].Remain_time == 0) //실행시간이 남아 있지 않을 경우
								{
									myQueue[i].Front++;
									num--;
									break;
								}																
							}
							break;
						}

						
					}
				}
			}
			i++;
			if (i == 4)                 //모든 큐 검색 완료
				break;
		} 		
	
		if(time>=total_time)             //총 실행시간 넘을 경우 종료
		{
			break;
		}
		
	}
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<total_time;j++)
		{
			if(matrix[i][j]==1)
			{
				printf("■ ");
			}
			else
			{
				printf("□ ");
			}
		}
		printf("\n");
	}
	for(int i=0;i<5;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void Stride(PROCESS* p)
{
	int cm_value=CM(p);
	int min_value=0;
	int index;
	int count=0;
	bool flag=false;
	for(int i=0;i<3;i++)
	{
		p[i].Stride_value*=cm_value;
		min_value+=p[i].Stride_value;
	}
	for(;;)
	{
		int min=min_value;
		count=0;
		for(int i=0;i<3;i++)
		{
			if(p[i].Pass_value==0)
			{
				count++;
			}
			if(p[i].Pass_value<=min)
			{
				min=p[i].Pass_value;
				index=i;
			}
		}
		if(count>1)
		{
			for(int i=0;i<3;i++)
			{
				if(p[i].Pass_value==0)
				{
					index=i;
					break;
				}
			}
		}
		printf("process %c executed, pass value %d \n",p[index].Pid,p[index].Pass_value);
		p[index].Pass_value+=p[index].Stride_value;
		count=0;
		for(int i=0;i<2;i++)
		{
			if(p[i].Pass_value==p[i+1].Pass_value)
			{
				count++;
			}
			if(count==2)
			{
				flag=true;
				break;				
			}
		}
		if(flag==true)
		{
			break;
		}
	}
}


