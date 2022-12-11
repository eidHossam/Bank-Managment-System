#include "header.h"

static account_t curr;
static FILE *myfile;
static char name[NAME_MAX];
static UINT16 id;

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

    case 4:
        print_account_data();
        break;

    default:
        break;
    }
}

void add_account()
{
    system("cls");

// To eliminate the repetition in this segment of code i can take all the inputs from the user then validate all of them together
// but i prefered this style as it gives instant feedback to the user if what he just entered is valid on not.
validAccNo:
    printf("Choose an account number: ");
    scanf("%d", &id);
    if (!check_duplicate_id())
    {
        printf("Account number already exists please choose another ID!.\n");
        goto validAccNo;
    }

validName:
    fflush(stdin);
    printf("Enter your name: ");
    gets(name);
    if (!check_duplicate_name())
    {
        printf("Username already exists please choose another username!.\n");
        goto validName;
    }

    fflush(stdin);

    printf("Enter your phone number: ");
    scanf("%d", &curr.phoneNum);

validPass:
    fflush(stdin);
    printf("Enter your password: ");
    gets(curr.password);
    if (strlen(curr.password) < 8)
    {
        printf("The password must be at least 8 characters\n");
        goto validPass;
    }

    printf("Enter your balance: ");
    scanf("%d", &curr.balance);

    add_data_to_file();
}

void add_data_to_file(void)
{
    myfile = fopen("data.bin", "ab");

    if (myfile)
    {
        fwrite(&curr, sizeof(account), 1, myfile);
        // fprintf(myfile, "%d %s %s %d %d\n", curr.acc_no, curr.name, curr.password, curr.phoneNum, curr.balance);
        fclose(myfile);
        return;
    }

    printf("There was an error opening the file!.\n");
    system_body();
}

bool check_duplicate_name(void)
{
    myfile = fopen("data.bin", "rb");

    if (myfile)
    {
        while (!feof(myfile))
        {
            fread(&curr, sizeof(account), 1, myfile);
            if (strcmp(curr.name, name) == 0)
            {
                fclose(myfile);
                return false;
            }
        }
    }
    fclose(myfile);
    strcpy(curr.name, name);
    return true;
}

bool check_duplicate_id(void)
{
    myfile = fopen("data.bin", "rb");

    if (myfile)
    {
        while (!feof(myfile))
        {
            fread(&curr, sizeof(account), 1, myfile);
            if (curr.acc_no == id)
            {
                fclose(myfile);
                return false;
            }
        }
    }
    fclose(myfile);
    curr.acc_no = id;
    return true;
}

void print_account_data(void)
{
    system("cls");

    myfile = fopen("data.bin", "rb");
    if (myfile)
    {
        printf("\n\t\t  Acc_no\t   Acc_name\t\t    Password\t\tPhone_num\t     Balance\n");
        printf("\t\t----------------------------------------------------------------------------------------------------");
        while (!feof(myfile))
        {
            fread(&curr, sizeof(account), 1, myfile);
            printf("\n\t\t%6d\t%20s\t%20s\t\t%6d\t\t%10d", curr.acc_no, curr.name, curr.password, curr.phoneNum, curr.balance);
        }
        fclose(myfile);
        return;
    }

    printf("There was an error retrieving the data!.\n");
}