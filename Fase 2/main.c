/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "src/lib/processplan.h"
#include "src/lib/jobs.h"
#include "src/lib/escalation.h"
#include "src/lib/files.h"
#include "src/lib/mainf.h"
#include "src/lib/menu.h"


int main()
{
    UINT CPAGE_UTF8 = 65001; 
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
	
    InitializeComponent(); 

    SetConsoleOutputCP(CPAGE_DEFAULT);	
}