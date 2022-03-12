#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/jobs.h"
#include "../lib/mainf.h"
#include "../lib/menu.h"

int Menu()
{
    int choice = -1;
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t|                                                               Menu                                                        |");
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    printf("\n\t\t| [0] -> Sair do programa                                                                                                   |");
    printf("\n\t\t| [1] -> Guardar dados num ficheiro txt.                                                                                    |");
    printf("\n\t\t| [2] -> Ler dados de um ficheiro txt com a representação de um job.                                                         |");
    printf("\n\t\t| [3] -> Inserção de uma nova operação.                                                        |");
    printf("\n\t\t| [4] -> Remoção de uma determinada operação.                                                        |");
    printf("\n\t\t| [5] -> Editar de uma determinada operação.                                                        |");
    printf("\n\t\t| [6] -> Quantidade mínima de unidades de tempo necessárias para completar o job.        |");
    printf("\n\t\t| [7] -> Quantidade máxima de unidades de tempo necessárias para completar o job.        |");
    printf("\n\t\t| [8] -> Quantidade média de unidades de tempo necessárias para completar uma operação.  |");
    printf("\n\t\t+---------------------------------------------------------------------------------------------------------------------------+");
    
    choice = readInt("\n\t\tEscolha uma opção: -> ","\n\t\t[Erro] Escolha uma opção: -> ");
    return choice;
}

void DisplayMessage(char *msg)
{
    printf("\n\t\t+-----------------------------------------------------------------------------------+");
    printf("\n\t\t| %s",msg);
    printf("\n\t\t+-----------------------------------------------------------------------------------+\n");
}

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

int DisplayOperations(Operations *lst, char *msg, char *errMsg)
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

void DistplaySubOperations(OperationsLst *lst)
{
    SubOperations *ptr = lst->first;
    while (ptr) {
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->numMachine, ptr->time);
        ptr = ptr->next;
    }
}

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

void ShowFirst(Operations *lst)
{
    OperationsLst *ptr = lst->first;
    while (ptr) {
        printf("\n\t\tOperação -> %d", ptr->numOperation);
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->first->numMachine, ptr->first->time);
        ptr = ptr->next;
    }

}
void ShowLast(Operations *lst)
{
    OperationsLst *ptr = lst->first;
    while (ptr) {
        printf("\n\t\tOperação -> %d", ptr->numOperation);
        printf("\t\tMáquina número [%d] com uma duração de [%d]\n", ptr->last->numMachine, ptr->last->time);
        ptr = ptr->next;
    }

}