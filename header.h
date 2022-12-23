#ifndef HEADER_H
#define HEADER_H

#define NAME_MAX 20
#define PASS_MAX 20

#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct transaction
{
    UINT16 acc_no;
    char typeOfTransaction[NAME_MAX];
    UINT32 amount;
} transaction_t;

typedef struct account
{
    UINT16 acc_no;
    char name[NAME_MAX];
    char password[PASS_MAX];
    UINT32 balance;
    UINT8 phoneNum;
} account_t;

void print_menu(void);
void system_body(void);
void add_account(void);
void get_data(void);
void add_data_to_file(void);
void get_phoneNumber(void);
void get_balance(void);
void get_password(void);
bool check_duplicate_name(void);
bool check_duplicate_id(void);
void print_accounts_data(void);
void print_transactions_data(void);
void print_account_data(void);
void modify_data(void);
void delete_account(void);
void make_transaction(void);
void select_account(char operation[]);
void data(void (*fun)(void), char operation[]);
void del(void);
void mod(void);
void trans(void);
void nav_to_main_menu(void);
void close(void);
#endif