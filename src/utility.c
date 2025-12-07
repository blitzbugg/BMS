#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/utility.h"
#include "../include/account.h"

int getNextId(const char *filename, size_t recordSize, int offset) {
    FILE *fp;
    int maxId = 0;
    int currentId;
    void *record = malloc(recordSize);
    
    if (record == NULL) {
        return 1; // Start from 1 if memory allocation fails
    }
    
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        free(record);
        return 1; // File doesn't exist, start from 1
    }
    
    // Read all records and find maximum ID
    while (fread(record, recordSize, 1, fp) == 1) {
        memcpy(&currentId, (char*)record + offset, sizeof(int));
        if (currentId > maxId) {
            maxId = currentId;
        }
    }
    
    fclose(fp);
    free(record);
    
    return maxId + 1; // Return next ID
}

int accountExists(int accountNo) {
    FILE *fp;
    Account acc;
    
    fp = fopen("data/account.dat", "rb");
    if (fp == NULL) {
        return 0; // File doesn't exist, so account doesn't exist
    }
    
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        if (acc.a_no == accountNo) {
            fclose(fp);
            return 1; // Account exists
        }
    }
    
    fclose(fp);
    return 0; // Account not found
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause() {
    setColor(COLOR_BRIGHT_YELLOW, COLOR_BLACK << 4);
    printf("\nPress Enter to continue...");
    resetColor();
    clearInputBuffer();
    getchar();
}

void printHeader(const char *title) {
    int len = strlen(title);
    int i;
    
    printf("\n");
    for (i = 0; i < len + 4; i++) {
        printf("=");
    }
    printf("\n  %s\n", title);
    for (i = 0; i < len + 4; i++) {
        printf("=");
    }
    printf("\n");
}

void removeNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// GUI Functions Implementation
void clearScreen() {
    system("cls");
}

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | bgColor);
}

void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_WHITE | (COLOR_BLACK << 4));
}

void centerText(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    int i;
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (i = padding + len; i < width; i++) {
        printf(" ");
    }
}

void printCenteredHeader(const char *title, int textColor, int bgColor, int width) {
    int len = strlen(title);
    int boxWidth = len + 6; // Add padding for borders
    if (boxWidth < width) {
        boxWidth = width;
    }
    
    setColor(textColor, bgColor);
    printf("\n");
    
    // Top border
    int padding = (80 - boxWidth) / 2;
    int i;
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < boxWidth; i++) {
        printf("=");
    }
    printf("\n");
    
    // Title line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("  %s", title);
    for (i = len + 4; i < boxWidth; i++) {
        printf(" ");
    }
    printf("\n");
    
    // Bottom border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < boxWidth; i++) {
        printf("=");
    }
    printf("\n\n");
    
    resetColor();
}

void printBox(const char *title, int textColor, int bgColor) {
    int width = 70;
    printCenteredHeader(title, textColor, bgColor, width);
}

void printMenuBox(const char *title, const char *options[], int optionCount, int textColor, int bgColor) {
    int width = 70;
    int i, j;
    int padding = (80 - width) / 2;
    
    clearScreen();
    
    setColor(textColor, bgColor);
    
    // Top border
    printf("\n");
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < width; i++) {
        printf("=");
    }
    printf("\n");
    
    // Title
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    int titleLen = strlen(title);
    int titlePadding = (width - titleLen) / 2;
    for (i = 0; i < titlePadding; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (i = titlePadding + titleLen; i < width; i++) {
        printf(" ");
    }
    printf("\n");
    
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < width; i++) {
        printf("=");
    }
    printf("\n\n");
    
    // Menu options
    for (i = 0; i < optionCount; i++) {
        for (j = 0; j < padding; j++) {
            printf(" ");
        }
        int optionPadding = (width - strlen(options[i]) - 4) / 2;
        for (j = 0; j < optionPadding; j++) {
            printf(" ");
        }
        printf("%d. %s\n", i + 1, options[i]);
    }
    
    printf("\n");
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < width; i++) {
        printf("=");
    }
    printf("\n\n");
    
    resetColor();
}

void printCenteredLine(const char *text, int width) {
    centerText(text, width);
    printf("\n");
}

void drawHorizontalLine(char ch, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

// Menu-specific color schemes
void setMainMenuColor() {
    setColor(COLOR_BRIGHT_WHITE, BG_BLUE);
}

void setAccountMenuColor() {
    setColor(COLOR_BRIGHT_WHITE, BG_GREEN);
}

void setTransactionMenuColor() {
    setColor(COLOR_BRIGHT_WHITE, BG_CYAN);
}

void setLoanMenuColor() {
    setColor(COLOR_BRIGHT_WHITE, BG_MAGENTA);
}

void setSuccessColor() {
    setColor(COLOR_BRIGHT_GREEN, COLOR_BLACK << 4);
}

void setErrorColor() {
    setColor(COLOR_BRIGHT_RED, COLOR_BLACK << 4);
}

void setInfoColor() {
    setColor(COLOR_BRIGHT_CYAN, COLOR_BLACK << 4);
}

// Professional GUI Functions Implementation
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return 80; // Default width
}

void printCenteredText(const char *text, int totalWidth) {
    int len = strlen(text);
    int padding = (totalWidth - len) / 2;
    int i;
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

void printSeparator(int width, char ch) {
    int padding = (80 - width) / 2;
    int i;
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    for (i = 0; i < width; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

void printDoubleBorderBox(const char *title, int textColor, int bgColor, int width) {
    int len = strlen(title);
    int padding = (80 - width) / 2;
    int i;
    
    setColor(textColor, bgColor);
    
    // Top border with double line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)201); // ╔ Top-left corner
    for (i = 0; i < width - 2; i++) {
        printf("%c", (char)205); // ═ Horizontal line
    }
    printf("%c\n", (char)187); // ╗ Top-right corner
    
    // Title line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)186); // ║ Vertical line
    int titlePadding = (width - 2 - len) / 2;
    for (i = 0; i < titlePadding; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (i = titlePadding + len; i < width - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)186); // ║ Vertical line
    
    // Bottom border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)200); // ╚ Bottom-left corner
    for (i = 0; i < width - 2; i++) {
        printf("%c", (char)205); // ═ Horizontal line
    }
    printf("%c\n\n", (char)188); // ╝ Bottom-right corner
    
    resetColor();
}

void printProfessionalMenu(const char *title, const char *options[], int optionCount, int textColor, int bgColor) {
    clearScreen();
    
    int consoleWidth = getConsoleWidth();
    int boxWidth = 60;
    int padding = (consoleWidth - boxWidth) / 2;
    int i, j, maxOptionLen = 0;
    
    // Find longest option for proper alignment
    for (i = 0; i < optionCount; i++) {
        int optLen = strlen(options[i]);
        if (optLen > maxOptionLen) {
            maxOptionLen = optLen;
        }
    }
    
    // Add vertical spacing at top
    printf("\n\n");
    
    setColor(textColor, bgColor);
    
    // Top border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)218); // ╔
    for (i = 0; i < boxWidth - 2; i++) {
        printf("%c", (char)196); // ─
    }
    printf("%c\n", (char)191); // ┐
    
    // Title line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179); // │
    int titleLen = strlen(title);
    int titlePadding = (boxWidth - 2 - titleLen) / 2;
    for (i = 0; i < titlePadding; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (i = titlePadding + titleLen; i < boxWidth - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179); // │
    
    // Separator after title
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)195); // ├
    for (i = 0; i < boxWidth - 2; i++) {
        printf("%c", (char)196); // ─
    }
    printf("%c\n", (char)180); // ┤
    
    // Menu options with perfect centering
    for (i = 0; i < optionCount; i++) {
        for (j = 0; j < padding; j++) {
            printf(" ");
        }
        printf("%c", (char)179); // │
        
        // Center the option text
        int optLen = strlen(options[i]);
        int optPadding = (boxWidth - 2 - optLen - 4) / 2; // -4 for "X. "
        
        for (j = 0; j < optPadding; j++) {
            printf(" ");
        }
        printf("%d. %s", i + 1, options[i]);
        
        // Fill remaining space
        int remaining = boxWidth - 2 - optPadding - optLen - 4;
        for (j = 0; j < remaining; j++) {
            printf(" ");
        }
        printf("%c\n", (char)179); // │
    }
    
    // Bottom border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)192); // └
    for (i = 0; i < boxWidth - 2; i++) {
        printf("%c", (char)196); // ─
    }
    printf("%c\n\n", (char)217); // ┘
    
    // Don't reset color here - keep menu background active for prompt
    // resetColor() will be called after printCenteredPrompt() in main.c
}

void printWelcomeBanner() {
    clearScreen();
    
    int consoleWidth = getConsoleWidth();
    int bannerWidth = 70;
    int padding = (consoleWidth - bannerWidth) / 2;
    int i;
    
    // Add top spacing
    printf("\n\n\n");
    
    setMainMenuColor();
    
    // Top decorative border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)218);
    for (i = 0; i < bannerWidth - 2; i++) {
        printf("%c", (char)196);
    }
    printf("%c\n", (char)191);
    
    // Empty line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179);
    for (i = 0; i < bannerWidth - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179);
    
    // Main title - centered
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179);
    int titleLen = strlen("  BANK MANAGEMENT SYSTEM");
    int titlePadding = (bannerWidth - 2 - titleLen) / 2;
    for (i = 0; i < titlePadding; i++) {
        printf(" ");
    }
    setColor(COLOR_BRIGHT_YELLOW, BG_BLUE);
    printf("  BANK MANAGEMENT SYSTEM");
    setMainMenuColor();
    for (i = titlePadding + titleLen; i < bannerWidth - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179);
    
    // Subtitle - centered
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179);
    int subTitleLen = strlen("  Professional Banking Solution");
    int subTitlePadding = (bannerWidth - 2 - subTitleLen) / 2;
    for (i = 0; i < subTitlePadding; i++) {
        printf(" ");
    }
    setColor(COLOR_BRIGHT_CYAN, BG_BLUE);
    printf("  Professional Banking Solution");
    setMainMenuColor();
    for (i = subTitlePadding + subTitleLen; i < bannerWidth - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179);
    
    // Empty line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179);
    for (i = 0; i < bannerWidth - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179);
    
    // Bottom decorative border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)192);
    for (i = 0; i < bannerWidth - 2; i++) {
        printf("%c", (char)196);
    }
    printf("%c\n\n\n", (char)217);
    
    resetColor();
}

void printCenteredPrompt(const char *prompt) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD originalAttribs = 0;
    int consoleWidth = getConsoleWidth();
    int promptLen = strlen(prompt);
    int padding = (consoleWidth - promptLen) / 2;
    int i;
    
    // Get current console attributes to preserve menu background color
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        originalAttribs = csbi.wAttributes;
    } else {
        // If we can't get attributes, use default
        originalAttribs = COLOR_WHITE | (COLOR_BLACK << 4);
    }
    
    // Extract background color from current attributes (preserve menu background)
    WORD bgColor = originalAttribs & 0xF0; // Upper 4 bits are background
    
    // Print padding spaces with current attributes (preserves menu background)
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    
    // Set only the foreground (text) color, preserve the background color
    WORD newAttribs = COLOR_BRIGHT_WHITE | bgColor;
    SetConsoleTextAttribute(hConsole, newAttribs);
    printf("%s", prompt);
    
    // Restore original console attributes (includes menu background color)
    SetConsoleTextAttribute(hConsole, originalAttribs);
    printf("\n");
}

void printStyledBox(const char *title, int textColor, int bgColor, int width, int height) {
    int len = strlen(title);
    int consoleWidth = getConsoleWidth();
    int padding = (consoleWidth - width) / 2;
    int i, j;
    
    setColor(textColor, bgColor);
    
    // Top border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)218);
    for (i = 0; i < width - 2; i++) {
        printf("%c", (char)196);
    }
    printf("%c\n", (char)191);
    
    // Title line
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)179);
    int titlePadding = (width - 2 - len) / 2;
    for (i = 0; i < titlePadding; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (i = titlePadding + len; i < width - 2; i++) {
        printf(" ");
    }
    printf("%c\n", (char)179);
    
    // Separator
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)195);
    for (i = 0; i < width - 2; i++) {
        printf("%c", (char)196);
    }
    printf("%c\n", (char)180);
    
    // Empty lines for content area
    for (j = 0; j < height - 3; j++) {
        for (i = 0; i < padding; i++) {
            printf(" ");
        }
        printf("%c", (char)179);
        for (i = 0; i < width - 2; i++) {
            printf(" ");
        }
        printf("%c\n", (char)179);
    }
    
    // Bottom border
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%c", (char)192);
    for (i = 0; i < width - 2; i++) {
        printf("%c", (char)196);
    }
    printf("%c\n\n", (char)217);
    
    resetColor();
}

