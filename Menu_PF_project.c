#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max_item 50

typedef struct{
	int id;
    char name[100];
    float price;
}menuitem;



int no_items = 3;
int initial_item = 3;
 menuitem item[]={
 {1, "Burger", 25.56},
 {2, "Pizza", 20.89},
 {3, "Fries", 10.00}
 };




void createMenu(){
	
	FILE *menu= fopen("menu.txt","r");
	if(menu != NULL){
		fclose(menu);
		return;
	}
	
    menu=fopen("menu.txt","w");
    
 if(menu == NULL){
	printf("ERROR,unable to create menu\n");
	return;
    }
fprintf(menu,"____________________________________________________________\n");
fprintf(menu,"                         Menu\n");
fprintf(menu,"____________________________________________________________\n");
 int i;
 for(i=0;i<no_items;i++){
 	fprintf(menu,"\t no: %d\n \t name: %s\n \t price: %.2f\n",item[i].id,item[i].name,item[i].price);
 }
 printf("Success\n");
 fclose(menu);

}    

void displayMenu(){
	FILE *menu = fopen("menu.txt","r");
	if(menu == NULL){
		printf("Error");
		return;
	}
	int count=1;
	char string[255];
	while(fgets(string,255,menu) != NULL){
		printf("%s",string);
		if(count%3==0){
			printf("\n");
		}
		count++;
	}
	fclose(menu);
}

void saveMenu(){
	FILE *menu=fopen("menu.txt","w");
	if(menu == NULL){
		printf("Error: unable to open file\n");
		return;
	}
	
	int i;
	for(i=0;i < no_items;i++){
	   fprintf(menu," no: %d\n name: %s\n price: %.2f\n",item[i].id,item[i].name,item[i].price);
	}
	
	fclose(menu);
	printf("Menu saved\n");
}

void addItem(){
	initial_item = no_items;
	if(no_items >= max_item){
		printf("Menu is full\n");
		return;
	}
	int n,i;
	float price;
	char name[50];
     
	printf("Enter the number items to be added to the menu: \n");
	scanf("%d",&n);
	getchar();
	for(i=0; i< n;i++){
		
		
		printf("\nEnter the name of the item: ");
		fgets(name,sizeof(name),stdin);
	    name[strcspn(name,"\n")] = 0;

		printf("Enter the price of the item:");
		scanf("%f", &price);
		getchar();
		
		item[no_items].id=no_items+1;
		strcpy(item[no_items].name,name);
		item[no_items].price = price;
		no_items++;
	}
}

void updateItem(){
	int id,choice;
    float newprice;
	char newname[50];
	do{
	printf("Enter the ID of the item you want to update:");
	scanf("%d",&id);
	}while(id <= 0 || id > no_items);
	printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);
    do{
	printf("1. To update price\n");
	printf("2. To update name\n");
	printf("3. To update both\n");
	printf("4. Exit\n");
	printf("Select an option:");
	scanf("%d",&choice);

	switch(choice){
		case 1:
        printf("Enter the new price:");
		scanf("%f",&newprice);
		item[id-1].price = newprice;
		printf("Item has been updated\n");
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);
        break;

		case 2:
		printf("Enter the new name:");
		getchar();
		fgets(newname,sizeof(newname),stdin);
	    newname[strcspn(newname,"\n")] = 0;
		strcpy(item[id-1].name,newname);
		printf("Item has been updated\n");
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);
        break;

		case 3:
		printf("Enter the new name:");
		getchar();
		fgets(newname,sizeof(newname),stdin);
	    newname[strcspn(newname,"\n")] = 0;
		strcpy(item[id-1].name,newname);
		printf("Enter the new price:");
		scanf("%f",&newprice);
		item[id-1].price = newprice;
		printf("Item has been updated\n");
	    printf("Id:%d \nname:%s \nprice:%.2f\n\n",id,item[id-1].name,item[id-1].price);
        break;

		case 4:
		printf("Exiting\n");
		break;  
	}
  }while(choice != 4);
}

void removeItem(){
	int id,i;
	do{
	printf("Enter the item ID to be removed:");
	scanf("%d",&id);
	if(id < 1 || id > no_items){
		printf("Invalid ID\n");
	}
	else{
		break;
	}
    }while(1);
    
    
	for(i=id-1;i<no_items-1;i++){
		item[i]=item[i+1];
		item[i].id = i+1;
	}
	no_items--;
	printf("Item removed \n");
}

int main(){
	int option,choice,n,i;
	while(1){
	printf("Are you \n1.Management\n2.Customer \n");
	printf("Please Select a valid option\n");
	scanf("%d",&option);
	if(option !=1 && option !=2){
		printf("Invalid Selection \n select again\n");
		continue;
	    }
	else{
		break;
	    }
	}

    createMenu();
     
	if(option == 1){
	 do{
		printf("1.View the menu\n");
		printf("2.Add items to the menu\n");
		printf("3.Update items in the menu\n");
		printf("4.Remove items from the menu\n");
		printf("5.Exit\n");
		printf("Select a valid option:");
        scanf("%d",&choice);

		switch(choice){
			case 1:
            displayMenu();
            system("pause");
            system("cls");
			break;


			case 2:
			displayMenu();
			addItem();
			saveMenu();
			displayMenu();
			system("pause");
            system("cls");
			break;


			case 3:
			displayMenu();
			printf("Enter the number of items to be Updated:");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				updateItem();
				saveMenu();
				displayMenu();
			}
			system("pause");
            system("cls");
			break;

			case 4:
			displayMenu();
			printf("Enter the number of items to be Removed:");
			scanf("%d",&n);
				for(i=0;i<n;i++){
				removeItem();
				saveMenu();
				displayMenu();
			}
			system("pause");
            system("cls");
			break;

			case 5:
			printf("Exiting\n");
			system("pause");
            system("cls");
			break;

			default:
			printf("Invalid Selection");
		}
	 }while(choice != 5);
    
	}
	else if(option == 2){
		displayMenu();
	}
}
