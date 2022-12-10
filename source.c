#include "header.h"

static account_t curr;
static FILE *myfile;

void print_menu(void)
{
    printf("\n\n\n\n\t\t-----------------Welcome to our Bank Managment System-------------------------\n");
    printf("\n\t\t-----------------Please select one of the following operations-----------------\n");
    printf("\n\t\t\t\t1 - Add a new account.\n");
    printf("\t\t\t\t2 - Modify an existing account.\n");
    printf("\t\t\t\t3 - Make a transaction.\n");
    printf("\t\t\t\t4 - Show all accounts.\n");
    printf("\t\t\t\t5 - Show a specifc account.\n");
    printf("\t\t\t\t6 - Delete an account.\n");
    printf("\t\t\t\t7 - Exit.\n\n");
    printf("\t\t-------------------------------------------------------------------------------\n");
}

void system_body(void)
{
    system("cls");
    int choice = 0;
    print_menu();
    printf("\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add_account();
        break;

    default:
        break;
    }
}

void add_account()
{
    system("cls");
    printf("Enter your name: ");
    getchar();
    gets(curr.name);
    fflush(stdin);
    printf("Enter your phone number: ");
    scanf("%d", &curr.phoneNum);
    do
    {
        getchar();
        printf("Enter your password: ");
        gets(curr.password);
        if (strlen(curr.password) < 8)
            printf("The password must be at least 8 characters\n");
    } while (strlen(curr.password) < 8);
    printf("Enter your balance: ");
    scanf("%d", &curr.balance);

    add_data_to_file();
}

void add_data_to_file(void)
{
    FILE *myfile;
    myfile = fopen("data.txt", "a");

    if (myfile)
    {
        fprintf(myfile, "%s %s %d %d\n", curr.name, curr.password, curr.phoneNum, curr.balance);
        fclose(myfile);
    }
    else
    {
        printf("There was an error opening the file!.\n");
        system_body();
    }
}
