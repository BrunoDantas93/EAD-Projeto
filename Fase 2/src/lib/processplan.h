/**
 * @file processplan.h
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This file will contain all the identification of the functions to manipulate the structure of process plan.
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef processplan
#define processplan

/**
 * @brief Stores all process plans and pointers to their corresponding operations  
 * 
 */
typedef struct _ProcessPlan
{
    int ProcessPlanID;  /** Number: plan process identifier  */
    struct _ProcessPlan *next; /** Next process plan */
    
}ProcessPlan;

/**
 * @brief 
 * 
 */
typedef struct _Message
{  
    bool type; /** MessageType: Message type success or error */
    int M; /** Hash length */
    char message[1000]; /** Message: Contains the message to present to the user*/
}Message;





/**
 * @brief Generates a value to identify a position in the hashtable to insert the new process plan 
 * 
 * @param str String to use as a basis for creating the number  
 * @return int position identifier in the hashtable
 */
int MagicNumber( Message *msg, const char* str);

/**
 * @brief Create the position on hash table to insert the value
 * 
 * @param hash hast with the pointers to the lists 
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 */
void insert_hash(ProcessPlan **hash, Message *msg, int processplanID);

/**
 * @brief Insert the value into the list 
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan *insert_list(ProcessPlan* lst, Message *msg, int processplanID);

/**
 * @brief Checks if the value exists within the hash 
 * 
 * @param hash hast with the pointers to the lists 
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan * exists_in_hash(ProcessPlan **hash, Message *msg, int processplanID);

/**
 * @brief  Checks if the value exists within the list
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param processplanID process plan identifier
 * @return ProcessPlan* 
 */
ProcessPlan * exists_in_list(ProcessPlan *lst, Message *msg, int processplanID);

#endif
