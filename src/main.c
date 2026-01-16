#include <stdio.h>
#include <stdlib.h>
#include "../include/account.h"
#include "../include/transaction.h"
#include "../include/loan.h"
#include "../include/utility.h"

void accountMenu() {
    int choice;
    const char *options[] = {
        "Insert Record",
        "Edit Record",
        "Delete Record",
        "View Records",
        "Back to Main Menu"
    };
    
    do {
        printWelcomeBanner(); // Show welcome banner
        setAccountMenuColor();
        printProfessionalMenu("ACCOUNT MASTER FILE", options, 5, COLOR_BRIGHT_WHITE, BG_GREEN);
        // Keep menu color active for prompt
        
        printf("\n");
        printCenteredPrompt("Enter your choice: ");
        resetColor(); // Reset after prompt
        scanf("%d", &choice);
        clearInputBuffer();
        
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
                clearScreen();
                setErrorColor();
                printf("\n\n");
                printCenteredText("Invalid choice! Please try again.", 80);
                resetColor();
                pause();
        }
    } while(choice != 5);
}

void transactionMenu() {
    int choice;
    const char *options[] = {
        "Insert Record",
        "Edit Record",
        "Delete Record",
        "View Records",
        "Back to Main Menu"
    };
    
    do {
        printWelcomeBanner(); // Show welcome banner
        setTransactionMenuColor();
        printProfessionalMenu("TRANSACTION FILE", options, 5, COLOR_BRIGHT_WHITE, BG_CYAN);
        // Keep menu color active for prompt
        
        printf("\n");
        printCenteredPrompt("Enter your choice: ");
        resetColor(); // Reset after prompt
        scanf("%d", &choice);
        clearInputBuffer();
        
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
                clearScreen();
                setErrorColor();
                printf("\n\n");
                printCenteredText("Invalid choice! Please try again.", 80);
                resetColor();
                pause();
        }
    } while(choice != 5);
}

void loanMenu() {
    int choice;
    const char *options[] = {
        "Insert Record",
        "Edit Record",
        "Delete Record",
        "View Records",
        "Back to Main Menu"
    };
    
    do {
        printWelcomeBanner(); // Show welcome banner
        setLoanMenuColor();
        printProfessionalMenu("LOAN FILE", options, 5, COLOR_BRIGHT_WHITE, BG_MAGENTA);
        // Keep menu color active for prompt
        
        printf("\n");
        printCenteredPrompt("Enter your choice: ");
        resetColor(); // Reset after prompt
        scanf("%d", &choice);
        clearInputBuffer();
        
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
                clearScreen();
                setErrorColor();
                printf("\n\n");
                printCenteredText("Invalid choice! Please try again.", 80);
                resetColor();
                pause();
        }
    } while(choice != 5);
}

void printWelcomeScreen() {
    printWelcomeBanner();
}

int main() {
    int choice;
    const char *options[] = {
        "Account Master File",
        "Transaction File",
        "Loan File",
        "Exit"
    };
    
    printWelcomeScreen();
    
    do {
        setMainMenuColor();
        printProfessionalMenu("MAIN MENU", options, 4, COLOR_BRIGHT_WHITE, BG_BLUE);
        // Keep menu color active for prompt
        
        printf("\n");
        printCenteredPrompt("Enter your choice: ");
        resetColor(); // Reset after prompt
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                accountMenu();
                printWelcomeScreen(); // Show welcome banner again when returning
                break;
            case 2:
                transactionMenu();
                printWelcomeScreen();
                break;
            case 3:
                loanMenu();
                printWelcomeScreen();
                break;
            case 4:
                clearScreen();
                printf("\n\n\n");
                setSuccessColor();
                printCenteredText("Thank you for using Bank Management System!", 80);
                printf("\n\n");
                resetColor();
                exit(0);
            default:
                clearScreen();
                setErrorColor();
                printf("\n\n");
                printCenteredText("Invalid choice! Please try again.", 80);
                resetColor();
                pause();
        }
    } while(choice != 4);
    
    return 0;
}
