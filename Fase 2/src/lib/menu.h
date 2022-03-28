/**
 * @file menu.h
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

#ifndef menus
#define menus



int FirstMenu();

/**
 * @brief This is main menu to navegate to the functions of the program
 * 
 * @return int 
 */
int Menu();

/**
 * @brief This is the menu to display all the messages to the user
 * 
 * @param msg 
 */
void DisplayMessage(char *msg);


/**
 * @brief This menu gives when using the option to continue in the program or if you want to exit
 * 
 */
void ReturnMenu();


/**
 * @brief This is a menu to ask the user if he wants to continue adding sub-operations or if he wants to stop
 * 
 * @return true 
 * @return false 
 */
bool ChoiceMenu();


/**
 * @brief Shows the user all the operations and gives him the option to choose the operation to use in the rest of the functions
 * 
 * @param lst list with all the data
 * @param msg Contains the message to show the user
 * @param errMsg Contains the error message to show the user
 * @return int 
 */
int DisplayOperations(ProcessPlan *lst, char *msg, char *errMsg);


/**
 * @brief Sow all the sub-operations
 * 
 * @param lst list with all the data
 */
void DistplaySubOperations(OperationsLst *lst);


/**
 * @brief Shows the user all the Sub-operations and gives him the option to choose the sub-operation to use in the rest of the functions
 * 
 * @param lst list with all the data
 * @param msg Contains the message to show the user
 * @param errMsg Contains the error message to show the user
 * @return int 
 */
SubOperations *DisplaySubOperationsChoice(OperationsLst *lst, char *msg, char *errMsg);

/**
 * @brief Show the user all the options they have to be able to change a suboption
 * 
 * @return int 
 */
int SubOperationsChoice();

/**
 * @brief Show the fastest operations to complete at work
 * 
 * @param lst 
 */
//void ShowFirst(Operations *lst);

/**
 * @brief Show the slowest operations to complet on job
 * 
 * @param lst 
 */
//void ShowLast(Operations *lst);

#endif