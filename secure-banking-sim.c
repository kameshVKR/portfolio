#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define BUFFER_SIZE 256

typedef struct {
    int id;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN]; 
    int balance;
} User;

User users[MAX_USERS];
int user_count = 0;
int current_user_index = -1; 

void log_event(const char *tag, const char *message) {
    FILE *file = fopen("bank_logs.txt", "a");
    if (file != NULL) {
        fprintf(file, "[%s] %s\n", tag, message);
        fclose(file);
    }
}

void load_database() {
    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        user_count = 0;
        return;
    }
    
    user_count = 0;
    while (user_count < MAX_USERS && 
           fscanf(file, "%d %49s %49s %d", 
                  &users[user_count].id, 
                  users[user_count].username, 
                  users[user_count].password, 
                  &users[user_count].balance) == 4) {
        user_count++;
    }
    fclose(file);
}

void save_database() {
    FILE *file = fopen("database.txt", "w");
    if (file == NULL) {
        printf("[ERROR] Failed to save data to database.txt!\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%d %s %s %d\n", users[i].id, users[i].username, users[i].password, users[i].balance);
    }
    fclose(file);
}

void handle_register() {
    if (user_count >= MAX_USERS) {
        printf("\n[ERROR] System storage full. Cannot register new accounts.\n");
        return;
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char log_msg[BUFFER_SIZE];

    printf("\n=== CREATE ACCOUNT ===\n");
    printf("Enter new username (min 6 chars): ");
    if (scanf("%49s", username) != 1) return;

    if (strlen(username) < 6) {
        printf("[INVALID] Username is too short!\n");
        log_event("REGISTRATION_REJECTED", "Username below minimum length constraint.");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("[INVALID] Username already exists!\n");
            return;
        }
    }

    printf("Enter new password (min 8 chars): ");
    if (scanf("%49s", password) != 1) return;

    if (strlen(password) < 8) {
        printf("[INVALID] Password is too short!\n");
        return;
    }
    users[user_count].id = 1000 + user_count; 
    strncpy(users[user_count].username, username, USERNAME_LEN);
    strncpy(users[user_count].password, password, PASSWORD_LEN);
    users[user_count].balance = 0; 

    snprintf(log_msg, sizeof(log_msg), "Account #%d registered for user '%s'", users[user_count].id, username);
    log_event("REGISTRATION_SUCCESS", log_msg);

    printf("\n[SUCCESS] Registration complete! Your Account Number is: %d\n", users[user_count].id);
    user_count++;
    save_database();
}
void handle_login() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char log_msg[BUFFER_SIZE];

    printf("\n=== USER LOGIN ===\n");
    printf("Username: ");
    if (scanf("%49s", username) != 1) return;
    printf("Password: ");
    if (scanf("%49s", password) != 1) return;

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            current_user_index = i;
            snprintf(log_msg, sizeof(log_msg), "User '%s' logged in successfully.", username);
            log_event("AUTH_SUCCESS", log_msg);
            printf("\n[SUCCESS] Welcome back, %s!\n", users[i].username);
            return;
        }
    }

    printf("\n[ERROR] Invalid credentials provided.\n");
    snprintf(log_msg, sizeof(log_msg), "Failed login attempt for username: '%s'", username);
    log_event("SECURITY_ALERT", log_msg);
}

void handle_banking_operations() {
    char input_buffer[BUFFER_SIZE];
    int selection = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (current_user_index != -1) {
        printf("\n--- ACCOUNT DASHBOARD (Acc: %d) ---\n", users[current_user_index].id);
        printf("1. Check Balance\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Logout\n");
        printf("Select an option (1-4): ");
        
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) continue;
        if (sscanf(input_buffer, "%d", &selection) != 1) {
            printf("[INVALID] Please type a valid numerical choice.\n");
            continue;
        }

        if (selection == 1) {
            printf("\n>> Current Available Balance: $%d\n", users[current_user_index].balance);
        } 
        else if (selection == 2) {
            int amount = 0;
            char log_msg[BUFFER_SIZE];
            printf("Enter deposit amount: $");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) && sscanf(input_buffer, "%d", &amount) == 1) {
                if (amount <= 0) {
                    printf("[ERROR] Deposit value must be a positive integer.\n");
                } else {
                    users[current_user_index].balance += amount;
                    save_database();
                    printf("[SUCCESS] Deposited $%d. New Balance: $%d\n", amount, users[current_user_index].balance);
                    
                    snprintf(log_msg, sizeof(log_msg), "Acc %d deposited $%d", users[current_user_index].id, amount);
                    log_event("TRANSACTION", log_msg);
                }
            } else {
                printf("[INVALID] Input format rejected.\n");
            }
        } 
        else if (selection == 3) {
            int amount = 0;
            char log_msg[BUFFER_SIZE];
            printf("Enter withdrawal amount: $");
            if (fgets(input_buffer, sizeof(input_buffer), stdin) && sscanf(input_buffer, "%d", &amount) == 1) {
                if (amount <= 0) {
                    printf("[ERROR] Withdrawal value must be a positive integer.\n");
                } else if (amount > users[current_user_index].balance) {
                    printf("[DENIED] Insufficient account balance.\n");
                } else {
                    users[current_user_index].balance -= amount;
                    save_database();
                    printf("[SUCCESS] Withdrew $%d. New Balance: $%d\n", amount, users[current_user_index].balance);
                    
                    snprintf(log_msg, sizeof(log_msg), "Acc %d withdrew $%d", users[current_user_index].id, amount);
                    log_event("TRANSACTION", log_msg);
                }
            } else {
                printf("[INVALID] Input format rejected.\n");
            }
        } 
        else if (selection == 4) {
            printf("\n[INFO] Logging out. Thank you for banking with XYZ Bank!\n");
            current_user_index = -1; 
        } 
        else {
            printf("[INVALID] Out of range option selected.\n");
        }
    }
}

int main() {
    load_database();
    char input_buffer[BUFFER_SIZE];
    int choice = 0;
    printf("       WELCOME TO THE XYZ BANKING SYSTEM    \n");
    while (1) {
        printf("\nMAIN GATEWAY:\n");
        printf("1. Register Account\n");
        printf("2. Login to Account\n");
        printf("3. Exit System\n");
        printf("Enter selection (1-3): ");

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) break;
        if (sscanf(input_buffer, "%d", &choice) != 1) {
            printf("[INVALID] Please select a numerical option from the menu.\n");
            continue;
        }

        switch (choice) {
            case 1:
                handle_register();
                break;
            case 2:
                handle_login();
                if (current_user_index != -1) {
                    handle_banking_operations();
                }
                break;
            case 3:
                printf("\nShutting down system gateway. Goodbye!\n");
                return 0;
            default:
                printf("[INVALID] Out of range option selected.\n");
        }
    }
    return 0;
}
