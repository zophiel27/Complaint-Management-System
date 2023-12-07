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

void start();

//Class for main system
class System{
private:
    Admin* admin;
    vector<Department*>departments;
    vector<Teacher*>teachers; 
public:
    System();//Dept initialized, hard coded teachers initialized
    void loadAdmin(Admin*);
    void readDept();
    void readTeachers();
    void printUI();
    void Login();
    void notifyteacher();
    void notifymanager();
    void generateReport();
};

enum ComplaintStatus { NEW, ASSIGNED, RESOLVED,COMPLETED, CLOSED };

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
	string assignedEmployee; // Employees assigned to the complaint
	string feedback; // Teacher's feedback
public:
    time_t dateAssigned; // Date complaint was assigned to an employee
	time_t dateResolved; // Date complaint was marked as resolved
	time_t dateClosed; // Date complaint was closed
    Complaint(string, Teacher*, Department*&);
    void assignEmployee(string);
    void printInfo();
    void printDetails();
    void shiftStatus(ComplaintStatus);
    ComplaintStatus getStatus();
    void pushTask();
    void addFeedback(string);
    void notify();
    void createReport();

};

//Department Class
class Department{
private:
    string name; //IT, accounts or admin.
    vector<Employee*> employees;
    Manager* manager;
    vector<Complaint*> tasks;
    vector<Complaint*> assignedtasks;
    vector<Complaint*> resolvedtasks;
    vector<Complaint*> completedtasks;

public:
    Department(string);
    Department(string, vector<Employee*>, Manager*);
    void addTask(Complaint *&task);
    string getName();
    void readStaff();
    void updateTaskList();
    void notifyteacher();
    void pushTask();
    void completeTask();
    void printStaff();
    void createReport();
    void login(int, string,bool &logged);
};

// Employee Class
class Employee //:public Person
{
private:
    int id;
	string name; // Employee name
    vector<Complaint*> tasks;
    
public:
    Employee(int,string);
    Employee(int,string, vector<Complaint*>);
    int getID();
    string getName();
    void receiveTask(Complaint*&);
    void checkTasks(ComplaintStatus);
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
    int id;
	string name; // manager name
    vector<Employee*> employees;
    vector<Complaint*> tasks;
public:
    Manager(int,string);
    Manager(int,string, vector<Employee*>);
    void getEmployees(vector<Employee*>);
    int getID();
    string getName();
    void reviewTask();
    void getTask(Complaint* &task);
    void checkTasks(ComplaintStatus);
    void assignTask();
    void checkComplainProgress();
    void notifySystem();
    void print();
    void managerUI();
    void printUI();
    int getIndex(int);
};

// Teacher Class
class Teacher //:public Person 
{
private:
	int id; // Teacher ID
	string name; // Teacher name
    string notifications;
    vector<Complaint*> complain;
    vector<Department*> departments;
public:
    Teacher(vector<Department*> departments, int, string);
    void fileComplaint(); //if there is any problem, or if any service/equipment is required, teacher shall forward her request to a particular supporting department such as IT, accounts or admin.
    void printUI();
    void teacherUI();
    void checkComplainProgress();
    void checkNotifications();
    void printNotifications();
    void clearNotifications();
    void recordFeedback();
    void setNoti();
    void printComplains();
    void print();//Print info
    int getID();
    void pushTask();
    string getName();
};

//Admin Class, can be singelton
class Admin{
private:
	int id; // Admin ID
	string name; // Admin name
    System *sys;
public:
    Admin(int, string,System *);
    void addEmployee();
    void addManager();
    void addTeacher();
    void removeTeacher();
    int getID();
    string getName();
    void printUI();
    void adminUI();
};
