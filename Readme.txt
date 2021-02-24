Build date 	: 15 July 2020
Author		: BebekMacho69
Language	: C

Compiling	: (linux terminal)
	cd sourcecodedir
	gcc -o structio structio.c
	./structio

Important NOTE : 
	never empty structio_data.txt, and always include these structure below, including whitespace on empty data and below each data (if filled) or the program will not work as intended

	1	itemIndex:*numeric*
	2	*whitespace*

	do not add extra whitespace below

Information : 
Structio (struct_i/o) is a basic program to simulate input and output sequence using structures

Methods
	void spaces();
		-> screen cleaning method by spamming many spaces

	void print();
		-> method to print in-program listed data from struct, excluding empty data

	void printSingle(int index);
		-> same as print() but only print single data based on itemID

	void insertData();
		-> insert data to struct

	void deleteData();
		-> delete data from struct

	void editData();
		-> edit data on struct

	int inFile_items();
		-> count total of items inside external file (structio_data.txt)

	void openFile();
		-> method to read data from external file (structio_data.txt), then inserting it into the application struct, it also verifies index to prevent the program to fail

	void saveFile();
		-> method to save struct data, from program session saved into external file (structio_data.txt)
		-> only important data is saved, excluding flags and other measurements from the struct
	int main();
		-> the program

Attributes
	struct object
		-> a struct contains several attributes for use
	object items[255]
		-> declared object to use, up to 255 data
	int itemList
		-> constant variable specified for print()
	int itemIndex
		-> random access variable used to identify current program session index
	int lastIndex
		-> random access variable used to identify last inserted data index
	int deletedIndex
		-> current session variable used to record number of deleted data by user in the current session

External files
	structio_data.txt
		-> a file used to store the program data, begins with itemIndex and its value, the structure details are below

		itemIndex:*numeric*
		*whitespace*

		NOTE : never empty the file, and always include above structure, including whitespace or the program will not work as intended