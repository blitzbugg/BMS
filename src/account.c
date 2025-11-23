#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/utility.h"

#define FILENAME "data/account.dat"

Account *findAccount(int accountNo) {
    FILE *fp;
    Account *acc = (Account *)malloc(sizeof(Account));
    Account temp;
    
    if (acc == NULL) {
        return NULL;
    }
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        free(acc);
        return NULL;
    }
    
    while (fread(&temp, sizeof(Account), 1, fp) == 1) {
        if (temp.a_no == accountNo) {
            *acc = temp;
            fclose(fp);
            return acc;
        }
    }
    
    fclose(fp);
    free(acc);
    return NULL;
}

void insertAccount() {
    Account acc;
    FILE *fp;
    
    printHeader("INSERT ACCOUNT");
    
    // Auto-generate account number
    acc.a_no = getNextId(FILENAME, sizeof(Account), 0);
    printf("Auto-generated Account Number: %d\n", acc.a_no);
    
    printf("Enter Account Name: ");
    clearInputBuffer();
    fgets(acc.a_name, sizeof(acc.a_name), stdin);
    removeNewline(acc.a_name);
    
    printf("Enter Address: ");
    fgets(acc.a_addr, sizeof(acc.a_addr), stdin);
    removeNewline(acc.a_addr);
    
    printf("Enter Balance: ");
    scanf("%d", &acc.a_bal);
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    
    printf("\nAccount inserted successfully!\n");
    pause();
}

void editAccount() {
    Account acc;
    FILE *fp;
    int accNo, found = 0;
    long int pos;
    
    printHeader("EDIT ACCOUNT");
    printf("Enter Account Number to edit: ");
    scanf("%d", &accNo);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        pause();
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no == accNo) {
            found = 1;
            pos = ftell(fp) - sizeof(Account);
            fseek(fp, pos, SEEK_SET);
            
            printf("\nCurrent Account Details:\n");
            printf("Name: %s\n", acc.a_name);
            printf("Address: %s\n", acc.a_addr);
            printf("Balance: %d\n", acc.a_bal);
            
            printf("\nEnter new Account Name: ");
            clearInputBuffer();
            fgets(acc.a_name, sizeof(acc.a_name), stdin);
            removeNewline(acc.a_name);
            
            printf("Enter new Address: ");
            fgets(acc.a_addr, sizeof(acc.a_addr), stdin);
            removeNewline(acc.a_addr);
            
            printf("Enter new Balance: ");
            scanf("%d", &acc.a_bal);
            
            fwrite(&acc, sizeof(Account), 1, fp);
            printf("\nAccount updated successfully!\n");
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        printf("Account not found!\n");
    }
    
    pause();
}

void deleteAccount() {
    Account acc;
    FILE *fp, *temp;
    int accNo, found = 0;
    
    printHeader("DELETE ACCOUNT");
    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);
    
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
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no != accNo) {
            fwrite(&acc, sizeof(Account), 1, temp);
        } else {
            found = 1;
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if (found) {
        remove(FILENAME);
        rename("data/temp.dat", FILENAME);
        printf("\nAccount deleted successfully!\n");
    } else {
        remove("data/temp.dat");
        printf("Account not found!\n");
    }
    
    pause();
}

void viewAccounts() {
    Account acc;
    FILE *fp;
    int count = 0;
    
    printHeader("VIEW ALL ACCOUNTS");
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No accounts found. File is empty or doesn't exist.\n");
        pause();
        return;
    }
    
    printf("%-15s %-20s %-40s %-15s\n", "Account No", "Name", "Address", "Balance");
    printf("--------------------------------------------------------------------------------\n");
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        printf("%-15d %-20s %-40s %-15d\n", acc.a_no, acc.a_name, acc.a_addr, acc.a_bal);
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
