/**
 * @file mainf.h
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

#ifndef mainf
#define mainf

/**
 * @brief hello 
 * 
 */
void InitializeComponent();

/**
 * @brief This function is an evaluator of users inputs that only accepts inputs of type integer, also content custom message and error message
 * This functions 
 * @param msg Message to display the user about some element of type integer
 * @param msgErr Error message to show the user if the element inserted was not valid
 * @return int 
 */
int readInt(char *msg, char *msgErr);


/**
 * @brief This function is an evaluator of users inputs that only accepts inputs of type integer, also content custom message and error message
 * This functions 
 * @param msg Message to display the user about some element of type integer
 * @param msgErr Error message to show the user if the element inserted was not valid
 * @return int 
 */
char *readString(const char *msg, const char *msgErr);



/**
 * @brief In this function the program to be displayed to the user in the option of reading or writing in a file and the option of choosing the name of the file.
 * 
 * @param lst List to import/export all data to file or form a file
 * @param msg Variable to display the response menssage to the users
 * @param type Determines whether it is the read or save function
 * @return Operations* 
 */
Operations *FilesInterpreter(Operations *lst, Message *msg, int type);

/**
 * @brief In this function the program to be displayed to the user in the option of reading or writing in a file and the option of choosing the name of the file.
 * 
 * @param lst List to import/export all data to file or form a file
 * @param msg Variable to display the response menssage to the users
 * @param type Determines whether it is the read or save function
 * @return Operations* 
 */
Operations *InsertOp(Operations *lst, Message *msg);

/**
 * @brief This operation gives the user the option to delete an entire job from the list
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
Operations *DeleteOperation(Operations *lst, Message *msg);

/**
 * @brief This operation gives the user the option to change a given data of an operation
 * 
 * @param lst list with all the data 
 * @param msg Variable to display the response menssage to the users
 * @return Operations* 
 */
Operations *ChangeOperation(Operations *lst, Message *msg);

#endif