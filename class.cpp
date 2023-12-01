#include "class.h"
using namespace std;

int Complaint:: id=0;

System::System(Department *dpt[],int size){
    for(int i=0;i<size;i++)
        departments.push_back(dpt[i]);
}  
Complaint::Complaint(string Description,Teacher *Teacher, Department *Dept ){//Constructor for Complaint
    id++;
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
void Complaint::printInfo() {

    cout << id << endl << description << endl;
    department->print();
    teacher->print();
}
void Department::addTask(Complaint *task)
{
    tasks.push_back(task);
}
void Department::print() {
    cout << name << endl;
}
void Teacher::print() {
    cout << name << endl;
}
Employee::Employee(int ID,string Name,vector<string> Tasks){//Constructor for for Employee
    id=ID;
    name=Name;
    tasks=Tasks;
}
Manager::Manager(int ID,string Name,vector<Employee *> Employees){//Constructor for Manager
    id=ID;
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
    string s="Test complain";
    complain=new Complaint(s,this,departments[0]);
    departments[0]->addTask(complain);
    complain->printInfo();
}

Admin::Admin(int ID,string Name){//Constructor for Admin
    id=ID;
    name=Name;
}

