/**
 * @file jobs.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This file will contain all the main functions of the program.
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 *  
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"
#include "../lib/menu.h"
#include "../lib/mainf.h"

/**
 * @brief 
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param ProcessPlan_Operation operation identifier
 * @return Operations* 
 */
ProcessPlan *newOperation(ProcessPlan *lst, Message *msg, int ProcessPlan_Operation)
{
    Operations *new = (Operations *)malloc(sizeof(Operations));
    
    if(!new)
    {
        msg->type = false;
        strcpy(msg->message, "Ocorreu um erro");
        return NULL;
    }
    new->ProcessPlan_Operations = ProcessPlan_Operation;
    new->first = new->last = NULL;
    new->TotalOperation = 0; 
    
    new->next = lst->first;
    lst->first = new;
    lst->totalProcesses++;
    return lst;
}


/**
 * @brief  Checks if the value exists within the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
Operations * exists_in_list2(Operations *lst, Message *msg, int ProcessPlan_Operations) 
{
    bool found = false;
    while(lst)
    {
        if (lst->ProcessPlan_Operations == ProcessPlan_Operations)
        { 
            found = true; 
            break;
        }
        lst = lst->next;
    }
    
    msg->type = found;
    if(msg->type == false)
    { 
        char c[1000];
        sprintf(c, "Não process plan ID = %d não existe.", ProcessPlan_Operations);
        strcpy(msg->message, c);
        return NULL;
    }
    else
    {
        char c[1000];
        sprintf(c, "O process id %d foi encontrado com sucesso.", ProcessPlan_Operations);
        strcpy(msg->message, c);
        return lst;
    }
}


/**
 * @brief This function looks for the position to insert the new operation identifier in the list in order from smallest to largest
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @return Operations* 
 */
Operations *Operations_List(Operations *lst, Message *msg, int numOperations)
{
    if(!lst->last)
    {
        lst->first = lst->last = insertOperation(lst->last, msg, numOperations);
        lst->TotalOperation++;
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
            lst->TotalOperation++;              
        }
        else if(lst->last->numOperation < numOperations)
        {            
            cell->prev = lst->last;
            lst->last->next = cell;
            lst->last = cell;
            lst->TotalOperation++;
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
                lst->TotalOperation++;
            }            
        }
    }
    return lst;
}

/**
 * @brief This function inserts new operation identifiers.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @return OperationsLst* 
 */
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

/**
 * @brief This function looks for the position that has the same operation identifier to insert new alternatives to perform the operation with different machines and times.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return Operations* 
 */
Operations *CheckOperations(Operations *lst, Message *msg, int numOperation, int numMachine, int time)
{
   if(lst->first->numOperation == numOperation)
   {
       lst->first = InsertSubOperation(lst->first, msg, numMachine, time);
       lst->first->TotalSubOperation++;
   }
   else if(lst->last->numOperation == numOperation)
   {
       lst->last = InsertSubOperation(lst->last, msg, numMachine, time);
       lst->last->TotalSubOperation++;
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
            aux->TotalSubOperation++;
       }
   }
   return lst;
}

/**
 * @brief This function looks for the position to insert the new alternatives in the list in order 
 * from shortest time to longest time to complete the operation
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return OperationsLst* 
 */
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

/**
 * @brief Insert the new alternatives in the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return OperationsLst* 
 */
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
    cell->tested = false;
    
    cell->next = NULL;
    cell->prev = lst;
    if (cell->prev) {
        cell->prev->next = cell;
    }   
    return cell;
}

/**
 * @brief Remove  element from the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param element Element to be removed from the list
 * @return Operations* 
 */
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
        free(aux);
    }
    msg->type = true;
    char str[1000];
    sprintf(str,"Elemento com número [%d] de operação foi apagado com sucesso.",element);
    strcpy(msg->message, str);
    return lst;
}

/**
 * @brief Remove the element that was changed to be able to sort the list in an orderly way
 * 
 * @param ptr list where we will store the data 
 * @return Operations* 
 */
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
        free(aux);
    }
    return ptr;

}

/**
 * @brief Determines the minimum amount of time units needed to complete the job
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
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
        strcpy(msg->message, str);
    }
    else
    {
        strcpy(msg->message, "Não tem dados na lista para serem porcessados.");
    }
    free(ptr);
}

/**
 * @brief Determines maximum amount of time units needed to complete the job
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
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
    free(ptr);
}

/**
 * @brief Determines the average amount of time units required to complete an operation,
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
void AverageTimeUnits(Operations *lst, Message *msg)
{
    OperationsLst *ptr = lst->first;
    if(ptr)
    {
        strcpy(msg->message, "");
        for(; ptr; ptr = ptr->next ) 
        { 
            int TotalTime = 0, count = 0;
            SubOperations *ptr2 = ptr->first; 
            for( ; ptr2; ptr2 = ptr2->next)
            {
                TotalTime += ptr2->time;
                count++;  
            }
            if(strcmp(msg->message, "") == 0)
            {
                sprintf(msg->message, "O tempo médio possível da operação %d é: %d/%d = %d   |", ptr->numOperation, TotalTime, count, TotalTime/count);
            }   
            else         
            {
                sprintf(msg->message, "%s\n\t\t| O tempo médio possível da operação %d é: %d/%d = %d   |", msg->message, ptr->numOperation, TotalTime, count, TotalTime/count);
            }   
            free(ptr2);
        }
        msg->type = true;
    }
    else
    {
        strcpy(msg->message, "Não tem dados na lista para serem porcessados.");
    }
    free(ptr);
}