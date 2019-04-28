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
	Employee(std::string _name, std::string _email);
	Employee(std::ifstream& inputFile);

	/**
	prints employee data
	*/
	void print() const;

	/**
	function to get name of employee
	@return: returns employee name
	*/
	const std::string& get_name() const;

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

	//virtual destructor
	virtual ~Employee() = default;

	//re-enable move and copy constructors and assignments
	Employee(Employee&&) noexcept = default;
	Employee& operator = (Employee&&) noexcept = default;
	Employee(const Employee&) = default;
	Employee& operator = (const Employee&) = default;

protected:
	/**
	function to get email of employee
	@return: returns employee email
	*/
	const std::string& get_email() const;

	/**
	function to get id of employee
	@return: returns employee id
	*/
	const int& get_id() const;

	/**
	function to set next id
	@param _id: id to be set
	*/
	static void set_next_id(const int& _id);

private:
	std::string name;
	std::string email;
	int id;
	static int next_id;
};

#endif