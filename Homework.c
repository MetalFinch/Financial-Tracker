#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CATEGORY_LENGTH 50
#define DATABASE_FILE "wallet_database.txt"  // File name for saving transactions

// Define the structure for Date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// Define the structure for a single Transaction node in the linked list
typedef struct Transaction {
    Date date;
    char type;  // 'I' for income, 'E' for expense
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char currency[4];  // Currency code
    struct Transaction *next;  // Pointer to the next transaction in the list
} Transaction;

// Head pointer for the linked list
Transaction *transactionListHead = NULL;

// Function prototypes
void loadDatabase();
void saveDatabase();
void addTransaction();
void deleteTransaction();
void editTransaction();
void generateReport();
void freeTransactionList();
Transaction* createTransaction(Date date, char type, char *category, float amount, char *currency);

// Function to load transactions from the database file into a linked list
void loadDatabase() {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) {
        printf("Database file not found. Starting with an empty database.\n");
        return;
    }

    // Load each transaction from the file and add to the linked list
    while (!feof(file)) {
        Date date;
        char type;
        char category[MAX_CATEGORY_LENGTH];
        float amount;
        char currency[4];

        if (fscanf(file, "%d,%d,%d,%c,%[^,],%f,%s\n",
                   &date.year, &date.month, &date.day,
                   &type, category, &amount, currency) == 7) {
            Transaction *newTransaction = createTransaction(date, type, category, amount, currency);
            newTransaction->next = transactionListHead;
            transactionListHead = newTransaction;  // Add to the head of the list
        }
    }
    fclose(file);
    printf("Database loaded successfully.\n");
}

// Function to save all transactions in the linked list to the database file
void saveDatabase() {
    FILE *file = fopen(DATABASE_FILE, "w");
    if (!file) {
        printf("Error: Could not open file for saving data.\n");
        return;
    }

    Transaction *current = transactionListHead;
    while (current != NULL) {
        fprintf(file, "%d,%d,%d,%c,%s,%.2f,%s\n",
                current->date.year, current->date.month, current->date.day,
                current->type, current->category, current->amount,
                current->currency);
        current = current->next;
    }
    fclose(file);
    printf("Database saved successfully.\n");
}

// Function to create a new transaction dynamically
Transaction* createTransaction(Date date, char type, char *category, float amount, char *currency) {
    Transaction *newTransaction = (Transaction*)malloc(sizeof(Transaction));
    if (newTransaction == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newTransaction->date = date;
    newTransaction->type = type;
    strncpy(newTransaction->category, category, MAX_CATEGORY_LENGTH);
    newTransaction->amount = amount;
    strncpy(newTransaction->currency, currency, 3);
    newTransaction->currency[3] = '\0';  // Ensure currency is null-terminated
    newTransaction->next = NULL;
    return newTransaction;
}

// Function to add a transaction to the linked list
void addTransaction() {
    Date date;
    char type;
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char currency[4];

    printf("Enter date (year month day): ");
    scanf("%d %d %d", &date.year, &date.month, &date.day);
    printf("Enter type (I for income, E for expense): ");
    scanf(" %c", &type);
    printf("Enter category: ");
    scanf("%s", category);
    printf("Enter amount: ");
    scanf("%f", &amount);
    printf("Enter currency: ");
    scanf("%s", currency);

    Transaction *newTransaction = createTransaction(date, type, category, amount, currency);
    newTransaction->next = transactionListHead;
    transactionListHead = newTransaction;
    printf("Transaction added successfully.\n");
}

// Function to delete a transaction by index
void deleteTransaction() {
    if (transactionListHead == NULL) {
        printf("No transactions to delete.\n");
        return;
    }

    int index, i = 0;
    printf("Enter the index of transaction to delete: ");
    scanf("%d", &index);

    Transaction *current = transactionListHead;
    Transaction *previous = NULL;

    while (current != NULL && i < index) {
        previous = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Invalid index.\n");
    } else {
        if (previous == NULL) {
            transactionListHead = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
        printf("Transaction deleted successfully.\n");
    }
}

// Function to edit an existing transaction
void editTransaction() {
    int index, i = 0;
    printf("Enter the index of transaction to edit: ");
    scanf("%d", &index);

    Transaction *current = transactionListHead;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Invalid index.\n");
        return;
    }

    printf("Editing transaction %d\n", index);
    printf("Enter new date (year month day) or -1 to skip: ");
    int newYear, newMonth, newDay;
    scanf("%d %d %d", &newYear, &newMonth, &newDay);
    if (newYear != -1) current->date.year = newYear;
    if (newMonth != -1) current->date.month = newMonth;
    if (newDay != -1) current->date.day = newDay;

    char newType;
    printf("Enter new type (I or E, or '-' to skip): ");
    scanf(" %c", &newType);
    if (newType != '-') current->type = newType;

    char newCategory[MAX_CATEGORY_LENGTH];
    printf("Enter new category or '-' to skip: ");
    scanf("%s", newCategory);
    if (strcmp(newCategory, "-") != 0) strcpy(current->category, newCategory);

    float newAmount;
    printf("Enter new amount or -1 to skip: ");
    scanf("%f", &newAmount);
    if (newAmount != -1) current->amount = newAmount;

    char newCurrency[4];
    printf("Enter new currency or '-' to skip: ");
    scanf("%s", newCurrency);
    if (strcmp(newCurrency, "-") != 0) strcpy(current->currency, newCurrency);

    printf("Transaction edited successfully.\n");
}

// Function to generate a report
void generateReport() {
    float totalIncome = 0, totalExpense = 0;
    Transaction *current = transactionListHead;
    while (current != NULL) {
        if (current->type == 'I') {
            totalIncome += current->amount;
        } else if (current->type == 'E') {
            totalExpense += current->amount;
        }
        current = current->next;
    }
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Net Balance: %.2f\n", totalIncome - totalExpense);
}

// Free the memory used by the transaction linked list
void freeTransactionList() {
    Transaction *current = transactionListHead;
    while (current != NULL) {
        Transaction *next = current->next;
        free(current);
        current = next;
    }
}

// Main program loop
int main() {
    loadDatabase();

    int userChoice;
    do {
        printf("\nWallet Program Menu:\n");
        printf("1. Add Transaction\n");
        printf("2. Delete Transaction\n");
        printf("3. Edit Transaction\n");
        printf("4. Generate Report\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                addTransaction();
                break;
            case 2:
                deleteTransaction();
                break;
            case 3:
                editTransaction();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                saveDatabase();
                freeTransactionList();
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (userChoice != 5);

    return 0;
}


