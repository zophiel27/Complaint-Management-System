#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"

using namespace std;

int main()
{
    string name="Rafay";
    string nd="IT";
    Department *dpt[1];
    dpt[0]=new Department(nd);
    Teacher *t=new Teacher(*&dpt,1,1,name);
    t->fileComplaint();
    system("pause");
    return 0;
}
