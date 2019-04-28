//SalariedWorker.h

#ifndef SALARIEDWORKER
#define SALARIEDWORKER
#include <string>
#include "Employee.h"

class SalariedWorker final : public Employee {
public:
	//constructors
	SalariedWorker(std::string _name, std::string _email, const int& _salary);
	SalariedWorker(std::ifstream& inputFile);

	/**
	override of inherited function print_pay, prints salary of worker
	*/
	void print_pay() const final;

	/**
	override of inherited function save, re-writes updated employee data to text file
	*/
	void save() const final;

private:
	//variable for worker salary 
	int salary;
};
#endif	