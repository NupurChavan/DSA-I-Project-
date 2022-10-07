#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customerName[50];
    char date[30];
    int numOfItems;
    struct items itm[50];
};

void generateInvoiceHeader(char customerName[50], char date[10]){
    printf("\n\n");
    printf("-----------------------------------------------");
    printf("\nDate: %s",date);
    printf("\nInvoice To: %s",customerName);
    printf("\n");
    printf("-----------------------------------------------");
    printf("\nItems\t\t");
    printf("Quantity\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------------");
    printf("\n\n");
}




int main()
{
    //system("cls");
    int choice,num;
    struct orders ord;
    struct orders order;
    FILE *fp;
    char saveBill = 'y';
    char name[50];
    char contFlag='y';

    while(contFlag=='y')
    {
        float total=0;
        int invoiceFound=0;
        //Dashboard
        system("cls");
        printf("\n\n");
        printf("=======Invoice Generator=======\n");
        printf("\n\nChoose any of the below operation:\n");
        printf("\n\n 1.Generate Invoice");
        printf("\n 2.Show all Invoices");
        printf("\n 3.Search Invoice");
        printf("\n 4.Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);
        fgetc(stdin);

        switch(choice)
        {
        case 1:
            system("cls");
            printf("\nPlease enter the customer name: ");
            fgets(ord.customerName,50,stdin);
            ord.customerName[strlen(ord.customerName)-1]=0; //length of string -1 position = 0 (To remove \n)
            strcpy(ord.date,__DATE__);
            printf("\nPlease enter the number of items: ");
            scanf("%d",&num);
            ord.numOfItems=num;

            for(int i=0; i<num; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Enter Item %d: ",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("Enter Item Quantity: ");
                scanf("%d",&ord.itm[i].qty);

                fgetc(stdin);
                printf("Enter unit price: ");
                scanf("%f",&ord.itm[i].price);
                total = total + ord.itm[i].qty * ord.itm[i].price;
            }
            generateInvoiceHeader(ord.customerName,ord.date);
            for(int i=0; i<ord.numOfItems; i++)
            {
                generateInvoiceBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateInvoiceFooter(total);

            printf("\nDo you want to save the Invoice:[y/n]  ");
            scanf("%s",&saveBill);

            if(saveBill=='y'||saveBill=='Y')
            {
                fp = fopen("Invoice.dat","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if(fwrite!=0)
                    printf("\nInvoice saved successfully!");
                else
                    printf("\nEncountered an Error while saving the Invoice.");
                fclose(fp);
            }
            break;

        case 2:
            system("cls");
            fp = fopen("Invoice.dat","r");
            printf("\n ********Your Previous Invoices********\n");
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot=0;
                generateInvoiceHeader(order.customerName,order.date);
                for(int i=0; i<order.numOfItems; i++)
                {
                    generateInvoiceBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty * order.itm[i].price;
                }
                generateInvoiceFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter customer name:\t");
            //fgetc(stdin);
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            system("cls");
            fp = fopen("Invoice.dat","r");
            printf("\n ********Invoice of %s********\n",name);
            while(fread(&order,sizeof(struct orders),1,fp))
            {
                float tot=0;
                if(!strcmp(order.customerName,name))
                {
                    generateInvoiceHeader(order.customerName,order.date);
                    for(int i=0; i<order.numOfItems; i++)
                    {
                        generateInvoiceBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        tot+=order.itm[i].qty * order.itm[i].price;
                    }
                    generateInvoiceFooter(tot);
                    invoiceFound=1;
                }
            }
            if(!invoiceFound)
            {
                printf("\n\nSorry the invoice for %s doesn't exist.",name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Terminating.....\n\n");
            exit(0);
            break;

        default:
            printf("\nPlease select an appropriate operation!");
            break;
        }

        printf("\n\n\nDo you want to perform another operation?[y/n]:  ");
        scanf("%s",&contFlag);
    }
    printf("\n\t\t Terminating.....\n\n");
    printf("\n\n");

    return 0;
}
