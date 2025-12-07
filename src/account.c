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
    
    clearScreen();
    setAccountMenuColor();
    printDoubleBorderBox("INSERT ACCOUNT", COLOR_BRIGHT_WHITE, BG_GREEN, 60);
    resetColor();
    
    // Auto-generate account number
    acc.a_no = getNextId(FILENAME, sizeof(Account), 0);
    setInfoColor();
    printf("Auto-generated Account Number: ");
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%d\n", acc.a_no);
    resetColor();
    
    printf("\nEnter Account Name: ");
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
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    fwrite(&acc, sizeof(Account), 1, fp);
    fclose(fp);
    
    setSuccessColor();
    printf("\nAccount inserted successfully!\n");
    resetColor();
    pause();
}

void editAccount() {
    Account acc;
    FILE *fp;
    int accNo, found = 0;
    long int pos;
    
    clearScreen();
    setAccountMenuColor();
    printDoubleBorderBox("EDIT ACCOUNT", COLOR_BRIGHT_WHITE, BG_GREEN, 60);
    resetColor();
    
    printf("Enter Account Number to edit: ");
    scanf("%d", &accNo);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no == accNo) {
            found = 1;
            pos = ftell(fp) - sizeof(Account);
            fseek(fp, pos, SEEK_SET);
            
            setInfoColor();
            printf("\nCurrent Account Details:\n");
            resetColor();
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
            setSuccessColor();
            printf("\nAccount updated successfully!\n");
            resetColor();
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        setErrorColor();
        printf("\nAccount not found!\n");
        resetColor();
    }
    
    pause();
}

void deleteAccount() {
    Account acc;
    FILE *fp, *temp;
    int accNo, found = 0;
    
    clearScreen();
    setAccountMenuColor();
    printDoubleBorderBox("DELETE ACCOUNT", COLOR_BRIGHT_WHITE, BG_GREEN, 60);
    resetColor();
    
    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    temp = fopen("data/temp.dat", "wb");
    if (temp == NULL) {
        setErrorColor();
        printf("\nError creating temporary file!\n");
        resetColor();
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
        setSuccessColor();
        printf("\nAccount deleted successfully!\n");
        resetColor();
    } else {
        remove("data/temp.dat");
        setErrorColor();
        printf("\nAccount not found!\n");
        resetColor();
    }
    
    pause();
}

void viewAccounts() {
    Account acc;
    FILE *fp;
    int count = 0;
    
    clearScreen();
    setAccountMenuColor();
    printDoubleBorderBox("VIEW ALL ACCOUNTS", COLOR_BRIGHT_WHITE, BG_GREEN, 70);
    resetColor();
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        setInfoColor();
        printf("No accounts found. File is empty or doesn't exist.\n");
        resetColor();
        pause();
        return;
    }
    
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%-15s %-20s %-40s %-15s\n", "Account No", "Name", "Address", "Balance");
    resetColor();
    drawHorizontalLine('-', 90);
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        printf("%-15d %-20s %-40s %-15d\n", acc.a_no, acc.a_name, acc.a_addr, acc.a_bal);
        count++;
    }
    
    fclose(fp);
    
    if (count == 0) {
        setInfoColor();
        printf("No records found.\n");
        resetColor();
    } else {
        setInfoColor();
        printf("\nTotal records: %d\n", count);
        resetColor();
    }
    
    pause();
}
