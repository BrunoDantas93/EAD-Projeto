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

	Operations *op = newOperation(msg);
    if(msg->type == false)
	{
        printf("%s", msg->message);
		exit(0);
	}
    
    bool disable = false; 
    do
    {
        msg->type = true;
        strcpy(msg->message, "");
        system("cls");
        int value = Menu();
        switch(value)
        {
            free(msg);
            case 0:
                disable = true;
                DisplayMessage("Volte sempre!                                                       |");
                break;

            case 1:
                FilesInterpreter(op, msg, 2);
                break;

            case 2:
                op = FilesInterpreter(op, msg, 1);
                break;
            
            case 3:
                op = InsertOp(op, msg);
                break;

            case 4:
                op = DeleteOperation(op, msg);
                break;

            case 5:
                op = ChangeOperation(op, msg);
                break;
            
            case 6:
                MinimumTimeUnits(op, msg);
                DisplayMessage(msg->message);
                ShowFirst(op);
                ReturnMenu();
                break;
            
            case 7:
                MaximumTimeUnits(op, msg);
                DisplayMessage(msg->message);
                ShowLast(op);
                ReturnMenu();
                break;

            
            case 8:
                AverageTimeUnits(op, msg);
                DisplayMessage(msg->message);
                ReturnMenu();
                break;
        }
    }while(disable == false);
}

/**
 * @brief In this function the program to be displayed to the user in the option of reading or writing in a file and the option of choosing the name of the file.
 * 
 * @param lst List to import/export all data to file or form a file
 * @param msg Variable to display the response menssage to the users
 * @param type Determines whether it is the read or save function
 * @return Operations* 
 */
Operations *FilesInterpreter(Operations *lst, Message *msg, int type)
{
    time_t elapsed = 1110;
    DisplayMessage("Para o ficheiros serem encontrados                                                | \n\t\t| tem que estar neste directorio [src/data/nomeficheiro.txt]                        |");
    char *filename = readString("\n\t\tQual ?? o nome do ficheiro.txt: ","\n\t\t[ERROR] Qual ?? o nome do ficheiro.txt: ");
    char str[100];
    
    switch (type)
    {
        case 1:;
            time_t begin, end;
            time(&begin);
            //free(lst);
            sprintf (str, "src/data/%s.txt", filename);
            lst = filesRead(lst, msg, str);
                    
            time(&end);
            elapsed = end - begin;
            break;

        case 2:;
            sprintf (str, "src/data/%s.txt", filename);
            filesWrite(lst, msg, str);
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


    return lst;
}

/**
 * @brief Insert new operations and sub-operations in the list
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
Operations *InsertOp(Operations *lst, Message *msg)
{
    DisplayMessage("Inserir um nova Opera????o e novas Sub-Opera????es");
    int numOperation = readInt("\n\t\tQual ?? o n??mero da Opera????o: ","\n\t\t [ERROR] Qual ?? o n??mero da Opera????o: ");
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
            sprintf(str, "Esta Opera????o [%d] j?? tem algumas Sub-Opera????es adicionadas. ", numOperation);
            DisplayMessage(str);
            DistplaySubOperations(aux);
        }

        char str[100];
        sprintf(str, "Adicionar uma nova Sub-Opera????o a Opera????o numero [%d]", numOperation);
        DisplayMessage(str);
        
        int numMachine = readInt("\n\t\tQual ?? o n??mero da M??quina: ","\n\t\t [ERROR] Qual ?? o n??mero da M??quina: ");
        int time = readInt("\n\t\tQual ?? a dura????o da opera????o: ","\n\t\t [ERROR] Qual ?? a dura????o da opera????o: ");

        lst = CheckOperations(lst, msg, numOperation, numMachine, time);

        if(msg->type == false)
        { disable = true; break;}
        
        DisplayMessage("Sub-Opera????o adicionada com sucesso.");
        
        disable = ChoiceMenu();

    }while (disable == false);
    
    if(msg->type == false)
    {
        DisplayMessage(strcat(msg->message, " |"));
        ReturnMenu();
    }

    return lst;
}

/**
 * @brief This operation gives the user the option to delete an entire job from the list
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
Operations *DeleteOperation(Operations *lst, Message *msg)
{
    DisplayMessage("Escolha o n??mero de opera????o que pertende apagar.");
    if(lst->first)
    {
        int element = DisplayOperations(lst, "\n\t\tQual e o elemento que pertende apagar: ", "[ERROR] Qual e o elemento que pertende apagar: ");
        
        lst = OperationsRemove(lst, msg, element);

        DisplayMessage(msg->message);

    }   
    else
    {
        DisplayMessage("N??o existe nenhum elemento para apagar.");
    }

    ReturnMenu();
    return lst;
}

/**
 * @brief This operation gives the user the option to change a given data of an operation
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
Operations *ChangeOperation(Operations *lst, Message *msg)
{
    DisplayMessage("Escolha o n??mero de opera????o que pertende alterar.");
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
                numMachine = readInt("\n\t\tQual ?? o n??mero da M??quina: ","\n\t\t [ERROR] Qual ?? o n??mero da M??quina: ");
                element->numMachine = numMachine;
                strcpy(msg->message,"O n??mero da m??quina foi alterado com sucesso.");
                break;

            case 1:;
                time = readInt("\n\t\tQual ?? a dura????o da opera????o: ","\n\t\t [ERROR] Qual ?? a dura????o da opera????o: ");
                numMachine = element->numMachine;
                element->numMachine = -930;
                element->time = -930;
                lst = RearrangeElements(lst);
                lst = CheckOperations(lst, msg, elementOp, numMachine, time);
                if (msg->type == true)
                {
                    strcpy(msg->message, "A opera????o foi alterada com sucesso.");
                }                
                break;
            
            case 2:;
                numMachine = readInt("\n\t\tQual ?? o n??mero da M??quina: ","\n\t\t [ERROR] Qual ?? o n??mero da M??quina: ");
                time = readInt("\n\t\tQual ?? a dura????o da opera????o: ","\n\t\t [ERROR] Qual ?? a dura????o da opera????o: ");
                element->numMachine = -930;
                element->time = -930;
                lst = RearrangeElements(lst);
                lst = CheckOperations(lst, msg, elementOp, numMachine, time);
                if (msg->type == true)
                {
                    strcpy(msg->message, "A opera????o foi alterada com sucesso.");
                }
                break;
        }

        DisplayMessage(msg->message);
    }   
    else
    {
        DisplayMessage("N??o existe nenhum elemento para alterar.");
    }
    DisplayMessage(msg->message);
    ReturnMenu();
    return lst;
}

