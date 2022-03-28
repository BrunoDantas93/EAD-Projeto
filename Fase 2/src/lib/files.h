/**
 * @file files.h
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This is the file where we will manipulate the text files
 * @version 1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * In this file the program will create/write and read the test file
 * 
 * 
 */

#ifndef files1
#define files1



/**
 * @brief loops through the file to see how many process plans there are 
 * 
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file that contains the data
 * @return int 
 */
void HashSize(Message *msg, char *filename);

/**
 * @brief Function to read the data from a file.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file that contains the data
 * @return Operations* 
 */
int filesRead(ProcessPlan **Hash, Message *msg, char *filename);

/**
 * @brief Function to write the data from the list.
 * 
 * @param lst list where we will store the data
 * @param msg variable for the message type and its corresponding messages
 * @param filename name of the file where will save the data 
 * @return int 
 */
int filesWrite(ProcessPlan **Hash, Message *msg, char *filename);

#endif