#include "../include/distributech.h"
#include "../include/variables.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidxml;
using namespace std;

int Distributech::machineDisplay_EU (xml_node<> * root_node )
{
    int col_count = 0;
    for (xml_node<> * product_node = root_node->first_node("product"); product_node; product_node = product_node->next_sibling())
    {
        printf("%s : ", product_node->first_attribute("name")->value());
            

        xml_node<> * price_node = product_node->first_node("price");
        printf("%s €", price_node->value());


        xml_node<> * quantity_node = product_node->first_node("quantity");
        printf("  nb %s", quantity_node->value());
        if(col_count >= (DEU_x -1))
        {
            cout << endl;
            col_count = 0;
        }
        else
        {
            cout << "   ";
            col_count ++;
        }
    }
	return SUCCESS;
}

int Distributech::machineDisplay_NA (xml_node<> * root_node )
{
    int col_count = 0;

    for (xml_node<> * product_node = root_node->first_node("product"); product_node; product_node = product_node->next_sibling())
    {
        printf("%s : ", product_node->first_attribute("name")->value());

        xml_node<> * price_node = product_node->first_node("price");
        printf("%s €", price_node->value());


        xml_node<> * quantity_node = product_node->first_node("quantity");
        printf("  nb %s", quantity_node->value());
        if(col_count >= (DNA_x -1))
        {
            cout << endl;
            col_count = 0;
        }
        else
        {
            cout << "   ";
            col_count ++;
        }

    }
    return SUCCESS;
}

int Distributech::findProductPrice(int productNumber,xml_node<> * root_node, float * price)
{

    xml_node<> * product_node = root_node->first_node("product");
    xml_node<> * price_node = product_node->first_node("price");

    for (int i = 0; i< productNumber; i++)
    {
        product_node = product_node->next_sibling();
        if(!product_node)
        {
            return ERROR;
        }
    }
    *price = stof(product_node->first_node("price")->value());
    return SUCCESS;
}

int Distributech::findProductQuantity(int productNumber,xml_node<> * root_node, int * r_quantity)
{

    xml_node<> * product_node = root_node->first_node("product");
    xml_node<> * price_node = product_node->first_node("quantity");

    for (int i = 0; i< productNumber; i++)
    {
        product_node = product_node->next_sibling();
        if(!product_node)
        {
            return ERROR;
        }
    }
    *r_quantity = stoi(product_node->first_node("quantity")->value());
    return SUCCESS;
}

int Distributech::initQuantityVector(xml_node<> * root_node)
{
	int res;
	for (xml_node<> * product_node = root_node->first_node("product"); product_node; product_node = product_node->next_sibling())
    {
        xml_node<> * quantity_node = product_node->first_node("quantity");
        quantity.push_back(stoi(quantity_node->value()));
	}
	return SUCCESS;
}

int Distributech::getQuantity(int productNumber,int *productQuantity)
{
	*productQuantity = quantity.at(productNumber);
	return SUCCESS;
}

int Distributech::setQuantity(int productNumber,int productQuantity)
{
	quantity.at(productNumber) = productQuantity;
	return SUCCESS;
}