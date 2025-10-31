Developer Documentation


1. Program Overview
This program, called Wallet Manager, is a command-line tool for managing personal financial transactions. Users can add, delete, edit, and generate reports on income and expenses, with data saved to a text file. The program supports dynamic memory allocation and a linked list data structure to handle transactions efficiently.

2. Modules and Data Structures

Modules (Functions)
i. Main Menu and User Interface:
   - main(): Entry point of the program that handles user input and routes to the appropriate functions.

ii. Data Management:
   - loadDatabase(): Reads transaction data from a file into a linked list.
   - saveDatabase(): Saves the linked list of transactions to a file.

iii. Transaction Operations:
   - addTransaction(): Adds a new transaction to the linked list.
   - deleteTransaction(): Deletes a specific transaction by index.
   - editTransaction(): Edits an existing transaction’s details.
   - generateReport(): Generates a summary report of income, expenses, and net balance.

iv. Memory Management:
   - freeTransactionList(): Frees memory allocated for the linked list before program termination.

 Data Structures
i. Date: Holds date information (year, month, day).
ii. Transaction (Linked List Node)**: Each transaction node contains:
   - Date: Date of the transaction.
   - Type: Transaction type, either 'I' (Income) or 'E' (Expense).
   - Category: Category of the transaction.
   - Amount: Transaction amount.
   - Currency: Currency code 
   - next: Pointer to the next transaction in the list.

3. Algorithms
i. Linked List Operations: Adding, deleting, and editing nodes are accomplished through pointer manipulation.
ii. File Parsing: Data is read from and written to a plain text file with comma-separated fields.
iii. Report Generation: Totals for income and expenses are calculated by iterating through the linked list.

4. List of Functions and Interfaces
`loadDatabase()`
- Input: None
- Output: None (loads data into the linked list)
- Description: Loads transaction data from the file `wallet_database.txt` and adds each transaction to the linked list.

`saveDatabase()`
- Input: None
- Output: None (writes linked list data to file)
- Description: Iterates through the linked list and saves each transaction to the database file.

`addTransaction()`
- Input: User-provided date, type, category, amount, and currency.
- Output: None
- Description: Prompts the user for transaction details, creates a new transaction node, and adds it to the head of the linked list.

 `deleteTransaction()`
- Input: Index of the transaction to delete.
- Output: None
- Description: Removes the transaction at the specified index from the linked list.

 `editTransaction()`
- Input: Index of the transaction to edit and new field values.
- Output: None
- Description: Prompts the user to modify fields of a specific transaction in the list.

`generateReport()`
- Input: None
- Output: Displays total income, expense, and net balance.
- Description: Calculates the total income and expense by traversing the list.

`freeTransactionList()`
- Input: None
- Output: None (frees memory)
- Description: Frees each node in the linked list to avoid memory leaks.



