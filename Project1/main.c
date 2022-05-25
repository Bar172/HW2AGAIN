#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_Year '0'
#define Char_Year '1'



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

//All functions
WorkerList* addWorker(WorkerList* head, Worker* w);
Worker* CreateWorker(yearT);
void PrintWorker(char type, const Worker* infoW);
int index(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
//WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);
void update_worker(WorkerList* head, float percent);


//B
Worker* CreateWorker(yearT)
{
	char tmp[30]={0};//temporary for allocation name string
	Worker* nw = (Worker*)malloc(sizeof(Worker));//// Creating new worker information for the new node
	if (nw==NULL)//cheak allocation
	{
		printf("Error: unavailable memory!!");
		exit(1);
	}
	printf("enter worker id:");
	scanf_s("%g",&(nw->id));
	printf("enter worker salary:");
	scanf_s("%g", &(nw->salary));
	printf("enter worker name:");
	scanf_s("%s",tmp);
	(nw->name) = (char*)malloc((strlen(tmp)+ 1)* sizeof(char));
	if (nw->name == NULL)
	{
		printf("Error: unavailable memory!!\n\n");
		exit(1);
	}
	strcpy(nw->name,tmp);

	
	switch (yearT)
	{
	case Char_Year://לחזור לזה אחככ
		do
		{
			fseek(stdin, 0, SEEK_END);
			printf("enter the starting Work year in hebrew: ");
			scanf_s("%s", nw->year.yearc);
			if ((nw->year.yearc > 128) || (nw->year.yearc < 255))puts("Value should be in hebrew only");//משו לא תקין
		} while ((nw->year.yearc > 128) || (nw->year.yearc < 255));
		break;
	case NUM_Year:
		do
		{
			printf("enter the starting Work year in numbers: ");
			scanf_s("%ld", &(nw->year.yearN));
			if ((nw->year.yearN > 9999) || (nw->year.yearN < 1000))puts("Value should be in right numbers!\n");

		} while ((nw->year.yearN > 9999) || (nw->year.yearN < 1000));//הקליטה של השנה לא תקינה צריך לבדוק
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
		printf("year: %s\n", &(infoW->year.yearc));//הדפסת תאריך תחילת עבודה תאריך עברי,תווים
		break;
	case NUM_Year:
		printf("year: %ld\n", infoW->year.yearN);//הדפסת תאריך תחילת עבודה תאריך לועזי מספרים
		break;
	default:
		printf("Worng Format!! ");
		break;
	}
}

//1
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
		newItem->data = w;//insert the worker data
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

//2
//loop version
int index(WorkerList* head,long unsigned id)
{
	int idx = 1;//place of wanted worker id
	if (head == NULL)
	{
		printf("the worker list is empty!");
		exit(1);
	}
	while (head != NULL)
	{
		WorkerList* tmpW;//to run for all list
		tmpW = head;
		if (tmpW->data->id == id)
		{
			return idx;
			break;
		}
		idx++;
		tmpW = tmpW->next;
	}
	return -1;//if the wanted worker isnt in the list:return -1


}

//3
WorkerList* deleteWorstWorker(WorkerList* head)
{
	if (head == NULL)//case no workers
	{
		printf("the worker list is empty!");
		exit(1);
	}
	//the worker with lowest salary is the firt one because it sort
	WorkerList* tmpD;
	tmpD = head;
	head = tmpD->next;
	free(tmpD->data);
	free(tmpD);
	tmpD = head;
	return head;

}

//4
void update_worker(WorkerList* head, float percent)
{
	if (head == NULL)//case no workers
	{
		printf("the worker list is empty!");
		exit(1);
	}
	WorkerList* tmpP = head;
	while (tmpP!= NULL)
	{
		tmpP->data->salary = ((tmpP->data->salary) + ((tmpP->data->salary) * percent));//update salary
		tmpP = tmpP->next;
	}

}

//5
//WorkerList* reverse(WorkerList* head)
//{

//}

//6
void freeWorkers(WorkerList* head)
{
	if (head == NULL) // Case list is empty
	{
		printf("The list is empty, nothing to free...\n\n");
		printf("--------------------- END OF OPTION -----------------------\n\n");
		return NULL;
	}
		WorkerList* tmp1 = head;
		WorkerList* tmp2 = NULL;
		while (tmp1 != NULL)
		{
			tmp2 = tmp1->next;
			free(tmp1->data);
			free(tmp1);
			tmp1 = tmp2;
		}

		head = tmp1;

		printf("Free items was successful!\n\n");
		printf("--------------------- END OF OPTION -----------------------\n\n");
}
//D
int menu()
{
	int option = 0;

	do
	{
		printf("\nDatabase System Menu:"
			"\n   1. add worker"
			"\n   2. print worker"
			"\n   3. find place of worker according to his ID"
			"\n   4. delete worst worker"
			"\n   5. update worker salary"
			"\n   6. reverse list"
			"\n   7. free memory"
			"\n   8. quit");

		printf("\nPlease choose one of the options: ");
		scanf_s("%d", &option);

		if (option > 8 || option < 1)
			printf("\nInvalid number, please try again...\n\n");
	} while (option > 8 || option < 1);

	return option;
}
void main()
{
	WorkerList* head = NULL;
	int yearT ;
	float percentS;
	unsigned long ChoosenID;
	while (1)
	{
		
		int option = menu();

		switch (option)
		{
		case 1:
			//add worker to list
			printf("to enter starting year of work:press-1 to write in hebrew'press 0 to write in numbers");
			scanf_s("%d", &yearT);
			head = addWorker(head,CreateWorker(yearT));
			break;

		case 2:
			//print details of worker
			PrintWorker(yearT, head->data);
			break;

		case 3:
			//find place of worker according to his ID
			printf("enter ID of worker to search: \n");
			scanf_s("%ld", &ChoosenID);
			printf("the index of worker with wanted ID is:%d", index(head,ChoosenID));
			break;

		case 4:
			//delete worst worker
			head = deleteWorstWorker(head);
			break;

		case 5:
			//update worker salary
			printf("enter percent to up salary workers:\n");
			scanf("%g", &percentS);
			update_worker(head, percentS);	
			break;

		case 6:
			//reverse list
			//reverse(head);
			break;
		case 7:
			//free memory
			freeWorkers(head);
			break;
		case 8:
			freeWorkers(head);
			printf("\nEnd of program\n");
			exit(1);
		}
	}


}
