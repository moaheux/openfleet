#ifndef  __LIBRARY__
#define __LIBRARY__
#include "./rapidxml_1.13/rapidxml.hpp"

#define DNA_x 6
#define DNA_y 10

#define DEU_x 6
#define DEU_y 6

using namespace rapidxml;
using namespace std;
bool is_number(const std::string& s);
int machineDisplay_EU (xml_node<> * root_node );
int machineDisplay_NA (xml_node<> * root_node );
int findProductPrice(int productNumber,xml_node<> * root_node, float * price);

#endif