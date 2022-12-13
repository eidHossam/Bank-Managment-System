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

    case 2:
        modify_data();
        break;

    case 4:
        print_accounts_data();
        break;

    case 5:
        print_account_data();
        break;

    case 7:
        close();

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

    system_body();
}

void add_data_to_file(void)
{
    myfile = fopen("data.bin", "ab");

    if (myfile)
    {
        fwrite(&curr, sizeof(account_t), 1, myfile);
        fclose(myfile);
        printf("\n\n\n\t\t\tYour account was successfully added to the system!.\n");
        nav_to_main_menu();
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
            fread(&curr, sizeof(account_t), 1, myfile);
            if (strcmp(curr.name, name) == 0)
            {
                fclose(myfile);
                return false;
            }
        }
    }
    fclose(myfile);
    strcpy(curr.name, name);
    curr.acc_no = id;
    return true;
}

bool check_duplicate_id(void)
{
    myfile = fopen("data.bin", "rb");

    if (myfile)
    {
        while (!feof(myfile))
        {
            fread(&curr, sizeof(account_t), 1, myfile);
            if (curr.acc_no == id)
            {
                fclose(myfile);
                return false;
            }
        }
    }
    fclose(myfile);
    return true;
}

void print_accounts_data(void)
{
    system("cls");

    myfile = fopen("data.bin", "rb");
    if (myfile)
    {
        printf("\n\t\t  Acc_no\t   Acc_name\t\t    Password\t\tPhone_num\t     Balance\n");
        printf("\t\t----------------------------------------------------------------------------------------------------");
        while (fread(&curr, sizeof(account_t), 1, myfile) > 0)
        {
            printf("\n\t\t%6d\t%20s\t%20s\t\t%6d\t\t%10d", curr.acc_no, curr.name, curr.password, curr.phoneNum, curr.balance);
        }
        fclose(myfile);
        nav_to_main_menu();
        system_body();
        return;
    }

    printf("There was an error retrieving the data!.\n");
}

void modify_data(void)
{
    system("cls");
    printf("\n\n\n\n\t\t\t\tEnter the number of the account you want to modify: ");
    fflush(stdin);
    scanf("%d", id);

    // myfile = fopen("data.bin", "rb");
    // if (myfile)
    // {
    //     while (!feof(myfile))
    //     {
    //         fread(&curr, sizeof(account), 1, myfile);
    //         if (curr.acc_no == id)
    //         {
    //         }
    //     }
    // }
}

void print_account_data(void)
{
    system("cls");
    printf("\n\n\n\n\t\t\t\tEnter the number of the account you want to show: ");
    scanf("%d", &id);

    myfile = fopen("data.bin", "rb");
    if (myfile)
    {
        while (fread(&curr, sizeof(account_t), 1, myfile) > 0)
        {
            if (curr.acc_no == id)
            {
                printf("\n\t\t  Acc_no\t   Acc_name\t\t    Password\t\tPhone_num\t     Balance\n");
                printf("\t\t----------------------------------------------------------------------------------------------------");
                printf("\n\t\t%6d\t%20s\t%20s\t\t%6d\t\t%10d", curr.acc_no, curr.name, curr.password, curr.phoneNum, curr.balance);

                nav_to_main_menu();

                fclose(myfile);
                system_body();
                return;
            }
        }

        printf("\n\n\t\t\t\tThis account doesn't exist!.\n");
        nav_to_main_menu();
    }
    system_body();
}

void close(void)
{
    system("cls");
    printf("\n\n\n\n\t\t\t\t\tThank you for using our system!.");
}

void nav_to_main_menu(void)
{
    printf("\n\n\t\t\t\tPress any key to go back to the main menu.");
    fflush(stdin);
    getchar();
}