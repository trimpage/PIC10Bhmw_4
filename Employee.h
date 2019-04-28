//Employee.h

#ifndef EMPLOYEE
#define EMPLOYEE
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Employee {
public:
	//constructors
	Employee(const std::string& _name, const std::string& _email);
	Employee(std::ifstream& inputFile);

	/**
	prints employee data
	*/
	void print() const;

	/**
	function to get name of employee
	@return: returns employee name
	*/
	std::string get_name() const;

	/**
	writes employee data to a file named after their ID
	*/
	virtual void write_data() const;

	/**
	pure virtual function, will be used in derived classes to print wage/salary information
	*/
	virtual void print_pay() const = 0;

	/**
	pure virtual function, will be used in derived classes to update employee file with new data
	*/
	virtual void save() const = 0;

protected:
	std::string name;
	std::string email;
	int id;
	static int next_id;
};

#endif