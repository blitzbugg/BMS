#include <stdio.h>
#include <stdlib.h>
#include "../include/account.h"
#include "../include/transaction.h"
#include "../include/loan.h"

void accountMenu() {
    int choice;
    do {
        printf("\n=== ACCOUNT MASTER FILE ===\n");
        printf("1. Insert Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. View Records\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                insertAccount();
                break;
            case 2:
                editAccount();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                viewAccounts();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

void transactionMenu() {
    int choice;
    do {
        printf("\n=== TRANSACTION FILE ===\n");
        printf("1. Insert Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. View Records\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                insertTransaction();
                break;
            case 2:
                editTransaction();
                break;
            case 3:
                deleteTransaction();
                break;
            case 4:
                viewTransactions();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

void loanMenu() {
    int choice;
    do {
        printf("\n=== LOAN FILE ===\n");
        printf("1. Insert Record\n");
        printf("2. Edit Record\n");
        printf("3. Delete Record\n");
        printf("4. View Records\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                insertLoan();
                break;
            case 2:
                editLoan();
                break;
            case 3:
                deleteLoan();
                break;
            case 4:
                viewLoans();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

int main() {
    int choice;
    
    printf("========================================\n");
    printf("   BANK MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    
    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Account Master File\n");
        printf("2. Transaction File\n");
        printf("3. Loan File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                accountMenu();
                break;
            case 2:
                transactionMenu();
                break;
            case 3:
                loanMenu();
                break;
            case 4:
                printf("Thank you for using Bank Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
    
    return 0;
}

