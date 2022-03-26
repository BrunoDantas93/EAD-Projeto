/**
 * @file jobs.h
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This file will contain all the main functions of the program.
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 *  
 */

#ifndef jobs
#define jobs


/**
 * @brief This structure will store the data of the alternatives to perform an operation in an orderly way from the shortest time to the longest.
 *  
 */
typedef struct _SubOperations
{
    int numMachine; /** Number: Identifier of the machine*/
    int time; /** Number: Time oro complete the operation */
    struct _SubOperations *prev, *next; /** SubOperations: pointers to the next and previous element in the list */

}SubOperations;

/**
 * @brief All operation identifiers will be stored in the structure, taking care that these identifiers are unique, it will also store two pointers to the first and last element of the structure
 *  
 */
typedef struct _OperationsLst
{
    int numOperation; /* Number: Identifier if the operation */
    int TotalSubOperation;

    struct _SubOperations *first, *last; /** SubOperations: Pointer to the first and last element of the list */
    struct _OperationsLst *prev, *next; /** OperationsLst: pointers to the next and previous element in the list */

}OperationsLst;

/**
 * @brief This structure is auxiliary to the Operations structure, its function is to store the pointer to the first and last element of the List
 * 
 */
typedef struct _Operations
{
    struct _OperationsLst *first, *last; /** OperationsLst: Pointer to the first and last element of the list */
}Operations;

/**
 * @brief 
 * 
 */
typedef struct _Message
{  
    bool type; /** MessageType: Message type success or error */
    char message[1000]; /** Message: Contains the message to present to the user*/
}Message;


/**
 * @brief
 * 
 * @param msg variable for the message type and its corresponding messages
 * @return Operations* 
 */
Operations *newOperation(Message *msg);

/**
 * @brief This function looks for the position to insert the new operation identifier in the list in order from smallest to largest
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @return Operations* 
 */
Operations *Operations_List(Operations *lst, Message *msg, int numOperations);

/**
 * @brief This function inserts new operation identifiers.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @return OperationsLst* 
 */
OperationsLst *insertOperation(OperationsLst *lst, Message *msg, int numOperations);

/**
 * @brief This function looks for the position that has the same operation identifier to insert new alternatives to perform the operation with different machines and times.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numOperations operation identifier
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return Operations* 
 */
Operations *CheckOperations(Operations *lst, Message *msg, int numOperation, int numMachine, int time);

/**
 * @brief This function looks for the position to insert the new alternatives in the list in order 
 * from shortest time to longest time to complete the operation
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return OperationsLst* 
 */
OperationsLst *InsertSubOperation(OperationsLst *lst, Message *msg, int numMachine, int time);

/**
 * @brief Insert the new alternatives in the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param numMachine machine identifier
 * @param time time to complete the operation
 * @return OperationsLst* 
 */
SubOperations *addSubOperations(SubOperations *lst, Message *msg, int numMachine, int time);

/**
 * @brief Remove  element from the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param element Element to be removed from the list
 * @return Operations* 
 */
Operations *OperationsRemove(Operations *lst, Message *msg, int element);

/**
 * @brief Remove the element that was changed to be able to sort the list in an orderly way
 * 
 * @param ptr list where we will store the data 
 * @return Operations* 
 */
Operations *RearrangeElements(Operations *lst);

/**
 * @brief Determines the minimum amount of time units needed to complete the job
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
void MinimumTimeUnits(Operations *lst, Message *msg);

/**
 * @brief Determines maximum amount of time units needed to complete the job
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
void MaximumTimeUnits(Operations *lst, Message *msg);

/**
 * @brief Determines the average amount of time units required to complete an operation,
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 */
void AverageTimeUnits(Operations *lst, Message *msg);

#endif
