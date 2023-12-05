#include "class.h"
using namespace std;

int Complaint::cID = 0;
int Employee::empID = 0;
int Manager::mgrID = 0;

System::System() {
    string tname = "Rafay";
    string dname = "IT";
    Department* dpt =  new Department(dname);
    departments.push_back(dpt);
    Teacher* tr = new Teacher(departments, 1, 1, tname);
    teachers.push_back(tr);
}
void System::printUI()
{
    system("cls");
    cout << "Welcome to the Complaint Management System";
    cout << "\nPress 1 to Login || Press 0 to Exit: ";
}
void System::Login()
{
    int temp = 1;
    int UID;
    string Uname;
    while (temp)
    {
        bool logged = 0;
        printUI();
        cin >> temp;
        if (temp)
        {
            cout << "\nEnter ID: ";
            cin >> UID;
            cout << "Enter your name: ";
            cin >> Uname;
            for (int i = 0; i < teachers.size() && !logged; i++)
            {
                if (UID == teachers[i]->getID())
                    if (Uname == teachers[i]->getName())
                    {
                        logged = 1;
                        teachers[i]->teacherUI();
                    }
            }
            if (!logged)
            {
                for (int i = 0; i < departments.size(); i++)
                {
                    departments[i]->login(UID,Uname,logged);
                }
            }
            if (!logged)
            {
                cout << "\nInvalid Credentials\nPress 1 to Retry: ";
                cin >> temp;
            }
        }
    }


}
void Complaint::printInfo() {

    cout << "\nComplaint ID: " << id << ", Description: " << description << endl;
    //department->print();
    //teacher->print();
    
}
Complaint::Complaint(string Description, Teacher* Teacher, Department* Dept) {//Constructor for Complaint
    cID++;
    id = cID;
    description = Description;
    teacher = Teacher;
    department = Dept;
    datefiled = time(0);
    //cout<<ctime(&datefiled);
}
void Department::login(int UID,string Uname,bool& logged)
{

    for (int i = 0; i < employees.size() && !logged; i++)
    {
        if (UID == employees[i]->getID())
            if (Uname == employees[i]->getName())
            {
                logged = 1;
                employees[i]->employeesUI();
            }
    }
    if(!logged)
        if (UID == manager->getID())
            if (Uname == manager->getName())
            {
                logged = 1;
                manager->managerUI();
            }
    return;
}
Department::Department(string n) {//Constructor for Department
    name = n;
    addEmployees();
    addManager();
}
Department::Department(string n, vector<Employee*> Employees, Manager* Mngr) {//Constructor for Department
    name = n;
    employees = Employees;
    manager = Mngr;
}
void Department::addTask(Complaint* task)
{
    tasks.push_back(task);
}
void Department::addEmployees()
{
    Employee* e1 = new Employee("emp1");
    Employee* e2 = new Employee("emp2");
    employees.push_back(e1);
    employees.push_back(e2);
}
void Department::addManager()
{
    manager = new Manager("manager", employees);
}
void Department::print() 
{
    cout << "Dept Name: " << name << endl;
    manager->print();
    for (int i = 0; i < employees.size(); i++) {
        employees[i]->print();
    }
}

void Department::assignTask()
{

    assignedtasks.push_back(tasks[tasks.size()-1]);
    tasks.pop_back();
    assignedtasks[0]->printInfo();
    manager->assignTask(assignedtasks[assignedtasks.size()-1]);

}

void Employee::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 \nPress 2 \nPress 3 \nPress 4 to Logout\n";
}
void Employee::employeesUI()
{
    int option;
    while (1) { // (for now) this while loop is to stay logged in
        printUI();
        cin >> option;
        switch (option)
        {
        case 1:
            
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return;
        }
    }
    return;
}
void Employee::print() {
    cout << "Employee ID: " << id << ", Name: " << name << "\nWith Tasks:";
    for (int i = 0; i < tasks.size(); i++) {
        tasks[i]->printInfo();
        cout << endl;
    }
}
Employee::Employee(string Name) {//Constructor for for Employee
    empID++;
    id = empID;
    name = Name;
}
Employee::Employee(string Name, vector<Complaint*> Tasks) {//Constructor for for Employee
    empID++;
    id = empID;
    name = Name;
    tasks = Tasks;
}
int Employee::getID()
{
    return id;
}
string Employee::getName()
{
    return name;
}
void Employee::receiveTask(Complaint* t)
{
    tasks.push_back(t);
    tasks[0]->printInfo();
    cout << "received by "<<name;
    _getch();

}
void Manager::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 \nPress 2 \nPress 3 \nPress 4 to Logout\n";
}
void Manager::managerUI()
{
    int option;
    while (1) { // (for now) this while loop is to stay logged in
        printUI();
        cin >> option;
        switch (option)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return;
        }
    }
    return;
}
int Manager::getID() {
    return id;
}
string Manager::getName() {
    return name;
}
void Manager::print() {
    cout << "Manager ID: " << id << ", Name: " << name << endl;
    cout << "Manages: \n";
    for (int i = 0; i < employees.size(); i++) {
        employees[i]->print();
    }
}
Manager::Manager(string Name) {//Constructor for Manager
    mgrID++;
    id = mgrID;
    name = Name;
}
Manager::Manager(string Name, vector<Employee*> Employees) {//Constructor for Manager
    mgrID++;
    id = mgrID;
    name = Name;
    employees = Employees;
}
void Manager::assignTask(Complaint* task)
{
    int emp;
    assignedtasks.push_back(task);
    for (int i=0;i<employees.size();i++)
        employees[i]->print();
    cout << "\nSelect Employee to assign the task: ";
    cin >> emp;
    employees[emp-1]->receiveTask(task);
}
void Teacher::print() {
    cout << "Teacher ID: " << id << ", Name: " << name << endl;
}
int Teacher::getID()
{
    return id;
}
string Teacher::getName()
{
    return name;
}
void Teacher::temp()
{
    complain[0]->temp();
}
void Complaint::temp()
{
    department[0].assignTask();
}
void Teacher::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 to file Complaint\nPress 2 to check notifications\nPress 3 to check status of Previous Complaints\nPress 4 to Logout\n";
}
void Teacher::teacherUI()
{
    int option;

    while (1) { // (for now) this while loop is to stay logged in
        printUI();
        cin >> option;
        switch (option)
        {
        case 1:
            fileComplaint();
            break;
        case 2:
            temp();
            break;
        case 3:
            printComplains();
            cout << "\nPress any key to continue";
            _getch();
            break;
        case 4:
            return;
        }
    }
    return;
}
Teacher::Teacher(vector<Department*> dpt, int size, int ID, string Name) {//Constructor for Teacher
    for (int i = 0; i < size; i++)
        departments.push_back(dpt[i]);
    id = ID;
    name = Name;
    no = 0;
}
void Teacher::fileComplaint()
{
    string des;
    cin.ignore();
    cout << "\nEnter Description of Complaint: ";
    getline(cin, des);
    complain.push_back(new Complaint(des, this, departments[0]));
    for (int i = 0; i < departments.size(); i++) {
        departments[i]->addTask(complain[complain.size()-1]);
    }
}
void Teacher::printComplains() {
    for (int i = 0; i < complain.size(); i++) {
        complain[i]->printInfo();
    }
}
Admin::Admin(int ID, string Name) {//Constructor for Admin
    id = ID;
    name = Name;
}

