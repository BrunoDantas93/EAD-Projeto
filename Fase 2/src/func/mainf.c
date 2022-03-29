/**
 * @file mainf.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This file will contain all the main functions of the program.
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"
#include "../lib/mainf.h"
#include "../lib/menu.h"
#include "../lib/files.h"

/**
 * @brief This function is an evaluator of users inputs that only accepts inputs of type integer, also content custom message and error message
 * This functions 
 * @param msg Message to display the user about some element of type integer
 * @param msgErr Error message to show the user if the element inserted was not valid
 * @return int 
 */
int readInt(char *msg, char *msgErr)
{
    int valueInt;
    printf("%s",msg);
    while(scanf("%i",&valueInt) != 1)
    {
        fflush(stdin);
        printf("%s",msgErr);
    }
    fflush(stdin);
    return valueInt;  
}

/**
 * @brief This function is an evaluator of users inputs that only accepts inputs of type integer, also content custom message and error message
 * This functions 
 * @param msg Message to display the user about some element of type integer
 * @param msgErr Error message to show the user if the element inserted was not valid
 * @return int 
 */
char *readString(const char *msg, const char *msgErr)
{
    fflush(stdin);
    char ValueString[100];
    printf("%s",msg);
    while ((fgets(ValueString, sizeof(ValueString), stdin) == NULL) || strtok(ValueString, "\n") == NULL)
    {     
        printf("%s",msgErr);
    }
    strtok(ValueString, "\n");

    return strdup(ValueString);  
}

/**
 * @brief This is the core function of the entire program.
 * And in this function where the pointers to the list of jobs and messages will be initialized
 * As it will also have an infinite loop of the menu to continue in the program when it finishes executing a function 
 */
void InitializeComponent()
{
    Message *msg = (Message *)malloc(sizeof(Message));
	msg->type = true;
	strcpy(msg->message, "");

    ProcessPlan **Hash;
    bool disable = false; 
    do
    {
        msg->type = true;
        strcpy(msg->message, "");
        system("cls");
        int value = FirstMenu();
        switch(value)
        {
            case 0:
                disable = true;
                DisplayMessage("Volte sempre!                                                       |");
                exit(0);
                break;

            case 1:
                Hash = FilesInterpreter(Hash, msg, 1);
                if(msg->type != false)
                    disable = true;
                break;
            
            case 2:
                disable = true;
                HashSize(msg, "");
                Hash = calloc(msg->M, sizeof(ProcessPlan*));
                break;
        }
    }while(disable == false);

    disable = false; 
    do
    {
        msg->type = true;
        strcpy(msg->message, "");
        system("cls");
        int value = Menu();
        switch(value)
        {
            case 0:
                disable = true;
                DisplayMessage("Volte sempre!                                                       |");
                exit(0);
                break;

            case 1:
                FilesInterpreter(Hash, msg, 2);
                break;

            case 2:
                newProcessPlan(Hash, msg);
                break;
            
            case 3:
                removeProcessPlan(Hash, msg);
                break;
            
            case 4:
                InsertOp(Hash, msg);
                break;

            case 5:
                DeleteOperation(Hash, msg);
                break;

            case 6:
                ChangeOperation(Hash, msg);
                break;

            case 7:
                calculateProcessPan(Hash, msg);
                break;

    
        }
    }while(disable == false);
}

/**
 * @brief In this function the program to be displayed to the user in the option of reading or writing in a file and the option of choosing the name of the file.
 * 
 * @param hash List to import/export all data to file or form a file
 * @param msg Variable to display the response menssage to the users
 * @param type Determines whether it is the read or save function
 * @return Operations* 
 */
ProcessPlan ** FilesInterpreter(ProcessPlan **Hash, Message *msg, int type)
{
    time_t elapsed = 0;
    DisplayMessage("Para o ficheiros serem encontrados                                                | \n\t\t| tem que estar neste directorio [src/data/nomeficheiro.txt]                        |");
    char *filename = readString("\n\t\tQual é o nome do ficheiro.txt: ","\n\t\t[ERROR] Qual é o nome do ficheiro.txt: ");
    char str[100];
    
    switch (type)
    {
        case 1:;
            time_t begin, end;
            time(&begin);
            sprintf (str, "src/data/%s.txt", filename);
            HashSize(msg, str);
            Hash = calloc(msg->M, sizeof(ProcessPlan*));
            filesRead(Hash, msg, str);
            time(&end);
            elapsed = end - begin;
            break;

        case 2:;
            sprintf (str, "src/data/%s.txt", filename);
            filesWrite(Hash, msg, str);
            break;    
    }

    if(msg->type == false)
    {
        DisplayMessage(strcat(msg->message, " |"));        

        ReturnMenu();
    }
    else
    {
        char str[100]; 
        sprintf(str, "%s \n\t\t| Tempo medido: %ld segundos. |", msg->message, elapsed);
        DisplayMessage(str);
        ReturnMenu();
    }

    if(type == 1)
        return Hash;
    return 0;
}

/**
 * @brief This function insert a new process plan in the list
 * 
 * @param Hash list all the process plan
 * @param msg  Variable to display the response menssage to the users
 * @return int 
 */
int newProcessPlan(ProcessPlan **Hash, Message *msg)
{
    DisplayMessage("Inserir um novo process plan.");
    int processplanID = readInt("\n\t\tQual é o número do Process Plan: ","\n\t\t [ERROR] Qual é o número da número do Process Plan: ");
    exists_in_hash(Hash, msg, processplanID);
    if(msg->type == false)
    {
        msg->type = true;
        insert_hash(Hash, msg, processplanID);
        if(msg->type == false)
        {
            DisplayMessage(strcat(msg->message, " |w"));
        }
        else
        {
            DisplayMessage("Process plan adicionada com sucesso.");
        }
    }
    else
    {
        DisplayMessage(strcat(msg->message, " |"));
    }
    ReturnMenu();
    return 0;
}


/**
 * @brief remove a process plan from the list
 * 
 * @param Hash list all the process plan
 * @param msg  Variable to display the response menssage to the users
 * @return int 
 */
int removeProcessPlan(ProcessPlan **Hash, Message *msg)
{
    DisplayMessage("Remover um process plan.");
    int processplanID = readInt("\n\t\tQual é o número do Process Plan que quer remover: ","\n\t\t [ERROR] Qual é o número da número do Process Plan que quer remover: ");
    exists_in_hash(Hash, msg, processplanID);
    if(msg->type != false)
    {
        hash_remove(Hash, msg, processplanID);
        DisplayMessage(msg->message);
    }
    else
    {
        DisplayMessage(msg->message);
    }
    
    ReturnMenu();
    return 0;
}


/**
 * @brief Insert a given process plan new operations and sub operations in the list
 * 
 * @param Hash list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
int InsertOp(ProcessPlan **Hash, Message *msg)
{
    int numProcesPlan = readInt("\n\t\tQual é o número do Process Plan: ","\n\t\t [ERROR] Qual é o número número do Process Plan: ");
    ProcessPlan *lst = exists_in_hash(Hash, msg, numProcesPlan);
    if(msg->type != false)
    {
        DisplayMessage("Inserir um nova Operação e novas Sub-Operações");
        int numOperation = readInt("\n\t\tQual é o número da Operação: ","\n\t\t [ERROR] Qual é o número da Operação: ");
        OperationsLst *aux = NULL;
        bool disable = false;
        do{
            system("cls");
            if(lst->first)
            {
                lst = Operations_List(lst, msg, numOperation);
                OperationsLst *aux2 = lst->first;
                
                while (aux2)
                {
                    if(aux2->numOperation == numOperation)
                    { 
                        aux = aux2; 
                        break; 
                    }
                    aux2 = aux2->next;
                }
            }
            else
            {
                lst = Operations_List(lst, msg, numOperation);
                aux = lst->first;
            }

            if(msg->type == false){ disable = true; break;}   


            if(aux->first)
            {
                char str[100];
                sprintf(str, "Esta Operação [%d] já tem algumas Sub-Operações adicionadas. ", numOperation);
                DisplayMessage(str);
                DistplaySubOperations(aux);
            }

            char str[100];
            sprintf(str, "Adicionar uma nova Sub-Operação a Operação numero [%d]", numOperation);
            DisplayMessage(str);
            
            int numMachine = readInt("\n\t\tQual é o número da Máquina: ","\n\t\t [ERROR] Qual é o número da Máquina: ");
            int time = readInt("\n\t\tQual é a duração da operação: ","\n\t\t [ERROR] Qual é a duração da operação: ");

            lst = CheckOperations(lst, msg, numOperation, numMachine, time);

            if(msg->type == false)
            { disable = true; break;}
            
            DisplayMessage("Sub-Operação adicionada com sucesso.");
            
            disable = ChoiceMenu();

        }while (disable == false);
    }   
    
    
    if(msg->type == false)
    {
        DisplayMessage(strcat(msg->message, " |"));
        ReturnMenu();
    }

    return 1;
}

/**
 * @brief This operation gives the user the option to delete an entire job from the list
 * 
 * @param Hash list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
int DeleteOperation(ProcessPlan **Hash, Message *msg)
{
    int numProcesPlan = readInt("\n\t\tQual é o número do Process Plan: ","\n\t\t [ERROR] Qual é o número número do Process Plan: ");
    ProcessPlan *lst = exists_in_hash(Hash, msg, numProcesPlan);
    if(msg->type != false)
    {
        DisplayMessage("Escolha o número de operação que pertende apagar.");
        if(lst->first)
        {
            int element = DisplayOperations(lst, "\n\t\tQual e o elemento que pertende apagar: ", "[ERROR] Qual e o elemento que pertende apagar: ");
            
            lst = OperationsRemove(lst, msg, element);

            DisplayMessage(msg->message);

        }   
        else
        {
            DisplayMessage("Não existe nenhum elemento para apagar.");
        }
    }
    else
    {
        DisplayMessage(strcat(msg->message, " |"));
        ReturnMenu();
    }

    ReturnMenu();
    return 0;
}


/**
 * @brief This operation gives the user the option to change a given data of an operation
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
int ChangeOperation(ProcessPlan **Hash, Message *msg)
{
    int numProcesPlan = readInt("\n\t\tQual é o número do Process Plan: ","\n\t\t [ERROR] Qual é o número número do Process Plan: ");
    ProcessPlan *lst = exists_in_hash(Hash, msg, numProcesPlan);
    if(msg->type != false)
    {
        
        DisplayMessage("Escolha o número de operação que pertende alterar.");
        if(lst->first)
        {
            int elementOp = DisplayOperations(lst, "\n\t\tQual e o elemento que pertende apagar: ", "[ERROR] Qual e o elemento que pertende apagar: ");
            
            OperationsLst *ptr = lst->first;
            while (ptr)
            {
                if(ptr->numOperation == elementOp){break;}
                ptr = ptr->next;
            }

            SubOperations *element = DisplaySubOperationsChoice(ptr, "\n\t\tQual e o elemento que pertende alterar: ", "[ERROR] Qual e o elemento que pertende alterar: ");

            int choice = SubOperationsChoice();

            int numMachine;
            int time; 
            switch (choice)
            {
                case 0:;
                    numMachine = readInt("\n\t\tQual é o número da Máquina: ","\n\t\t [ERROR] Qual é o número da Máquina: ");
                    element->numMachine = numMachine;
                    strcpy(msg->message,"O número da máquina foi alterado com sucesso.");
                    break;

                case 1:;
                    time = readInt("\n\t\tQual é a duração da operação: ","\n\t\t [ERROR] Qual é a duração da operação: ");
                    numMachine = element->numMachine;
                    element->numMachine = -930;
                    element->time = -930;
                    lst = RearrangeElements(lst);
                    lst = CheckOperations(lst, msg, elementOp, numMachine, time);
                    if (msg->type == true)
                    {
                        strcpy(msg->message, "A operação foi alterada com sucesso.");
                    }                
                    break;
                
                case 2:;
                    numMachine = readInt("\n\t\tQual é o número da Máquina: ","\n\t\t [ERROR] Qual é o número da Máquina: ");
                    time = readInt("\n\t\tQual é a duração da operação: ","\n\t\t [ERROR] Qual é a duração da operação: ");
                    element->numMachine = -930;
                    element->time = -930;
                    lst = RearrangeElements(lst);
                    lst = CheckOperations(lst, msg, elementOp, numMachine, time);
                    if (msg->type == true)
                    {
                        strcpy(msg->message, "A operação foi alterada com sucesso.");
                    }
                    break;
            }

            DisplayMessage(msg->message);
        }   
        else
        {
            DisplayMessage("Não existe nenhum elemento para alterar.");
        }
    }
    DisplayMessage(msg->message);
    ReturnMenu();
    return 0;
}

/**
 * @brief Get the Order List object
 * 
 * @param lst List with all the data
 * @param orderedlist array to save order list
 * @return int 
 */
int GetOrderList(ProcessPlan *lst, OperationsLst *orderedlist[])
{
    OperationsLst *ptr = lst->first;
    //OperationsLst *orderedlist[lst->TotalOperation];
    int count = 0;
    for( ; ptr; ptr = ptr->next)
    {  
        orderedlist[count] = ptr;
        count++;
    }
    
    for(int i = 0; i < lst->TotalOperation; i++)
    {
        for(int j = 0; j < lst->TotalOperation; j++)
        {
            if(orderedlist[j]->TotalSubOperation < orderedlist[i]->TotalSubOperation )
            {
                OperationsLst *aux = orderedlist[i];
                orderedlist[i] = orderedlist[j];
                orderedlist[j] = aux;
            }
        }
    }
    return 0;
}

/**
 * @brief 
 * 
 * @param Hash List with all of operations to calculate the best time
 * @param msg Variable to display the response menssage to the users
 * @return int 
 */
int calculateProcessPan(ProcessPlan **Hash, Message *msg)
{
    int numProcesPlan = readInt("\n\t\tQual é o número do Process Plan: ","\n\t\t [ERROR] Qual é o número número do Process Plan: ");
    ProcessPlan *lst = exists_in_hash(Hash, msg, numProcesPlan);
    if(msg->type != false)
    {
        OperationsLst *orderedlist[lst->TotalOperation]; 
        GetOrderList(lst, orderedlist);

        for(int i = 0; i < lst->TotalOperation; i++)
        {
            printf("%d -> %d\n",orderedlist[i]->numOperation, orderedlist[i]->TotalSubOperation);
        }

        




        /*OperationsLst *ptr = lst->first;
        //printf("\n%d\n",lst->TotalOperation);
        SubOperations *bestTime[lst->TotalOperation];
        int count = 0;

        for( ; ptr; ptr = ptr->next)
        {
            if(count == 0)
            {
                bestTime[count] = ptr->first;
            }
            else
            {  
                
                //Verificar se a maquina ja esta em uso.
                //se nao estiver adicionar
                //se estiver valtar a fazer o mesmo.


                //bestTime[count] = ptr->first;
            }

            count++;
        }*/

        
    }   
    //ProcessPlan bestTime;
    ReturnMenu();
    return 0;
}





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
        printf("\t\t%d -> %d \n", ptr->numMachine, ptr->time);
        ptr = ptr->next;
    }
}


void list_queue(ProcessPlan *q) {
    OperationsLst *ptr = q->first;
    while (ptr) {
        printf("%d: %d\n", ptr->numOperation, ptr->TotalSubOperation);
		list_queue2(ptr->first);
        ptr = ptr->next;
    }
}

void trash(ProcessPlan **Hash, Message *msg)
{

    for (int i = 0; i < msg->M; i++)
    {
        ProcessPlan *lst = Hash[i];
        for ( ; lst; lst = lst->next)
        {
            printf("--------%d--------\n", lst->ProcessPlanID);
            if(lst->first != NULL)
                list_queue(lst);
            printf("------------------\n");
            
        }
        
    }
}
