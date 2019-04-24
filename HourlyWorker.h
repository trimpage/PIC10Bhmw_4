//HourlyWorker.h

#ifndef HOURLYWORKER
#define HOURLYWORKER
#include <string>
#include "Employee.h"

class HourlyWorker : public Employee {
public:
	//constructors
	HourlyWorker(std::string _name, std::string _email, int _rate);
	HourlyWorker(const std::string& fileName);

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
	int hours;
	double rate;
};

#endif	