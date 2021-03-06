/**
 * @file files.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This is the file where we will manipulate the text files
 * @version 1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * In this file the program will create/write and read the test file
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../lib/jobs.h"
#include "../lib/mainf.h"

/**
 * @brief Function to read the data from a file.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file that contains the data
 * @return Operations* 
 */
Operations *filesRead(Operations *lst, Message *msg, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    if(file == NULL)
    {
        msg->type = false;        
        char str[1000];
        sprintf (str, "O ficheiro [%s] não existe.", filename);
        strcpy(msg->message, str);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    
    if(size == 0)
    {
        msg->type = false;
        char str[1000];
        sprintf (str, "O ficheiro [%s] não tem dados.", filename);
        strcpy(msg->message, str);
        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    while (!feof(file)) 
    {
        char string[1000];
    	int numOperation, numMachine,time;
	    fgets(string, 1000, file);
		sscanf(string, "%d,%d,%d", &numOperation, &numMachine, &time);        
        
        lst = Operations_List(lst, msg, numOperation);
        lst = CheckOperations(lst, msg, numOperation, numMachine, time);
        
        if(msg->type == false)
        {
            return NULL;
        }
	}
    
    fclose(file);
    msg->type = true;
    strcpy(msg->message, "Dado lidos com sucesso.         |");
    return lst;
}


/**
 * @brief Function to write the data from the list.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file where will save the data 
 * @return int 
 */
int filesWrite(Operations *lst, Message *msg, char *filename)
{
    FILE *file;

    OperationsLst *ptr = lst->first;
    
    if(!ptr)
    {
        msg->type = false;
        char str[1000];
        sprintf (str, "Não tem dados salvos no sistema.");
        strcpy(msg->message, str);
        return 0;
    }

    file = fopen(filename, "w+");

    if(file == NULL)
    {
        msg->type = false;
        char str[1000];
        sprintf (str, "Nao foi possível criar o ficheiro [%s].", filename);
        strcpy(msg->message, str);
        return 0;
    }

    while (ptr) 
    {
        SubOperations *ptr2 = ptr->first;
        while (ptr2) 
        {
            fprintf(file,"%d,%d,%d\n",ptr->numOperation, ptr2->numMachine, ptr2->time);
            ptr2 = ptr2->next;
        }
	    ptr = ptr->next;
    }
    
    msg->type = true;
    strcpy(msg->message, "O fecheiro foi criado e preenchido com sucesso. ");
    fclose(file);
    return 1;
}