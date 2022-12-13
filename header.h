#ifndef HEADER_H
#define HEADER_H

#define NAME_MAX 20
#define PASS_MAX 20

#include <stdio.h>
#include <windows.h>
#include <string.h>

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
void add_data_to_file(void);
bool check_duplicate_name(void);
bool check_duplicate_id(void);
void add_account(void);
void print_accounts_data(void);
void print_account_data(void);
void modify_data(void);
void nav_to_main_menu(void);
void close(void);
#endif