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
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"

/**
 * @brief loops through the file to see how many process plans there are 
 * 
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file that contains the data
 * @return int 
 */
int HashSize(Message *msg, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    int size = 0;
    int lines = 0;
    
    if(file != NULL)
    {
       
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        
        if(size == 0)
        {
            msg->type = false;
            char str[1000];
            sprintf (str, "O ficheiro [%s] não tem dados.", filename);
            strcpy(msg->message, str);
        }

        fseek(file, 0, SEEK_SET);
        
        int count = 0;
        
        while (!feof(file)) 
        {
            char string[1000];
            fgets(string, 1000, file);
            count++;
        }
        
        int processplanArr[count];

        fseek(file, 0, SEEK_SET);

        while (!feof(file)) 
        {
            char string[1000];
            int processplanID;
            fgets(string, 1000, file);
            sscanf(string, "%d", &processplanID);        

            if(lines == 0)
            {
                processplanArr[lines] = processplanID;
                lines++;
            }
            else
            {
                bool found = false;
                for (int i = 0; i < lines; i++)
                {
                    if(processplanID == processplanArr[i])
                    {
                        found = true;
                    }
                }
                if(found == false)
                {
                    processplanArr[lines] = processplanID;
                    lines++;
                }            
            }
        }
    }
    
    if(size == 0) { lines = 1280; }
    
    size = 0;
    if( lines >= 100)
    {
        float j = lines;
        float b;
        do
        {
            j = (j*0.75);
            b = lines/j;
        }while(b < 44 || b > 76);
        size = ceil(j)+0.1;

    }else{ size = ceil((lines*0.75))+0.1;}


    fclose(file);
    msg->type = true;
    msg->S = lines;
    msg->M = size;
    return 0;
}

/**
 * @brief Function to read the data from a file.
 * 
 * @param Hash list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file that contains the data
 * @return Operations* 
 */
int filesRead(ProcessPlan **Hash, Message *msg, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    if(file == NULL)
    {
        msg->type = false;        
        char str[1000];
        sprintf (str, "O ficheiro [%s] não existe.", filename);
        strcpy(msg->message, str);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    
    if(size == 0)
    {
        msg->type = false;
        char str[1000];
        sprintf (str, "O ficheiro [%s] não tem dados.", filename);
        strcpy(msg->message, str);
        return 0;
    }

    fseek(file, 0, SEEK_SET);

    int lines = 0;


    while (!feof(file)) 
    {
        char string[1000];
    	int processplanID, processPlan_operation, numOperation, numMachine, time;
	    fgets(string, 1000, file);
        sscanf(string, "%d,%d,%d,%d,%d", &processplanID, &processPlan_operation, &numOperation, &numMachine, &time); 
        
        if(lines == 0)
        {
            insert_hash(Hash, msg, processplanID); 
            lines++;           
        }
        else
        {
            ProcessPlan *lst = exists_in_hash(Hash, msg, processplanID);
            
            if(msg->type == false)
            {  
                insert_hash(Hash, msg, processplanID);
                msg->type = true;
            } 

        }

        ProcessPlan *lst = exists_in_hash(Hash, msg, processplanID);

        if(lst->first == NULL)
        {
            newOperation(lst, msg, processPlan_operation);
        }         
        
        Operations *op = exists_in_list2(lst->first, msg, processPlan_operation);
        
        if(msg->type == false)
        {    
            //verificar maquina e verificar o tempo
            newOperation(lst, msg, processPlan_operation);
            msg->type = true;
            op = exists_in_list2(lst->first, msg, processPlan_operation);
        }            
        Operations_List(op, msg, numOperation);
        CheckOperations(op, msg, numOperation, numMachine, time);
        
        if(msg->type == false)
        {
            return 0;
        }
	}
    
    fclose(file);
    msg->type = true;
    strcpy(msg->message, "Dado lidos com sucesso.         |");
    return 0;
}


/**
 * @brief Function to write the data from the list.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file where will save the data 
 * @return int 
 */ 
int filesWrite(ProcessPlan **Hash, Message *msg, char *filename)
{
    FILE *file;
    file = fopen(filename, "w+");
    if(file == NULL)
    {
        msg->type = false;
        char str[1000];
        sprintf (str, "Nao foi possível criar o ficheiro [%s].", filename);
        strcpy(msg->message, str);
        return 0;
    }

    for (int i = 0; i < msg->M; i++)
    {
        ProcessPlan *lst = Hash[i];

        for ( ; lst; lst = lst->next)
        {   
            int processplanID = lst->ProcessPlanID; 

            Operations *ptr = lst->first;
            for ( ; ptr; ptr = ptr->next)
            {
                OperationsLst *ptr2 = ptr->first;
        
                if(ptr2)
                {
                    while (ptr2) 
                    {
                        SubOperations *ptr3 = ptr2->first;
                        while (ptr3) 
                        {
                            fprintf(file,"%d,%d,%d,%d,%d\n",processplanID, ptr->ProcessPlan_Operations ,ptr2->numOperation, ptr3->numMachine, ptr3->time);
                            ptr3 = ptr3->next;
                        }
                        ptr2 = ptr2->next;
                    }
                }
            }
        }
    }
    msg->type = true;
    strcpy(msg->message, "O fecheiro foi criado e preenchido com sucesso. ");
    fclose(file);
    return 1;
}