/**
 * @file files.h
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief In this file, the calculations of a scheduling proposal for the FJSSP problem
 * @version 1
 * @date 2022-04-115
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * 
 */

#ifndef escalation
#define escalation

/**
 * @brief 
 * 
 */
/*typedef struct _auxList
{
    int operationID;
    int machine;
    int time;
    OperationsLst *list;
    ProcessPlan *pList;
    struct _auxList *next;

} AuxList;
typedef struct _MapOperation{
    int aa;
} MapOperation;

typedef struct _MapProcessPlan{
    int ProcessPlan;
    int steps;
} MapProcessPlan;

typedef struct _MapAux{
    int machine;
    int time;
    OperationsLst *oLst;
    SubOperations *subOp;
}MapAux;*/

//MapAux * tst(MapAux **aux, OperationsLst *lst, Message *msg, int stepCount);

//int dijkstra(ProcessPlan *lst, Message *msg, int target);
typedef struct _MapOperations{
    int Operations_ProcessPlanID;
    int OperationID;
    SubOperations *first;
    struct _MapOperations *next;
} MapOp;

typedef struct _MapPath{
    int Operations_ProcessPlanID;
    int OperationID;
    SubOperations *Subnext;
    struct _MapPath *next;
} MapPath;


typedef struct _MapProcessPlan{
    int ProcessPlanID;
    int numSteps;
    int totalOperations;
    MapOp *ptr;
    MapPath *start;
} MapPP;



void MapProcessPlan(ProcessPlan *lst, Message *msg);






#endif