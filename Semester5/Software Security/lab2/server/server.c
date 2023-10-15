#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\utils\utils.h"
#include "commands.h"
#include "data.h"
#include "server.h"

#define DEFAULT_PORT    "44011"

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#define CMD_EXIT        "exit"
#define CMD_USER        "user"
#define CMD_PASS        "pass"
#define CMD_LOGOFF      "logoff"
#define CMD_LIST        "list"
#define CMD_GET         "get"
#define CMD_AVAIL       "avail"
#define CMD_INFO        "info"
#define CMD_PUT         "put"
#define CMD_SRVLOGIN    "srvlogin"

typedef enum {
    CONN_INVALID = 0x10001001,
    CONN_UNAUTHENTICATED,       // Can change to: CONN_USER_OK (if 'user XXX' matches a correct user)
    CONN_USER_OK,               // Can change to: UNAUTHENTICATED (if 'pass XXX' fails too many times), or AUTHENTICATED (if 'pass XXX' matches correct password) 
    CONN_AUTHENTICATED,         // Can change to: UNAUTHENTICATED (if 'logoff' is given)
} CONNECTION_STATE;


CONNECTION_STATE connState = CONN_INVALID;

char recvbuf[DEFAULT_BUFLEN];
char sendbuf[DEFAULT_BUFLEN];


void Test()
{
    printf("*******************************************************\nS-a apelat functia cu numele Test!!!\n*******************************************************\n");
}

void SetReply(
    char *Output,
    int *OutLength,
    char *Message
    )
{
    sprintf_s(Output, DEFAULT_BUFLEN, Message);
    printf("Returning: %s\n", Output);
    *OutLength = strlen(Output);
}

void
Log(
    const char *Format,
    ...
    )
{
    char dest[128];
    va_list argptr;
    FILE *file;

    va_start(argptr, Format);
    vsprintf_s(dest, 128, Format, argptr);
    va_end(argptr);
    
    fopen_s(&file, "log.txt", "a");
    if (NULL != file)
    {
        fprintf(file, dest);
        fclose(file);
    }
    else
    {
        printf("Error opening log.txt file!\n");
    }
}


//
// Returns TRUE if we should continue processing otherwise, and FALSE otherwise (when 'exit' has been given).
//
BOOLEAN InterpretCommand(
    char *Command,
    char *Parameter,
    int ParameterLength,
    char *Output,
    int *OutLength,
    CONNECTION_STATE *State,
    int *UserId
    )
{
    UNREFERENCED_PARAMETER(UserId);
    UNREFERENCED_PARAMETER(Parameter);

    printf("[DEBUG] State = %d, Command = [%s], Parameter = [%s], UserId = %d\n", *State, Command, Parameter, *UserId);

    if (*State == CONN_UNAUTHENTICATED)
    {
        // Command = 'EXIT', Parameter = NULL
        if (0 == _stricmp(Command, CMD_EXIT))
        {
            *State = CONN_INVALID;
            SetReply(Output, OutLength, "[OK] Exiting.");
            return FALSE;
        }

        // Command = 'USER', Parameter = username
        if (0 == _stricmp(Command, CMD_USER))
        {
            if (NULL == Parameter)
            {
                SetReply(Output, OutLength, "[ERROR] No username provided.");
                return TRUE;
            }

            if (CmdHandleUser(Parameter, UserId))
            {
                *State = CONN_USER_OK;
                SetReply(Output, OutLength, "[OK] User is valid, provide password.");
                return TRUE;
            }

            SetReply(Output, OutLength, "[ERROR] Invalid user, try again.");
            return TRUE;
        }
    }

    if (*State == CONN_USER_OK)
    {
        // Command = 'EXIT', Parameter = NULL
        if (0 == _stricmp(Command, CMD_EXIT))
        {
            *State = CONN_INVALID;
            SetReply(Output, OutLength, "[OK] Exiting.");
            return FALSE;
        }

        // Command = 'USER', Parameter = username
        if (0 == _stricmp(Command, CMD_USER))
        {
            if (NULL == Parameter)
            {
                SetReply(Output, OutLength, "[ERROR] No username provided.");
                return TRUE;
            }

            if (CmdHandleUser(Parameter, UserId))
            {
                *State = CONN_USER_OK;
                SetReply(Output, OutLength, "[OK] User is valid, provide password.");
                return TRUE;
            }

            *State = CONN_UNAUTHENTICATED;
            *UserId = -1;
            SetReply(Output, OutLength, "[ERROR] Invalid user, try again.");
            return TRUE;
        }

        // Command = 'PASS', Parameter = password
        if (0 == _stricmp(Command, CMD_PASS))
        {
            if (NULL == Parameter)
            {
                SetReply(Output, OutLength, "[ERROR] No password provided.");
                return TRUE;
            }

            if (CmdHandlePass(*UserId, Parameter))
            {
                *State = CONN_AUTHENTICATED;
                SetReply(Output, OutLength, "[OK] Authentication successful.");

                Log("[LOGIN] User %s (%d) logged in\n", gUserData[*UserId].Username, *UserId);

                return TRUE;
            }

            Log("[AUTH] User %s (%d) failed to log in with password %s\n", gUserData[*UserId].Username, *UserId, Parameter);

            SetReply(Output, OutLength, "[ERROR] Wrong password.");
            return TRUE;
        }
    }

    if (*State == CONN_AUTHENTICATED)
    {
        // Command = 'LOGOFF', Parameter = NULL
        if (0 == _stricmp(Command, CMD_LOGOFF))
        {
            *State = CONN_UNAUTHENTICATED;
            SetReply(Output, OutLength, "[OK] Logged off.");

            Log("[LOGOFF] User %s (%d) logged off\n", gUserData[*UserId].Username, *UserId);

            *UserId = -1;

            return TRUE;
        }

        // Command = 'INFO', Parameter = NULL
        if (0 == _stricmp(Command, CMD_INFO))
        {
            // *State doesn't change

            *OutLength = 0;
            Output[0] = 0;

            if (NULL == Parameter)
            {
                SetReply(Output, OutLength, "[ERROR] No parameter given for 'info' command.");
                return TRUE;
            }

            if (!CmdHandleInfo(*UserId, Parameter, Output, OutLength))
            {
                SetReply(Output, OutLength, "[ERROR] Invalid parameter given for 'info' command.");
                return TRUE;
            }
            else
            {
                // Reply has been already set
            }

            return TRUE;
        }

        // Command = 'LIST', Parameter = NULL
        if (0 == _stricmp(Command, CMD_LIST))
        {
            // *State doesn't change

            *OutLength = 0;
            Output[0] = 0;

            SetReply(Output, OutLength, "[OK] Available messages: ");
            
            CmdHandleList(*UserId, Output, OutLength);

            return TRUE;
        }

        // Command = 'GET', Parameter = index
        if (0 == _stricmp(Command, CMD_GET))
        {
            // *State doesn't change

            if (NULL == Parameter)
            {
                SetReply(Output, OutLength, "[ERROR] No message index provided.");
                return TRUE;
            }

            CmdHandleGet(*UserId, Parameter, Output, OutLength);

            return TRUE;
        }

        // Command = 'PUTMSG', Parameter = received buffer
        if (0 == _stricmp(Command, CMD_PUT))
        {
            // *State doesn't change

            CmdHandlePutmsg(*UserId, Parameter, ParameterLength);

            SetReply(Output, OutLength, "[OK] Message has been stored, use 'list' or 'get' to see it.");

            return TRUE;
        }
    }

    if (0 == _stricmp(Command, CMD_SRVLOGIN))
    {
        CmdHandleSrvlogin(Output, OutLength);

        return TRUE;
    }
    else if (0 == _stricmp(Command, CMD_AVAIL))
    {
        switch(*State)
        {
        case CONN_UNAUTHENTICATED:
            SetReply(Output, OutLength, "[OK] Available commands: exit, user");
            break;
        case CONN_USER_OK:
            SetReply(Output, OutLength, "[OK] Available commands: pass, user, exit");
            break;
        case CONN_AUTHENTICATED:
            SetReply(Output, OutLength, "[OK] Available commands: info, logoff, list, get, putmsg");
            break;
        }
        return TRUE;
    }

    SetReply(Output, OutLength, "[ERROR] Invalid command.");

    return TRUE;
}


BOOLEAN
ProcessCommand(
    char *Input,
    int InLength,
    char *Output,
    int *OutLength,
    CONNECTION_STATE *State,
    int *UserId
    )
{
    int i = 0;
    int paramIndex = 0;

    PrintBuffer(Input, InLength);

    // Search the end of the command
    while ((Input[i] != ' ') && (i < InLength)) {i++;};

    // Check if we are at the end of the received buffer
    if (i == InLength)
    {
        // Comanda fara parametri
        Input[i] = 0;
        return InterpretCommand(Input, NULL, 0, Output, OutLength, State, UserId);
    }

    Input[i] = 0;
    i++;

    // Skip all spaces
    while ((Input[i] == ' ') && (i < InLength)) {i++;};

    // Check if we are at the end of the received buffer
    if (i == InLength)
    {
        // Only spaces, no parameter
        return InterpretCommand(Input, "", 0, Output, OutLength, State, UserId);
    }

    paramIndex = i;
    Input[InLength] = 0;

    //printf("[%s] [%s] %d\n", Input, &Input[paramIndex], paramIndex);

    return InterpretCommand(Input, &Input[paramIndex], InLength - paramIndex, Output, OutLength, State, UserId);
}


int main(int argc, char* argv[])
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;

    int sendSize = 0;
    int recvbuflen = DEFAULT_BUFLEN;
    
    struct sockaddr_in clientInfo;
    int size = sizeof(clientInfo);

    int userId = -1;

    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Listening on port %s...\n\n", DEFAULT_PORT);
    //printf("connState=%x\n", (DWORD)&connState);
    Log("Server started and listening on port %s\n", DEFAULT_PORT);

    // Accept a client socket
    ClientSocket = accept(ListenSocket, (struct sockaddr *)&clientInfo, &size);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    {
        char *connected_ip= inet_ntoa(clientInfo.sin_addr); 
        int port = ntohs(clientInfo.sin_port);
        printf("Connected client: %s:%d\n", connected_ip, port);
    }

    connState = CONN_UNAUTHENTICATED;

    // Receive until the peer shuts down the connection
    do
    {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {
            printf(">>>\n");
            printf("Bytes received: %d\n", iResult);

            if (!ProcessCommand(recvbuf, iResult, sendbuf, &sendSize, &connState, &userId))
            {
                iResult = 0;
            }

            // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, sendbuf, sendSize > DEFAULT_BUFLEN ? DEFAULT_BUFLEN : sendSize, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
            printf("<<<\n\n");
        }
        else if (iResult == 0)
        {
            printf("Connection closing...\n");
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}

