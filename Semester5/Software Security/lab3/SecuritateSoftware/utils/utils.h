#ifndef _UTILS_H_
#define _UTILS_H_

#include <windows.h>

#define FIELD_SIZE      25
typedef struct _USER_DATA
{
    char Username[FIELD_SIZE];
    char Name[FIELD_SIZE];
    char Email[FIELD_SIZE];
    char Password[FIELD_SIZE];
} USER_DATA;

void
PrintBuffer(
    char *Buffer,
    int Length
    );

#endif // _UTILS_H_

