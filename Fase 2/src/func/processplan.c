/**
 * @file processplan.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This file will contain all the functions to manipulate the structure of process plan.
 * @version 0.2
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "../lib/processplan.h"

/**
 * @brief Generates a value to identify a position in the hashtable to insert the new process plan 
 * 
 * @param str String to use as a basis for creating the number  
 * @return int position identifier in the hashtable
 */
int MagicNumber(Message *msg, const char* str)
{
    int seed = 5381;
    int hash = 0;
    int i = 0;
    int size = strlen(str);
    
    for (i = 0; i < size; str++, i++)
    {
        hash = (hash << seed) + (*str);  
    }

    return abs(hash % msg->M);
}

/**
 * @brief Create the position on hash table to insert the value
 * 
 * @param hash hast with the pointers to the lists 
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 */
void insert_hash(ProcessPlan **hash, Message *msg, int processplanID) 
{
    char c[100];
    sprintf (c, "%d", processplanID);
    int h = MagicNumber(msg, c);
    *(hash + h) = insert_list(*(hash + h), msg, processplanID);
}


/**
 * @brief Insert the value into the list 
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan *insert_list(ProcessPlan *lst, Message *msg, int processplanID)
{
    ProcessPlan *cell = malloc(sizeof(ProcessPlan));
     if(!cell)
    {
        msg->type = false;
        strcpy(msg->message, "Ocorreu um erro");
        return NULL;
    }
    cell->ProcessPlanID = processplanID;
    cell->next = lst;
    return cell;
}

/**
 * @brief Checks if the value exists within the hash 
 * 
 * @param hash hast with the pointers to the lists 
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan * exists_in_hash(ProcessPlan **hash, Message *msg, int processplanID) 
{
    char c[100];
    sprintf (c, "%d", processplanID);
    int h = MagicNumber(msg, c);
    ProcessPlan *cell = exists_in_list(*(hash+h), msg, processplanID);
    return cell;
}

/**
 * @brief  Checks if the value exists within the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan * exists_in_list(ProcessPlan *lst, Message *msg, int processplanID) 
{
    bool found = false;
    while(lst)
    {
        if (lst->ProcessPlanID == processplanID)
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
        sprintf(c, "Não process plan ID = %d não existe.", processplanID);
        strcpy(msg->message, c);
        return NULL;
    }
    else
    {
        char c[1000];
        sprintf(c, "O process id %d foi encontrado com sucesso.", processplanID);
        strcpy(msg->message, c);
        return lst;
    }
}
