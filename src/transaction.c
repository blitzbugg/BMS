#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/transaction.h"
#include "../include/account.h"
#include "../include/utility.h"

#define FILENAME "data/transaction.dat"
#define ACCOUNT_FILE "data/account.dat"

// Helper function to update account balance
int updateAccountBalance(int accountNo, int amount, int transactionType) {
    FILE *fp;
    Account acc;
    int found = 0;
    long int pos;
    
    fp = fopen(ACCOUNT_FILE, "rb+");
    if (fp == NULL) {
        return 0; // Failed to open file
    }
    
    // Find the account
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no == accountNo) {
            found = 1;
            pos = ftell(fp) - sizeof(Account);
            fseek(fp, pos, SEEK_SET);
            
            // Update balance based on transaction type
            if (transactionType == 1) { // Credit
                acc.a_bal += amount;
                setColor(COLOR_BRIGHT_GREEN, COLOR_BLACK << 4);
                printf("Account %d: +%d (Credit). New Balance: %d\n", 
                       accountNo, amount, acc.a_bal);
                resetColor();
            } else if (transactionType == 2) { // Debit
                if (acc.a_bal >= amount) {
                    acc.a_bal -= amount;
                    setColor(COLOR_BRIGHT_RED, COLOR_BLACK << 4);
                    printf("Account %d: -%d (Debit). New Balance: %d\n", 
                           accountNo, amount, acc.a_bal);
                    resetColor();
                } else {
                    setErrorColor();
                    printf("Error: Insufficient balance in account %d! Current balance: %d, Required: %d\n",
                           accountNo, acc.a_bal, amount);
                    resetColor();
                    fclose(fp);
                    return -1; // Insufficient funds
                }
            }
            
            // Write updated account back
            fwrite(&acc, sizeof(Account), 1, fp);
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        setErrorColor();
        printf("Error: Account %d not found while updating balance!\n", accountNo);
        resetColor();
        return 0;
    }
    
    return 1; // Success
}

// Helper function to revert account balance (for edit/delete operations)
int revertAccountBalance(int accountNo, int amount, int transactionType) {
    // Reverse the transaction: if it was credit, now debit; if debit, now credit
    int reverseType = (transactionType == 1) ? 2 : 1;
    return updateAccountBalance(accountNo, amount, reverseType);
}

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
    
    clearScreen();
    setTransactionMenuColor();
    printDoubleBorderBox("INSERT TRANSACTION", COLOR_BRIGHT_WHITE, BG_CYAN, 65);
    resetColor();
    
    // Auto-generate transaction ID
    trans.t_id = getNextId(FILENAME, sizeof(Transaction), 0);
    setInfoColor();
    printf("Auto-generated Transaction ID: ");
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%d\n", trans.t_id);
    resetColor();
    
    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    
    // Cross-validation: Check if account exists
    if (!accountExists(accNo)) {
        setErrorColor();
        printf("Error: Account Number %d does not exist!\n", accNo);
        printf("Please create the account first.\n");
        resetColor();
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
        setErrorColor();
        printf("Invalid transaction type! Use 1 for Credit or 2 for Debit.\n");
        resetColor();
        pause();
        return;
    }
    
    printf("Enter Amount: ");
    scanf("%d", &trans.t_amt);
    
    // Validate amount
    if (trans.t_amt <= 0) {
        setErrorColor();
        printf("Error: Amount must be greater than zero!\n");
        resetColor();
        pause();
        return;
    }
    
    // Update account balance
    int balanceResult = updateAccountBalance(accNo, trans.t_amt, trans.t_type);
    if (balanceResult == -1) {
        setErrorColor();
        printf("Transaction cancelled due to insufficient funds!\n");
        resetColor();
        pause();
        return;
    } else if (balanceResult == 0) {
        setErrorColor();
        printf("Error updating account balance!\n");
        resetColor();
        pause();
        return;
    }

    // Save the transaction
    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        setErrorColor();
        printf("Error opening transaction file!\n");
        resetColor();
        // Revert the balance update since we failed to save transaction
        revertAccountBalance(accNo, trans.t_amt, trans.t_type);
        pause();
        return;
    }
    
    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);
    
    setSuccessColor();
    printf("\nTransaction inserted successfully!\n");
    resetColor();
    pause();
}

void editTransaction() {
    Transaction trans;
    FILE *fp;
    int transId, accNo, found = 0;
    long int pos;
    int oldAccountNo, oldAmount, oldType;
    
    clearScreen();
    setTransactionMenuColor();
    printDoubleBorderBox("EDIT TRANSACTION", COLOR_BRIGHT_WHITE, BG_CYAN, 60);
    resetColor();
    
    printf("Enter Transaction ID to edit: ");
    scanf("%d", &transId);
    
    fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        setErrorColor();
        printf("\nError opening file!\n");
        resetColor();
        pause();
        return;
    }
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (trans.t_id == transId) {
            found = 1;
            pos = ftell(fp) - sizeof(Transaction);
            fseek(fp, pos, SEEK_SET);
            
            setInfoColor();
            printf("\nCurrent Transaction Details:\n");
            resetColor();
            printf("Account Number: %d\n", trans.a_no);
            printf("Date: %s\n", trans.t_date);
            printf("Type: %s\n", (trans.t_type == 1) ? "Credit" : "Debit");
            printf("Amount: %d\n", trans.t_amt);
            
            // Store old values for reverting balance
            oldAccountNo = trans.a_no;
            oldAmount = trans.t_amt;
            oldType = trans.t_type;
            
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
            
            trans.a_no = accNo;
            
            printf("Enter new Date (DD/MM/YYYY): ");
            clearInputBuffer();
            fgets(trans.t_date, sizeof(trans.t_date), stdin);
            removeNewline(trans.t_date);
            
            printf("Enter new Type (1=Credit, 2=Debit): ");
            scanf("%d", &trans.t_type);
            
            if (trans.t_type != 1 && trans.t_type != 2) {
                setErrorColor();
                printf("Invalid transaction type! Use 1 for Credit or 2 for Debit.\n");
                resetColor();
                fclose(fp);
                pause();
                return;
            }

            printf("Enter new Amount: ");
            scanf("%d", &trans.t_amt);
            
            // Validate amount
            if (trans.t_amt <= 0) {
                setErrorColor();
                printf("Error: Amount must be greater than zero!\n");
                resetColor();
                fclose(fp);
                pause();
                return;
            }
            
            // First, revert the old transaction from old account
            if (revertAccountBalance(oldAccountNo, oldAmount, oldType) != 1) {
                setErrorColor();
                printf("Error reverting old transaction balance!\n");
                resetColor();
                fclose(fp);
                pause();
                return;
            }
            
            // Then, apply the new transaction to the new account
            int balanceResult = updateAccountBalance(accNo, trans.t_amt, trans.t_type);
            if (balanceResult == -1) {
                setErrorColor();
                printf("Transaction cancelled due to insufficient funds!\n");
                resetColor();
                // Revert the reversion since we failed to apply new transaction
                updateAccountBalance(oldAccountNo, oldAmount, oldType);
                fclose(fp);
                pause();
                return;
            } else if (balanceResult == 0) {
                setErrorColor();
                printf("Error updating account balance!\n");
                resetColor();
                // Revert the reversion since we failed to apply new transaction
                updateAccountBalance(oldAccountNo, oldAmount, oldType);
                fclose(fp);
                pause();
                return;
            }
            
            // Save the updated transaction
            fwrite(&trans, sizeof(Transaction), 1, fp);
            setSuccessColor();
            printf("\nTransaction updated successfully!\n");
            resetColor();
            break;
        }
    }
    
    fclose(fp);
    
    if (!found) {
        setErrorColor();
        printf("\nTransaction not found!\n");
        resetColor();
    }
    
    pause();
}

void deleteTransaction() {
    Transaction trans;
    FILE *fp, *temp;
    int transId, found = 0;
    
    clearScreen();
    setTransactionMenuColor();
    printDoubleBorderBox("DELETE TRANSACTION", COLOR_BRIGHT_WHITE, BG_CYAN, 65);
    resetColor();
    
    printf("Enter Transaction ID to delete: ");
    scanf("%d", &transId);
    
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
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        if (trans.t_id != transId) {
            fwrite(&trans, sizeof(Transaction), 1, temp);
        } else {
            found = 1;
            // Revert the account balance change
            int result = revertAccountBalance(trans.a_no, trans.t_amt, trans.t_type);
            if (result == 1) {
                setInfoColor();
                printf("\nTransaction %d reversed from account %d\n", transId, trans.a_no);
                resetColor();
            } else if (result == -1) {
                setErrorColor();
                printf("\nWarning: Could not fully reverse transaction due to insufficient funds!\n");
                resetColor();
            } else {
                setErrorColor();
                printf("\nWarning: Could not update account balance for transaction reversal!\n");
                resetColor();
            }
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if (found) {
        remove(FILENAME);
        rename("data/temp.dat", FILENAME);
        setSuccessColor();
        printf("\nTransaction deleted successfully!\n");
        resetColor();
    } else {
        remove("data/temp.dat");
        setErrorColor();
        printf("\nTransaction not found!\n");
        resetColor();
    }
    
    pause();
}

void viewTransactions() {
    Transaction trans;
    FILE *fp;
    int count = 0;
    char typeStr[10];
    
    clearScreen();
    setTransactionMenuColor();
    printDoubleBorderBox("VIEW ALL TRANSACTIONS", COLOR_BRIGHT_WHITE, BG_CYAN, 75);
    resetColor();
    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        setInfoColor();
        printf("No transactions found. File is empty or doesn't exist.\n");
        resetColor();
        pause();
        return;
    }
    
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("%-15s %-15s %-15s %-15s %-15s\n", "Transaction ID", "Account No", "Date", "Type", "Amount");
    resetColor();
    drawHorizontalLine('-', 75);
    
    while (fread(&trans, sizeof(Transaction), 1, fp) == 1) {
        strcpy(typeStr, (trans.t_type == 1) ? "Credit" : "Debit");
        printf("%-15d %-15d %-15s %-15s %-15d\n", trans.t_id, trans.a_no, trans.t_date, typeStr, trans.t_amt);
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
