#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/loan.h"
#include "../include/utility.h"

#define FILENAME "data/loan.dat"

Loan *findLoan(int loanId) {
    FILE *fp;
    Loan *loan = (Loan *)malloc(sizeof(Loan));
    Loan temp;
    
    if (loan == NULL) {
        return NULL;
    }
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        free(loan);
        return NULL;
    }
    
    while (fread(&temp, sizeof(Loan), 1, fp) == 1) {
        if (temp.l_id == loanId) {
            *loan = temp;
            fclose(fp);
            return loan;
        }
    }
    
    fclose(fp);
    free(loan);
    return NULL;
}

void insertLoan() {
    Loan loan;
    FILE *fp;
    int accNo;
    
    clearScreen();
    setLoanMenuColor();
    printDoubleBorderBox("INSERT LOAN", COLOR_BRIGHT_WHITE, BG_MAGENTA, 55);
    resetColor();
    
    // Auto-generate loan ID
    loan.l_id = getNextId(FILENAME, sizeof(Loan), 0);
    setInfoColor();
    printf("Auto-generated Loan ID: ");
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%d\n", loan.l_id);
    resetColor();
    
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    // clearInputBuffer(); // Clear buffer after scanf
    
    // Cross-validation: Check if account exists
    if (!accountExists(accNo)) {
        setErrorColor();
        printf("Error: Account Number %d does not exist!\n", accNo);
        printf("Please create the account first.\n");
        resetColor();
        pause();
        return;
    }
    
    loan.a_no = accNo;
    
    printf("Enter Loan Date (DD/MM/YYYY): ");
    fflush(stdout);
    clearInputBuffer();
    if (fgets(loan.l_date, sizeof(loan.l_date), stdin) == NULL) {
        printf("Error reading input!\n");
        pause();
        return;
    }
    removeNewline(loan.l_date);
    
    // Read loan type with validation
    // clearInputBuffer();
    do {
        printf("Enter Loan Type: ");
        scanf("%d", &loan.l_type);
        if (fgets(loan.l_type, sizeof(loan.l_type), stdin) == NULL) {
            printf("Error reading input!\n");
            pause();
            return;
        }
        removeNewline(loan.l_type);
        
        if (strlen(loan.l_type) == 0) {
            printf("Loan Type cannot be empty! Please enter a valid loan type.\n");
        }
    } while (strlen(loan.l_type) == 0);
    
    printf("Enter Loan Amount: ");
    scanf("%d", &loan.l_amt);
    clearInputBuffer();
    
    printf("Enter Duration (months): ");
    scanf("%d", &loan.l_dur);
    clearInputBuffer();
    
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    fwrite(&loan, sizeof(Loan), 1, fp);
    fclose(fp);
    
    setSuccessColor();
    printf("\nLoan inserted successfully!\n");
    resetColor();
    pause();
}

void editLoan() {
    Loan loan;
    FILE *fp;
    int loanId, accNo, found = 0;
    long int pos;
    
    clearScreen();
    setLoanMenuColor();
    printDoubleBorderBox("EDIT LOAN", COLOR_BRIGHT_WHITE, BG_MAGENTA, 55);
    resetColor();
    
    printf("Enter Loan ID to edit: ");
    scanf("%d", &loanId);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    while (fread(&loan, sizeof(Loan), 1, fp) == 1) {
        if (loan.l_id == loanId) {
            found = 1;
            pos = ftell(fp) - sizeof(Loan);
            fseek(fp, pos, SEEK_SET);
            
            setInfoColor();
            printf("\nCurrent Loan Details:\n");
            resetColor();
            printf("Account Number: %d\n", loan.a_no);
            printf("Date: %s\n", loan.l_date);
            printf("Type: %s\n", loan.l_type);
            printf("Amount: %d\n", loan.l_amt);
            printf("Duration: %d months\n", loan.l_dur);
            
            printf("\nEnter new Account Number: ");
            scanf("%d", &accNo);
            
            // Cross-validation: Check if account exists
            if (!accountExists(accNo)) {
                setErrorColor();
                printf("Error: Account Number %d does not exist!\n", accNo);
                printf("Please create the account first.\n");
                resetColor();
                fclose(fp);
                pause();
                return;
            }
            
            loan.a_no = accNo;
            
            printf("Enter new Loan Date (DD/MM/YYYY): ");
            fflush(stdout);
            clearInputBuffer();
            if (fgets(loan.l_date, sizeof(loan.l_date), stdin) == NULL) {
                printf("Error reading input!\n");
                fclose(fp);
                pause();
                return;
            }
            removeNewline(loan.l_date);
            
            // Read loan type with validation
            do {
                printf("Enter new Loan Type: ");
                fflush(stdout);
                if (fgets(loan.l_type, sizeof(loan.l_type), stdin) == NULL) {
                    printf("Error reading input!\n");
                    fclose(fp);
                    pause();
                    return;
                }
                removeNewline(loan.l_type);
                
                if (strlen(loan.l_type) == 0) {
                    printf("Loan Type cannot be empty! Please enter a valid loan type.\n");
                }
            } while (strlen(loan.l_type) == 0);
            
            printf("Enter new Loan Amount: ");
            scanf("%d", &loan.l_amt);
            clearInputBuffer();
            
            printf("Enter new Duration (months): ");
            scanf("%d", &loan.l_dur);
            
            fwrite(&loan, sizeof(Loan), 1, fp);
            setSuccessColor();
            printf("\nLoan updated successfully!\n");
            resetColor();
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        setErrorColor();
        printf("\nLoan not found!\n");
        resetColor();
    }
    
    pause();
}

void deleteLoan() {
    Loan loan;
    FILE *fp, *temp;
    int loanId, found = 0;
    
    clearScreen();
    setLoanMenuColor();
    printDoubleBorderBox("DELETE LOAN", COLOR_BRIGHT_WHITE, BG_MAGENTA, 55);
    resetColor();
    
    printf("Enter Loan ID to delete: ");
    scanf("%d", &loanId);
    
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
        setSuccessColor();
        printf("\nLoan deleted successfully!\n");
        resetColor();
    } else {
        remove("data/temp.dat");
        setErrorColor();
        printf("\nLoan not found!\n");
        resetColor();
    }
    
    pause();
}

void viewLoans() {
    Loan loan;
    FILE *fp;
    int count = 0;
    
    clearScreen();
    setLoanMenuColor();
    printDoubleBorderBox("VIEW ALL LOANS", COLOR_BRIGHT_WHITE, BG_MAGENTA, 75);
    resetColor();
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        setInfoColor();
        printf("No loans found. File is empty or doesn't exist.\n");
        resetColor();
        pause();
        return;
    }
    
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%-10s %-15s %-15s %-20s %-15s %-10s\n", "Loan ID", "Account No", "Date", "Loan Type", "Amount", "Duration");
    resetColor();
    drawHorizontalLine('-', 85);
    
    while (fread(&loan, sizeof(Loan), 1, fp) == 1) {
        printf("%-10d %-15d %-15s %-20s %-15d %-10d\n", loan.l_id, loan.a_no, loan.l_date, loan.l_type, loan.l_amt, loan.l_dur);
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
