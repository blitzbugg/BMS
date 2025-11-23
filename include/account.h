#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int a_no;
    char a_name[20];
    char a_addr[40];
    int a_bal;
} Account;

void insertAccount();
void editAccount();
void deleteAccount();
void viewAccounts();
Account *findAccount(int accountNo);

#endif
