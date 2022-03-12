#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/jobs.h"
#include "../lib/menu.h"
#include "../lib/mainf.h"


Operations *newOperation(Message *msg)
{
    Operations *new = (Operations *)malloc(sizeof(Operations));
    if(!new)
    {
        msg->type = false;
        strcpy(msg->message, "Ocorreu um erro");
        return NULL;
    }
    new->first = new->last = NULL;
    return new;
}

Operations *Operations_List(Operations *lst, Message *msg, int numOperations)
{
    
    if(!lst->last)
    {
        lst->first = lst->last = insertOperation(lst->last, msg, numOperations);
    }
    else
    {
        OperationsLst *cell = NULL;
        cell = insertOperation(cell, msg, numOperations);
        if(cell == false){return NULL;}   

        if(lst->first->numOperation > numOperations)
        {
            cell->next = lst->first;
            lst->first = cell;
            lst->first->next->prev = cell;                    
        }
        else if(lst->last->numOperation < numOperations)
        {            
            cell->prev = lst->last;
            lst->last->next = cell;
            lst->last = cell;
        }
        else if(lst->last->numOperation > numOperations && lst->first->numOperation < numOperations)
        { 
            OperationsLst *temp = lst->first;
            for( ;temp && temp->numOperation <= numOperations; temp = temp->next){}
            
            if(temp->prev->numOperation != numOperations)
            {
                temp->prev->next = cell;
                cell->prev = temp->prev;
                temp->prev = cell;
                cell->next = temp;
            }            
        }
    }
    return lst;
}

OperationsLst *insertOperation(OperationsLst *lst, Message *msg, int numOperations)
{
    OperationsLst *cell = (OperationsLst *)malloc(sizeof(OperationsLst));
    if(!cell)
    {
        msg->type = false;
        strcpy(msg->message, "Ocorreu um erro");
        return NULL;
    }

    cell->numOperation = numOperations;
    cell->TotalSubOperation = 0;

    cell->first = cell->last = NULL;
    cell->next = NULL;
    cell->prev = lst;
    if (cell->prev) {
        cell->prev->next = cell;
    }
    return cell;
}

Operations *CheckOperations(Operations *lst, Message *msg, int numOperation, int numMachine, int time)
{
   if(lst->first->numOperation == numOperation)
   {
       lst->first = InsertSubOperation(lst->first, msg, numMachine, time);
   }
   else if(lst->last->numOperation == numOperation)
   {
       lst->last = InsertSubOperation(lst->last, msg, numMachine, time);
   }
   else
   {
       OperationsLst *aux = lst->first;
       while(aux)
       {
           if(aux->numOperation == numOperation){break;}
           aux = aux->next;
       }
       
       if(!aux)
       {
            msg->type = false;
            strcpy(msg->message, "Ocorreu um erro");
            return NULL;
       }
       else
       {
            aux = InsertSubOperation(aux, msg, numMachine, time);
       }
   }
   return lst;
}

OperationsLst *InsertSubOperation(OperationsLst *lst, Message *msg, int numMachine, int time)
{   
   if(!lst->last)
   {
       lst->first = lst->last = addSubOperations(lst->last, msg, numMachine, time);
   }
   else
   {
        SubOperations *cell = NULL;
        cell = addSubOperations(cell, msg, numMachine, time);
        if(cell == false){return NULL;}

        if(lst->first->time >= time)
        {
            cell->next = lst->first;
            lst->first = cell;
            lst->first->next->prev = cell; 
        }
        else if(lst->last->time <= time)
        {   
            cell->prev = lst->last;
            lst->last->next = cell;
            lst->last = cell;
        }
        else if(lst->first->time < time && lst->last->time > time)
        {
            SubOperations *temp = lst->first;
            for( ;temp && temp->time <= time; temp = temp->next){}
            
            temp->prev->next = cell;
            cell->prev = temp->prev;
            temp->prev = cell;
            cell->next = temp;
        }
   }
   return lst;
}


SubOperations *addSubOperations(SubOperations *lst, Message *msg, int numMachine, int time)
{       
    SubOperations *cell = (SubOperations *)malloc(sizeof(SubOperations));
    if(!cell)
    {
        msg->type = false;
        strcpy(msg->message, "Ocorreu um erro");
        return NULL;
    }
    cell->numMachine = numMachine;
    cell->time = time;
    
    cell->next = NULL;
    cell->prev = lst;
    if (cell->prev) {
        cell->prev->next = cell;
    }   
   
    return cell;
}


Operations *OperationsRemove(Operations *lst, Message *msg, int element)
{
    if(lst->first->numOperation == element)
    {
        if(lst->first->next)
        {
            lst->first = lst->first->next;
            lst->first->prev = NULL;
        }
        else
        {
            lst->first = NULL;
            lst->last = NULL;
        }
    }
    else if(lst->last->numOperation == element)
    {
        lst->last = lst->last->prev;
        lst->last->next = NULL;
    }
    else
    {
        OperationsLst *aux = lst->first;
        while(aux)
        {
            if(aux->numOperation == element){break;}
            aux = aux->next;
        }
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }
    msg->type = true;
    char str[1000];
    sprintf(str,"Elemento com número [%d] de operação foi apagado com sucesso.",element);
    strcpy(msg->message, str);
    return lst;
}

Operations *RearrangeElements(Operations *ptr)
{
    OperationsLst *lst = ptr->first;
    if(lst->first->numMachine == -930 && lst->first->time == -930)
    {
        if(lst->first->next)
        {
            lst->first = lst->first->next;
            lst->first->prev = NULL;
        }
        else
        {
            lst->first = NULL;
            lst->last = NULL;
        }
    }
    else if(lst->last->numMachine == -930 && lst->last->time == -930)
    {
        lst->last = lst->last->prev;
        lst->last->next = NULL;
    }
    else
    {
        SubOperations *aux = lst->first;
        while(aux)
        {
            if(aux->numMachine == -930 && aux->time == -930){break;}
            aux = aux->next;
        }
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }
    return ptr;
}


void MinimumTimeUnits(Operations *lst, Message *msg)
{
    OperationsLst *ptr = lst->first;
    if(ptr)
    {
        int TotalTime = 0;
        for(; ptr; ptr = ptr->next ) { TotalTime += ptr->first->time; }
        msg->type = true;
        char str[80];
        sprintf(str, "O tempo minimo possível é: %d", TotalTime);
        
    }
    else
    {
        strcpy(msg->message, "Não tem dados na lista para serem porcessados.");
    }
}

void MaximumTimeUnits(Operations *lst, Message *msg)
{
    OperationsLst *ptr = lst->first;
    if(ptr)
    {
        int TotalTime = 0;
        for(; ptr; ptr = ptr->next ) { TotalTime += ptr->last->time; }
        msg->type = true;
        char str[80];
        sprintf(str, "O tempo maximo possível é: %d", TotalTime);
        strcpy(msg->message, str);
    }
    else
    {
        strcpy(msg->message, "Não tem dados na lista para serem porcessados.");
    }
}

void AverageTimeUnits(Operations *lst, Message *msg)
{
    OperationsLst *ptr = lst->first;
    if(ptr)
    {
        int TotalTime = 0, count = 0;
        for(; ptr; ptr = ptr->next ) 
        { 
            SubOperations *ptr2 = ptr->first; 
            for( ; ptr2; ptr2 = ptr2->next)
            {
                TotalTime += ptr2->time;
                count++;  
            } 
        }
        msg->type = true;
        char str[80];
        sprintf(str, "O tempo médio possível e: %d/%d = %d\n", TotalTime, count, TotalTime/count);
        strcpy(msg->message, str);
    }
    else
    {
        strcpy(msg->message, "Não tem dados na lista para serem porcessados.");
    }
}