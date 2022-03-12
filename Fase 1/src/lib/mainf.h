#ifndef mainf
#define mainf

void InitializeComponent();
 
int readInt(char *msg, char *msgErr);

char *readString(const char *msg, const char *msgErr);

Operations *FilesInterpreter(Operations *lst, Message *msg, int type);

Operations *InsertOp(Operations *lst, Message *msg);

Operations *DeleteOperation(Operations *lst, Message *msg);

Operations *ChangeOperation(Operations *lst, Message *msg);

#endif