#include <stdio.h>
#include <string.h>

#define MAX_RESERVATIONS 5
#define MAX_NAME_LEN 50

typedef struct { /* typedef is making the code easier; instead of writing "struct Reservation res", 
				the programmar can write "Reservation res" */
    char name[MAX_NAME_LEN]; // these 3 are members of the structure Reservation
    int table_size;
    char status[10];
} Reservation; // Reservation is a structure 

Reservation lunch_res[MAX_RESERVATIONS]; // lunch_res and dinner_res are Reservation's object arrays
Reservation dinner_res[MAX_RESERVATIONS]; // These objects are initialized to later used in the main() function

void initialize_reservations(Reservation res[], int size) { //initializing reservations
    int i;
	for (i = 0; i < size; i++) { // making sure that all the tables are empty and are not reserved
        strcpy(res[i].status, "empty");
        res[i].table_size = 0;
        
    }
}

void add_reservation(Reservation res[], const char *meal_name) { // function to add reservation
    int table;
    printf("Select a table (1-%d): ", MAX_RESERVATIONS);
    scanf("%d", &table);
    getchar(); 

    if (table < 1 || table > MAX_RESERVATIONS) { // to handle error; preventing the user to select wrong table
        printf("Invalid table selection.\n");
        return;
    }

    table--; // Convert to 0-based index
    if (strcmp(res[table].status, "reserved") == 0) { // alerting the user if the table is already reserved
        printf("Table %d is already reserved.\n", table + 1);
        return;
    }

    printf("Enter customer name: ");
    fgets(res[table].name, MAX_NAME_LEN, stdin); // using fgets to avoid spacing issues
    res[table].name[strcspn(res[table].name, "\n")] = '\0'; // to remove new line

    while(1){
    printf("Enter table size (upto 10): "); // taking the table size the user wants
    scanf("%d", &res[table].table_size);
    if(res[table].table_size > 10){
        printf("Table size cannot exceed 10\n");
    }
    else{
        break;
    }
    }

    strcpy(res[table].status, "reserved"); /* after reserving the table for the user, 
											making sure that the table remains reserved and isn't reserved by others */
    printf("Table %d reserved for %s (%d people).\n", table + 1, res[table].name, res[table].table_size);
}

void view_reservations(Reservation res[], const char *meal_name) { // function to view reservation
    printf("\n%s Reservations:\n", meal_name);
    int i;
    for (i = 0; i < MAX_RESERVATIONS; i++) {
        if (strcmp(res[i].status, "reserved") == 0) { //reserving the tables
            printf("Table %d: %s (%d people)\n", i + 1, res[i].name, res[i].table_size);
        } else {
            printf("Table %d: Available\n", i + 1);
        }
    }
}

void remove_reservation(Reservation res[], const char *meal_name) { // function to remove reservation
    int table;
    printf("Select a table to cancel (1-%d): ", MAX_RESERVATIONS); // selecting a table
    scanf("%d", &table);
    

    if (table < 1 || table > MAX_RESERVATIONS) { // to handle error related to wrong table choosing
        printf("Invalid table selection.\n");
        return;
    }

    table--; // as indexes start from 0, so we decrement the table value so it starts from one number prior
    if (strcmp(res[table].status, "empty") == 0) { // ensuring table is empty or not
        printf("Table %d is already empty.\n", table + 1);
    } else {
        printf("Reservation for Table %d (%s) canceled.\n", table + 1, res[table].name); // cancelling the reservation
        strcpy(res[table].status, "empty"); // labelling the table as empty after cancelling
        memset(res[table].name, 0, MAX_NAME_LEN); // memset is being used to clear the name 
        res[table].table_size = 0;
    }
}

int main() {
    initialize_reservations(lunch_res, MAX_RESERVATIONS); // initializing the function
    initialize_reservations(dinner_res, MAX_RESERVATIONS);

    int choice, meal;
    while (1) { 			// The loop will keep running as the condition is always true
        printf("\nReservation System:\n");
        printf("1. Add Reservation\n");
        printf("2. Remove Reservation\n");
        printf("3. View Reservations\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
         

        if (choice == 4) { // to exit the program
            break;
        }

        printf("Select Meal (1. Lunch, 2. Dinner): "); //Input which meal the user wants
        scanf("%d", &meal); /*Once the user enters the characters, they are temporarily stored in the buffer. 
							And when the program processes the characters, some are left in the buffer. 
							To avoid leftover characters stay in the buffer, we use getchar() function */
        getchar(); // Flush input buffer; flush out the leftover characters in the buffer to avoid any errors

        if (meal < 1 || meal > 2) { //Meal must only be Lunch or Dinner
            printf("Invalid meal selection.\n");
            continue;
        }

        Reservation *selected_res = (meal == 1) ? lunch_res : dinner_res; //ternary if; choosing lunch if the user presses 1 or choosing dinner
        const char *meal_name = (meal == 1) ? "Lunch" : "Dinner";

        switch (choice) {
            case 1:
                add_reservation(selected_res, meal_name); // adding reservation
                break;
            case 2:
                remove_reservation(selected_res, meal_name); // removing reservation
                break;
            case 3:
                view_reservations(selected_res, meal_name); // viewing reservation
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // error handling if wrong choice
        }
    }

    printf("Thank you for using the reservation system.\n");
    return 0;
}

