//HourlyWorker.h

#ifndef HOURLYWORKER
#define HOURLYWORKER
#include <string>
#include "Employee.h"

class HourlyWorker : public Employee {
public:
	//constructors
	HourlyWorker(const std::string& _name, const std::string& _email, const int& _rate);
	HourlyWorker(std::ifstream& inputFile);

	/**
	function to set hours worked
	@param _hours: int amount of hours worked
	*/
	void set_hours(int _hours);

	/**
	override of inherited function print_pay, prints amount of payment for worker
	*/
	void print_pay() const override;

	/**
	override of inherited function save, re-writes updated employee data to text file
	*/
	void save() const override;

private:
	//variables for hours and rate
	int hours;
	double rate;
};

#endif	