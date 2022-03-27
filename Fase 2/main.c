/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "src/lib/processplan.h"
#include "src/lib/jobs.h"
#include "src/lib/files.h"


int length(ProcessPlan *lst) {
    int i = 0;
    while (lst) { i++; lst = lst->next; }
    return i;
}


void stats(ProcessPlan **hash, Message *msg) {
    int max = 0, min = length(*hash), tot = 0;
    
    for (int i = 1; i < msg->M; i++ ) {
        int l = length(*(hash+i));
        if (l > max) max = l; 
        if (l < min) min = l;
        tot += l;
    }
    printf("Hash: %d Total: %d Min: %d Max: %d Med: %.2f\n", msg->M, tot, min, max, (float)tot / msg->M);
}

void list_queue2(SubOperations *ptr) {
    while (ptr) {
        printf("\t\t%d -> %d\n", ptr->numMachine, ptr->time);
        ptr = ptr->next;
    }
}


void list_queue(ProcessPlan *q) {
    OperationsLst *ptr = q->first;
    while (ptr) {
        printf("%d\n", ptr->numOperation);
		list_queue2(ptr->first);
        ptr = ptr->next;
    }
}

int main()
{
    time_t begin, end;
    time(&begin);
    
    Message *msg = (Message *)malloc(sizeof(Message));
	msg->type = true;
    msg->M = 0;
	strcpy(msg->message, "");
    
    HashSize(msg, "src/data/processplan2.txt");
    
    ProcessPlan **Hash = calloc(msg->M, sizeof(ProcessPlan*));
    
    filesRead(Hash, msg, "src/data/processplan2.txt");

    /*for (int i = 0; i < 640; i++)
    {
        insert_hash(Hash, msg, i);  
    }*/
    time(&end);
    time_t elapsed = end - begin;
    
    
    printf("Time measured: %ld seconds.\n", elapsed);

    stats(Hash, msg);

    for (int i = 0; i < msg->M; i++)
    {
        printf("--------%d--------\n", (*(Hash+i))->ProcessPlanID);
        list_queue(*(Hash+i));
        printf("---------------..-\n");
    }
    



    while(true)
    {
        int a;
        scanf("%d", &a);
        exists_in_hash(Hash, msg, a);
        printf("%s\n", msg->message);
    }
    
    int a = 1276;
    exists_in_hash(Hash, msg, a);
    printf("%s\n", msg->message);
    
    
    system("pause");
    return 0;
}