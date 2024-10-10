## Employee Payroll System
This is a simple Employee Payroll System written in C, designed to manage employee details, calculate salaries including allowances and deductions, generate pay slips, and save data to a file. The system allows users to add new employees, generate pay slips for individual employees, display all employees, and save employee data to a file for persistence.

# Features
Add employee details (ID, name, base salary, allowances, deductions).
Calculate net salary (Base Salary + Allowances - Deductions).
Generate and display a pay slip for a specific employee.
Display details of all employees.
Save employee data to a file and load data from the file.
# File Structure
main.c: The main program file that contains all functionalities of the Employee Payroll System.
empdata.dat: A binary file used for storing employee records persistently.

# Usage
Adding Employees: You can add up to 100 employees.
Generating Pay Slip: Enter the employee ID to generate and view the pay slip.
Displaying All Employees: View the details of all employees.
Saving and Loading Data: Employee data is automatically loaded from the file on program start and saved on exit.
# Compilation
To compile the program, use the following command:

bash
Copy code
gcc main.c -o payroll
# How to Run
After compiling, run the program:

bash
Copy code
./payroll
# Functions
addEmp(): Adds a new employee to the system.
calcSal(): Calculates the net salary of an employee.
genPaySlip(): Generates a pay slip for a specific employee.
dispEmps(): Displays all employee details.
saveEmpsToFile(): Saves employee data to a binary file.
loadEmpsFromFile(): Loads employee data from the binary file.
# License
This project is for educational purposes and does not have any specific license.

