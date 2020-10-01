#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../include/mock/hardware.h"
#include "../include/error_variables.h"
#include "../include/main.h"
#include "../include/rapidxml_1.13/rapidxml.hpp"
#include "../include/library.h"

#define DNA_x 6
#define DNA_y 10

#define DEU_x 6
#define DEU_y 6

#define nb_Arg 4
using namespace std;
using namespace rapidxml;
// code is launch with the machine type "DEU" or "DNA" follow by the currency
int main (int argc, char *argv[]) 
{
	int res = ERROR;
	static bool isNFC = false;
	static string customerInput;
	static string machine;
	static string currency;
	static string name;
	static float insertedMoney , productPrice;
	static int productNumber;
	xml_document<> doc;
	static xml_node<> * root_node;
	if(argc < 3)
	{
		cout << " arguments are missing " << endl;
		return ERROR;
	}
	
	
	machine = argv[1];

	// In most machine currency is detect by the hardware
	// This variable will certainly won't be use
	currency = argv[2];
	res = set_Hardware(currency);
	if(SUCCESS != res)
	{
		cout << "error while setting the hardware"<< endl;
	}
	
	
	if(0 == machine.compare("DEU"))
	{		
		ifstream file ("./productsFile/DEU_Products_Price.xml");		
		vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
		root_node = doc.first_node("Distributech_EU");
		file.close();
	}	
	else if(0 == machine.compare("DNA"))
	{
		ifstream file ("./productsFile/DNA_Products_Price.xml");
		vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);
		root_node = doc.first_node("Distributech_NA");
		file.close();
	}
	

	res = setMachineConfig (machine, root_node);
	// First argument is coin value or "NFC"
	// if NFC, third is employee name or "technician"
	while(1)
	{
		cout << "Select product number (0 for coffee) or present NFC" << endl;
		cin >> customerInput;

		if(is_number(customerInput)) 
		{
			isNFC = false;
			productNumber = stoi(customerInput);
		}
		else if(customerInput.compare("NFC"))
		{
			isNFC = true;
		}
		else
		{
			cout << "Wrong entry" << endl;
			res = ERROR;
			break;
		}
		
		// in case no NFC ask find the price then ask for it		
		if(!isNFC)
		{
			res = findProductPrice(productNumber,root_node, &productPrice);
			cout << "Price is : " << productPrice  << endl;
			cout << "Insert money "<< endl;
			cin >> customerInput;
			if(is_number(customerInput)) 
			{
				insertedMoney = stof(customerInput);
			}
			else
			{
				cout << "Wrong entry" << endl;
				res = ERROR;
				break;
			}
		}			
		
		cout << insertedMoney << "  " << productNumber << endl;
		customerInput = "";
	}	
}

int setMachineConfig (string machine, xml_node<> * root_node)
{
	int res = ERROR;
	vector <float> vecRow;	
	string temp;
	

		
	cout <<  machine << endl;
	// This part will get the reference file with the associated price for each product
	if(0 == machine.compare("DEU"))
		res = machineDisplay_EU (root_node );
	
	else if(0 == machine.compare("DNA"))
	{
		res = machineDisplay_NA (root_node);
	}
	else
	{
		cout << "Machine does not exist" << endl;
		res = ERROR;
	}
	return res;
}