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

int main()
{
	  
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
	
    InitializeComponent();

    SetConsoleOutputCP(CPAGE_DEFAULT);
	
}
