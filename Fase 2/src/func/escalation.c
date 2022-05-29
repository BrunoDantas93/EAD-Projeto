#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../lib/processplan.h"
#include "../lib/jobs.h"
#include "../lib/escalation.h"

/**
 * @brief This operation gives to the program o number max of operations
 * 
 * @param lst list with all the data 
 * @return max* 
 */
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

/**
 * @brief This operation verify if the jobid is in the list.
 * 
 * @param lst list with all the data 
 * @param msg list with the date to display to the user
 * @param ProcessPlan_Operations list with all the data 
 * @return boolean 
 */
int existInList(MapOp *lst, Message *msg, int ProcessPlan_Operations)
{
    msg->type = false;
    
    if(lst==NULL) return 0;
    
    if(lst->OperationID == ProcessPlan_Operations){
        msg->type = true;
        return 0;
    }
    return 0;
}

/**
 * @brief This operation verify if the machine is not in use on the map.
 * 
 * @param cell list with all the data 
 * @param msg list with the date to display to the user
 * @param machineid number that identifies the machine 
 * @param jobid number that identifies the job
 * @return boolean 
 */
MapOp *CheckMachine(MapOp *cell, Message *msg, int machineid, int jobid){
    msg->type = false;
    while(cell){
        if(jobid != cell->jobID ){
            if(cell->selected){
                if (cell->tested == true){     
                    if(machineid == cell->selected->numMachine)
                    {
                        msg->type = true;
                        return cell; 
                    }           
                }
            }
        }
        cell = cell->next;
    }
    return 0;
}


/**
 * @brief This operation verify if the machine is not in use on the map.
 * 
 * @param lst list with all the data 
 * @param msg list with the date to display to the user
 * @return the map 
 */
int MapProcessPlan(ProcessPlan *lst, Message *msg)
{
    int totOp = MaxOperation(lst);
    MapOp **MapSteps = calloc(totOp, sizeof(MapOp*));

    int maxSubOp = 0;
    //Mapeia a lista por numero da operação
    Operations *ptr = lst->first;
    while (ptr){
        OperationsLst *oLst = ptr->first;
        if(oLst->TotalSubOperation > maxSubOp) maxSubOp = oLst->TotalSubOperation;

        int xp = 0;
        while (oLst){
            existInList(MapSteps[xp], msg, oLst->numOperation);
            
            if(msg->type == false){
                MapOp *cell = (MapOp *)malloc(sizeof(MapOp));
                cell->jobID = ptr->ProcessPlan_Operations;
                cell->OperationID = oLst->numOperation;
                cell->tested = false;
                cell->selected = NULL;
                cell->position = oLst->first;
                cell->first = oLst->first;
                cell->next = NULL;
                MapSteps[xp] = cell; 
            }
            else{ 
                MapOp *cell = (MapOp *)malloc(sizeof(MapOp));
                cell->jobID = ptr->ProcessPlan_Operations;
                cell->OperationID = oLst->numOperation;
                cell->tested = false;
                cell->selected = NULL;
                cell->position = oLst->first;
                cell->first = oLst->first;
                cell->next = MapSteps[xp];
                MapSteps[xp] = cell;
            }
            
            xp++;
            oLst = oLst->next;
        }
       ptr = ptr->next; 
    } 
    
    bool status = true;
    //Testas disponibilidade das maquias
    for(int i = 0; i < totOp; i++){
        MapOp *cell = MapSteps[i];
        while(cell){
            if (cell->tested == false)
            {
                bool running = true;
                int breakpoint = 0;
                do{
                    MapOp *ptr = CheckMachine(MapSteps[i], msg, cell->position->numMachine, cell->jobID);
                    if(msg->type == false){
                        cell->tested = true;
                        cell->selected = cell->position;
                        running = false;
                    }
                    else{
                        int diff = ptr->selected->time - cell->position->time;
                        
                        if(diff <= 0 ){
                            if(cell->position->next)
                            { cell->position = cell->position->next; }
                            else cell->position = cell->first;
                        }else{ 
                            cell->tested = true;
                            cell->selected = cell->position;
                            cell->position = cell->first;

                            MapOp *rld = MapSteps[i];
                            while(rld){
                                if(rld->jobID == ptr->jobID){
                                    rld->tested = false;
                                    rld->position = rld->first;
                                    rld->selected = NULL;
                                }
                                rld = rld->next;
                            }
                            cell = MapSteps[i];
                        }

                    } 
                    breakpoint++;
                    if(breakpoint == (totOp*maxSubOp)+1000){
                        return -1;
                    }                   
                }while(running == true);

            }
            cell = cell->next;
        }
    }
    if(status == true)
    {
        char head[1000] = "<tr><th>Process Plan</th>";
        char body[1000] = "";
        for (int i = 1; i <= totOp+2; i++){ sprintf(head, "%s<th>Job_ID %i</th>", head, i);}

        for(int i = 0; i < totOp; i++){
            MapOp *cell = MapSteps[i];
            int x = 1;
            
            
            while(cell){
                if(x == 1){
                    sprintf(body, "%s<tr><td>Operation number %i</td>", body, cell->OperationID);
                }
                
                if(x != cell->jobID){
                    sprintf(body, "%s<td> </td>", body);
                }

                sprintf(body, "%s<td>[%d](%d)</td>", body, cell->selected->numMachine, cell->selected->time);
                cell = cell->next;
                x++;
            }
            sprintf(body, "%s</tr>", body);
        }
        
        sprintf(head, "%s</tr>", head);
        char htmlhead[1000] = "<!DOCTYPE html><html><head><title>HTML Table Generator</title> <style>table {	border:1px solid #b3adad;	border-collapse:collapse;	padding:5px;}table th {	border:1px solid #b3adad;	padding:5px;	background: #f0f0f0;	color: #313030;}table td {	border:1px solid #b3adad;	text-align:center;	padding:5px;	background: #ffffff;	color: #313030;}</style></head><body><table><thead>";
        char mid[1000] = "</thead><tbody>";
        char end[1000] = "</tbody></table></body></html>";

        char fullhtml[1000] = "";
        sprintf(fullhtml, "%s%s%s%s%s", htmlhead, head, mid, body, end);
        FILE *fptr = fopen("index.html", "w+");
        fprintf(fptr,"%s",fullhtml);
        fclose(fptr);
        msg->type = true;
        sprintf(msg->message,"O plano foi criado com sucesso");
    }else{ sprintf(msg->message,"O plano nao foi criado com sucesso"); }

    return 0;
}