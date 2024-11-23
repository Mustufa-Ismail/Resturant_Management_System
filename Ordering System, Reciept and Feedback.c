#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ITEMS 50

typedef struct{
	int id;
    char name[100];
    float price;
}menuitem;
 
typedef struct{
	int itemId;
	int quantity;
	
}OrderItem;

OrderItem order[MAX_ITEMS]; 
int orderCount = 0;

int no_items = 3;
int initial_item = 3;
 menuitem item[]={
 {1, "Burger", 25.56},
 {2, "Pizza", 20.89},
 {3, "Fries", 10.00}
 };

void savefeedback(const char* feedback){
	FILE *feedbackfile = fopen("feedback.txt", "w");
	if (feedbackfile == NULL) {
		printf("Error\n");
		return;
	}
	
	fprintf(feedbackfile, "Feedback: %s\n", feedback);
	fclose(feedbackfile);
}

void givefeedback(){
	int option;
	char feedbackText[500];
	
	printf("Would you like to give feedback?\n 1.Yes\n 2.No\nSelect option: ");
	scanf("%d", &option);
	
	if (option ==2) {
		strcpy(feedbackText, "No feedback given.\n");
        savefeedback(feedbackText); 
        printf("Thank you for being our guest. \n");
        return;
	}
	else if(option == 1){
		printf("Please enter your feedback:\n");
		getchar();
		fgets(feedbackText, sizeof(feedbackText),stdin);
		feedbackText[strcspn(feedbackText, "/n")] =0;
		savefeedback(feedbackText);
		printf("Thank you for your feedback.\n");
		printf("Thank you for being our guest. \n");
		return;
	}
	else {
		printf("Invalid option!\n");
		return;
	}
}

void viewfeedback(){
	FILE *feedbackfile = fopen("feedback.txt","r");
	if (feedbackfile == NULL){
		printf("Error");
		return;
	}
	
	char line[500];
	printf("            Customer Feedback\n");
	while (fgets(line, sizeof(line), feedbackfile) != NULL) {
        printf("%s", line);
    }
}

void takeOrder(){
    int orderID, quantity;
    float total = 0.0;
    char moreOrders = 'y';
    int dineInOption;  

    
    printf("Would you like to \n 1. Dine-in \n 2. Takeaway \n");
    printf("Select a valid option: ");
    scanf("%d", &dineInOption);

    while (dineInOption != 1 && dineInOption != 2) {
        printf("Invalid selection, please select 1 for Dine-in or 2 for Takeaway: ");
        scanf("%d", &dineInOption);
    }

    while (moreOrders == 'y' || moreOrders == 'Y') {
        printf("Enter the ID of the item you want to order: ");
        scanf("%d", &orderID);

        if (orderID < 1 || orderID > no_items) {
            printf("Invalid item ID. Please try again.\n");
            continue;
        }

        printf("Enter the quantity of %s: ", item[orderID - 1].name);
        scanf("%d", &quantity);
        int i;
        int found = 0;
        for (i = 0; i < orderCount; i++) {
            if (order[i].itemId == orderID) {
                order[i].quantity += quantity;
                found = 1;
                break;
            }
        }

    
        if (!found) {
            order[orderCount].itemId = orderID;
            order[orderCount].quantity = quantity;
            orderCount++;
        }

        float itemTotal = item[orderID - 1].price * quantity;
        total += itemTotal;

        printf("You ordered %d x %s. Item Total: %.2f\n", quantity, item[orderID - 1].name, itemTotal);

        printf("Would you like to order another item? (y/n): ");
        getchar();
        scanf("%c", &moreOrders);
    }
    givefeedback();
    
    printf("\n____________________________________________________________\n");
    printf("                     Receipt\n");
    printf("____________________________________________________________\n");
    printf("Dine-in option: %s\n", dineInOption == 1 ? "Dine-in" : "Takeaway");
	printf("Item(s) ordered:\n");
		int i;
		for (i = 0; i < orderCount; i++) {
    int itemId = order[i].itemId;
    int quantity = order[i].quantity;
    float itemTotal = item[itemId - 1].price * quantity;
    
    printf("%d x %s = %.2f\n", quantity, item[itemId - 1].name, itemTotal);
}

    printf("____________________________________________________________\n");
    printf("Total amount: %.2f\n", total);
    printf("____________________________________________________________\n");
    printf("Thank you for your order!\n");

	viewfeedback();
}


int main(){
	takeOrder();
}
