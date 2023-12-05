#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <conio.h>
using namespace std;
class System;
class Complaint;
class Department;
class Manager;
class Employee;
class Teacher;
class Admin;

//Class for main system
class System{
private:
    vector<Department*>departments;
    vector<Teacher*>teachers; 
public:
    System();//Dept initialized, hard coded teachers initialized
    void printUI();
    void Login();
    void notifyteacher();
    void notifymanager();
    void generateReport();
};

class Person
{
//public:
//    int getID()=0;
//    string getName()=0;
};
enum ComplaintStatus { NEW, ASSIGNED, RESOLVED, CLOSED };

// Complaint Class
class Complaint {
private:
	static int cID; // Complaint ID
    int id;
	string description; // Complaint description
    Teacher* teacher; // Teacher who filed the complaint
    Department* department; // Department assigned to
	ComplaintStatus status; // Complaint status (new, assigned, resolved or closed. The teacher or manager can view its status any time)
	time_t datefiled; // Date complaint was filed
	time_t dateAssigned; // Date complaint was assigned to an employee
	time_t dateResolved; // Date complaint was marked as resolved
	time_t dateClosed; // Date complaint was closed
	vector<Employee*> assignedEmployees; // Employees assigned to the complaint
	string feedback; // Teacher's feedback
public:
    Complaint(string, Teacher*, Department*&);
    void assignedEmployee(vector<Employee*> assignedEmployees);
    void printInfo();
    void temp();

};

//Department Class
class Department{
private:
    string name; //IT, accounts or admin.
    vector<Employee*> employees;
    Manager* manager;
    vector<Complaint*> tasks;
    vector<Complaint*> assignedtasks;
    vector<Complaint*> completedtasks;
public:
    Department(string);
    Department(string, vector<Employee*>, Manager*);
    void addTask(Complaint *task);
    void addManager();
    void addEmployees();
    void updateTaskList();
    void pushforReview();
    void notifyteacher();
    void assignTask();
    void completeTask();
    void print();
    void login(int, string,bool &logged);

};

// Employee Class
class Employee //:public Person
{
private:
    static int empID; // Employee ID
    int id;
	string name; // Employee name
    vector<Complaint*> tasks;
    
public:
    Employee(string);
    Employee(string, vector<Complaint*>);
    int getID();
    string getName();
    void receiveTask(Complaint*);
    void checkTasks();
    void completeTask();
    void updateSystem();
    void print();
    void employeesUI();
    void printUI();
};

//Manager class
class Manager //:public Person
{
private:
    static int mgrID;
    int id;
	string name; // manager name
    vector<Employee*> employees;
    vector<Complaint*> tasks;
    vector<Complaint*> assignedtasks;
    vector<Complaint*> completedtasks;
public:
    Manager(string);
    Manager(string, vector<Employee*>);
    int getID();
    string getName();
    void reviewTask();
    void reviewRequest();
    void getTask(Complaint* task);
    void checkTasks();
    void assignTask();
    void checkComplainProgress();
    void notifySystem();
    void print();
    void managerUI();
    void printUI();
};

// Teacher Class
class Teacher //:public Person 
{
private:
	int id; // Teacher ID
	string name; // Teacher name
    vector<string> notifications;
    vector<Complaint*> complain;
    vector<Department*> departments;
    int no;
public:
    Teacher(vector<Department*> departments, int size, int, string);
    void fileComplaint(); //if there is any problem, or if any service/equipment is required, teacher shall forward her request to a particular supporting department such as IT, accounts or admin.
    void printUI();
    void teacherUI();
    void checkComplainProgress();
    void checkNotifications();
    void printNotifications();
    void clearNotifications();
    void recordFeedback();
    void printComplains();
    void print();//Print info
    int getID();
    void temp();
    string getName();
};

//Admin Class, can be singelton
class Admin{
private:
	int id; // Admin ID
	string name; // Admin name
public:
    Admin(int, string);
    void addEmployee();
    void addManager();
    void addTeacher();
    void removeEmployee();
    void removeManager();
    void removeTeacher();
};
