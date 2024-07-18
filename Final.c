#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define EMPLOYEE_DATA_FILE "employees.dat"

typedef struct {
    int id;
    char name[50];
    float base_salary;
    float allowances;
    float deductions;
    float net_salary;
} Employee;

void addEmployee(Employee employees[], int *num_employees);
void calculateSalary(Employee *employee);
void generatePaySlip(Employee employee);
void displayEmployees(Employee employees[], int num_employees);
void saveEmployeesToFile(Employee employees[], int num_employees);
int loadEmployeesFromFile(Employee employees[]);

void addEmployee(Employee employees[], int *num_employees) {
    if (*num_employees >= MAX_EMPLOYEES) {
        printf("Maximum number of employees reached.\n");
        return;
    }

    Employee new_employee;
    printf("Enter employee ID: ");
    if (scanf("%d", &new_employee.id) != 1) {
        printf("Invalid input for employee ID.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    printf("Enter employee name: ");
    if (scanf("%s", new_employee.name) != 1) {
        printf("Invalid input for employee name.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    printf("Enter base salary: ");
    if (scanf("%f", &new_employee.base_salary) != 1) {
        printf("Invalid input for base salary.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    printf("Enter allowances: ");
    if (scanf("%f", &new_employee.allowances) != 1) {
        printf("Invalid input for allowances.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    printf("Enter deductions: ");
    if (scanf("%f", &new_employee.deductions) != 1) {
        printf("Invalid input for deductions.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    calculateSalary(&new_employee);
    employees[*num_employees] = new_employee;
    (*num_employees)++;
}

void calculateSalary(Employee *employee) {
    employee->net_salary = employee->base_salary + employee->allowances - employee->deductions;
}

void generatePaySlip(Employee employee) {
    printf("\nPay Slip for Employee ID: %d\n", employee.id);
    printf("Name: %s\n", employee.name);
    printf("Base Salary: %.2f\n", employee.base_salary);
    printf("Allowances: %.2f\n", employee.allowances);
    printf("Deductions: %.2f\n", employee.deductions);
    printf("Net Salary: %.2f\n", employee.net_salary);
    printf("----------------------------\n");
}

void displayEmployees(Employee employees[], int num_employees) {
    for (int i = 0; i < num_employees; i++) {
        printf("Employee ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Base Salary: %.2f\n", employees[i].base_salary);
        printf("Allowances: %.2f\n", employees[i].allowances);
        printf("Deductions: %.2f\n", employees[i].deductions);
        printf("Net Salary: %.2f\n", employees[i].net_salary);
        printf("----------------------------\n");
    }
}

void saveEmployeesToFile(Employee employees[], int num_employees) {
    FILE *file = fopen(EMPLOYEE_DATA_FILE, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&num_employees, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), num_employees, file);

    fclose(file);
}

int loadEmployeesFromFile(Employee employees[]) {
    FILE *file = fopen(EMPLOYEE_DATA_FILE, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 0;
    }

    int num_employees;
    fread(&num_employees, sizeof(int), 1, file);
    fread(employees, sizeof(Employee), num_employees, file);

    fclose(file);
    return num_employees;
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int num_employees = loadEmployeesFromFile(employees);
    int choice;

    while (1) {
        printf("\nEmployee Payroll System\n");
        printf("1. Add Employee\n");
        printf("2. Generate Pay Slip\n");
        printf("3. Display All Employees\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &num_employees);
                break;
            case 2: {
                int emp_id;
                printf("Enter employee ID for pay slip: ");
                scanf("%d", &emp_id);
                int found = 0;
                for (int i = 0; i < num_employees; i++) {
                    if (employees[i].id == emp_id) {
                        generatePaySlip(employees[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Employee not found.\n");
                }
                break;
            }
            case 3:
                displayEmployees(employees, num_employees);
                break;
            case 4:
                saveEmployeesToFile(employees, num_employees);
                printf("Employee data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
