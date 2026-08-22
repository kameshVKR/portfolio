#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

int main(void) {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int start_choice;



    printf("WELCOME TO THE JPMorgan chase BANK\n");
    printf("Terms & Conditions\n\n"
           "Copyright & Trademarks: Content is owned by JPMorgan Chase & Co. or its subsidiaries. Unauthorized use is prohibited. Trademarks include \"JPMorgan,\" \"Chase,\" and the Octagon Symbol [1].\n\n"
           "Web Content & Liability: Information is provided \"as is\" without warranties. JPMorgan Chase may update or change the site without notice. Users are responsible for checking for updates [1].\n\n"
           "Limitation of Liability: JPMorgan Chase is not liable for any damages, including direct, indirect, or consequential, arising from the use of the site [1].\n\n"
           "Links & Legal: Links to other sites are provided for convenience, but JPMorgan Chase does not control or endorse them. Usage is subject to New York law [1].\n\n"
           "Copyright \u00A9 2026 JPMorgan Chase & Co. All rights reserved.\n");
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
 printf("thanks for choosing JPMorgan chase for your  banking we are exicited for your next visit ");
 printf("~JPMorgan support team ");
 // Printing the JPMorganChase announcement text
    printf("JPMorganChase Investments and Commitments\n\n");

    printf("1. Small Business Support in Southern California\n");
    printf("JPMorganChase, the Official Bank of Team USA and the LA28 Olympic and Paralympic Games, is expanding its support for small businesses in Southern California.\n");
    printf("- The firm is growing its team of business bankers in the region by nearly 30%%.\n");
    printf("- It plans to expand the Coaching for Impact program to graduate over 3,700 additional entrepreneurs across Greater Los Angeles and Riverside over the next five years.\n");
    printf("- The bank is providing more than $1 million in new philanthropic funding to strengthen the local small business ecosystem, adding to the $15 million deployed since 2020.\n\n");

    printf("2. Affordable Housing and Homeownership\n");
    printf("The firm is increasing its housing goals through its American Dream Initiative, aiming to deploy $750 billion through 2035.\n");
    printf("- This new target represents an increase of more than $200 billion over previous goals.\n");
    printf("- The expanded financing and policy engagement aim to help build or preserve 1,000,000 affordable housing units.\n");
    printf("- The initiative is designed to help 500,000 customers purchase their own homes.\n\n");

    printf("3. Strengthening Shipbuilding in Philadelphia\n");
    printf("JPMorganChase has announced a $24 million investment to support Philadelphia's shipbuilding industry and America's defense industrial base.\n");
    printf("- The funding will support regional collaboration and workforce training programs.\n");
    printf("- It will help small business suppliers connect with national competitiveness and resilience priorities.\n");
    printf("- The investment links local job and business opportunities directly to national defense needs.\n");

    return 0;
}

