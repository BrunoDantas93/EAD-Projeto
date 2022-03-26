/**
 * @file main.c
 * @author Bruno Dantas (a20807@alunos.ipca.pt)
 * @brief This is the main file of the project
 * @version 1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * \mainpage Description
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include "src/lib/jobs.h"
#include "src/lib/menu.h"
#include "src/lib/mainf.h"
#include "src/lib/files.h"

/**
 * @brief This is the main function
 * 
 * @return int 
 */
int main()
{	  
    UINT CPAGE_UTF8 = 65001; 
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
	
    InitializeComponent(); 

    SetConsoleOutputCP(CPAGE_DEFAULT);	
    return 0;
}
