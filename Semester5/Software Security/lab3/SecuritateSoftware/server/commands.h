#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <windows.h>


BOOLEAN
CmdHandleUser(
    char* User,
    int *UserId
    );


BOOLEAN
CmdHandlePass(
    int UserId,
    char *Password
    );

void
CmdHandleList(
    int UserId,
    char *Output,
    int *OutLength
);

BOOLEAN
CmdHandleInfo(
    int UserId,
    char *Details,
    char *Output,
    int *OutLength
    );

void
CmdHandleGet(
    int UserId,
    char *Message,
    char *Output,
    int *OutLength
    );

DWORD
CmdHandlePutmsg(
    int UserId,
    char *Buffer,
    int Length
    );

void
CmdHandleSrvlogin(
    char *Output,
    int *OutLength
    );

BOOLEAN
CmdHandleRandQ(
    char* Param,
    char *Output,
    int *OutLength
);

BOOLEAN
CmdHandleRand(
    char* Param,
    char *Output,
    int *OutLength
);

#endif _COMMANDS_H_
