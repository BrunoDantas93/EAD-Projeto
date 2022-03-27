#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define M 10000000

typedef struct _ProcessPlan
{
    int ProcessPlanID;
    struct _ProcessPlan *next;
}ProcessPlan;

int MagicNumber(const char* str)
{
    int seed = 5381;
    int hash = 0;
    int i = 0;
    
    for (i = 0; i < strlen(str); str++, i++)
    {
        hash = (hash << seed) + (*str);  
    }

    return abs(hash % M);
}

//! LIXO
char *random_name() {
    int len = 5 + rand() % 10;
    char *name = malloc( len + 1);

    name[0] = 'A' + rand() % 26;
    for (int i = 1; i < len; i++) {
        name[i] = 'a' + rand() % 26;
    }
    name[len] = '\0';
    return name;
}

int length(ProcessPlan *lst) {
    int i = 0;
    while (lst) { i++; lst = lst->next; }
    return i;
}

//* NOT IMPORTANT BUT Useful 
void stats(ProcessPlan **hash) {
    int max = 0, min = length(*hash), tot = 0;
    
    for (int i = 1; i < M; i++ ) {
        int l = length(*(hash+i));
        if (l > max) max = l; 
        if (l < min) min = l;
        if(l > 0) tot++;
    }
    printf("Hash: %d Total: %d Min: %d Max: %d Med: %.2f\n", M, tot, min, max, (float)tot / M);
}


ProcessPlan *insert_list(ProcessPlan* lst, int v) {
    ProcessPlan *cell = malloc(sizeof(ProcessPlan));
    assert(cell);
    cell->ProcessPlanID = v;
    cell->next = lst;
    return cell;
}

//Prepara o hash para o ID
void insert_hash(ProcessPlan **hash, int v) {
    char c[100];
    sprintf (c, "%dProcessPlan", v);
    int h = MagicNumber(c);
    *(hash + h) = insert_list(*(hash + h), v);
}

bool exists_in_list(ProcessPlan *lst, int v) {
    bool found = false;
    while(lst)
    {
        if (lst->ProcessPlanID == v)
        { 
            found = true; 
            break;
        }
        lst = lst->next;
    }
    /*for ( ; lst && !found ; lst = lst->next) {
        if (lst->ProcessPlanID == v)
        { 
            found = true; break;
        }
    }*/
    printf("%d = %d", v, lst->ProcessPlanID);
    return found;
}

bool exists_in_hash(ProcessPlan **hash, int v) {
    char c[100];
    sprintf (c, "%dProcessPlan", v);
    int h = MagicNumber(c);
    return exists_in_list(*(hash+h), v);
}

int main(){
    time_t begin, end;
    time(&begin);
    
    ProcessPlan **Hash = calloc(M, sizeof(ProcessPlan*));
    
    
    for (int i = 0; i < M; i++)
    {
    
        //char c[100];
        //sprintf (c, "Process%dPlan", i);
        insert_hash(Hash,i);

    

    }
    time(&end);
    time_t elapsed = end - begin;
        
    printf("Time measured: %ld seconds.\n", elapsed);
    
    
    system("pause");
    stats(Hash);
    int a = 20198;
    printf("O valor %d == %s\n", a, exists_in_hash(Hash, a) ? "true" : "false" );
    
    
    system("pause");
    return 0;
}