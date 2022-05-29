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
 * @brief This structure will store the data of the calculations of a scheduling proposal.
 *  
 */
typedef struct _MapOperations{
    int jobID; /** Number: Identifier of the job*/
    int OperationID; /** Number: Identifier of the operation*/
    bool tested;
    SubOperations *first; /**SubOperations: Pointer to first element of the operation*/
    SubOperations *position; /**SubOperations: Pointer to the actual element of the operation*/
    SubOperations *selected; /**SubOperations: Pointer to the selected element of the operation */
    struct _MapOperations *next; /** _MapOperations: Pointer to the next element of the list*/
} MapOp;

/**
 * @brief This operation gives to the program o number max of operations
 * 
 * @param lst list with all the data 
 * @return max* 
 */
int MaxOperation(ProcessPlan *lst);

/**
 * @brief This operation verify if the jobid is in the list.
 * 
 * @param lst list with all the data 
 * @param msg list with the date to display to the user
 * @param ProcessPlan_Operations list with all the data 
 * @return boolean 
 */
int existInList(MapOp *lst, Message *msg, int ProcessPlan_Operations);

/**
 * @brief This operation verify if the machine is not in use on the map.
 * 
 * @param cell list with all the data 
 * @param msg list with the date to display to the user
 * @param machineid number that identifies the machine 
 * @param jobid number that identifies the job
 * @return boolean 
 */
MapOp *CheckMachine(MapOp *cell, Message *msg, int machineid, int jobid);

/**
 * @brief This operation verify if the machine is not in use on the map.
 * 
 * @param lst list with all the data 
 * @param msg list with the date to display to the user
 * @return the map 
 */
int MapProcessPlan(ProcessPlan *lst, Message *msg);


#endif