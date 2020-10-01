#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "../include/mock/hardware.h"
#include "../include/error_variables.h"
#include "../include/main.h"

typedef std::vector<double> vec;
typedef std::vector<vec> vec2;

#define DNA_x 6
#define DNA_y 10

#define DEU_x 6
#define DEU_y 6
using namespace std;

// code is launch with the machine type "DEU" or "DNA" follow by the currency
int main (int argc, char *argv[]) 
{
	int res = ERROR;
	static string customerInput;
	static string machine;
	static string currency;
	static vector<vector <float> > v_product;
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
	
	res = setMachineConfig (machine, &v_product);
	// First argument is coin value or "NFC"
	// if NFC, third is employee name or "technician"
	while(1)
	{
		cout << "Insert Coin or present NFC + name" << endl;
		cin >> customerInput >> name;
	}
	
}

int setMachineConfig (string machine, vector<vector <float> > *v_product)
{
	int res = ERROR;
	vector <float> vecRow;	
	ifstream file;
	string temp;
	// This part will get the reference file with the associated price for each product
	if(0 == machine.compare("DEU"))
	{
		file.open("./productsFile/DEU_Products_Price.txt", ios::in);
		if(!file.is_open())
		{
			cout << "File not found!";
			res = ERROR;
		}
		else
		{
			for(int i = 0; i < DEU_x; i++){
				for(int j = 0; j < DEU_y; j++){
					
					getline(file, temp, ',');
					
					vecRow.push_back(stof(temp));
				}
				for (auto& it : vecRow) {
					cout << it << " ";
				}
				v_product->push_back(vecRow);
				vecRow.clear();
				cout << endl;
			}	
		}
	}
	else if(0 == machine.compare("DNA"))
	{
		file.open("./productsFile/DNA_Products_Price.txt", ios::in);
 		if(!file.is_open())
		{
			cout << "File not found!";
			res = ERROR;
		}
		else
		{
			for(int i = 0; i < DNA_x; i++){
				for(int j = 0; j < DNA_y; j++){
					
					getline(file, temp, ',');
					
					vecRow.push_back(stof(temp));
				}
				for (auto& it : vecRow) {
					cout << it << " ";
				}
				v_product->push_back(vecRow);
				vecRow.clear();
				cout << endl;
			}	
		}
	}
	else
	{
		cout << "Machine does not exist" << endl;
		res = ERROR;
	}
	file.close();
	return res;
}