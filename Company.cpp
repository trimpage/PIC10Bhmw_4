//Company.cpp

#include "Company.h"
#include "Employee.h"
#include "HourlyWorker.h"
#include "SalariedWorker.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//FREE FUNCTION DEFINITIONS
//find next id function
int find_next_id() {
	//next id variable to return
	int _next_id = 0;

	//for loop to iterate through employee files
	for (size_t i = 0; i < SIZE_MAX; ++i) {
		//construct file name for each id
		std::string fileName = "employee";
		fileName += std::to_string(i);
		fileName += ".txt";

		//create ifstream and attempt to open file
		std::ifstream file;
		file.open(fileName);

		//if fails to open, return next id
		if (file.fail()) {
			_next_id = static_cast<int>(i);
			break;
		}
		//else, close and continue
		else {
			file.close();
			continue;
		}
	}
	return _next_id;
}

//run events function
void run_events() {
	//response variable
	char response = 'C';

	//create company object
	Company company = Company();

	//while response is valid, run loop
	while ((response == 'C') || (response == 'D') || (response == 'H') || (response == 'P')) {
		//ask user what to do and get input
		std::cout << "What would you like to do?\n"
			<< "C - Create Employee\n"
			<< "D - Display Current Directory\n"
			<< "H - Set Hours\n"
			<< "P - Print Payroll\n"
			<< "Quit (all other inputs)? ";
		std::cin >> response;
		std::cout << '\n';

		//if response is C
		if (response == 'C') {
			//call create employee
			company.create_employee();
		}
		//else if D
		else if (response == 'D') {
			//call print directory
			company.print_directory();
		}
		//else if H
		else if (response == 'H') {
			//call do hours
			company.do_hours();
		}
		//else if P
		else if (response == 'P') {
			//call print payroll
			company.print_payroll();
		}
		//otherwise abort
		else {
			break;
		}
	}
}

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

				//close file
				inputFile.close();
			}
			//else, if hourly type
			else if (employeeType == "hourly") {
				//create hourly employee
				HourlyWorker employee = HourlyWorker(inputFile);

				//create pointer to employee and push back to employees vector
				auto employeePointer = std::make_shared<HourlyWorker>(employee);
				employees.push_back(employeePointer);

				//close file
				inputFile.close();
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
		//else continue
		else {
			continue;
		}
	}
}

//company print payroll function
void Company::print_payroll() {
	//for loop to iterate through employee vector
	for (size_t i = 0; i < employees.size(); ++i) {
		employees[i]->print_pay();
	}
	//newline
	std::cout << '\n';
}

//company create salaried worker function
void Company::create_salaried() {
	//prompt user for name and get input
	std::string name;
	std::cout << "Enter name: ";
	getline(std::cin, name);

	//prompt user for email and get input
	std::string email;
	std::cout << "Enter email: ";
	getline(std::cin, email);

	//prompt user for salary and get input
	int salary;
	std::cout << "Enter salary: $";
	std::cin >> salary;
	std::cout << '\n';
	
	//create worker with inputted values and push back to employees
	SalariedWorker employee = SalariedWorker(name, email, salary);
	employee.save();
	auto employeePointer = std::make_shared<SalariedWorker>(employee);
	employees.push_back(employeePointer);
}

//company create hourly worker function
void Company::create_hourly() {
	//prompt user for name and get input
	std::string name;
	std::cout << "Enter name: ";
	getline(std::cin, name);

	//prompt user for email and get input
	std::string email;
	std::cout << "Enter email: ";
	getline(std::cin, email);

	//prompt user for salary and get input
	int rate;
	std::cout << "Enter hourly rate: $";
	std::cin >> rate;
	std::cout << '\n';

	//create worker with inputted values and push back to employees
	HourlyWorker employee = HourlyWorker(name, email, rate);
	employee.save();
	auto employeePointer = std::make_shared<HourlyWorker>(employee);
	employees.push_back(employeePointer);
}

//company create employee function
void Company::create_employee() {
	//ask user what kind of employee to make
	char response;
	std::cout << "What type of employee?\n S - Salaried\n H - Hourly\n Abort (all other inputs)? ";
	std::cin >> response;

	//ignore response from buffer and create new line
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << '\n';

	//if response is S, create salaried employee
	if (response == 'S') {
		create_salaried();
	}
	//else if H, create hourly employee
	else if (response == 'H') {
		create_hourly();
	}
	//else abort
	else {
		std::cout << "Creation aborted.\n\n";
		return;
	}
}

//EMPLOYEE CLASS DEFINITIONS
//set next id
int Employee::next_id = find_next_id();

//define first employee constructor
Employee::Employee(std::string _name, std::string _email) : name(std::move(_name)), email(std::move(_email)), id(next_id) {
	//increment next id
	++next_id;
}

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
const std::string& Employee::get_name() const {
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

//employee get email function
const std::string& Employee::get_email() const {
	return email;
}

//employee get id function
const int& Employee::get_id() const {
	return id;
}

//employee set next id function
void Employee::set_next_id(const int& _id) {
	next_id = _id;
}

//HOURLYWORKER CLASS DEFINITIONS
//define first hourly worker constructor
HourlyWorker::HourlyWorker(std::string _name, std::string _email, const int& _rate) 
	: Employee(std::move(_name), std::move(_email)), rate(_rate), hours(0) {}

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
	std::string email;
	std::string id;
	ss >> employeeType >> firstName >> lastName >> email >> id >> hours >> rate;

	//close file
	inputFile.close();
}

//hourly worker set hours function
void HourlyWorker::set_hours(int _hours) {
	hours = _hours;
}

//hourly worker print pay override
void HourlyWorker::print_pay() const {
	int amount = rate * hours;
	std::cout << get_name() << " receives $" << amount << '\n';
}

//hourly worker save override
void HourlyWorker::save() const {
	//construct file name using employee id
	int _id = get_id();
	std::string fileName = "employee";
	fileName += std::to_string(_id);
	fileName += ".txt";

	//create file and output employee data to it
	std::ofstream outputFile;
	outputFile.open(fileName);
	outputFile << "hourly\t" << get_name() << '\t' << get_email() << '\t' << _id << '\t'
		<< hours << '\t' << rate;

	//close file
	outputFile.close();
}

//SALARIEDWORKER CLASS DEFINITIONS
//define first hourly worker constructor
SalariedWorker::SalariedWorker(std::string _name, std::string _email, const int& _salary) 
	: Employee(std::move(_name), std::move(_email)), salary(_salary) {}

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
	std::string email;
	std::string id;
	ss >> employeeType >> firstName >> lastName >> email >> id >> salary;

	//close file
	inputFile.close();
}

//salaried worker print pay override
void SalariedWorker::print_pay() const {
	std::cout << get_name() << " receives $" << salary << '\n';
}

//salaried worker save override
void SalariedWorker::save() const {
	//construct file name using employee id
	int _id = get_id();
	std::string fileName = "employee";
	fileName += std::to_string(_id);
	fileName += ".txt";

	//create file and output employee data to it
	std::ofstream outputFile;
	outputFile.open(fileName);
	outputFile << "salaried\t" << get_name() << '\t' << get_email() << '\t' << _id << '\t' << salary;

	//close file
	outputFile.close();
}