//main.cpp

#include "Employee.h"
#include "Company.h"
#include<iostream>
#include<string>

int main() {
	Employee employee0 = Employee("arian owji", "arianowji67@gmail.com");
	employee0.print();

	std::cin.get();
	
	return 0;
}