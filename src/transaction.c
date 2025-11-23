#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/transaction.h"
#include "../include/utility.h"

#define FILENAME "data/transaction.dat"

Transaction *findTransaction(int transId) {
    FILE *fp;
    Transaction *trans = (Transaction *)malloc(sizeof(Transaction));
    Transaction temp;
    
    if (trans == NULL) {
        return NULL;
    }
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        free(trans);
        return NULL;
    }
    
    while (fread(&temp, sizeof(Transaction), 1, fp) == 1) {
        if (temp.t_id == transId) {
            *trans = temp;
            fclose(fp);
            return trans;
        }
    }
    
    fclose(fp);
    free(trans);
    return NULL;
}

void insertTransaction() {
    Transaction trans;
    FILE *fp;
    int accNo;
    
    printHeader("INSERT TRANSACTION");
    
    // Auto-generate transaction ID
    trans.t_id = getNextId(FILENAME, sizeof(Transaction), 0);
    printf("Auto-generated Transaction ID: %d\n", trans.t_id);
    
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    
    // Cross-validation: Check if account exists
    if (!accountExists(accNo)) {
        printf("Error: Account Number %d does not exist!\n", accNo);
        printf("Please create the account first.\n");
        pause();
        return;
    }
    
    trans.a_no = accNo;
    
    printf("Enter Date (DD/MM/YYYY): ");
    clearInputBuffer();
    fgets(trans.t_date, sizeof(trans.t_date), stdin);
    removeNewline(trans.t_date);
    
    printf("Enter Type (1=Credit, 2=Debit): ");
    scanf("%d", &trans.t_type);
    
    if (trans.t_type != 1 && trans.t_type != 2) {
        printf("Invalid transaction type! Use 1 for Credit or 2 for Debit.\n");
        pause();
        return;
    }
    
    printf("Enter Amount: ");
    scanf("%d", &trans.t_amt);
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        pause();
        return;
    }
    
    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);
    
    printf("\nTransaction inserted successfully!\n");
    pause();
}

void editTransaction() {
    Transaction trans;
    FILE *fp;
    int transId, accNo, found = 0;
    long int pos;
    
    printHeader("EDIT TRANSACTION");
    printf("Enter Transaction ID to edit: ");
    scanf("%d", &transId);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        pause();
        return;
    }
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (trans.t_id == transId) {
            found = 1;
            pos = ftell(fp) - sizeof(Transaction);
            fseek(fp, pos, SEEK_SET);
            
            printf("\nCurrent Transaction Details:\n");
            printf("Account Number: %d\n", trans.a_no);
            printf("Date: %s\n", trans.t_date);
            printf("Type: %s\n", (trans.t_type == 1) ? "Credit" : "Debit");
            printf("Amount: %d\n", trans.t_amt);
            
            printf("\nEnter new Account Number: ");
            scanf("%d", &accNo);
            
            // Cross-validation: Check if account exists
            if (!accountExists(accNo)) {
                printf("Error: Account Number %d does not exist!\n", accNo);
                printf("Please create the account first.\n");
                fclose(fp);
                pause();
                return;
            }
            
            trans.a_no = accNo;
            
            printf("Enter new Date (DD/MM/YYYY): ");
            clearInputBuffer();
            fgets(trans.t_date, sizeof(trans.t_date), stdin);
            removeNewline(trans.t_date);
            
            printf("Enter new Type (1=Credit, 2=Debit): ");
            scanf("%d", &trans.t_type);
            
            if (trans.t_type != 1 && trans.t_type != 2) {
                printf("Invalid transaction type! Use 1 for Credit or 2 for Debit.\n");
                fclose(fp);
                pause();
                return;
            }
            
            printf("Enter new Amount: ");
            scanf("%d", &trans.t_amt);
            
            fwrite(&trans, sizeof(Transaction), 1, fp);
            printf("\nTransaction updated successfully!\n");
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("Transaction not found!\n");
    }
    
    pause();
}

void deleteTransaction() {
    Transaction trans;
    FILE *fp, *temp;
    int transId, found = 0;
    
    printHeader("DELETE TRANSACTION");
    printf("Enter Transaction ID to delete: ");
    scanf("%d", &transId);
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        pause();
        return;
    }
    
    temp = fopen("data/temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        pause();
        return;
    }
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (trans.t_id != transId) {
            fwrite(&trans, sizeof(Transaction), 1, temp);
        } else {
            found = 1;
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if (found) {
        remove(FILENAME);
        rename("data/temp.dat", FILENAME);
        printf("\nTransaction deleted successfully!\n");
    } else {
        remove("data/temp.dat");
        printf("Transaction not found!\n");
    }
    
    pause();
}

void viewTransactions() {
    Transaction trans;
    FILE *fp;
    int count = 0;
    char typeStr[10];
    
    printHeader("VIEW ALL TRANSACTIONS");
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No transactions found. File is empty or doesn't exist.\n");
        pause();
        return;
    }
    
    printf("%-15s %-15s %-15s %-15s %-15s\n", "Transaction ID", "Account No", "Date", "Type", "Amount");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        strcpy(typeStr, (trans.t_type == 1) ? "Credit" : "Debit");
        printf("%-15d %-15d %-15s %-15s %-15d\n", trans.t_id, trans.a_no, trans.t_date, typeStr, trans.t_amt);
        count++;
    }
    
    fclose(fp);
    
    if (count == 0) {
        printf("No records found.\n");
    } else {
        printf("\nTotal records: %d\n", count);
    }
    
    pause();
}
