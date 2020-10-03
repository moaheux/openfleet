#ifndef  __DISTRIBUTECH__
#define __DISTRIBUTECH__
#include <vector>
#include "./rapidxml_1.13/rapidxml.hpp"
using namespace std;
using namespace rapidxml;
class Distributech
{
    private:
        vector<int> quantity;
    public:
        int machineDisplay_EU (xml_node<> * root_node );
        int machineDisplay_NA (xml_node<> * root_node );
        int findProductPrice(int productNumber,xml_node<> * root_node, float * price);
        int findProductQuantity(int productNumber,xml_node<> * root_node, int * r_quantity);
        int getQuantity(int productNumber,int *productQuantity);
        int initQuantityVector(xml_node<> * root_node);
        int setQuantity(int productNumber,int productQuantity);
};

#endif