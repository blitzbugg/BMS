#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loan.h"

#define FILENAME "data/loan.dat"

void insertLoan() {
    Loan loan;
    FILE *fp;
    
    printf("\n=== INSERT LOAN ===\n");
    printf("Enter Loan ID: ");
    scanf("%d", &loan.l_id);
    
    printf("Enter Account Number: ");
    scanf("%d", &loan.a_no);
    
    printf("Enter Loan Date (DD/MM/YYYY): ");
    scanf("%s", loan.l_date);
    
    printf("Enter Loan Type: ");
    scanf("%s", loan.l_type);
    
    printf("Enter Loan Amount: ");
    scanf("%d", &loan.l_amt);
    
    printf("Enter Duration (months): ");
    scanf("%d", &loan.l_dur);
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&loan, sizeof(Loan), 1, fp);
    fclose(fp);
    
    printf("Loan inserted successfully!\n");
}

void editLoan() {
    Loan loan;
    FILE *fp;
    int loanId, found = 0;
    long int pos;
    
    printf("\n=== EDIT LOAN ===\n");
    printf("Enter Loan ID to edit: ");
    scanf("%d", &loanId);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    while (fread(&loan, sizeof(Loan), 1, fp) == 1) {
        if (loan.l_id == loanId) {
            found = 1;
            pos = ftell(fp) - sizeof(Loan);
            fseek(fp, pos, SEEK_SET);
            
            printf("Enter new Account Number: ");
            scanf("%d", &loan.a_no);
            
            printf("Enter new Loan Date (DD/MM/YYYY): ");
            scanf("%s", loan.l_date);
            
            printf("Enter new Loan Type: ");
            scanf("%s", loan.l_type);
            
            printf("Enter new Loan Amount: ");
            scanf("%d", &loan.l_amt);
            
            printf("Enter new Duration (months): ");
            scanf("%d", &loan.l_dur);
            
            fwrite(&loan, sizeof(Loan), 1, fp);
            printf("Loan updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Loan not found!\n");
    }
    
    fclose(fp);
}

void deleteLoan() {
    Loan loan;
    FILE *fp, *temp;
    int loanId, found = 0;
    
    printf("\n=== DELETE LOAN ===\n");
    printf("Enter Loan ID to delete: ");
    scanf("%d", &loanId);
    
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
    
    while (fread(&loan, sizeof(Loan), 1, fp) == 1) {
        if (loan.l_id != loanId) {
            fwrite(&loan, sizeof(Loan), 1, temp);
        } else {
            found = 1;
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if (found) {
        remove(FILENAME);
        rename("data/temp.dat", FILENAME);
        printf("Loan deleted successfully!\n");
    } else {
        remove("data/temp.dat");
        printf("Loan not found!\n");
    }
}

void viewLoans() {
    Loan loan;
    FILE *fp;
    
    printf("\n=== VIEW ALL LOANS ===\n");
    printf("%-10s %-15s %-15s %-20s %-15s %-10s\n", "Loan ID", "Account No", "Date", "Loan Type", "Amount", "Duration");
    printf("--------------------------------------------------------------------------------\n");
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file or file is empty!\n");
        return;
    }
    
    while (fread(&loan, sizeof(Loan), 1, fp) == 1) {
        printf("%-10d %-15d %-15s %-20s %-15d %-10d\n", loan.l_id, loan.a_no, loan.l_date, loan.l_type, loan.l_amt, loan.l_dur);
    }
    
    fclose(fp);
}

