#include "class.h"
using namespace std;

int Complaint::cID = 0;
int Employee::empID = 0;
int Manager::mgrID = 0;

System::System(Department *dpt[],int size){
    for(int i=0;i<size;i++)
        departments.push_back(dpt[i]);
}  
Complaint::Complaint(string Description,Teacher *Teacher, Department *Dept ){//Constructor for Complaint
    cID++;
    id = cID;
    description=Description;
    teacher=Teacher;
    department=Dept;
    datefiled=time(0);
	//cout<<ctime(&datefiled);
}
Department::Department(string n){//Constructor for Department
    name=n;
}
Department::Department(string n,vector<Employee *> Employees,Manager* Mngr){//Constructor for Department
    name=n;
    employees=Employees;
    manager=Mngr;
}
void Department::addTask(Complaint *task)
{
    tasks.push_back(task);
}
void Department::print() {
    cout << "Dept Name: " << name << endl;
    manager->print();
    for (int i = 0; i < employees.size(); i++) {
        employees[i]->print();
    }
}
void Teacher::print() {
    cout << "Teacher ID: " << id << ", Name: " << name << endl;
}
void Employee::print() {
    cout << "Employee ID: " << id << ", Name: " << name << "\nWith Tasks: \n";
    for (int i = 0; i < tasks.size(); i++) {
        cout << "-" << tasks[i];
        cout << endl;
    }
}
void Manager::print() {
    cout << "Manager ID: " << id << ", Name: " << name << endl;
    //cout << "\nManages: \n";
    //for (int i = 0; i < employees.size(); i++) {
    //    employees[i]->print();
    //}
}
void Complaint::printInfo() {

    cout << "Complaint ID: " << id << ", Description: " << description << endl;
    department->print();
    teacher->print();
}
Employee::Employee(string Name,vector<string> Tasks){//Constructor for for Employee
    empID++;
    id = empID;
    name=Name;
    tasks=Tasks;
}
Manager::Manager(string Name,vector<Employee *> Employees){//Constructor for Manager
    mgrID++;
    id = mgrID;
    name=Name;
    employees=Employees;
}

Teacher::Teacher(Department *dpt[],int size,int ID,string Name){//Constructor for Teacher
    for(int i=0;i<size;i++)
        departments.push_back(dpt[i]);
    id=ID;
    name=Name;
}
void Teacher :: fileComplaint()
{
    string s = "Test complain";
    complain = new Complaint(s, this, departments[0]);
    for (int i = 0; i < departments.size(); i++) {
        departments[i]->addTask(complain);
        complain->printInfo();
    }
    
}

Admin::Admin(int ID,string Name){//Constructor for Admin
    id=ID;
    name=Name;
}

