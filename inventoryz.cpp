/*
Baric
cis 1202
Binary Update
july 1 2018
*/

//display inventory
//display a certain product
//mod a product

#include<iostream>
#include<string>
#include<fstream>//read, write
#include<stdlib.h>//exit

using namespace std;


const int desc_size = 40;//for char member

struct product//structure
{
	long prod_number;
	char prod_name[desc_size];
	double price;
	int qty;

};

int menu(int user_choice);//menu
void display_all(fstream &, product, int count);//read and display from .dat, found my decoder ring
void search(fstream &, product database, int user_record);//ram search
long byte_num(int rec_num);//ram search
void show_rec(product database);//ram search
void mod_data(fstream &file_inv, product database);//mod dat data :}


int item_counter = 0;


int main()
{
	fstream file_inv;//file in data
	product database;//structure data
	//file_inv.open("inventory.dat", ios::binary | ios::in);
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));//have to put this here because i have to intiulize product database

	int user_choice = 0;//if pic
	int count = 0;//count for display
	int user_record = 0;//input from mod function

	user_choice = menu(user_choice);

	//need to make menu and if statement to choose option
	while (user_choice < 4 && user_choice > 0)
	{
		if (user_choice == 1)
		{		
			cout << endl;
			cout << "Display the database" << endl;
			display_all(file_inv, database, count);//problem here database not defined//display all works now
			file_inv.close();//close file
			file_inv.clear();//used to clear flags for another read
			user_choice = menu(user_choice);	
		}
		else if (user_choice == 2)
		{
			cout << endl;
			cout << "Search for a entry" << endl;
			search(file_inv, database, user_record);//ram search
			file_inv.close();
			file_inv.clear();
			user_choice = menu(user_choice);
		}
		else if (user_choice == 3)
		{
			cout << endl;
			cout << "Change a entry" << endl;
			mod_data(file_inv, database);//modding data
			file_inv.close();
			file_inv.clear();
			user_choice = menu(user_choice);
		}
		else if (user_choice == 4)
		{
			exit(0);
		}
	}

	system("pause");
	return 0;
}
//menu
int menu(int user_choice)//menu
{
	cout << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << "X Binary File Update X" << endl;
	cout << "XXXXXXXXXXXXXXXXXXXXXX" << endl;
	cout << endl;
	cout << "press 1 Display Product inventory " << endl;
	cout << "press 2 Display a chosen product " << endl;
	cout << "press 3 Modify a product entry " << endl;
	cout << "press 4 Exit" << endl;
	cout << "please pick a number: ";
	cin >> user_choice;

	return user_choice;
}
//print entrys
void display_all(fstream &file_inv, product database, int count)
	{

	file_inv.open("inventory.dat", ios::binary | ios::in);
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));
	
	if (file_inv.fail())
	{
		cout << "-----------------" << endl;
		cout << "your file didnt open " << endl;//if fail true
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
	}
	else
	{
		cout << "-----------------" << endl;
		cout << "your file opened " << endl;//if fail false
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
	}

	while (file_inv)
	{
		cout << endl;
		cout << "Product " << count << endl;
		cout << "Product Number: " << database.prod_number << endl;
		cout << "Product name: " << database.prod_name << endl;
		cout << "Price: $" << database.price << endl;
		cout << "Quanity: " << database.qty << endl;
		count++;

		file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));
		
	}
	cout << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////randomly searching from text//freeeken difficult instead of using sequental search//3 functions that all work together now that is cool :}
void search(fstream &file_inv, product database, int user_record)
{
	file_inv.open("inventory.dat", ios::binary | ios::in);
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));
	file_inv.clear();

	if (file_inv.fail())//needed for gage to help me see whats going on
	{
		cout << "-----------------" << endl;
		cout << "your file didnt open " << endl;//if fail true
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
	}
	else
	{
		cout << "-----------------" << endl;
		cout << "your file opened " << endl;//if fail false
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
		cout << endl;
	}

	cout << "Enter the number of the record you want to search: ";
	cin >> user_record;

	file_inv.seekg(byte_num(user_record));//took out ios::beg and it works guessing the pointer was staying on 0 index
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));
	show_rec(database);
	file_inv.seekg(0L, ios::beg);//setting pointer to starting point
}
long byte_num(int rec_num)
{
	return sizeof(product) * rec_num;
}
void show_rec(product record)
{
	cout << endl;
		cout << "Product Number: " << record.prod_number << endl;
		cout << "Product Name: " << record.prod_name << endl;
		cout << "Price: $" << record.price << endl;
		cout << "Quanity: " << record.qty << endl;
		cout << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mod_data(fstream &file_inv, product database)
{
	file_inv.open("inventory.dat", ios::binary | ios::in | ios::out);
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));

	if (file_inv.fail())
	{
		cout << "-----------------" << endl;
		cout << "your file didnt open " << endl;//if fail true
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
	}
	else
	{
		cout << "-----------------" << endl;
		cout << "your file opened " << endl;//if fail false
		cout << "failed: " << file_inv.fail() << endl;
		cout << "eof: " << file_inv.eof() << endl;
		cout << "bad: " << file_inv.bad() << endl;
		cout << "works: " << file_inv.good() << endl;
		cout << "-----------------" << endl;
		cout << endl;
	}

	cout << "What database entry do you want to modify: ";
	long mod_record;
	cin >> mod_record;
	cout << endl;
	file_inv.seekg(byte_num(mod_record));
	file_inv.read(reinterpret_cast<char *>(&database), sizeof(database));

	cout << "Product Number: " << database.prod_number << endl;
	cout << "Product Name: " << database.prod_name << endl;
	cout << "Price: " << database.price << endl;
	cout << "Quanity: " << database.qty << endl;
	cout << endl;

	cout << "Enter new data " << endl;
	

	cout << "product number: ";
	cin >> database.prod_number;
	cout << "Product name: ";
	cin.ignore();
	cin.getline(database.prod_name, desc_size);
	cout << "Price: $";
	cin >> database.price;
	cout << "Quanity: ";
	cin >> database.qty;
	cout << endl;

	file_inv.seekp(mod_record * sizeof(product));
	file_inv.write(reinterpret_cast<char *>(&database), sizeof(database));
}
