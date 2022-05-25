#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define NUM_Year '0'
#define Char_Year '1'

//All functions
WorkerList* addWorker(WorkerList* head, Worker* w);
Worker* CreateWorker(yearT);
void PrintWorker(char type, const Worker* infoW);


//A
typedef struct
{
	unsigned long  id;
	char* name;
	unsigned long salary;

	union Year
	{
		unsigned long yearN;
		char yearc[6];
	} year;

}Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
}WorkerList;

//B
Worker* CreateWorker(yearT)
{
	char* tmp[30];//temporary for allocation name string
	Worker* nw = (Worker*)malloc(sizeof(Worker));//// Creating new worker information for the new node
	if (nw==NULL)//cheak allocation
	{
		printf("Error: unavailable memory!!");
		exit(1);
	}
	printf("enter worker id: ");
	scanf_s("%ld\n", &(nw->id));
	printf("enter worker salary: ");
	scanf_s("%ld\n", &(nw->salary));
	printf("enter worker name: ");
	gets(tmp);
	nw->name = (char*)calloc(strlen(tmp) + 1, sizeof(char));
	if (nw->name == NULL)
	{
		printf("Error: unavailable memory!!\n\n");
		exit(1);
	}
	trcpy(nw->name,tmp);

	printf("enter the starting Work year: ");
	fseek(stdin, 0, SEEK_END);
	switch (yearT)
	{
	case Char_Year://����� ��� ����
		do
		{
			fseek(stdin, 0, SEEK_END);
			scanf_s("%s", &(nw->year.yearc));
			if ((nw->year.yearc > 128) || (nw->year.yearc < 255))puts("Value should be in hebrew only");//��� �� ����
		} while ((nw->year.yearc > 128) || (nw->year.yearc < 255));
		break;
	case NUM_Year:
		do
		{
			scanf_s("%ld", &(nw->year.yearN));
			if ((nw->year.yearN > 9999) || (nw->year.yearN < 1000))puts("Value should be in right numbers!\n");

		} while ((nw->year.yearN > 9999) || (nw->year.yearN < 1000));//������ �� ���� �� ����� ���� �����
		break;
	}
	return nw;
}

void PrintWorker(char type, const Worker* infoW)
{
	printf("Id: %ld\n", infoW->id);
	printf("salary: %ld\n", infoW->salary);
	printf("name: %s\n", infoW->name);
	switch (type)
	{
	case Char_Year:
		printf("year: %s\n", &(infoW->year.yearc));//����� ����� ����� ����� ����� ����,�����
		break;
	case NUM_Year:
		printf("year: %ld\n", infoW->year.yearN);//����� ����� ����� ����� ����� ����� ������
		break;
	default:
		printf("Worng Format!! ");
		break;
	}
}

//C
WorkerList* addWorker(WorkerList* head, Worker* w)
{
	if(head == NULL)//if list is empty
	{
		WorkerList* newItem = (WorkerList*)malloc(sizeof(WorkerList));
		if (newItem == NULL)
		{
			printf("Error: unavailable memory!!\n\n");
			exit(1);
		}
		head = newItem;//points to newitem
		newItem->data = w;//inser the worker data
		newItem->next = NULL;//last item points to null

		printf("--------------------- END OF OPTION -----------------------\n\n");
		return head;
	}

	if (head != NULL)//case not emptylist
	{
		WorkerList* tmp = (WorkerList*)malloc(sizeof(WorkerList));
		if (tmp == NULL)
		{
			printf("Error: unavailable memory!!\n\n");
			exit(1);
		}
		
		tmp->next = NULL;
		tmp->data = w;
		
		WorkerList* ptr = head;

		while (ptr->next) // Searching the last 
			ptr = ptr->next;
		ptr->next = tmp;  // Define the new as last to become sort list workers

		printf("--------------------- END OF OPTION -----------------------\n\n");
		return head;
	}
}

