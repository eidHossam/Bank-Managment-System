#include "header.h"

static account_t curr;
static transaction_t transaction;
static FILE *myfile;
static FILE *temp;
static char name[NAME_MAX];
static UINT16 id;
static bool found = false;

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
    printf("\t\t\t\t7 - Print transactions history.\n");
    printf("\t\t\t\t8 - Exit.\n\n");
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

    case 3:
        make_transaction();
        break;

    case 4:
        print_accounts_data();
        break;

    case 5:
        print_account_data();
        break;

    case 6:
        delete_account();
        break;

    case 7:
        print_transactions_data();
        break;

    case 8:
        close();

    default:
        break;
    }
}

void add_account()
{
    system("cls");

    get_data();

    add_data_to_file();

    system_body();
}

void get_data(void)
{

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

    get_phoneNumber();

    get_password();

    get_balance();
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

void get_phoneNumber(void)
{
    fflush(stdin);
    printf("Enter your phone number: ");
    scanf("%d", &curr.phoneNum);
}

void get_password(void)
{
validPass:
    fflush(stdin);
    printf("Enter your password: ");
    gets(curr.password);
    if (strlen(curr.password) < 8)
    {
        printf("The password must be at least 8 characters\n");
        goto validPass;
    }
}

void get_balance(void)
{
    fflush(stdin);
    printf("Enter your balance: ");
    scanf("%d", &curr.balance);
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

void print_transactions_data(void)
{
    system("cls");

    myfile = fopen("transaction.bin", "rb");
    if (myfile)
    {
        printf("\n\t\t\t\t  Acc_no\t   type\t\t    amount\n");
        printf("\t\t\t\t---------------------------------------");
        while (fread(&transaction, sizeof(transaction_t), 1, myfile) > 0)
        {
            printf("\n\t\t\t\t%6d\t%20s\t%6d", transaction.acc_no, transaction.typeOfTransaction, transaction.amount);
        }
        fclose(myfile);
        nav_to_main_menu();
        system_body();
        return;
    }

    printf("There was an error retrieving the data!.\n");
}

void print_account_data(void)
{
    char show[] = "show";
    select_account(show);

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

void data(void (*fun)(void), char operation[])
{
    select_account(operation);

    found = false;
    myfile = fopen("data.bin", "rb");
    temp = fopen("temp.bin", "ab");
    if (myfile)
    {
        while (fread(&curr, sizeof(account_t), 1, myfile) > 0)
        {
            (*fun)();
        }
    }

    fclose(myfile);
    fclose(temp);
    remove("data.bin");
    rename("temp.bin", "data.bin");

    if (found)
        printf("\n\n\n\n\t\t\t\tThe changes you made were successful!.");
    else
        printf("\n\n\n\n\t\t\t\tThere is no account with that number.");

    nav_to_main_menu();
    system_body();
}

void modify_data(void)
{
    char modify[] = "modify";
    data(mod, modify);
}

void mod(void)
{
    if (curr.acc_no == id)
    {
        found = true;
        fflush(stdin);
        printf("Enter your name: ");
        gets(curr.name);

        get_phoneNumber();

        get_password();
    }

    fwrite(&curr, sizeof(account_t), 1, temp);
}

void delete_account(void)
{
    char dele[] = "delete";
    data(del, dele);
}

void del(void)
{
    if (curr.acc_no == id)
        found = true;

    fwrite(&curr, sizeof(account_t), 1, temp);
}

void make_transaction(void)
{
    char transaction_select[] = "make a transaction in";
    data(trans, transaction_select);
}

void trans(void)
{
    FILE *tra;
    char type[2][NAME_MAX] = {"Withdraw", "Deposit"};
    int select = 0;
    if (curr.acc_no == id)
    {
        tra = fopen("transaction.bin", "wb");
        found = true;
        transaction.acc_no = id;
        fflush(stdin);

        printf("\n\n\n\n\t\t\t\t\tPress (0) to withdraw , (1) to deposit: ");
        scanf("%d", &select);

        strcpy(transaction.typeOfTransaction, type[select]);
        printf("\n\t\t\t\tEnter the amount: ");
        scanf("%d", &transaction.amount);

        fwrite(&transaction, sizeof(transaction_t), 1, tra);
        fclose(tra);

        if (select == 0)
            curr.balance -= transaction.amount;
        else
            curr.balance += transaction.amount;
    }

    fwrite(&curr, sizeof(account_t), 1, temp);
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

void select_account(char operation[])
{
    system("cls");
    printf("\n\n\n\n\t\t\t\tEnter the number of the account you want to %s: ", operation);
    fflush(stdin);
    scanf("%d", &id);
}