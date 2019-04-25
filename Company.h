//Company.h

#ifndef COMPANY
#define COMPANY
#include "Employee.h"
#include "SalariedWorker.h"
#include "HourlyWorker.h"
#include <string>
#include <vector>

class Company {
public:
	//default constructor
	Company();



private:
	//member variable to store pointers to employees
	std::vector<std::shared_ptr<Employee>> employees;
};

#endif	
