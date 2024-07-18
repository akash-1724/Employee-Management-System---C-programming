#include <stdio.h>
#include <string.h>

#define MAX_EMP 100
#define EMP_FILE "empdata.dat"

typedef struct {
    int id;
    char name[50];
    float base_sal;
    float allow;
    float deduct;
    float net_sal;
} Emp;

void addEmp(Emp emps[], int *num_emp);
void calcSal(Emp *emp);
void genPaySlip(Emp emp);
void dispEmps(Emp emps[], int num_emp);
void saveEmpsToFile(Emp emps[], int num_emp);
int loadEmpsFromFile(Emp emps[]);

void addEmp(Emp emps[], int *num_emp) {
    if (*num_emp >= MAX_EMP) {
        printf("Max number of employees reached.\n");
        return;
    }

    Emp new_emp;
    printf("Enter employee ID: ");
    if (scanf("%d", &new_emp.id) != 1) {
        printf("Invalid input for employee ID.\n");
        while (getchar() != '\n'); 
        return;
    }

    printf("Enter employee name: ");
    if (scanf("%s", new_emp.name) != 1) {
        printf("Invalid input for employee name.\n");
        while (getchar() != '\n'); 
        return;
    }

    printf("Enter base salary: ");
    if (scanf("%f", &new_emp.base_sal) != 1) {
        printf("Invalid input for base salary.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    printf("Enter allowances: ");
    if (scanf("%f", &new_emp.allow) != 1) {
        printf("Invalid input for allowances.\n");
        while (getchar() != '\n'); 
        return;
    }

    printf("Enter deductions: ");
    if (scanf("%f", &new_emp.deduct) != 1) {
        printf("Invalid input for deductions.\n");
        while (getchar() != '\n');
        return;
    }

    calcSal(&new_emp);
    emps[*num_emp] = new_emp;
    (*num_emp)++;
}

void calcSal(Emp *emp) {
    emp->net_sal = emp->base_sal + emp->allow - emp->deduct;
}

void genPaySlip(Emp emp) {
    printf("\nPay Slip for Employee ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Base Salary: %.2f\n", emp.base_sal);
    printf("Allowances: %.2f\n", emp.allow);
    printf("Deductions: %.2f\n", emp.deduct);
    printf("Net Salary: %.2f\n", emp.net_sal);
    printf("----------------------------\n");
}

void dispEmps(Emp emps[], int num_emp) {
    for (int i = 0; i < num_emp; i++) {
        printf("Employee ID: %d\n", emps[i].id);
        printf("Name: %s\n", emps[i].name);
        printf("Base Salary: %.2f\n", emps[i].base_sal);
        printf("Allowances: %.2f\n", emps[i].allow);
        printf("Deductions: %.2f\n", emps[i].deduct);
        printf("Net Salary: %.2f\n", emps[i].net_sal);
        printf("----------------------------\n");
    }
}

void saveEmpsToFile(Emp emps[], int num_emp) {
    FILE *file = fopen(EMP_FILE, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&num_emp, sizeof(int), 1, file);
    fwrite(emps, sizeof(Emp), num_emp, file);

    fclose(file);
}

int loadEmpsFromFile(Emp emps[]) {
    FILE *file = fopen(EMP_FILE, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 0;
    }

    int num_emp;
    fread(&num_emp, sizeof(int), 1, file);
    fread(emps, sizeof(Emp), num_emp, file);

    fclose(file);
    return num_emp;
}

int main() {
    Emp emps[MAX_EMP];
    int num_emp = loadEmpsFromFile(emps);
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
                addEmp(emps, &num_emp);
                break;
            case 2: {
                int emp_id;
                printf("Enter employee ID for pay slip: ");
                scanf("%d", &emp_id);
                int found = 0;
                for (int i = 0; i < num_emp; i++) {
                    if (emps[i].id == emp_id) {
                        genPaySlip(emps[i]);
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
                dispEmps(emps, num_emp);
                break;
            case 4:
                saveEmpsToFile(emps, num_emp);
                printf("Employee data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
