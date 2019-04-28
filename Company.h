//Company.h

#ifndef COMPANY
#define COMPANY
#include "Employee.h"
#include "SalariedWorker.h"
#include "HourlyWorker.h"
#include <string>
#include <vector>
#include <memory>

class Company {
public:
	//default constructor
	Company();

	/**
	print directory function that displays number of employees and prints their data
	*/
	void print_directory() const;

	/**
	do hours function that goes through vector and prompts user to enter hours for hourly workers, then saves to their file
	*/
	void do_hours();

	/**
	print payroll function to print pay for all workers
	*/
	void print_payroll();

	/**
	create salaried worker function
	*/
	void create_salaried();

	/**
	create hourly worker function
	*/
	void create_hourly();

	/**
	creeate employee function
	*/
	void create_employee();

private:
	//member variable to store pointers to employees
	std::vector<std::shared_ptr<Employee>> employees;
};

#endif	
