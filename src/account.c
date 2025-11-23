#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"

#define FILENAME "data/account.dat"

void insertAccount() {
    Account acc;
    FILE *fp;
    
    printf("\n=== INSERT ACCOUNT ===\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.a_no);
    
    printf("Enter Account Name: ");
    scanf("%s", acc.a_name);
    
    printf("Enter Address: ");
    scanf("%s", acc.a_addr);
    
    printf("Enter Balance: ");
    scanf("%d", &acc.a_bal);
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    
    printf("Account inserted successfully!\n");
}

void editAccount() {
    Account acc;
    FILE *fp;
    int accNo, found = 0;
    long int pos;
    
    printf("\n=== EDIT ACCOUNT ===\n");
    printf("Enter Account Number to edit: ");
    scanf("%d", &accNo);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no == accNo) {
            found = 1;
            pos = ftell(fp) - sizeof(Account);
            fseek(fp, pos, SEEK_SET);
            
            printf("Enter new Account Name: ");
            scanf("%s", acc.a_name);
            
            printf("Enter new Address: ");
            scanf("%s", acc.a_addr);
            
            printf("Enter new Balance: ");
            scanf("%d", &acc.a_bal);
            
            fwrite(&acc, sizeof(Account), 1, fp);
            printf("Account updated successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Account not found!\n");
    }
    
    fclose(fp);
}

void deleteAccount() {
    Account acc;
    FILE *fp, *temp;
    int accNo, found = 0;
    
    printf("\n=== DELETE ACCOUNT ===\n");
    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);
    
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
        printf("Account deleted successfully!\n");
    } else {
        remove("data/temp.dat");
        printf("Account not found!\n");
    }
}

void viewAccounts() {
    Account acc;
    FILE *fp;
    
    printf("\n=== VIEW ALL ACCOUNTS ===\n");
    printf("%-15s %-20s %-40s %-15s\n", "Account No", "Name", "Address", "Balance");
    printf("--------------------------------------------------------------------------------\n");
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("Error opening file or file is empty!\n");
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        printf("%-15d %-20s %-40s %-15d\n", acc.a_no, acc.a_name, acc.a_addr, acc.a_bal);
    }
    
    fclose(fp);
}

