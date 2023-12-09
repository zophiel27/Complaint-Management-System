#include "class.h"
using namespace std;

int Complaint::cID = 0;
const char* statusArray[] = { "NEW", "ASSIGNED", "RESOLVED","COMPLETED", "CLOSED" };

void start()
{
    int op;
    System* s = new System();
    Admin* admin = initAdmin(s);
    s->loadAdmin(admin);
    while (1) {
        s->printUI();
        cin >> op;
        switch (op)
        {
        case 1:
            s->Login();
            break;
        case 2:
            s->generateReport();
            cout << "\nPress any key to continue...";
            _getch();
            return;
        case 3:
            return;
        default:
            cout << "Invalid\nPress any key to continue...";
            _getch();
            break;
        }
    }
}
Admin* initAdmin(System* s)
{
    string filename = "admins.txt";
    ifstream inputFile(filename);
    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cout << "Error opening the file " << filename << endl;
        _getch();
        return nullptr;
    }
    int id;
    string name;
    // Read data from the file until the end is reached
    inputFile >> id >> name;
    // Close the file
    inputFile.close();

    return (new Admin(id, name, s));
}
System::System()//Constructor for System
{
    readDept();
    readTeachers();
}
void System::loadAdmin(Admin* ad)
{
    admin = ad;
}
void System::readDept()
{
    // Open the file
    string filename = "departments.txt";
    ifstream inputFile(filename);
    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cout << "Error opening the file " << filename << endl;
        _getch();
        return;
    }
    // Variables to store data read from the file
    string name;
    // Read data from the file until the end is reached
    while (inputFile >> name) 
    {
        // Store data in arrays
        Department* dpt = new Department(name);
        departments.push_back(dpt);
    }
    // Close the file
    inputFile.close();
}
void System::readTeachers()
{
    // Open the file
    ifstream inputFile("teachers.txt");
    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cout << "Error opening the file 'teachers.txt'" << endl;
        _getch();
        return;
    }
    // Variables to store data read from the file
    int id;
    string name;
    // Read data from the file until the end is reached
    while (inputFile >> id >> name) 
    {
        // Store data in arrays
        Teacher* tr = new Teacher(departments, id, name);
        teachers.push_back(tr);
    }
    // Close the file
    inputFile.close();
}
void System::printUI()//Prints Base level UI
{
    system("cls");
    cout << "Welcome to the Complaint Management System";
    cout << "\nPress 1 to Login || Press 2 to Generate Report and Exit || Press 3 to Exit\n";
}
void System::Login()//Login Function
{
    int temp = 1;
    int UID;
    string Uname;
    bool logged = 0;
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
                departments[i]->login(UID, Uname, logged);
            }
        }
        if (!logged)
        {
            if (UID == admin->getID())
                if (Uname == admin->getName())
                {
                    logged = 1;
                    admin->adminUI();
                }
        }
        if (!logged)
        {
            cout << "\nInvalid Credentials\nPress 1 to Retry: ";
            cin >> temp;
        }
    }
}
void System::generateReport()
{
    for (int i = 0; i < departments.size(); i++)
    {
        departments[i]->createReport();
    }
}
void System::addManager(Manager* m, string deptname)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i]->getName() == deptname)
        {
            departments[i]->updateManager(m);
        }
    }
}
void System::addEmployee(Employee* e, string deptname)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i]->getName() == deptname)
        {
            departments[i]->updateEmployee(e);
        }
    }
}
void System::addTeacher(int id, string name)
{
    teachers.push_back(new Teacher(departments, id, name));
}
ComplaintStatus Complaint::getStatus()
{
    return status;
}
void Complaint::printInfo()//Prints Info about complaint, status needs to be added 
{
    cout << "Complaint ID: " << id << ", Description: " << description << endl;
}
void Complaint::printDetails()
{
    printInfo();
    cout << "Status: " << statusArray[status] << "\nDepartment: " << department->getName() << "\nEmployee Assigned: " << assignedEmployee;
    if (feedback != "\0")
    {
        cout << "\nFeedback: " << feedback;
    }
    //cout<<"Date Filed: "<<ctime(&datefiled);
    cout << endl;
}
void Complaint::addFeedback(string s)
{
    feedback = s;
}
Complaint::Complaint(string Description, Teacher* Teacher, Department*& Dept) {//Constructor for Complaint
    cID++;
    id = cID;
    description = Description;
    teacher = Teacher;
    department = Dept;
    datefiled = time(0);
    shiftStatus(NEW);
}
void Complaint::shiftStatus(ComplaintStatus s)
{
    status = s;
}
void Complaint::createReport()
{
    string filename = department->getName();
    filename += "Report.txt";
    ofstream outFile(filename, ios_base::app);
    if (!outFile.is_open())
    {
        cout << "Error opening " << filename << endl;
        _getch();
        return;
    }

    outFile << "Complaint ID: " << id << "\nDescription: " << description << "\nStatus: " << statusArray[status] << "\nEmployee Assigned: " << assignedEmployee;
    if (feedback != "\0")
    {
        outFile << "\nFeedback: " << feedback;
    }
    outFile << "\n\n";
    outFile.close();
}
void  Complaint::assignEmployee(string name)
{
    assignedEmployee = name;
}
void Complaint::notify()
{
    teacher->setNoti();
}
void Department::login(int UID, string Uname, bool& logged)//Login for the respective department, i.e its manager and employees
{

    for (int i = 0; i < employees.size() && !logged; i++)
    {
        if (UID == employees[i]->getID())
            if (Uname == employees[i]->getName())
            {
                logged = 1;
                employees[i]->employeesUI();
                updateTaskList();
            }
    }
    if (!logged)
        if (UID == manager->getID())
            if (Uname == manager->getName())
            {
                logged = 1;
                manager->managerUI();
                updateTaskList();
                notifyteacher();
            }
    return;
}
void Department::notifyteacher()
{
    for (int i = 0; i < resolvedtasks.size(); i++)
    {
        if (resolvedtasks[i]->getStatus() == COMPLETED)
        {
            completedtasks.push_back(resolvedtasks[i]);
            for (int j = i; j < resolvedtasks.size() - 1; j++)
            {
                resolvedtasks[j] = resolvedtasks[j + 1];
            }
            resolvedtasks.pop_back();
            i--;
        }
    }
    for (int i = 0; i < completedtasks.size(); i++)
    {
        completedtasks[i]->notify();
    }
}
void Department::updateTaskList()
{
    bool update = 0;
    for (int i = 0; i < assignedtasks.size(); i++)
    {
        if (assignedtasks[i]->getStatus() == RESOLVED)
        {
            update = 1;
            resolvedtasks.push_back(assignedtasks[i]);
            for (int j = i; j < assignedtasks.size() - 1; j++)
            {
                assignedtasks[j] = assignedtasks[j + 1];
            }
            assignedtasks.pop_back();
            i--;
        }
    }
    if (update)
        pushTask();
}

Department::Department(string n) //Constructor for Department
{
    name = n;
    readStaff();
}
Department::Department(string n, vector<Employee*> Employees, Manager* Mngr) //Constructor for Department
{
    name = n;
    employees = Employees;
    manager = Mngr;
}
void Department::addTask(Complaint*& task)//Add the complain in the array of complaint
{
    tasks.push_back(task);
}
void Department::readStaff()
{
    // Open the file
    string fname = name;
    fname += ".txt";
    ifstream inputFile(fname);
    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cout << "Error opening the file " << fname << endl;
        _getch();
        return;
    }
    // Variables to store data read from the file
    string name;
    int id, i = 0;

    // Read data from the file until the end is reached
    while (inputFile >> id >> name) {
        // Store data in arrays
        if (i)
        {
            Employee* emp = new Employee(id, name);
            employees.push_back(emp);
        }
        else {
            manager = new Manager(id, name);
        }
        i++;
    }
    manager->getEmployees(employees);
    // Close the file
    inputFile.close();
}
string Department::getName()
{
    return name;
}
void Department::printStaff()
{
    cout << "Dept Name: " << name << endl;
    manager->print();
    for (int i = 0; i < employees.size(); i++) {
        employees[i]->print();
    }
}
void Department::updateManager(Manager* m)
{
    manager = m;
}
void Department::updateEmployee(Employee* e)
{
    employees.push_back(e);
}
void Department::createReport()
{

    for (int i = 0; i < assignedtasks.size(); i++)
    {
        assignedtasks[i]->createReport();
    }
    for (int i = 0; i < resolvedtasks.size(); i++)
    {
        resolvedtasks[i]->createReport();
    }
    for (int i = 0; i < completedtasks.size(); i++)
    {
        completedtasks[i]->createReport();
    }

}
void Department::pushTask()//pushes all the tasks to manager for assignment
{
    for (int i = 0; tasks.size() != 0; i++)
    {
        assignedtasks.push_back(tasks[tasks.size() - 1]);
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
    while (1) {
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            checkTasks(ASSIGNED);
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
    cout << "Name: " << name << "\nWith Tasks: ";
    for (int i = 0; i < tasks.size(); i++) {
        tasks[i]->printInfo();
        cout << endl;
    }
}
Employee::Employee(int ID, string Name) {//Constructor for for Employee
    id = ID;
    name = Name;
}
Employee::Employee(int ID, string Name, vector<Complaint*> Tasks) {//Constructor for for Employee
    id = ID;
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
void Employee::receiveTask(Complaint*& t)//Gets the task for employee to complete
{
    t->assignEmployee(name);
    tasks.push_back(t);
    tasks[tasks.size() - 1]->printInfo();
    cout << "received by " << name;
    t->dateAssigned = time(0);
    t->shiftStatus(ASSIGNED);
    _getch();
}
void Employee::checkTasks(ComplaintStatus s)
{
    if (tasks.size() == 0) {
        cout << "None available\n";
        _getch();
        return;
    }
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i]->getStatus() == s)
        {
            cout << i + 1 << ") ";
            tasks[i]->printInfo();
        }
    }
}
void Employee::completeTask()
{
    int tsk;
    checkTasks(ASSIGNED);
    cout << "Select task to Complete: ";
    cin >> tsk;
    if (tsk > tasks.size() || tasks[tsk - 1]->getStatus() != ASSIGNED)
    {
        cout << "No task at that index ";
        _getch();
        return;
    }
    tasks[tsk-1]->dateResolved=time(0);
    tasks[tsk - 1]->shiftStatus(RESOLVED);
}
void Manager::checkTasks(ComplaintStatus s)
{
    if (tasks.size() == 0) {
        cout << "None available\n";
        _getch();
        return;
    }
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i]->getStatus() == s)
        {
            cout << i + 1 << ") ";
            tasks[i]->printDetails();
        }
    }
}
void Manager::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 to Assign task\nPress 2 Review Tasks\nPress 3 to Logout\n";
}
void Manager::managerUI()
{
    int option;
    while (1) { 
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            assignTask();
            break;
        case 2:
            reviewTask();
            break;
        case 3:
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
Manager::Manager(int ID, string Name) {//Constructor for Manager
    id = ID;
    name = Name;
}
Manager::Manager(int ID, string Name, vector<Employee*> Employees) {//Constructor for Manager
    id = ID;
    name = Name;
    employees = Employees;
}
void Manager::getEmployees(vector<Employee*> Employees)
{
    employees = Employees;
}
void Manager::getTask(Complaint*& task)
{
    tasks.push_back(task);
}
int Manager::getIndex(int id)
{
    for (int i = 0; i < employees.size(); i++) {
        if (id == employees[i]->getID())
        {
            return i;
        }
    }
    return -1;
}
void Manager::reviewTask()
{
    int tsks;
    checkTasks(RESOLVED);
    cout << "\nEnter the task number you want to Review: ";
    cin >> tsks;
    if (tsks > tasks.size() || tasks[tsks - 1]->getStatus() != RESOLVED)
    {
        cout << "No task at that index ";
    }
    else {
        
        tasks[tsks - 1]->shiftStatus(COMPLETED);
        tasks[tsks - 1]->printDetails();
        cout << "Complete Task ";
    }
    _getch();
    return;
}
void Manager::assignTask()//Assigns 1 task to the selected emp
{
    int emp, tsks;
    checkTasks(NEW);
    cout << "\nEnter the task number you want to assign: ";
    cin >> tsks;
    if (tsks > tasks.size() || tasks[tsks - 1]->getStatus() != NEW)
    {
        cout << "No task at that index ";
        _getch();
        return;
    }
    /*assignedtasks.push_back(tasks[tsks - 1]);
    for (int i = tsks - 1; i < tasks.size() - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }
    tasks.pop_back();*/
    for (int i = 0; i < employees.size(); i++)
    {
        cout << i + 1 << ") ";
        employees[i]->print();
        cout << endl;
    }

    cout << "\n\nSelect Employee to assign the task: ";
    cin >> emp;
    if (emp > employees.size())
    {
        cout << "No Emp at that index ";
        _getch();
        return;
    }
    employees[emp - 1]->receiveTask(tasks[tsks - 1]);
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
void Teacher::pushTask()
{
    for (int i = 0; i < complain.size(); i++)
        complain[i]->pushTask();
}
void Complaint::pushTask()
{
    department->pushTask();
}
void Teacher::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 to file Complaint\nPress 2 to check notifications\nPress 3 to check status of Previous Complaints\nPress 4 Record Feedback\nPress 5 to Logout\n";
}
void Teacher::teacherUI()
{
    int option;

    while (1) { 
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            fileComplaint();
            break;
        case 2:
            checkNotifications();
            cout << "\nPress any key to continue...";
            _getch();
            clearNotifications();
            break;
        case 3:
            printComplains();
            cout << "\nPress any key to continue...";
            _getch();
            break;
        case 4:
            recordFeedback();
            break;
        case 5:
            pushTask();
            return;
        }
    }
    return;
}
Teacher::Teacher(vector<Department*> dpt, int ID, string Name) {//Constructor for Teacher
    for (int i = 0; i < dpt.size(); i++)
        departments.push_back(dpt[i]);
    id = ID;
    name = Name;
}
void Teacher::fileComplaint()
{
    int index = 10;
    string input;
    cout << "\nEnter name of department in which you want to file the complaint: IT Admin Accounts: ";
    cin >> input;
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i]->getName() == input)
        {
            index = i;
        }
    }
    if (index == 10)
    {
        cout << "Invalid Dept ";
        _getch();
        return;
    }
    string des;
    cin.ignore();
    cout << "\nEnter Description of Complaint: ";
    getline(cin, des);
    Complaint* comp = new Complaint(des, this, departments[index]);
    complain.push_back(comp);
    departments[index]->addTask(complain[complain.size() - 1]); //for now it is only going in department 1

}
void Teacher::setNoti() {
    notifications = "One of Your comlain has been resolved and reviewed ";
}
void Teacher::clearNotifications()
{
    notifications = "\0";
}
void Teacher::checkNotifications()
{
    if (notifications == "\0")
        cout << "\nNo Notifications ";
    cout << notifications << endl;
}
void Teacher::printComplains() {
    for (int i = 0; i < complain.size(); i++) {
        complain[i]->printDetails();
        cout << endl;
    }
}
void Teacher::recordFeedback()
{
    int comp;
    cout << "Which Complaint you want to record feedback for:\n";
    for (int i = 0; i < complain.size(); i++)
    {
        if (complain[i]->getStatus() == COMPLETED)
        {
            cout << i + 1 << ") ";
            complain[i]->printInfo();
        }
    }
    cin >> comp;
    if (comp - 1 < complain.size())
        if (complain[comp - 1]->getStatus() == COMPLETED) {
            complain[comp-1]->dateClosed=time(0);
            complain[comp - 1]->shiftStatus(CLOSED);
            string feedback;
            cin.ignore();
            cout << "Enter feedback: ";
            getline(cin, feedback);
            complain[comp - 1]->addFeedback(feedback);
        }
        else
        {
            cout << "Invalid Complaint ";
            _getch();
        }
}
Admin::Admin(int ID, string Name, System* s) {//Constructor for Admin
    id = ID;
    name = Name;
    sys = s;
}
int Admin::getID()
{
    return id;
}
string Admin::getName()
{
    return name;
}
void Admin::printUI()
{
    system("cls");
    cout << "Welcome " << name;
    cout << "\nSelect from the options below:";
    cout << "\nPress 1 Add Manager\nPress 2 Add Employee\nPress 3 Add Teacher\nPress 4 Logout\n";
}
void Admin::adminUI()
{
    int option;
    while (1) { 
        printUI();
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            addManager();
            break;
        case 2:
            addEmployee();
            break;
        case 3:
            addTeacher();
            break;
        case 4:
            return;
        }
    }
    return;
}
void Admin::addTeacher()
{
    int id;
    string name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;

    string filename = "teachers.txt";
    ofstream outFile(filename, ios_base::app);
    if (!outFile.is_open()){
        cout << "Error opening " << filename << endl;
        _getch();
        return;
    }

    outFile << id << " " << name << endl;

    sys->addTeacher(id, name);
    outFile.close();
}
void Admin::addManager()
{
    string filename, deptname;
    cout << "Which department do you want to add to: IT Accounts Admin: ";
    cin >> deptname;
    filename = deptname + ".txt";

    fstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "Error opening " << filename << endl;
        _getch();
        return;
    }
    int id;
    string name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;

    outFile.seekg(0, ios::beg);
    outFile << id << " " << name << endl;
    
    sys->addManager(new Manager(id, name), deptname);

    outFile.close();
}
void Admin::addEmployee()
{
    string filename, deptname;
    cout << "Which department do you want to add to: IT Accounts Admin: ";
    cin >> deptname;
    filename = deptname + ".txt";

    ofstream outFile(filename, ios_base::app);
    if (!outFile.is_open())
    {
        cout << "Error opening " << filename << endl;
        _getch();
        return;
    }
    int id;
    string name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;

    outFile << id << " " << name << endl;

    sys->addEmployee(new Employee(id, name), deptname);
    outFile.close();
}
