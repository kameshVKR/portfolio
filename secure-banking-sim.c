#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    
 #define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
    char username[50];
    char password[50];
    int start_choice;

    

    printf("WELCOME TO THE XYZ BANK\n");
    printf("1. Fresh Registration\n");
    printf("2. Login to Existing Account\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &start_choice);

    int login_success = 0; 
    
    if (start_choice == 1) {
        printf("\n--- REGISTRATION ---\n");
        printf("enter your user name here: ");
        scanf("%49s", username);
        
        if (strlen(username) < 6){
            printf("INVALID USERNAME: the user name must contain at least 6 characters\n");
            return 0; 
        }
        
        printf("loading the page...\n");
        printf("create your password it must at least contain 8 characters: ");
        scanf("%49s", password);
        
        if (strlen(password) < 8) {
            printf("INVALID PASSWORD: the password must contain at least 8 characters\n");
            return 0; 
        }

        // Save new user to file
        FILE *user_file = fopen("users.txt", "a");
        if (user_file != NULL) {
            fprintf(user_file, "%s %s\n", username, password);
            fclose(user_file);
            printf("Registration successful and saved!\n");
            login_success = 1; 
        }
    }
    
    else if (start_choice == 2) {
        char saved_username[50];
        char saved_password[50];
        
        printf("\n--- LOGIN ---\n");
        printf("Enter your username: ");
        scanf("%49s", username);
        printf("Enter your password: ");
        scanf("%49s", password);

        // Open file in read mode ("r")
        FILE *user_file = fopen("users.txt", "r");
        if (user_file == NULL) {
            printf("No registered users found. Please register first.\n");
            return 0;
        }

        
        while (fscanf(user_file, "%s %s", saved_username, saved_password) != EOF) {
            if (strcmp(username, saved_username) == 0 && strcmp(password, saved_password) == 0) {
                login_success = 1; 
                break; 
            }
        }
        fclose(user_file);

        if (login_success == 1) {
            printf("Login successful!\n");
        } else {
            printf("INVALID CREDENTIALS: Username or password incorrect.\n");
        }
    }
    else {
        printf("Invalid choice selected.\n");
    }

   
    if (login_success == 1) {
        printf("loading the user details...\n");
        int bank_balance = 100000;
        int deposit1;
        int withdraw1;
        char choise[20]; 

        int running = 1; 
        while (running == 1) {
            printf("\nENTER (deposit / withdraw / exit): ");
            scanf("%s", choise); 

            if (strcmp(choise, "exit") == 0) {
                printf("Thank you for using XYZ Bank. Goodbye!\n");
                running = 0; 
            }
            else if (strcmp(choise, "deposit") == 0) { 
                printf("enter your amount here: ");
                scanf("%d", &deposit1);
                
                bank_balance = bank_balance + deposit1; 
                printf("new balance %d\n", bank_balance);

                FILE *history = fopen("bank_records.txt", "a");
                if (history != NULL) {
                    fprintf(history, "User: %s | Deposit: %d | New Balance: %d\n", username, deposit1, bank_balance);
                    fclose(history);
                }
            }
            else if (strcmp(choise, "withdraw") == 0) { 
                printf("enter your amount here: ");
                scanf("%d", &withdraw1);
                
                bank_balance = bank_balance - withdraw1; 
                printf("new balance %d\n", bank_balance); 

                FILE *history = fopen("bank_records.txt", "a");
                if (history != NULL) {
                    fprintf(history, "User: %s | Withdraw: %d | New Balance: %d\n", username, withdraw1, bank_balance);
                    fclose(history);
                }
            }
            else {
                printf("Invalid choice! Please try again.\n");
            }
        } 
    }

    return 0;
}
