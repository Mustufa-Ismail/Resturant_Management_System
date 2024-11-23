#include <stdio.h>
#include <string.h>

void itemlist(float *item_price, int *quantity, float *discount, float *total_amount) {
    printf("Enter the item price: ");
    scanf("%f", item_price);
    printf("Enter the quantity: ");
    scanf("%d", quantity);

    *total_amount = (*item_price) * (*quantity);

    if (*total_amount > 10000) {
        *discount = 0.20;
    } else {
        *discount = 0.0;
    }
}

void paymentsystem(float item_price, int quantity, float discount) {
    float total_amount = item_price * quantity;
    float discounted_amount = total_amount - (discount * total_amount);
    char method, card_type[10], bank[50], ID[50], date[50];
    float cash, card_balance;

    printf("\nSelect Payment Method\n");
    printf("For Card (Enter 1) || For Cash (Enter 2): ");
    scanf(" %c", &method);

    printf("The total amount is %.2f\n", total_amount);

    if (discount > 0) {
        printf("The discount applied is %.2f%%\n", discount * 100);
        printf("The total amount after discount: %.2f\n", discounted_amount);
    } else {
        discounted_amount = total_amount;
    }

    if (method == '2') {
        printf("Enter the cash you have: ");
        scanf("%f", &cash);

        if (cash < discounted_amount) {
            printf("You need %.2f more to complete the payment.\n", discounted_amount - cash);
        } else if (cash > discounted_amount) {
            printf("Payment successful. Thank you for your order! Here is your change: %.2f\n", cash - discounted_amount);
        } else {
            printf("Payment successful. Thank you for your order!\n");
        }
    } else if (method == '1') {
        printf("Select Card Type (Credit/Debit): ");
        scanf("%s", card_type);

        if (strcmp(card_type, "Credit") == 0 && discount == 0.0) {
            discount = 0.10;
        } else if (strcmp(card_type, "Debit") == 0 && discount == 0.0) {
            discount = 0.0;
        } else if (strcmp(card_type, "Credit") != 0 && strcmp(card_type, "Debit") != 0) {
            printf("Invalid card type!\n");
            return;
        }

        discounted_amount = total_amount - (discount * total_amount);
        printf("The discount applied is %.2f%%\n", discount * 100);
        printf("The total amount after discount: %.2f\n", discounted_amount);

        printf("Enter the Name of Your Bank: ");
        scanf("%19s", bank);
        printf("Enter Bank Account Number: ");
        scanf("%16s", ID);
        printf("Enter Last Date of your card: ");
        scanf("%s", date);

        if (strcmp(card_type, "Debit") == 0) {
            printf("Enter your card balance: ");
            scanf("%f", &card_balance);

            if (card_balance < discounted_amount) {
                printf("Insufficient Balance. You need %.2f more.\n", discounted_amount - card_balance);
            } else {
                printf("Payment successful. Thank you for your order!\n");
            }
        } else if (strcmp(card_type, "Credit") == 0) {
            printf("Payment successful. Thank you for your order!\n");
        }
    } else {
        printf("Invalid payment method selected!\n");
    }
}

int main() {
    float item_price, discount, total_amount;
    int quantity;

    itemlist(&item_price, &quantity, &discount, &total_amount);

    paymentsystem(item_price, quantity, discount);

    return 0;
}

