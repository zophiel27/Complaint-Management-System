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
    Complaint(string, Teacher*, Department*);
    void assignedEmployee(vector<Employee*> assignedEmployees);
    void printInfo();

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
    void updateTaskList();//
    void pushforReview();
    void notifyteacher();
    void assignTask();
    void completeTask();
    void print();

};

// Employee Class
class Employee {
private:
    static int empID; // Employee ID
    int id;
	string name; // Employee name
    vector<string> tasks;
    
public:
    Employee(string);
    Employee(string, vector<string>);
    int getID();
    string getName();
    void checkTasks();
    int completeTask();
    void updateSystem();
    void print();
};

//Manager class
class Manager
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
    void reviewTask();
    void reviewRequest();
    int assignTask();
    void checkComplainProgress();
    void notifySystem();
    void print();
};

// Teacher Class
class Teacher {
private:
	int id; // Teacher ID
	string name; // Teacher name
    vector<string> notifications;
    vector<Complaint*> complain;
    vector<Department*> departments;
    int no;
public:
    Teacher(Department* dpt[], int size, int, string);
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
