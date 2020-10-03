#ifndef  __MAIN__
#define __MAIN__
#include "../include/distributech.h"
#include "./rapidxml_1.13/rapidxml.hpp"
using namespace rapidxml;
int setMachineConfig (string machine, xml_node<> *root_node, Distributech distributech);
int findEmployeeName (string employee, int *employeePrivilege);
#endif
