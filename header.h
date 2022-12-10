#ifndef HEADER_H
#define HEADER_H

#define NAME_MAX 20
#define PASS_MAX 20

#include <stdio.h>
#include <windows.h>

typedef struct account
{
    char name[NAME_MAX];
    char password[PASS_MAX];
    UINT32 balance;
    UINT8 phoneNum;
} account_t;

void print_menu(void);
void system_body(void);
void add_data_to_file(void);
void add_account(void);
#endif