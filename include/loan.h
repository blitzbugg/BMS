#ifndef LOAN_H
#define LOAN_H

typedef struct {
    int l_id;
    int a_no;
    char l_date[10];
    char l_type[20];
    int l_amt;
    int l_dur;
} Loan;

void insertLoan();
void editLoan();
void deleteLoan();
void viewLoans();
Loan *findLoan(int loanId);

#endif
