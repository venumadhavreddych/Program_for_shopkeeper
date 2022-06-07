#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void add_product();
void display();
void update();
void check_threshold();

struct inventory{
    int sno,quantity;
    char product_name[20],product_id[10];

};struct inventory variable;

const int threshold = 50;

int main(){
    int choice;

    while(1){
	printf("_____\n");
    printf("|         SHOP INVENTORY          |\n");
    printf("|            THE MENU             |\n");
	printf("| 1) ADD PRODUCT                  |\n");
	printf("| 2) DISPLAY PRODUCT DETAILS      |\n");
	printf("| 3) UPDATE PRODUCT DETAILS       |\n");
    printf("| 4) THRESHOLD                    |\n");
	printf("| 5) EXIT                         |\n");
    printf("|_____|\n");

    printf("\nEnter your choice: ");
	scanf("%d",&choice);

    if(choice == 1){
		add_product();
    }
    else if(choice == 2){
        display();
    }
    else if(choice == 3){
        update();
    }

    else if(choice == 4){
        check_threshold();
    }

    else if(choice == 5){
        break;
    }

    }

}

void add_product(){
    char decision;
    printf("S.No :");
	scanf("%d",&variable.sno);

    printf("Enter the product id: ");
	scanf("%s",variable.product_id);

	printf("Enter the product name:");
	scanf("%s",variable.product_name);

	printf("Enter the quantity :");
	scanf("%d",&variable.quantity);

    FILE *fp = fopen("Inventory.txt","a");
    fprintf(fp,"%d|%s|%s|  %d    |%d\n",variable.sno,variable.product_id,variable.product_name,variable.quantity,threshold);
    fclose(fp);

    printf("Do you want to add more products? y or n: ");
    scanf("\n%c",&decision);
	printf("\n");

    if(decision == 'y' || decision == 'Y'){
        add_product();
    }

}

void display(){
    FILE *fp = fopen("Inventory.txt","r");
    while(1){
		char ch = fgetc(fp);
		if(ch == EOF)
			break;
		printf("%c",ch);
		}
	fclose(fp);

}

void update(){
    char line[50],name[20],new_quantity[5];
    int flag=1;
    FILE *fp = fopen("Inventory.txt", "r+");
    printf("Enter the name of the product whose value you wish to update: ");
    fflush(stdin);
    scanf("%s",name);
    printf("Enter the new quantity of the product: ");
    fflush(stdin);
    scanf("%s",new_quantity);

    while (fgets(line, sizeof(line), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s",line);
        if(strstr(line,name)!= NULL){
            flag = 0;
            fseek(fp, -10, SEEK_CUR);//it denotes file points current position.
            fprintf(fp,"%s",new_quantity);
        }
    }

    if(flag){
        printf("Please enter the name of an existing product!\n");
    }
    fclose(fp);
}

void check_threshold(){
    FILE *fp = fopen("Inventory.txt", "r+");
    char line[50],storage[50];
    while (fgets(line, sizeof(line), fp)) {
        //printf("%s",line);
        int count = 1;

        /* get the first token */
        char* token = strtok(line, "|");//pipe symbol it is a delimiter
        /* walk through other tokens */
        char product_name[20];
        while( token != NULL ) {
            //printf( "%s\n",token); //printing each token
            count += 1;
            token = strtok(NULL, "|");

            if(count == 3){

                strcpy(product_name,token);
            }

            else if(count == 4){

                strcpy(storage,token);

                int value;
                value = atoi(storage);
                if(value<threshold){
                    printf("%d %s has to be ordered!\n",threshold-value,product_name);
                }


            }
        }
    }
}
