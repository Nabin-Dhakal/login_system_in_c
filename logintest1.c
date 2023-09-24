#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct
{
    char username[100];
    char password[16];
} User;

User user[50];
int usercount = 0, maxuser = 10;

/* Load user data into array from file */
int loaduserdata()
{
    FILE *fp = NULL;
    fp = fopen("database.txt", "a+");
    if (fp == NULL)
    {
        perror("Failed to open the file");
        return 1;
    }
    while (fscanf(fp, "%s %s", user[usercount].username, user[usercount].password) == 2)
    {
        usercount++;
    }
    fclose(fp);
    return 0;
}
int register_account()
{
    char username[100];
    char password[16];
    FILE *fp = NULL;
    fp = fopen("database.txt", "a");
    printf("enter username: ");
    scanf("%s", username);
    printf("enter password: ");
    scanf("%s", password);
    fprintf(fp, "\n%s %s", username, password);
    fclose(fp);
    return 0;
}
/* Checking credentials of given inputs */
bool check_credentials(char *username, char *password)
{
    for (int i = 0; i < usercount; i++)
    {
        if (strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int n;
    printf("                        ****welcome to Chat- Hub *******\n");
        while(1){
    printf(" 1. login with existing account \n 2. Register an account \n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        if (loaduserdata() == 1)
        {
            perror("failed to load data");
            return 0;
        }

        char username[100];
        char password[16];

        printf("Enter username: ");
        scanf("%99s", username);

        printf("Enter password: ");
        scanf("%15s", password);
        if (check_credentials(username, password))
        {
            printf("Login was successful.\n");
        }
        else
        {
            printf("Username and password not found.\n");
        }
        break;
    case 2:
        register_account();
        break;
    case 81:
        return 0;
    default:
        printf("Wrong input");
        break;
    }
    }
    return 0;
}