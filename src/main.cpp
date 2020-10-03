#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../include/mock/hardware.h"
#include "../include/variables.h"
#include "../include/main.h"
#include "../include/rapidxml_1.13/rapidxml.hpp"
#include "../include/library.h"
#include "../include/distributech.h"

using namespace std;
using namespace rapidxml;
// code is launch with the machine type "DEU" or "DNA" follow by the currency
int main (int argc, char *argv[]) 
{
    int res = ERROR;
    static bool isNFC = false;
    static bool isActivated = true;
    static string customerInput;
    static string machine;
    static string currency;
    static string name;
    static float insertedMoney(0.0f), change , productPrice;
    static int productNumber, productQuantity;
    Distributech distributech;
    xml_document<> doc;
    static xml_node<> * root_node;
    static int employeePrivilege =0;

    static int operation_mode ;

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


    res = setMachineConfig (machine, root_node,distributech);
    if(SUCCESS != res)
    {
        cout << "Error while setting hardware" << endl;
        return res;
    }
    res = distributech.initQuantityVector(root_node);
    if(SUCCESS != res)
    {
        cout << "Error initializing quantity" << endl;
        return res;
    }
    // First argument is coin value or "NFC"

    while(1)
    {
        while(!isActivated) 
        {
            cout << "Machine Deactivated Technician must present NFC" << endl;
            cin >> customerInput;
            if(0 == customerInput.compare("NFC"))
            {
                cout << "Enter Name" << endl;
                cin >> name;
                res = findEmployeeName (name, &employeePrivilege);
                if(SUCCESS != res)
                {
                    cout << "Employee file could not be open" << endl;
                    return res;
                }
                if(technician_ID == employeePrivilege)
                {
                    cout << "Enter 1 to activate the machine"<< endl;
                    cin >> customerInput;
                    if( 0 == customerInput.compare("1"))
                    {
                        isActivated = true;
                        employeePrivilege = 0;
                    }
                }
            }
        }

        cout << "Select product number (0 for coffee) or present NFC" << endl;
        cin >> customerInput;

        if(is_number(customerInput)) 
        {
            isNFC = false;
            productNumber = stoi(customerInput);
        }
        else if(0 == customerInput.compare("NFC"))
        {
            isNFC = true;
        }
        else
        {
            cout << "Wrong entry" << endl;
            res = ERROR;
            break;
        }
        
        // normaly the employee ID is part of the NFC in our case you have to enter the name
        if(isNFC)
        {
            cout << " Employee name "<< endl;
            cin >> name;
            res = findEmployeeName (name, &employeePrivilege);
            if(SUCCESS != res)
            {
                cout << "Employee file could not be open" << endl;
                return res;
            }
            if(technician_ID != employeePrivilege)
            {
                if(0 == employeePrivilege)
                {
                    isNFC = false;
                }
                cout << "Select product number (0 for coffee)" <<endl;
                cin >> customerInput;

                if(is_number(customerInput)) 
                {
                    productNumber = stoi(customerInput);
                }
            }
        }

        if(technician_ID != employeePrivilege)
        {
            res = distributech.getQuantity(productNumber,&productQuantity);
            if(SUCCESS != res)
            {
                cout << "Quantity could not be get" << endl;
                return res;
            }
            if(productQuantity > 0)
            {
                if(!isNFC || (isNFC && (0 != productNumber)))
                {
                    res = distributech.findProductPrice(productNumber,root_node, &productPrice);
                    if(SUCCESS != res)
                    {
                        cout << "Price could not be found" << endl;
                        return res;
                    }
                    cout << "Price is : " << productPrice  << endl;
                    cout << "Insert money "<< endl;
                    while(0 < (productPrice - insertedMoney) )
                    {
                        cin >> customerInput;
                        if(is_number(customerInput)) 
                        {
                            insertedMoney += stof(customerInput);
                            change = productPrice - insertedMoney;
                            if(0 < change)
                                cout << "Remaining  :" << change <<endl;
                        }
                        else
                        {
                            cout << "Wrong entry" << endl;
                            res = ERROR;
                            break;
                        }
                    }
                    insertedMoney = 0.0f;
                }
                
                serve_Product();
                distributech.setQuantity(productNumber,productQuantity -1);
            }
            else
            {
                cout << "Product Not Available" << endl;
            }
        }
        else
        {
            cout << "technician Maintenance !!!" << endl;
            cout << "Select 1 to de activate Distribution" << endl;
            cout << "Select 2 to reset change in machine" << endl;
            cout << "Select 3 to reset product qauntity in machine" << endl;
            cin >> customerInput;
            if(is_number(customerInput)) 
                operation_mode = stoi(customerInput);

            switch(operation_mode)
            {
                case 1:
                    isActivated = false;
                    break;
                   
                case 2:
                    break;
                
                case 3:
                    res = distributech.initQuantityVector(root_node);
                    if(SUCCESS != res)
                    {
                        cout << "Quantity vector could not be initialized" << endl;
                        return res;
                    }
                    break;

                default:
                    break;
            }
        }
        customerInput = "";
    } // END WHILE 1
    return res;
} // END MAIN



int setMachineConfig (string machine, xml_node<> * root_node, Distributech distributech)
{
    int res = ERROR;
    vector <float> vecRow;
    string temp;


    cout <<  machine << endl;
    // This part will get the reference file with the associated price for each product
    if(0 == machine.compare("DEU"))
        res = distributech.machineDisplay_EU (root_node );

    else if(0 == machine.compare("DNA"))
    {
        res = distributech.machineDisplay_NA (root_node);
    }
    else
    {
        cout << "Machine does not exist" << endl;
        res = ERROR;
    }
    return res;
}

int findEmployeeName (string employee, int *employeePrivilege) 
{

    string substring;   // declaring subtring variable.

    ifstream file_text ("./employee/Employees.txt");  // creating file_text object of ifstream type.

    string x;
    *employeePrivilege = 0;
    
    if (file_text.is_open())       //is_open open the text file.
    {
        while ( getline (file_text,x) )
        {
            if (x.find(employee, 0) != string::npos) 
            {
                if(0 == employee.compare("technician"))
                    *employeePrivilege = technician_ID;
                else
                    *employeePrivilege = employee_ID;
                break;
            }

        }
        file_text.close(); //to close text file.

    }
    else
    {
        cout << "Unable to open file";
        return ERROR;
    }

    return SUCCESS;
}