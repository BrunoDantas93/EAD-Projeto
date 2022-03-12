#ifndef jobs
#define jobs

typedef struct _SubOperations
{
    int numMachine;
    int time;
    struct _SubOperations *prev, *next;

}SubOperations;

typedef struct _OperationsLst
{
    int numOperation;
    int TotalSubOperation;

    struct _SubOperations *first, *last;
    struct _OperationsLst *prev, *next;

}OperationsLst;

typedef struct _Operations
{
    struct _OperationsLst *first, *last;
}Operations;

typedef struct _Message
{  
    bool type;
    char message[1000];
}Message;

Operations *newOperation(Message *msg);
Operations *Operations_List(Operations *lst, Message *msg, int numOperations);
OperationsLst *insertOperation(OperationsLst *lst, Message *msg, int numOperations);
Operations *CheckOperations(Operations *lst, Message *msg, int numOperation, int numMachine, int time);
OperationsLst *InsertSubOperation(OperationsLst *lst, Message *msg, int numMachine, int time);
SubOperations *addSubOperations(SubOperations *lst, Message *msg, int numMachine, int time);
Operations *OperationsRemove(Operations *lst, Message *msg, int element);
Operations *RearrangeElements(Operations *lst);
void MinimumTimeUnits(Operations *lst, Message *msg);
void MaximumTimeUnits(Operations *lst, Message *msg);
void AverageTimeUnits(Operations *lst, Message *msg);

#endif
