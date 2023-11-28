#include "class.h"
using namespace std;

void System::notifymanager(){

}
void System::notifyteacher(){

}
void System::generateReport(){

}

System::System(){

}
Complaint::Complaint(int ID,string Description,Teacher *Teacher, Department *Dept ){
    id=ID;
    description=Description;
    teacher=Teacher;
    department=Dept;
    datefiled=time(0);
	//cout<<ctime(&datefiled);
}
Department::Department(string n,vector<Employee *> Employees,Manager* Mngr){//Constructor for Department
    name=n;
    employees=Employees;
    manager=Mngr;

}

Employee::Employee(int ID,string Name,vector<string> Tasks){
    id=ID;
    name=Name;
    tasks=Tasks;
}
Manager::Manager(int ID,string Name,vector<Employee *> Employees){
    id=ID;
    name=Name;
    employees=Employees;
}

Teacher::Teacher(int ID,string Name){
    id=ID;
    name=Name;
}

Admin::Admin(int ID,string Name){
    id=ID;
    name=Name;
}

