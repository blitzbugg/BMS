#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int t_id;
    char a_no[20];
    char t_date[10];
    int t_type;
    int t_amt;
} Transaction;

void insertTransaction();
void editTransaction();
void deleteTransaction();
void viewTransactions();

#endif
