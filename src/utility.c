#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("\nPress Enter to continue...");
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

