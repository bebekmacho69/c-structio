#include <stdio.h>
#include <string.h>

struct object {
	int notEmpty;
	int itemID;
	int itemPrice;
	char itemName[255];
	char itemDescription[255];
};

// static declaration
static struct object items[255];
static int itemList = 255;

// random access
static int itemIndex = 0;
static int lastIndex = 0;

// current session
static int deletedIndex = 0;

void spaces() {
	for(int i=0;i<100;i++) {
		puts("");
	}
}

void print() {
	// CALL FROM : main(); insertData(); deleteData();
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

void printSingle(int index) {
	// CALL FROM : deleteData();
	for(int i=0;i<itemIndex;i++) {
		if (items[i].itemID == index) {
			printf("%d 	",items[i].itemID);
			printf("%s 	",items[i].itemName);
			printf("%d 	",items[i].itemPrice);
			printf("%s 	\n",items[i].itemDescription);		
		}
	}
}

void insertData() {
	// CALL FROM : main();
	spaces();
	printf("Enter Name : ");
	printf(">> ");
	scanf("%[^\n]",items[itemIndex].itemName);

	printf("Enter Price : ");
	printf(">> ");
	scanf("%d",&items[itemIndex].itemPrice); getchar();

	printf("Enter Description : ");
	printf(">> ");
	scanf("%[^\n]",items[itemIndex].itemDescription);

	items[itemIndex].itemID = lastIndex;
	items[itemIndex].notEmpty = 1;
	itemIndex++;
	lastIndex++;
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
		for(int i=0;i<itemIndex;i++) {
			if (items[i].itemID == deleteIndex) {
				items[i].notEmpty = 0;
				items[i].itemID = -1;
				strcpy(items[i].itemName, "DELETED");
				strcpy(items[i].itemDescription, "DELETED");	
			}
		}
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

int inFile_items() {
	file = fopen("structio_data.txt","r");
	int init = 0;
	int items = 0;
	char c;
	while (init < 1) {
		if (c == '\n') init++;
		c = getc(file);
	}
	while (c != EOF) {
		if (c == '\n') items++;
		c = getc(file);
	}
	return items;
}

void openFile() {
	// CALL FROM : main();
	int indexBuffer;
	int priceBuffer;
	char nameBuffer[255];
	char descriptionBuffer[255];

	// #0-400-nau-pembalab#
	int file_itemIndex = 0;
	int verify_itemIndex = inFile_items();

	file = fopen("structio_data.txt","r");

	fscanf(file,"itemIndex:%d\n",&file_itemIndex);
	printf("Reading itemIndex value of %d\n",file_itemIndex);

	if (file_itemIndex != verify_itemIndex) {
		printf("itemIndex mismatch! (%d) matching with actual list (%d)....\n",file_itemIndex, verify_itemIndex);
		itemIndex = verify_itemIndex;
		printf("itemIndex verified! itemIndex : %d\n",itemIndex);
	} else {
		printf("itemIndex match! (%d) with actual list (%d)....\n excluding verification\n", file_itemIndex, verify_itemIndex);
		itemIndex = file_itemIndex;
	}
	
	
	for(int i=0;i<itemIndex;i++) {
		fscanf(file,"#%d-%d-%[^-]-%[^#]#\n", &indexBuffer, &priceBuffer, nameBuffer, descriptionBuffer);
		items[i].itemID = indexBuffer;
		items[i].itemPrice = priceBuffer;
		strcpy(items[i].itemName, nameBuffer);
		strcpy(items[i].itemDescription, descriptionBuffer);
		items[i].notEmpty = 1;
		// logs(2)
		printf("Fetched #%d => index : %d price : %d name : %s description : %s\n",i+1,items[i].itemID, items[i].itemPrice, items[i].itemName, items[i].itemDescription);
		if (items[i].itemID != 0) lastIndex = items[i].itemID + 1;
	}
}

void saveFile() {
	// CALL FROM : main();
	file = fopen("structio_data.txt","w+");

	fprintf(file,"itemIndex:%d\n",itemIndex);
	printf("Saved itemIndex value of %d\n",itemIndex);
	
	for(int i=0;i<itemIndex+deletedIndex;i++) {
		if (items[i].itemID != -1) {
			fprintf(file,"#%d-",items[i].itemID);
			fprintf(file,"%d-",items[i].itemPrice);
			fprintf(file,"%s-",items[i].itemName);
			fprintf(file,"%s#\n",items[i].itemDescription);
			printf("Recorded %d %d %s %s\n",items[i].itemID,items[i].itemPrice,items[i].itemName,items[i].itemDescription);	
		} else {
			puts("Excluding deleted items");
		}
	}
}

int main() {
	int menuStatus = 1;
	int userSellection = 0;
	spaces();
	openFile();
	getchar();
	while (menuStatus == 1) {
		spaces();
		print();
		puts("1. Insert data");
		puts("2. Delete data");
		puts("3. Edit data");
		puts("4. Verify data index");
		puts("5. Exit");
		printf(">>");
		scanf("%d",&userSellection); 
		getchar();
		if (userSellection == 1) insertData();
		if (userSellection == 2) deleteData();
		if (userSellection == 3) editData();
		if (userSellection == 5) {
			menuStatus = 0;
			saveFile();
			fclose(file);
		}
	}
}
