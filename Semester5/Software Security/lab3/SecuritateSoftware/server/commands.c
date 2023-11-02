#include "commands.h"
#include <stdio.h>
#include "data.h"
#include "server.h"
#include <time.h>

#define DEFAULT_MAX_PASS_LEN 40

int
ExceptionFilter(
    DWORD Code,
    EXCEPTION_POINTERS *ExceptionPointers
    )
{
    printf("[EXCEPTION] ExceptionCode=0x%x, EIP=0x%x, ESP=0x%x\n", Code, ExceptionPointers->ContextRecord->Eip, ExceptionPointers->ContextRecord->Esp);
    Log("[EXCEPTION] ExceptionCode=0x%x, EIP=0x%x, ESP=0x%p\n", Code, ExceptionPointers->ContextRecord->Eip, ExceptionPointers->ContextRecord->Esp);

    return EXCEPTION_EXECUTE_HANDLER;
}


BOOLEAN
CmdHandleUser(
    char* User,
    int *UserId
    )
{
    DWORD i;

    __try
    {
        //
        // Now search if the given username exists
        // 
        for (i = gUserCount-1; i >= 0; i--)
        {
            if (0 == _stricmp(gUserData[i].Username, User))
            {
                *UserId = i;
                return TRUE;
            }
        }
    }
    __except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
    {
    }

    *UserId = -1;
    return FALSE;
}


BOOLEAN
CmdHandlePass(
    int UserId,
    char *Password
    )
{
    char tempPass[DEFAULT_MAX_PASS_LEN];

    tempPass[0] = '\0';
    strcpy(tempPass, Password);

    if (0 == strcmp(gUserData[UserId].Password, tempPass))
    {
        return TRUE;
    }

    return FALSE;
}


void
_AddFileToOutput(
    char *File,
    char *Output,
    int *OutLength
    )
{
    int len = strlen(File);

    // Add file name to Output, but replace '.txt' with ' '
    strcat_s(Output, DEFAULT_BUFLEN, File);
    *OutLength += len - 3;
    Output[*OutLength - 1] = ' ';   //
    Output[*OutLength] = 0;         //
}


BOOLEAN
CmdHandleInfo(
    int UserId,
    char *Details,
    char *Output,
    int *OutLength
    )
{
    DWORD param = 1;
    DWORD fields;
    WORD size;
    BOOLEAN ret = TRUE;
    int i;

    __try
    {
        fields = sscanf_s(Details, "%d", &param);           // Get the number of fields to return
        size = (WORD)(fields * param * FIELD_SIZE);         // 'fields' should be 1 (one field identified by sscanf_s), 'param' - number of fields to return
                                                            // If either of those is 0, nothing will be returned
        if (param > 3)
        {
            //
            // Make sure we don't return more than needed (size will be maximum 3 * FIELD_SIZE = 75)
            //
            ret = FALSE;
            __leave;
        }

        *OutLength = size;
        printf("size = %d\n", size);

        //
        // Copy in Output the computed size
        //
        for (i = 0; i < size; i++)
        {
            Output[i] = ((char*)(&gUserData[UserId]))[i];
        }

        ret = TRUE;
    }
    __except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
    {   
    }

    return ret;
}


void
CmdHandleList(
    int UserId,
    char *Output,
    int *OutLength
    )
{
    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind;
    char folder[32];

    sprintf_s(folder, 20, ".\\%d\\*.txt", UserId);
    printf("Searching in folder: %s\n", folder);

    hFind = FindFirstFileA(folder, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
        return;
    } 

    //printf ("The first file found is %s\n", FindFileData.cFileName);
    _AddFileToOutput(FindFileData.cFileName, Output, OutLength);

    while (FindNextFileA(hFind, &FindFileData))
    {
        //printf ("The next file found is %s\n", FindFileData.cFileName);
        _AddFileToOutput(FindFileData.cFileName, Output, OutLength);
    }

    //printf("That's it\n");

    FindClose(hFind);
}


void
CmdHandleGet(
    int UserId,
    char *Message,
    char *Output,
    int *OutLength
    )
{
    FILE *file;
    char filename[64];

    sprintf_s(filename, 64, ".\\%d\\%s.txt", UserId, Message);

    printf("Opening file: %s\n", filename);

    fopen_s(&file, filename, "r");
    if (NULL == file)
    {
        sprintf_s(Output, DEFAULT_BUFLEN, "[ERROR] Message not found.");
        *OutLength = strlen(Output);

        printf("Error opening message file\n");
        return;
    }

    //printf("Success!\n");

    sprintf_s(Output, DEFAULT_BUFLEN, "[OK]\n");
    *OutLength = strlen(Output);

    *OutLength += fread_s(&Output[*OutLength], DEFAULT_BUFLEN, 1, DEFAULT_BUFLEN, file);

    ///
    fclose(file);
}


DWORD
CmdHandlePutmsg(
    int UserId,
    char *Buffer,
    int Length
    )
{
    char filepath[50];
    FILE *f = NULL;
    char* file = Buffer;
    char* bin = Buffer;
    int buflen = 0;

    UNREFERENCED_PARAMETER(UserId);
    UNREFERENCED_PARAMETER(Buffer);

    // First part of buffer is the file name, following the binary content of the file
    while (*bin != ' ') bin++;
    *bin++ = 0;
    // now, file points only to the file name, and bin to its binary contents

    // compute the length of the binary file
    buflen = Length - (int)((long long)bin - (long long)file);

    //printf("file: %s, bin: %s\n", file, bin);

    // create the path and write the binary data to the file
    snprintf(filepath, 49, ".\\%d\\%s.txt", UserId, file);
    printf("%s (buflen=%d)\n", filepath, buflen);

    if (0 != fopen_s(&f, filepath, "wb"))
    {
        printf("can't open file: %s\n", filepath);
        return 0;
    }

    fwrite(bin, 1, buflen, f);
    fclose(f);

    return 0;
}

void
CmdHandleSrvlogin(
    char *Output,
    int *OutLength
    )
{
    HMODULE hServerlib = INVALID_HANDLE_VALUE;
    char username[100];
    BOOLEAN(*Imported_GetUsername)(char*, DWORD) = NULL;

    hServerlib = LoadLibraryA("serverlib.dll");
    if (NULL == hServerlib)
    {
        snprintf(Output, DEFAULT_BUFLEN, "[ERROR] LoadLibrary('serverlib.dll') failed!\n");
        *OutLength = strlen(Output);

        return;
    }

    Imported_GetUsername = (BOOLEAN(__cdecl*)(char*, DWORD))GetProcAddress(hServerlib, "GetUsername");
    if (NULL == Imported_GetUsername)
    {
        snprintf(Output, DEFAULT_BUFLEN, "[ERROR] GetProcAddress(hServerlib, 'GetUsername') failed!\n");
        *OutLength = strlen(Output);

        return;
    }

    if (Imported_GetUsername(username, 100))
    {
        snprintf(Output, DEFAULT_BUFLEN, "[OK] Server is logged in with username: %s\n", username);
        printf("%s\n", Output);
        *OutLength = strlen(Output);
    }
    else
    {
        snprintf(Output, DEFAULT_BUFLEN, "[ERROR] Can't get username used by server!\n");
        *OutLength = strlen(Output);
    }

    FreeLibrary(hServerlib);
}

BOOLEAN
CmdHandleRand(
    char* Param,
    char *Output,
    int *OutLength
)
{
    BOOLEAN ret = TRUE;
    DWORD howMany = 0;
    BYTE i = 0;
    char buff[32] = { 0 };

    srand((unsigned int)time(NULL));

    __try
    {
        Output[0] = 0;
        *OutLength = 0;

        sscanf_s(Param, "%d", &howMany);

        strcat(Output, "[Random numbers]\r\n");
        *OutLength += strlen(Output);

        for (i = 0; i < howMany; i++)
        {
            sprintf_s(buff, sizeof(buff), "%d\r\n", rand());

            strcat(Output, buff);

            *OutLength += strlen(buff);
        }

        ret = TRUE;
    }
    __except (ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
    {}

    return ret;
}

static
char *Quotes[] =
{
    "ana are mere",
    "ana nu mai are mere",
    "ana este programator bun",
    "ana scrie cod frumos"
};

BOOLEAN
CmdHandleRandQ(
    char* Param,
    char *Output,
    int *OutLength
)
{
    BOOLEAN ret = TRUE;
    int quoteIndex = 0;
    int maxQuotes = sizeof(Quotes);
    char buff[32] = { 0 };

    __try
    {
        Output[0] = 0;
        *OutLength = 0;

        sscanf_s(Param, "%d", &quoteIndex);

        strcat(Output, "[Random quote] ");
        *OutLength += strlen(Output);

        sprintf_s(buff, sizeof(buff), "%s\r\n", Quotes[quoteIndex % maxQuotes]);

        strcat(Output, buff);

        *OutLength += strlen(buff);

        ret = TRUE;
    }
    __except (ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
    {}

    return ret;
}
