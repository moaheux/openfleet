#include <string>
#include <algorithm>    // std::find_if
#include <iostream>
#include <sstream>
#include "../include/library.h"
#include "../include/error_variables.h"

bool is_number(const std::string& s)
{
    std::istringstream iss(s);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}

int machineDisplay_EU (xml_node<> * root_node )
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

int machineDisplay_NA (xml_node<> * root_node )
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

int findProductPrice(int productNumber,xml_node<> * root_node, float * price)
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

    int findProductQuantity(int productNumber,xml_node<> * root_node, int * quantity)
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
    *quantity = stof(product_node->first_node("quantity")->value());
    return SUCCESS;
}