#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/transaction.h"

#define FILENAME "data/transaction.dat"

void insertTransaction() {
    Transaction trans;
    FILE *fp;
    
    printf("\n=== INSERT TRANSACTION ===\n");
    printf("Enter Transaction ID: ");
    scanf("%d", &trans.t_id);
    
    printf("Enter Account Number: ");
    scanf("%s", trans.a_no);
    
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", trans.t_date);
    
    printf("Enter Type (1=Credit, 2=Debit): ");
    scanf("%d", &trans.t_type);
    
    printf("Enter Amount: ");
    scanf("%d", &trans.t_amt);
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);
    
    printf("Transaction inserted successfully!\n");
}

void editTransaction() {
    Transaction trans;
    FILE *fp;
    int transId, found = 0;
    long int pos;
    
    printf("\n=== EDIT TRANSACTION ===\n");
    printf("Enter Transaction ID to edit: ");
    scanf("%d", &transId);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (trans.t_id == transId) {
            found = 1;
            pos = ftell(fp) - sizeof(Transaction);
            fseek(fp, pos, SEEK_SET);
            
            printf("Enter new Account Number: ");
            scanf("%s", trans.a_no);
            
            printf("Enter new Date (DD/MM/YYYY): ");
            scanf("%s", trans.t_date);
            
            printf("Enter new Type (1=Credit, 2=Debit): ");
            scanf("%d", &trans.t_type);
            
            printf("Enter new Amount: ");
            scanf("%d", &trans.t_amt);
            
            fwrite(&trans, sizeof(Transaction), 1, fp);
            printf("Transaction updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Transaction not found!\n");
    }
    
    fclose(fp);
}

void deleteTransaction() {
    Transaction trans;
    FILE *fp, *temp;
    int transId, found = 0;
    
    printf("\n=== DELETE TRANSACTION ===\n");
    printf("Enter Transaction ID to delete: ");
    scanf("%d", &transId);
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    temp = fopen("data/temp.dat", "wb");
    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
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
        printf("Transaction deleted successfully!\n");
    } else {
        remove("data/temp.dat");
        printf("Transaction not found!\n");
    }
}

void viewTransactions() {
    Transaction trans;
    FILE *fp;
    char typeStr[10];
    
    printf("\n=== VIEW ALL TRANSACTIONS ===\n");
    printf("%-15s %-20s %-15s %-15s %-15s\n", "Transaction ID", "Account No", "Date", "Type", "Amount");
    printf("--------------------------------------------------------------------------------\n");
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file or file is empty!\n");
        return;
    }
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        strcpy(typeStr, (trans.t_type == 1) ? "Credit" : "Debit");
        printf("%-15d %-20s %-15s %-15s %-15d\n", trans.t_id, trans.a_no, trans.t_date, typeStr, trans.t_amt);
    }
    
    fclose(fp);
}

