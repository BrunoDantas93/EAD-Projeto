#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "src/lib/processplan.h"
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




int main()
{
    time_t begin, end;
    time(&begin);
    
    ProcessPlan **Hash = calloc(178180, sizeof(ProcessPlan*));
    Message *msg = (Message *)malloc(sizeof(Message));
	msg->type = true;
    msg->M = 0;
	strcpy(msg->message, "");
    
    HashSize(msg, "src/data/processplan.txt");
    printf("%d", msg->M);
    for (int i = 0; i < 640; i++)
    {
        insert_hash(Hash, msg, i);  
    }
    time(&end);
    time_t elapsed = end - begin;
    
    
    printf("Time measured: %ld seconds.\n", elapsed);
    
    stats(Hash, msg);
    int a = 639;
    exists_in_hash(Hash, msg, a);
    printf("%s\n", msg->message);
    
    
    system("pause");
    return 0;
}