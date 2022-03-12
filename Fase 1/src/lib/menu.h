#ifndef menus
#define menus

int Menu();

void DisplayMessage(char *msg);

void ReturnMenu();

bool ChoiceMenu();

int DisplayOperations(Operations *lst, char *msg, char *errMsg);

void DistplaySubOperations(OperationsLst *lst);

SubOperations *DisplaySubOperationsChoice(OperationsLst *lst, char *msg, char *errMsg);

int SubOperationsChoice();

void ShowFirst(Operations *lst);

void ShowLast(Operations *lst);

#endif