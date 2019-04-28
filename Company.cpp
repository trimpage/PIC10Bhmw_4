//Company.cpp

#include "Company.h"
#include "Employee.h"
#include "HourlyWorker.h"
#include "SalariedWorker.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//COMPANY CLASS DEFINITIONS
//define company default constructor
Company::Company() {
	size_t i = 0;
	while (i < SIZE_MAX) {
		//create file name for individual employees
		std::ifstream inputFile;
		std::string fileName = "employee" + std::to_string(static_cast<int>(i)) + ".txt";

		//open file
		inputFile.open(fileName);

		//exit if unable to
		if (inputFile.fail()) {
			break;
		}
		//otherwise, continue by getting employee type from file stream
		else {
			std::string employeeType;
			inputFile >> employeeType;

			//if salaried type
			if (employeeType == "salaried") {
				//create salaried employee
				SalariedWorker employee = SalariedWorker(inputFile);

				//create pointer to employee and push back to employees vector
				auto employeePointer = std::make_shared<SalariedWorker>(employee);
				employees.push_back(employeePointer);
			}
			//else, if hourly type
			else if (employeeType == "hourly") {
				//create hourly employee
				HourlyWorker employee = HourlyWorker(inputFile);

				//create pointer to employee and push back to employees vector
				auto employeePointer = std::make_shared<HourlyWorker>(employee);
				employees.push_back(employeePointer);
			}
			//increment i for while loop
			++i;
		}
	}
}

//company print directory function
void Company::print_directory() const {
	//display number of employees
	std::cout << "There are " << employees.size() << " employees:\n";

	//for loop to display all employee data
	for (size_t i = 0; i < employees.size(); ++i) {
		employees[i]->print();
	}

	//newline
	std::cout << '\n';
}

//company do hours function
void Company::do_hours() {
	//for loop to go through the vector
	for (size_t i = 0; i < employees.size(); ++i) {
		//try dynamic cast for hourly worker
		auto hwPointer = std::dynamic_pointer_cast<HourlyWorker>(employees[i]);

		//if correctly casted to hourly worker
		if (hwPointer) {
			//prompt user for hours worked
			std::cout << "How many hours did " << hwPointer->get_name() << " work? ";

			//get hours from user
			int hours;
			std::cin >> hours;
			std::cout << '\n';

			//set hours to inputted hours
			hwPointer->set_hours(hours);

			//save to employee file
			hwPointer->save();

		}
		else {
			//do nothing
		}
	}
}











//EMPLOYEE CLASS DEFINITIONS
//define first employee constructor
Employee::Employee(const std::string& _name, const std::string& _email) : name(_name), email(_email) {}

//define second employee constructor 
Employee::Employee(std::ifstream& inputFile) {
	//line variable to be read
	std::string line;

	//grab line string while not at end of file
	while (!inputFile.eof()) {
		std::getline(inputFile, line);
	}

	//create and use stream to parse line data
	std::stringstream ss(line);
	std::string firstName;
	std::string lastName;
	ss >> firstName >> lastName >> email >> id;
	name = firstName + ' ' + lastName;
}

//employee print function
void Employee::print() const {
	std::cout << name << '\t' << id << '\t' << email << '\n';
}

//employee get name function
std::string Employee::get_name() const {
	return name;
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
HourlyWorker::HourlyWorker(const std::string& _name, const std::string& _email, const int& _rate) 
	: Employee(_name, _email), rate(_rate), hours(0) {}

//define second hourly worker constructor
HourlyWorker::HourlyWorker(std::ifstream& inputFile) : Employee(inputFile) {
	//line variable to be read
	std::string line;

	//clear and reset ifstream 
	inputFile.clear();
	inputFile.seekg(0);

	//while not at end of file
	while (!inputFile.eof()) {
		//grab string from file
		std::getline(inputFile, line);
	}
	
	//create and use stream to parse line data
	std::stringstream ss(line);
	std::string employeeType;
	std::string firstName;
	std::string lastName;
	ss >> employeeType >> firstName >> lastName >> email >> id >> hours >> rate;
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

//hourly worker save override
void HourlyWorker::save() const {
	//construct file name using employee id
	std::string fileName = "employee";
	fileName += std::to_string(id);
	fileName += ".txt";

	//create file and output employee data to it
	std::ofstream outputFile;
	outputFile.open(fileName);
	outputFile << "hourly\t" << name << '\t' << email << '\t' << id << '\t'
		<< hours << '\t' << rate;
}

//SALARIEDWORKER CLASS DEFINITIONS
//define first hourly worker constructor
SalariedWorker::SalariedWorker(const std::string& _name, const std::string& _email, const int& _salary) 
	: Employee(_name, _email), salary(_salary) {}

//define second hourly worker constructor
SalariedWorker::SalariedWorker(std::ifstream& inputFile) : Employee(inputFile) {
	//line variable to be read
	std::string line;

	//clear and reset ifstream 
	inputFile.clear();
	inputFile.seekg(0);

	//while not at end of file
	while (!inputFile.eof()) {
		//grab string from file
		std::getline(inputFile, line);
	}

	//create and use stream to parse line data
	std::stringstream ss(line);
	std::string employeeType;
	std::string firstName;
	std::string lastName;
	ss >> employeeType >> firstName >> lastName >> email >> id >> salary;
}

//salaried worker print pay override
void SalariedWorker::print_pay() const {
	std::cout << name << " receives $" << salary << '\n';
}

//salaried worker save override
void SalariedWorker::save() const {
	//construct file name using employee id
	std::string fileName = "employee";
	fileName += std::to_string(id);
	fileName += ".txt";

	//create file and output employee data to it
	std::ofstream outputFile;
	outputFile.open(fileName);
	outputFile << "salaried\t" << name << '\t' << email << 't' << id << '\t' << salary;
}