#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"

using namespace std;

int main()
{
    string tname = "Rafay";
    string dname = "IT";

    vector<string> tasks = {"Task 1", "Task 2"};
    vector<Employee*> employees;
    Employee* e1 = new Employee("employee-san-1", tasks);
    Employee* e2 = new Employee("employee-san-2", tasks);
    employees.push_back(e1);
    employees.push_back(e2);
    Manager* mgr = new Manager("manager-san", employees);
    
    Department* dpt[1] = { new Department(dname, employees, mgr) };

    Teacher* t = new Teacher(*&dpt, 1, 1, tname);
    t->fileComplaint();
    cout << endl;

    system("pause");
    return 0;
}
