//Company.cpp

#include "Company.h"
#include "Employee.h"
#include "HourlyWorker.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//EMPLOYEE CLASS DEFINITIONS
//define first employee constructor
Employee::Employee(std::string _name, std::string _email) : name(_name), email(_email) {}

//define second employee constructor
Employee::Employee(const std::string& fileName) {
	//create file object and open it
	std::ifstream inputFile;
	inputFile.open(fileName);

	//if file is unable to be opened, let user know, otherwise continue to parse data
	if (inputFile.fail()) {
		std::cout << "File was unable to be opened.\n";
	}
	else {
		//line variable to be read
		std::string line;

		//grab line string while not at end of file
		while (!inputFile.eof()) {
			getline(inputFile, line);
		}

		//create and use stream to parse line data, store first string as employee type
		std::stringstream ss(line);
		std::string employeeType;
		std::string firstName;
		std::string lastName;
		ss >> employeeType >> firstName >> lastName >> email >> id;
		name = firstName + ' ' + lastName;
	}
}

//employee print function
void Employee::print() const {
	std::cout << name << '\t' << id << '\t' << email << '\n';
}

//employee write data function
void Employee::write_data() const {
	//construct file name using employee id
	std::string fileName = "employee";
	fileName += std::to_string(id);
	fileName += ".txt";

	//create file and output employee data to it
	std::ofstream outputFile;
	outputFile.open(fileName);
	outputFile << name << '\t' << email << 't' << id << '\n';
}

//HOURLYWORKER CLASS DEFINITIONS
//define first hourly worker constructor
HourlyWorker::HourlyWorker(std::string _name, std::string _email, int _rate) : Employee(_name, _email), rate(_rate), hours(0) {}

//define second hourly worker constructor
HourlyWorker::HourlyWorker(const std::string& fileName) {
	//create file object and open it
	std::ifstream inputFile;
	inputFile.open(fileName);

	//if file is unable to be opened, let user know, otherwise continue to parse data
	if (inputFile.fail()) {
		std::cout << "File was unable to be opened.\n";
	}
	else {
		//line variable to be read
		std::string line;

		//grab line string while not at end of file
		while (!inputFile.eof()) {
			getline(inputFile, line);
		}

		//create and use stream to parse line data, store first string as employee type
		std::stringstream ss(line);
		std::string employeeType;
		std::string firstName;
		std::string lastName;
		ss >> employeeType >> firstName >> lastName >> email >> id >> hours >> rate;
		name = firstName + ' ' + lastName;
	}
}

//hourly worker set hours function
void HourlyWorker::set_hours(int _hours) {
	hours = _hours;
}

//hourly worker print pay override
void HourlyWorker::print_pay() const {
	int amount = rate * hours;
	std::cout << name << " receives $" << amount << '\n';
}
