#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <windows.h>

// Color constants for Windows console
#define COLOR_BLACK         0
#define COLOR_BLUE          1
#define COLOR_GREEN         2
#define COLOR_CYAN          3
#define COLOR_RED           4
#define COLOR_MAGENTA       5
#define COLOR_YELLOW        6
#define COLOR_WHITE         7
#define COLOR_BRIGHT_BLACK  8
#define COLOR_BRIGHT_BLUE   9
#define COLOR_BRIGHT_GREEN  10
#define COLOR_BRIGHT_CYAN   11
#define COLOR_BRIGHT_RED    12
#define COLOR_BRIGHT_MAGENTA 13
#define COLOR_BRIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE  15

// Background colors
#define BG_BLUE      (COLOR_BLUE << 4)
#define BG_GREEN     (COLOR_GREEN << 4)
#define BG_CYAN      (COLOR_CYAN << 4)
#define BG_RED       (COLOR_RED << 4)
#define BG_MAGENTA   (COLOR_MAGENTA << 4)
#define BG_YELLOW    (COLOR_YELLOW << 4)
#define BG_WHITE     (COLOR_WHITE << 4)
#define BG_BRIGHT_BLUE    (COLOR_BRIGHT_BLUE << 4)
#define BG_BRIGHT_GREEN   (COLOR_BRIGHT_GREEN << 4)
#define BG_BRIGHT_CYAN    (COLOR_BRIGHT_CYAN << 4)
#define BG_BRIGHT_RED     (COLOR_BRIGHT_RED << 4)
#define BG_BRIGHT_MAGENTA (COLOR_BRIGHT_MAGENTA << 4)
#define BG_BRIGHT_YELLOW  (COLOR_BRIGHT_YELLOW << 4)
#define BG_BRIGHT_WHITE   (COLOR_BRIGHT_WHITE << 4)

// Get next auto-increment ID from a binary file
int getNextId(const char *filename, size_t recordSize, int offset);

// Check if account exists
int accountExists(int accountNo);

// Clear input buffer
void clearInputBuffer();

// Pause execution until user presses Enter
void pause();

// Print formatted header
void printHeader(const char *title);

// Remove trailing newline from string
void removeNewline(char *str);

// GUI Functions
void clearScreen();
void setColor(int textColor, int bgColor);
void resetColor();
void centerText(const char *text, int width);
void printCenteredHeader(const char *title, int textColor, int bgColor, int width);
void printBox(const char *title, int textColor, int bgColor);
void printMenuBox(const char *title, const char *options[], int optionCount, int textColor, int bgColor);
void printCenteredLine(const char *text, int width);
void drawHorizontalLine(char ch, int length);

// Professional GUI Functions
void printCenteredText(const char *text, int totalWidth);
void printDoubleBorderBox(const char *title, int textColor, int bgColor, int width);
void printProfessionalMenu(const char *title, const char *options[], int optionCount, int textColor, int bgColor);
void printWelcomeBanner();
void printCenteredPrompt(const char *prompt);
int getConsoleWidth();
void printSeparator(int width, char ch);
void printStyledBox(const char *title, int textColor, int bgColor, int width, int height);
void printDecoratedMenuHeader(const char *title, int textColor, int bgColor);

// Menu-specific color schemes
void setMainMenuColor();
void setAccountMenuColor();
void setTransactionMenuColor();
void setLoanMenuColor();
void setSuccessColor();
void setErrorColor();
void setInfoColor();

#endif
