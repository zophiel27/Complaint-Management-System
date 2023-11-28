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
Complaint::Complaint(int ID,string Description,Teacher *Teacher, Department *Dept ){//Constructor for Complaint
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

Teacher::Teacher(int ID,string Name){//Constructor for Teacher
    id=ID;
    name=Name;
}

Admin::Admin(int ID,string Name){//Constructor for Admin
    id=ID;
    name=Name;
}

