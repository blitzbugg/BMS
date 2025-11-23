#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>

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

#endif
