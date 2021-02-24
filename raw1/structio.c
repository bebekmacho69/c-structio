#include <stdio.h>
#include <string.h>

struct object {
	int notEmpty;
	int itemID;
	int itemPrice;
	char itemName[255];
	char itemDescription[255];
};

static struct object items[255];
static int itemList = 255;
static int itemToFile = 0;
static int itemIndex = 0;

void spaces() {
	for(int i=0;i<100;i++) {
		puts("");
	}
}

void print() {
	// CALL FROM : main(); insertData(); deleteData();"
	for(int i=0;i<itemList;i++) {
		if (items[i].notEmpty == 1) {
			printf("%d 	",items[i].itemID);
			printf("%s 	",items[i].itemName);
			printf("%d 	",items[i].itemPrice);
			printf("%s 	\n",items[i].itemDescription);
		}
	}
	puts("\n\n");
}

void printSingle(int i) {
	// CALL FROM : deleteData();
	printf("%d 	",items[i].itemID);
	printf("%s 	",items[i].itemName);
	printf("%d 	",items[i].itemPrice);
	printf("%s 	\n",items[i].itemDescription);
}

void insertData() {
	// CALL FROM : main();
	spaces();
	printf("Enter Name : ");
	printf(">> ");
	scanf("%s",items[itemIndex].itemName);

	printf("Enter Price : ");
	printf(">> ");
	scanf("%d",&items[itemIndex].itemPrice);

	printf("Enter Description : ");
	printf(">> ");
	scanf("%s",items[itemIndex].itemDescription);

	items[itemIndex].itemID = itemIndex;
	items[itemIndex].notEmpty = 1;
	itemIndex++;
	itemToFile++;
}

void deleteData() {
	// CALL FROM : main();
	int inputTemp;
	spaces();
	print();
	puts("Enter index to delete");
	printf(">> ");
	scanf("%d",&inputTemp);
	int deleteIndex = inputTemp;

	// CONFIRMATION SEQUENCE
	puts("Are you sure do you want to delete the sellected data ?");
	printSingle(deleteIndex);
	printf("[0/1] >> ");
	scanf("%d",&inputTemp);
	if (inputTemp == 0) return;
	// DELETION SEQUENCE
	else {
		items[deleteIndex].notEmpty = 0;
		strcpy(items[deleteIndex].itemName, "DELETED");
		itemToFile--;
	}
}

void editData() {
	// CALL FROM : main();
	int inputTemp;
	spaces();
	print();
	puts("Sellect index to edit");
	printf(">> ");
	scanf("%d",&inputTemp);
	int editIndex = inputTemp;
	char editName[255];

	printSingle(editIndex);
	puts("Editing sequence");
	printf("itemName : ");
	scanf("%s",items[editIndex].itemName);
	printf("itemPrice : ");
	scanf("%d",&items[editIndex].itemPrice);
	printf("itemDescription : ");
	scanf("%s",items[editIndex].itemDescription);

	// strcpy(items[editIndex].itemName, editName);
}

static FILE *file;

void openFile() {
	// CALL FROM : main();
	int indexBuffer;
	int priceBuffer;
	char nameBuffer[255];
	char descriptionBuffer[255];

	file = fopen("structio_data.txt","r");

	// #0-400-nau-pembalab#
	fscanf(file,"itemToFile:%d\n",&itemToFile);
	fscanf(file,"itemIndex:%d\n",&itemIndex);

	// read listed items
	// logs(1)
	printf("Reading itemToFile value of %d\n",itemToFile);
	printf("Reading itemIndex value of %d\n",itemIndex);
	for(int i=0;i<itemToFile;i++) {
		fscanf(file,"#%d-%d-%[a-z&&A-Z&&0-9]-%[a-z&&A-Z&&0-9]#\n", &indexBuffer, &priceBuffer, nameBuffer, descriptionBuffer);
		items[i].itemID = indexBuffer;
		items[i].itemPrice = priceBuffer;
		strcpy(items[i].itemName, nameBuffer);
		strcpy(items[i].itemDescription, descriptionBuffer);
		items[i].notEmpty = 1;
		// logs(2)
		printf("reading => index : %d price : %d name : %s description : %s\n",items[i].itemID, items[i].itemPrice, items[i].itemName, items[i].itemDescription);
	}
}

void saveFile() {
	// CALL FROM : main();
	file = fopen("structio_data.txt","w+");
	fprintf(file,"itemToFile:%d\n",itemToFile);
	fprintf(file,"itemIndex:%d\n",itemIndex);
	// logs (1)
	printf("Saved itemToFile value of %d\n",itemToFile);
	printf("Saved itemIndex value of %d\n\n",itemIndex);
	for(int i=0;i<itemToFile;i++) {
		fprintf(file,"#%d-",items[i].itemID);
		fprintf(file,"%d-",items[i].itemPrice);
		fprintf(file,"%s-",items[i].itemName);
		fprintf(file,"%s#\n",items[i].itemDescription);
		// logs (2)
		printf("Writted %d %d %s %s\n",items[i].itemID,items[i].itemPrice,items[i].itemName,items[i].itemDescription);
	}


}

int main() {
	int menuStatus = 1;
	int userSellection = 0;
	openFile();
	while (menuStatus == 1) {
		spaces();
		print();
		puts("1. Insert data");
		puts("2. Delete data");
		puts("3. Edit data");
		puts("4. Exit");
		printf(">>");
		scanf("%d",&userSellection); 
		getchar();
		if (userSellection == 1) insertData();
		if (userSellection == 2) deleteData();
		if (userSellection == 3) editData();
		if (userSellection == 4) {
			menuStatus = 0;
			fclose(file);
			saveFile();
		}
	}
}