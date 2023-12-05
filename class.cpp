#include "class.h"
using namespace std;

int Complaint::cID = 0;
int Employee::empID = 0;
int Manager::mgrID = 0;

System::System()//Constructor for System
{
    string tname = "Rafay";
    string dname = "IT";
    Department* dpt =  new Department(dname);
    departments.push_back(dpt);
    Teacher* tr = new Teacher(departments, 1, 1, tname);
    teachers.push_back(tr);
}
void System::printUI()//Prints Base level UI
{
    system("cls");
    cout << "Welcome to the Complaint Management System";
    cout << "\nPress 1 to Login || Press 0 to Exit: ";
}
void System::Login()//Login Function
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
            cout << "Enter ID: ";
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
void Complaint::printInfo()//Prints Info about complaint, status needs to be added 
{

    cout << "Complaint ID: " << id << ", Description: " << description << endl;
    //department->print();
    //teacher->print();
    
}
Complaint::Complaint(string Description, Teacher* Teacher, Department*& Dept) {//Constructor for Complaint
    cID++;
    id = cID;
    description = Description;
    teacher = Teacher;
    department = Dept;
    datefiled = time(0);
    //cout<<ctime(&datefiled);
}
void Department::login(int UID,string Uname,bool& logged)//Login for the respective department, i.e its manager and employees
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
Department::Department(string n) //Constructor for Department
{   name = n;
    addEmployees();
    addManager();
}
Department::Department(string n, vector<Employee*> Employees, Manager* Mngr) //Constructor for Department
{   name = n;
    employees = Employees;
    manager = Mngr;
}
void Department::addTask(Complaint* task)//Add the complain in the array of complaint
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

void Department::assignTask()//pushes all the tasks to manager for assignment
{
    for(int i=0;tasks.size()!=0;i++)
    {
        assignedtasks.push_back(tasks[tasks.size()-1]);
        tasks.pop_back();
        manager->getTask(assignedtasks[i]);
    }
}

void Employee::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 Check Tasks\nPress 2 Complete Task\nPress 3 \nPress 4 to Logout\n";
}
void Employee::employeesUI()
{
    int option;
    while (1) { // (for now) this while loop is to stay logged in
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            checkTasks();
            _getch();
            break;
        case 2:
            completeTask();
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
    cout << "\nEmployee ID: " << id << ", Name: " << name << "\nWith Tasks:";
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
void Employee::receiveTask(Complaint* t)//Gets tje task for employee to complete
{
    tasks.push_back(t);
    tasks[0]->printInfo();
    cout << "received by "<<name;
    _getch();

}
void Employee::checkTasks()
{
    for(int i=0;i<tasks.size();i++)
        {cout<<i+1<<") ";
        tasks[i]->printInfo();}
}
void Employee::completeTask()
{
    int tsk;
    checkTasks();
    cout<<"Select task to Complete: ";
    cin>>tsk;
    tasks[tsk];
}
void Manager::checkTasks()
{
    for(int i=0;i<tasks.size();i++)
        {cout<<i+1<<") ";
        tasks[i]->printInfo();}
}
void Manager::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 to Assign task\nPress 2 \nPress 3 \nPress 4 to Logout\n";
}
void Manager::managerUI()
{
    int option;
    while (1) { // (for now) this while loop is to stay logged in
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            assignTask();
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
void Manager::getTask(Complaint* task)
{
    tasks.push_back(task);
    
}
void Manager::assignTask()//Assigns 1 task to the selected emp
{
    int emp,tsks;
    checkTasks();
    cout<<"\nEnter the task number you want to assign: ";
    cin>>tsks;
    assignedtasks.push_back(tasks[tsks-1]);
    for(int i=tsks-1;i<tasks.size()-1;i++)
    {
        tasks[i]=tasks[i+1];
    }
    tasks.pop_back();                                                  
    for (int i=0;i<employees.size();i++)
        employees[i]->print();
    cout << "\n\nSelect Employee to assign the task: ";
    cin >> emp;
    employees[emp-1]->receiveTask(assignedtasks[assignedtasks.size()-1]);
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
    for(int i=0;i<complain.size();i++)
        complain[i]->temp();
}
void Complaint::temp()
{
    department->assignTask();
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
        system("cls");
        switch (option)
        {
        case 1:
            fileComplaint();
            break;
        case 2:
            break;
        case 3:
            printComplains();
            cout << "\nPress any key to continue";
            _getch();
            break;
        case 4:
            temp();
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
    Complaint *comp=new Complaint(des, this, departments[0]);
    complain.push_back(comp);
    departments[0]->addTask(complain[complain.size()-1]);
    
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

