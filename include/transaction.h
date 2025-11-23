#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int t_id;
    int a_no;
    char t_date[11];
    int t_type; // 1=Credit, 2=Debit
    int t_amt;
} Transaction;

void insertTransaction();
void editTransaction();
void deleteTransaction();
void viewTransactions();
Transaction *findTransaction(int transId);

#endif
