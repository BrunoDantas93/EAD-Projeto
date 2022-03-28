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
#include "src/lib/files.h"
#include "src/lib/mainf.h"
#include "src/lib/menu.h"


int main()
{
    InitializeComponent();
    /*ProcessPlan **Hash = calloc(msg->M, sizeof(ProcessPlan*));
    
    filesRead(Hash, msg, "src/data/processplan2.txt");

    time(&end);
    time_t elapsed = end - begin;
    
    
    printf("Time measured: %ld seconds.\n", elapsed);

    stats(Hash, msg);

    for (int i = 0; i < msg->M; i++)
    {
        printf("--------%d--------\n", (*(Hash+i))->ProcessPlanID);
        list_queue(*(Hash+i));
        printf("------------------\n");
    }*/
    
    system("pause");
    return 0;
}