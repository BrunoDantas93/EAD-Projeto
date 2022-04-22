#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"
#include "../lib/escalation.h"


int MaxOperation(ProcessPlan *lst)
{
    int max = -1;
    Operations *ptr = lst->first;
    while(ptr){
        if(max < ptr->TotalOperation) 
            max = ptr->TotalOperation; 
        ptr = ptr->next;
    }   
    return max;
}

int existInList(MapPP *lst, Message *msg, int ProcessPlan_Operations)
{
    msg->type = false;
    
    if(lst==NULL) return 0;
    
    if(lst->numSteps == ProcessPlan_Operations){
        msg->type = true;
        return 0;
    }

    return 0;
}

void MapPaths(MapOp *lst, Message *msg)
{
    /**
        //* Verificar o melhor percurso para completar o process plan
        //! Vereficar se a maquina está disponível
        //! Se nao estiver disponível e o current nao tiver proximo testar no outro e guardar o current
            //! Se o anterior nao tiver proximo Matar o programa.
            
    */ 
   




}

void MapProcessPlan(ProcessPlan *lst, Message *msg)
{
    int totOp = MaxOperation(lst);
    printf("totOp = %d\n",totOp);
    MapPP **MapSteps = calloc(totOp, sizeof(MapPP*));

    Operations *ptr = lst->first;
    while (ptr){
        OperationsLst *oLst = ptr->first;
        int xp = 0;
        while (oLst){
            
            existInList(MapSteps[xp], msg, oLst->numOperation);
            
            if(msg->type == false){
                MapPP *cell = (MapPP *)malloc(sizeof(MapPP));
                cell->ProcessPlanID = lst->ProcessPlanID;
                cell->numSteps = oLst->numOperation;
                cell->totalOperations = 0;
                cell->ptr = NULL;
                cell->start = NULL;
                MapSteps[xp] = cell;                
            }

            
            MapOp *cell2 = (MapOp *)malloc(sizeof(MapOp));
            cell2->Operations_ProcessPlanID = ptr->ProcessPlan_Operations;
            cell2->OperationID = oLst->numOperation;
            cell2->first = oLst->first;
            cell2->next = MapSteps[xp]->ptr;
            MapSteps[xp]->ptr = cell2;
            MapSteps[xp]->totalOperations++;
            
            //printf("%s",msg->type == false ? "false" : "true");
            printf("ProcessPlan_Operations %d numOperation %d Maquina %d Time %d\n", ptr->ProcessPlan_Operations, oLst->numOperation, oLst->first->numMachine, oLst->first->time);
            xp++;
            oLst = oLst->next;
        }
       ptr = ptr->next; 
    }
    printf("\n\nExit\n");
    //printf("ProcessPlan_Operations %d numOperation %d \n", MapSteps[0]->ProcessPlanID, MapSteps[0]->numSteps);
    
    for(int i = 0; i < totOp; i++){
        printf("POS %d ProcessPlanID %d numOperation %d totalOperations %d\n", i, MapSteps[i]->ProcessPlanID, MapSteps[i]->numSteps, MapSteps[i]->totalOperations);
        MapOp *ptr = MapSteps[i]->ptr;
        while(ptr){
            printf("\t\tOperations_ProcesPlan %d OperationID %d Maquina %d Time %d \n", ptr->Operations_ProcessPlanID, ptr->OperationID, ptr->first->numMachine, ptr->first->time);
            ptr = ptr->next;
        }
    }

}