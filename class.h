#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

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
    vector<Department>*departments; 
public:
    System(Department *dpt[],int size);
    void notifyteacher();
    void notifymanager();
    void generateReport();
};

enum ComplaintStatus { NEW, ASSIGNED, RESOLVED, CLOSED };
// Complaint Class
class Complaint {
private:
	static int id; // Complaint ID
	string description; // Complaint description
	Teacher *teacher; // Teacher who filed the complaint
	Department *department; // Department assigned to
	ComplaintStatus status; // Complaint status (new, assigned, resolved or closed. The teacher or manager can view its status any time)
	time_t datefiled; // Date complaint was filed
	time_t dateAssigned; // Date complaint was assigned to an employee
	time_t dateResolved; // Date complaint was marked as resolved
	time_t dateClosed; // Date complaint was closed
	//vector<string> assignedEmployees; // Employees assigned to the complaint
	string feedback; // Teacher's feedback
public:
    Complaint(string ,Teacher *, Department * );

};

//Department Class
class Department{
private:
    string name; //IT, accounts or admin.
    vector<Employee *> employees;
    Manager* manager;
    vector<Complaint *> tasks;
    vector<Complaint *> assignedtasks;
    vector<Complaint *> completedtasks;
public:
    Department(string);
    Department(string ,vector<Employee *> ,Manager*);
    void addTask(Complaint *task);
    void pushforReview();
    void notifyteacher();
    void assignTask();
    void completeTask();


};

// Employee Class
class Employee {
private:
    int id; // Employee ID
	string name; // Employee name
    vector<string> tasks;
    
public:
    Employee(int,string,vector<string>);
    void checkTasks();
    void completeTask();
    void updateSystem();
};

//Manager class
class Manager
{
private:
    int id;
	string name; // manager name
    vector<Employee *> employees;
    public:
    Manager(int,string ,vector<Employee *>);
    void reviewTask();
    void reviewRequest();
    void assignTask();
    void checkComplainProgress();
    void notifySystem();
};

// Teacher Class
class Teacher {
private:
	int id; // Teacher ID
	string name; // Teacher name
    vector<string> notifications;
    Complaint *complain;
    vector<Department*> departments;
public:
    Teacher(Department *dpt[],int size,int,string);
    void fileComplaint();//if there is any problem, or if any service/equipment is required, teacher shall forward her request to a particular supporting department such as IT, accounts or admin.
    void checkComplainProgress();
    void checkNotifications();
    void printNotifications();
    void clearNotifications();
    void recordFeedback();
};

//Admin Class, can be singelton
class Admin{
private:
	int id; // Admin ID
	string name; // Admin name
public:
    Admin(int,string);
    void addEmployee();
    void addManager();
    void addTeacher();
    void removeEmployee();
    void removeManager();
    void removeTeacher();
};
