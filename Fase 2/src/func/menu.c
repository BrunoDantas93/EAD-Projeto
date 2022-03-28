/**
 * @file menu.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief The page will all outputs of the program
 * @version 1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * Contains all menus and list data display.
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"
#include "../lib/mainf.h"
#include "../lib/menu.h"


/**
 * @brief This is main menu to navegate to the functions of the program
 * 
 * @return int 
 */
int FirstMenu()
{
    int choice = -1;
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t|                                                               Menu                                                        |");
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t| [0] -> Sair do programa.                                                                                                   |");
    printf("\n\t\t| [1] -> Ler dados de um ficheiro txt com a representação de um process plan.                                                         |");
    printf("\n\t\t| [2] -> Continuar para o menu.                                                        |");
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    
    choice = readInt("\n\t\tEscolha uma opção: -> ","\n\t\t[Erro] Escolha uma opção: -> ");
    return choice;
}


/**
 * @brief This is main menu to navegate to the functions of the program
 * 
 * @return int 
 */
int Menu()
{
    int choice = -1;
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t|                                                               Menu                                                        |");
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t| [0] -> Sair do programa                                                                                                   |");
    printf("\n\t\t| [1] -> Guardar dados num ficheiro txt.                                                                                    |");
    printf("\n\t\t| [2] -> Inserção de um novo process plan.                                                        |");
    printf("\n\t\t| [3] -> Remoção de uma determinado process plan.                                                         |");
    printf("\n\t\t| [4] -> Inserção de uma nova operação.                                                        |");
    printf("\n\t\t| [5] -> Remoção de uma determinada operação.                                                        |");
    printf("\n\t\t| [6] -> Editar de uma determinada operação.                                                        |");
   printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    
    choice = readInt("\n\t\tEscolha uma opção: -> ","\n\t\t[Erro] Escolha uma opção: -> ");
    return choice;
}

/**
 * @brief This is the menu to display all the messages to the user
 * 
 * @param msg 
 */
void DisplayMessage(char *msg)
{
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t| %s",msg);
    printf("\n\t\t+-----------------------------------------------------------------------------------+\n");
}

/**
 * @brief This menu gives when using the option to continue in the program or if you want to exit
 * 
 */
void ReturnMenu()
{
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t|                            Escolha uma opção                                      |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t| [0] sair                                                                 [1] Menu |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+\n");
    int value;
    do
    {
        value = readInt("\n\t\tEscolha um opção? -> ", "\n\t\t[Erro] opção nao esta disponível escolha outra! -> ");

    }while(value < 0 && value > 1 );
    if(value == 0)
    {
        exit(0);
    }
}


/**
 * @brief This is a menu to ask the user if he wants to continue adding sub-operations or if he wants to stop
 * 
 * @return true 
 * @return false 
 */
bool ChoiceMenu()
{
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t|                     Quer continuar adicionar ou sair?                             |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t| [0] Continuar                                                            [1] Menu |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+\n");
    int value;
    do
    {
        value = readInt("\n\t\tEscolha um opção? -> ", "\n\t\t[Erro] A opção nao esta disponível escolha outra! -> ");

    }while(value < 0 && value > 1 );
    if(value == 0) 
    { return false; }
    else
    { return true; }
}

/**
 * @brief Shows the user all the operations and gives him the option to choose the operation to use in the rest of the functions
 * 
 * @param lst list with all the data
 * @param msg Contains the message to show the user
 * @param errMsg Contains the error message to show the user
 * @return int 
 */ 
int DisplayOperations(ProcessPlan *lst, char *msg, char *errMsg)
{
    OperationsLst *ptr = lst->first;
    while (ptr) {
        printf("\n\t\tOperação -> %d", ptr->numOperation);
        ptr = ptr->next;
    }
    printf("\n");

    bool disable = false;
    int element;
    do
    {
        element = readInt(msg, errMsg);
        OperationsLst *sch = lst->first;
        while(sch)
        {
            if(element == sch->numOperation)
            {
                disable = true;
                break; 
            }
            sch = sch->next;
        }
        
    }while(disable == false);

    return element;
}

/**
 * @brief Sow all the sub-operations
 * 
 * @param lst list with all the data
 */
void DistplaySubOperations(OperationsLst *lst)
{
    SubOperations *ptr = lst->first;
    while (ptr) {
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->numMachine, ptr->time);
        ptr = ptr->next;
    }
}

/**
 * @brief Shows the user all the Sub-operations and gives him the option to choose the sub-operation to use in the rest of the functions
 * 
 * @param lst list with all the data
 * @param msg Contains the message to show the user
 * @param errMsg Contains the error message to show the user
 * @return int 
 */
SubOperations *DisplaySubOperationsChoice(OperationsLst *lst, char *msg, char *errMsg)
{
    SubOperations *ptr = lst->first;
    int count = 0;
    while (ptr) {
        printf("\t\t[%d]-> Máquina número [%d] com uma duração de [%d]\n", count, ptr->numMachine, ptr->time);
        ptr = ptr->next;
        count++;
    }

    printf("\n");

    bool disable = false;
    int element;
    SubOperations *sch = NULL;
    do
    {
        element = readInt(msg, errMsg);
        sch = lst->first;
        count = 0;
        while(sch)
        {
            if(element == count)
            {
                disable = true;
                break; 
            }
            count++;
            sch = sch->next;
        }
        
    }while(disable == false);

    return sch;  
}

/**
 * @brief Show the user all the options they have to be able to change a suboption
 * 
 * @return int 
 */
int SubOperationsChoice()
{
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t|                         O que pertende alterar?                                   |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t|                 [0] Número da máquina  [1] O tempo [2] Os dois                    |");
    printf("\n\t\t+-----------------------------------------------------------------------------------+\n");
    int value;
    do
    {
        value = readInt("\n\t\tEscolha um opção? -> ", "\n\t\t[Erro] A opção nao esta disponível escolha outra! -> ");
    } while (value < 0 || value > 2);
 
    return value;
}

/**
 * @brief Show the fastest operations to complete at work
 * 
 * @param lst 
 */ /*
void ShowFirst(Operations *lst)
{
    OperationsLst *ptr = lst->first;
    while (ptr) {
        printf("\n\t\tOperação -> %d", ptr->numOperation);
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->first->numMachine, ptr->first->time);
        ptr = ptr->next;
    }

}*/

/**
 * @brief Show the slowest operations to complet on job
 * 
 * @param lst 
 */ /*
void ShowLast(Operations *lst)
{
    OperationsLst *ptr = lst->first;
    while (ptr) {
        printf("\n\t\tOperação -> %d", ptr->numOperation);
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->last->numMachine, ptr->last->time);
        ptr = ptr->next;
    }

}*/