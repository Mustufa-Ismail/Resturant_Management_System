#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ITEMS 50                //Defines the limit of the menu and in order
#define tax_rate 0.18               //Defines the sales tax rate

typedef struct{                     
	int id;                         //Sturucture for storing menu items
    char name[100];
    float price;
}menuitem;

typedef struct{       
	int itemId;                     //Structure for storing order items
	int quantity;
}OrderItem;

int no_items = 15;                  //Global varible to used in crud operations 
int initial_item = 15;              // relating to menu syste,

OrderItem order[MAX_ITEMS];          // Array to store orders
int orderCount = 0;                  // Global variable to count order items

 menuitem item[MAX_ITEMS]={
 {1, "Zinger Burger", 25.56},{2, "Chicken Burger", 20.89},{3, "Beef Burger", 27.00},
 {4, "Steak Burger",30.35},{5,"Chicken Tikka Pizza",20.36},{6,"Cheese Pizza",15.96},
 {7,"Chicken Tikka Boti",17.85},{8,"Chicken Malai Boti",18.85},{9,"Beef Behari Boti",19.85},
 {10,"Chicken Tikka Boti Roll",20.25},{11,"Chicken Malai Boti Roll",20.25},{12,"Beef Boti Roll",22.25},
 {13,"Paratha",2.50},{14,"Water 1.5L",0.99},{15,"Cold Drink",1.99}
 };
                    //Inital menu items

void createMenu();                
void displayMenu();
void saveMenu();
int validation();
void addItem();                       //Prototypes for funtion which will used in the main function
void updateItem();                    // Function are defined after the main function
void removeItem();
void savefeedback(const char* feedback);
void givefeedback();
void viewfeedback();
void takeOrder();
float paymentsystem(float total_amount,float net_amount,int *method, float *cash,int *card_type);


int main(){
	int option,choice,n,i;
	    createMenu();          //For creating the menu file
		while(1){
    system("cls");              // to clear the terminal
	system("color 0B");         // to change the color of the text in the terminal
    printf("\n\t\t--------------------\n");
	printf("\n\t\tAre you \n\t\t1. Management\n\t\t2. Customer \n");
    printf("\n\t\t--------------------\n");
	printf("\t\tPlease Select a valid option:");
	scanf("%d",&option);                // Taking he user choice as an input
	if(option !=1 && option !=2){
		printf("Invalid Selection \n select again\n");
		continue;
	    }             //Validating the input


    if(option == 1){
	if(validation() == 1){         // Function check if the User has authorization to access 
	 do{                           // Management features
		system("cls");
		system("color 03");         // For clearing the terminal and colour the new text
	 	printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t Welcome Management\n");
		printf("\t\t1.View the menu\n");
		printf("\t\t2.Add items to the menu\n");
		printf("\t\t3.Update items in the menu\n");
		printf("\t\t4.Remove items from the menu\n");
		printf("\t\t5.View Feedback\n");
		printf("\t\t6.Exit\n");
		printf("\n\t\t-------------------------------\n");
		printf("\t\tSelect a valid option:");
        scanf("%d",&choice);          //Taking Input , Invalid input will return program back to the
		system("color 0F");           // Selection menu through Switch case

		switch(choice){
			case 1:                     //If selection is 1
            displayMenu();              // display the menu
            system("pause");            // ask for an input to proceed
			break;


			case 2:
		    system("cls");            //clear the screen, display the menu
			displayMenu();  
			addItem();               //Calling the add item function
			saveMenu();              // Saving the updated menu
			displayMenu();           
			system("pause");           // ask for an input to proceed
			break;

			case 3:
			system("cls");     
			displayMenu();         //clear the screen, display the menu
			updateItem();          //Calling the function to update the item
			saveMenu();            // Saving the updated menu
			displayMenu();          // displaying the updated menu
			system("pause");        // ask for an input to proceed
			break;

			case 4:
			system("cls");           //clear the screen, display the menu
			displayMenu();
			removeItem();             // calling the function to remove an item
			saveMenu();             // Saving the updated menu
			displayMenu();            // displaying the updated menu
			system("pause");         // ask for an input to proceed
			break;
            
			case 5:
			system("cls");      //clearing the screen and showing the feedback
			viewfeedback();
			break;

			case 6:
			printf("Exiting\n");
			system("pause");         //exiting the management menu
            system("cls");
			break;

			default:
			printf("Invalid Selection\n");      // if invalid input is enter when asked for 
		}                                       // selection in the menu
	 }while(choice != 6);          // loop will not end until selected in the menu
	  }
	}
	else if(option == 2){
		system("cls");            //clearing the screen and changing the color
		system("color 03");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t Welcome Customer\n\n");
		printf("\t\tPlease Select a Valid option\n");
		printf("\t\t1.For Order");
		printf("\n\t\t-------------------------------\n");
		printf("\t\tSelection:");        // prompting for the selection
		scanf("%d",&choice);

		switch(choice){
			case 1:
			system("color 0F");       // clearing screen and changing the color
			system("cls");
			takeOrder();            // Calling a function to take order and show the recipt
			system("pause");
			break;

			default:
			printf("Invalid Option");
			exit(1);     // if invalid option is selction in the menu 
		}	                              //the program will exit
	  }  
 }
 return 0;
}

void createMenu(){

	FILE *menu= fopen("menu.txt","r");
	if(menu != NULL){                   // checking if the file exist
		fclose(menu);      // if the file exists funtion ends
		return;
	}

	
    menu=fopen("menu.txt","w");       //creating the menu file if it doesnt exit 
    
 if(menu == NULL){     // error message if file doesnt open
	printf("ERROR,unable to create menu\n");      
	exit(1);
    }

	//writing the menu into the text file
fprintf(menu,"------------------------------------------------------------\n");
fprintf(menu,"                         Menu\n");
fprintf(menu,"------------------------------------------------------------\n");
 int i;
 for(i=0;i<no_items;i++){
 	fprintf(menu,"\t no: %d\n \t name: %s\n \t price: %.2f\n",item[i].id,item[i].name,item[i].price);
 }
 fprintf(menu,"------------------------------------------------------------\n");
 fprintf(menu,"------------------------------------------------------------\n");
 printf("Success\n");
 fclose(menu);       //closing the text file

}    

void displayMenu(){
	FILE *menu = fopen("menu.txt","r");    //opening the menu file for reading
	if(menu == NULL){
		printf("Error,Menu cant be displayed");     //Error handling, if doesnt open program ends
		exit(1);
	}
	int count=1;            //counter for proper formating after every individual menu item
	char string[255];      //varible to hold the data read from the text file
	while(fgets(string,255,menu) != NULL){ // reading  the data until end of the text file
		printf("%s",string);         //outputing the data read line by line
		if(count%3==0){        
			printf("\n");        //new line to improve readabiltity of menu 
		}
		count++;
	}
	fclose(menu);    // closing the file
}

void saveMenu(){
	FILE *menu=fopen("menu.txt","w"); //opening the file for writing
	if(menu == NULL){
		printf("Error: unable to open file\n"); //Error handling, is file doesnt open program ends
		exit(1);
	}
	
	int i;            //counter for adding items into the menu file
	for(i=0;i < no_items;i++){
	   fprintf(menu," no: %d\n name: %s\n price: %.2f\n",item[i].id,item[i].name,item[i].price);
	}
	
	fclose(menu);   //closing the file
	printf("Menu saved\n");  //successful execution messaged
}

void addItem(){
	initial_item = no_items;     //Setting the initial items for tracking
	if(no_items >= MAX_ITEMS){    //For the menu to not exceed the limit
		printf("Menu is full\n");     //Error message
		return;        //exit the function
	}
	int n,i;          
	float price;      
	char name[50];    
    
	do{ 
	printf("Enter the number items to be added to the menu: \n");  //to get no of items to be inputted
	scanf("%d",&n); 
	if(n + no_items > MAX_ITEMS ){  //Checking if the added no of items will not exceed menu limit
		printf("Items will exceed menu limit by %d",MAX_ITEMS - (n+no_items));
	}
	else{
		break;  //ending the loop
	}               
    }while(1);           
	getchar();                  //clearing the buffer to remove any next line character
	for(i=0; i< n;i++){
		
		printf("\nEnter the name of the item: ");
		fgets(name,sizeof(name),stdin);            
	    name[strcspn(name,"\n")] = 0;

		printf("Enter the price of the item:");
		scanf("%f", &price);                     //name and price of the new item
		getchar();
		
		item[no_items].id=no_items+1;
		strcpy(item[no_items].name,name);       //adding the new item to the menu items array
		item[no_items].price = price;
		no_items++;                          //increamenting the no of items
    }
}

void updateItem(){
	int id,choice;            
    float newprice;            
	char newname[50];         
	do{
	printf("Enter the ID of the item you want to update:");
	scanf("%d",&id);         //To get the id of the item to be updated
	}while(id <= 0 || id > no_items);  //To stop any invalid input
	printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price); //showing the item to be updated
    do{
	printf("1. To update price\n");
	printf("2. To update name\n");
	printf("3. To update both\n");
	printf("4. Exit\n");
	printf("Select an option:");
	scanf("%d",&choice);         //menu to choose will property you want to update

	switch(choice){          
		case 1:   // for updating price only
        printf("Enter the new price:");  
		scanf("%f",&newprice);          //to get the new price
		item[id-1].price = newprice;    //to update the new price           
		printf("Item has been updated\n");
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price); //updating the menu with the new price
        break;

		case 2: // to update name only
		printf("Enter the new name:");     
		getchar();
		fgets(newname,sizeof(newname),stdin);
	    newname[strcspn(newname,"\n")] = 0; // to get new name
		strcpy(item[id-1].name,newname);
		printf("Item has been updated\n"); //to update the new name
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);
        break;

		case 3: // to update new name and new price
		printf("Enter the new name:");
		getchar();
		fgets(newname,sizeof(newname),stdin);  //get new name
	    newname[strcspn(newname,"\n")] = 0;
		strcpy(item[id-1].name,newname);
		printf("Enter the new price:");  //to get new price
		scanf("%f",&newprice);
		item[id-1].price = newprice;
		printf("Item has been updated\n");
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);//updating the menu with the new price and new name
        break;

		case 4:
		printf("Exiting\n"); // to exit the function
		break;  
	}
  }while(choice != 4);
}

void removeItem(){
	int id,i;
	do{
	printf("Enter the item ID to be removed:");
	scanf("%d",&id);         //to get id to be removed
	if(id < 1 || id > no_items){
		printf("Invalid ID\n");    //Error handling for invalid input
	}
	else{
		break;
	}
    }while(1);
    
    
	for(i=id-1;i<no_items-1;i++){    //removing the item and changing the menu accordingly
		item[i]=item[i+1];        
		item[i].id = i+1;
	}
	no_items--;
	printf("Item removed \n");     
}


int validation(){
	system("cls");      //clearing the screen and changing the color
	system("color 02");
	char username[20];
	char password[20];

	printf("\n\n\n\t\t\tUsername:");       
	getchar();             //clearing the new line character 
	fgets(username,20,stdin);        
	username[strcspn(username, "\n")] = 0; //removing the new line at the end of the input

	printf("\t\t\tPassword:");
	fgets(password,20,stdin);
	password[strcspn(password, "\n")] = 0;   //removing the new line at the end of the input
	system("color 0F");         //clearing the screen and changing the color
	system("cls");

	if(strcmp(username,"A") == 0 && strcmp(password,"A") == 0){ //Validating the input
		return 1;                                 //Username: A
	}                                             //Password: A
	else{
		printf("Invalid Username or Password"); //Error message
		return -1;
	}

}

void savefeedback(const char* feedback){
	FILE *feedbackfile = fopen("feedback.txt", "w");    // opening the file for writing
	if (feedbackfile == NULL) {    //Error message ,if file fails to open program will end
		printf("Error,reservation file not opened for writing\n");
		exit(1);
	}
	
	fprintf(feedbackfile, "Feedback: %s\n", feedback); //printing the feedback into the file
	fclose(feedbackfile);
}

void givefeedback(){
	int option;
	char feedbackText[500];
	
	printf("Would you like to give feedback?\n 1.Yes\n 2.No\nSelect option: ");
	scanf("%d", &option); //To get choice
	
	if (option ==2) {
		strcpy(feedbackText, "No feedback given.\n");
        savefeedback(feedbackText); //saving the message
        printf("Thank you for being our guest. \n");
        return; //exiting the function
	}
	else if(option == 1){
		printf("Please enter your feedback:\n");
		getchar();            //cleaaring the buffer
		fgets(feedbackText, sizeof(feedbackText),stdin);   //getting feedback
		feedbackText[strcspn(feedbackText, "/n")] =0;
		savefeedback(feedbackText);  //saving feedback
		printf("Thank you for your feedback.\n");
		printf("Thank you for being our guest. \n");
		return;
	}
	else {
		printf("Invalid option!\n");
		return;        //exiting the function
	}
}

void viewfeedback(){
	FILE *feedbackfile = fopen("feedback.txt","r"); //opening the file for reading
	if (feedbackfile == NULL){  //Error handling, exiting if the file doesnt open
		printf("Error, Feedback file not opened\n");
		exit(1);
	}
	
	char line[500];
	printf("            Customer Feedback\n");
	while (fgets(line, sizeof(line), feedbackfile) != NULL) {     //printing the feedback from the file
        printf("%s", line);
    }
}

void takeOrder(){
    int orderID, quantity, dineInOption,card_type;
    float total = 0.0, cash = 0.0;
    char moreOrders = 'y';
	int method = 0;
    
    printf("Would you like to \n 1. Dine-in \n 2. Takeaway \n");
    printf("Select a valid option: ");     
    scanf("%d", &dineInOption);     //To get selection

    while (dineInOption != 1 && dineInOption != 2) {    //For invalid input handling
        printf("Invalid selection, please select 1 for Dine-in or 2 for Takeaway: ");
        scanf("%d", &dineInOption);
    }
	system("cls"); //clearing the screen
	displayMenu(); //displaying the menu

    while (moreOrders == 'y' || moreOrders == 'Y') {
        printf("Enter the ID of the item you want to order: ");
        scanf("%d", &orderID);  // getting the order

        if (orderID < 1 || orderID > no_items) {   //Error handling
            printf("Invalid item ID. Please try again.\n");
            continue;     
        }
        do{
        printf("Enter the quantity of %s: ", item[orderID - 1].name);
        scanf("%d", &quantity);   //gettig the quantity of the item
		if(quantity > 0){
			break;
		}
		else{
			printf("Invalid quantity\n");
		}
	    }while(1);

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
        total += itemTotal;   //calulating the total
        
 
        printf("You ordered %d x %s. Item Total: %.2f\n", quantity, item[orderID - 1].name, itemTotal);
        //printing the item ordered with quantity
        printf("Would you like to order another item? (y/n): ");
        getchar();         
        scanf("%c", &moreOrders);
    }

    float net_amount = total + total*tax_rate;      //calculating net total with tax rate
	float discount = paymentsystem(total,net_amount,&method,&cash,&card_type);

    net_amount = net_amount - net_amount*discount; // calculting the net total with discount
	printf("Net amount: %.2f",net_amount);

	givefeedback(); // getting the feed back
    
	//printing the recipt 

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
    
    printf("%d x %s = %.2f\n", quantity, item[itemId - 1].name, itemTotal); // showing the order
    }
    printf("____________________________________________________________\n");
    printf("Total amount: %.2f\n", total);
	printf("Sales tax:%.2f\n", total*tax_rate);     //printing total,tax rate ,discount and net total
    printf("Total Discount:%.2f%%\n",discount);
	printf("Net Amount:%.2f\n",net_amount);
	if(method == 1){               //printing payment method
		if(card_type == 1){
			printf("Payment method: Credit Card\n");
		}
		else{
			printf("Payment method: Debit Card\n");
		}
	}else if(method == 2){
		printf("Payment method: Cash");        //printing cash paid and change returned
		printf("Total Cash Paid:%.2f\n",cash);
		printf("Change returned:%.2f\n",cash-net_amount);
	}
    printf("____________________________________________________________\n");
    printf("Thank you for your order!\n");

	viewfeedback();
}

//passing total and net amount,and pointers to method,cash and cars_type variable as parameters

float paymentsystem(float total_amount,float net_amount,int *method, float *cash,int * card_type) {
    float discount = 0.0;
    float card_balance,pay_cash;
	int pay_method,pay_card_type;
     
     if (total_amount > 5000) {
        discount = 0.20;          //checking if the total exceed the amount to get discount
    } 
    
    printf("\nSelect Payment Method\n");
    printf("For Card (Enter 1) || For Cash (Enter 2): ");
    scanf(" %d", &pay_method);
	*method = pay_method;       //selecting the payment method
    
    if (*method == 2) {
		do{
        printf("Enter the cash you have paid: ");
        scanf("%f", &pay_cash);                //to get the cash paid
		*cash = pay_cash;

        if (*cash < net_amount) {    //checking if the cash paid is enough
            printf("You need %.2f more to complete the payment.\n", *cash - net_amount);
			continue;
        } else {
            printf("Payment successful. Thank you for your order!\n");
			break; 
			}
	    }while(1);
    } else if (*method == 1) {    
    
    while (pay_card_type != 1 && pay_card_type != 2) { //Checking for invalid selection
    printf("Select Card Type \n 1. Credit\n 2. Debit\nSelection: ");
    scanf("%d", &pay_card_type);   //getting card type
    
    if(pay_card_type != 1 && pay_card_type != 2){
    	printf("Invalid Selection");     
     	}
    }
        *card_type = pay_card_type;

        if (*card_type == 1) {      //discount based on the card type
            discount += 0.10;       
        } else if (*card_type == 2) {    
        	
        } else  {
            printf("Invalid card type!\n");
        }
      } else {
        printf("Invalid payment method selected!\n");
    }
	return discount;           //returning the discount
}

