#include "EmployeeManager.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

EmployeeManager::EmployeeManager() {
    loadEmployees();
}

void EmployeeManager::loadEmployees() {
    employees.clear();
    
    std::ifstream file(DATA_FILE, std::ios::binary);
    if (!file) {
        return; // File doesn't exist yet
    }
    
    while (file.peek() != EOF) {
        Employee emp;
        emp.loadFromFile(file);
        
        if (file.eof()) break;
        
        employees.push_back(emp);
    }
    
    file.close();
}

void EmployeeManager::saveEmployees() {
    std::ofstream file(DATA_FILE, std::ios::binary | std::ios::trunc);
    if (!file) {
        displayStatusMessage("Error opening file for writing!");
        return;
    }
    
    for (const auto& emp : employees) {
        emp.saveToFile(file);
    }
    
    file.close();
}

void EmployeeManager::addEmployee(const Employee& emp) {
    employees.push_back(emp);
    saveEmployees();
    displayStatusMessage("Employee added successfully!");
}

void EmployeeManager::modifyEmployee(const Employee& emp) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [&emp](const Employee& e) { return e.getCode() == emp.getCode(); });
        
    if (it != employees.end()) {
        *it = emp;
        saveEmployees();
        displayStatusMessage("Employee modified successfully!");
    } else {
        displayStatusMessage("Employee not found!");
    }
}

void EmployeeManager::deleteEmployee(int code) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [code](const Employee& e) { return e.getCode() == code; });
        
    if (it != employees.end()) {
        employees.erase(it);
        saveEmployees();
        displayStatusMessage("Employee deleted successfully!");
    } else {
        displayStatusMessage("Employee not found!");
    }
}

Employee EmployeeManager::getEmployeeByCode(int code) {
    auto it = std::find_if(employees.begin(), employees.end(),
        [code](const Employee& e) { return e.getCode() == code; });
        
    if (it != employees.end()) {
        return *it;
    }
    
    return Employee(); // Return empty employee if not found
}

bool EmployeeManager::employeeExists(int code) {
    return std::any_of(employees.begin(), employees.end(),
        [code](const Employee& e) { return e.getCode() == code; });
}

const std::vector<Employee>& EmployeeManager::getAllEmployees() const {
    return employees;
}

int EmployeeManager::getLastEmployeeCode() const {
    if (employees.empty()) {
        return 0;
    }
    
    return std::max_element(employees.begin(), employees.end(),
        [](const Employee& a, const Employee& b) { return a.getCode() < b.getCode(); })->getCode();
}

void EmployeeManager::displayAllEmployees() const {
    if (employees.empty()) {
        displayStatusMessage("No employees found!");
        return;
    }
    
    clearScreen();
    displayTitle("LIST OF EMPLOYEES", 2);
    displayTitle("~~~~~~~~~~~~~~~~~", 3);
    
    gotoxy(1, 5);
    std::cout << "CODE  NAME                     PHONE    DOJ         DESIGNATION    GRADE  SALARY";
    gotoxy(1, 6);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    
    int row = 7;
    
    for (const auto& emp : employees) {
        gotoxy(1, row);
        std::cout << std::setw(5) << emp.getCode();
        gotoxy(7, row);
        std::cout << std::setw(24) << std::left << emp.getName().substr(0, 24);
        gotoxy(32, row);
        std::cout << std::setw(8) << emp.getPhone();
        gotoxy(41, row);
        std::cout << emp.getDay() << "/" << emp.getMonth() << "/" << emp.getYear();
        gotoxy(53, row);
        std::cout << std::setw(15) << std::left << emp.getDesignation().substr(0, 15);
        gotoxy(69, row);
        std::cout << emp.getGrade();
        gotoxy(76, row);
        
        if (emp.getGrade() != 'E') {
            std::cout << emp.getBasicSalary();
        } else {
            std::cout << "-";
        }
        
        row++;
        
        if (row >= 22) {
            displayStatusMessage("Press any key to continue...");
            std::cin.get();
            
            clearScreen();
            displayTitle("LIST OF EMPLOYEES (Continued)", 2);
            displayTitle("~~~~~~~~~~~~~~~~~~~~~~~~~~~", 3);
            
            gotoxy(1, 5);
            std::cout << "CODE  NAME                     PHONE    DOJ         DESIGNATION    GRADE  SALARY";
            gotoxy(1, 6);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            
            row = 7;
        }
    }
    
    waitForKeyPress();
}

void EmployeeManager::generateSalaryReport() const {
    if (employees.empty()) {
        displayStatusMessage("No employees found!");
        return;
    }
    
    clearScreen();
    displayTitle("SALARY REPORT", 2);
    displayTitle("=============", 3);
    
    gotoxy(1, 5);
    std::cout << "CODE  NAME                  GRADE  BASIC SALARY  ALLOWANCES  DEDUCTIONS  NET SALARY";
    gotoxy(1, 6);
    std::cout << "=====================================================================================";
    
    int row = 7;
    float totalBasic = 0.0f, totalAllowances = 0.0f, totalDeductions = 0.0f, totalNet = 0.0f;
    
    for (const auto& emp : employees) {
        float basicSalary = emp.getBasicSalary();
        float allowances = emp.calculateTotalAllowance();
        float deductions = emp.calculateTotalDeduction();
        float netSalary = emp.calculateNetSalary();
        
        totalBasic += basicSalary;
        totalAllowances += allowances;
        totalDeductions += deductions;
        totalNet += netSalary;
        
        gotoxy(1, row);
        std::cout << std::setw(5) << emp.getCode();
        gotoxy(7, row);
        std::cout << std::setw(22) << std::left << emp.getName().substr(0, 22);
        gotoxy(30, row);
        std::cout << std::setw(5) << emp.getGrade();
        gotoxy(37, row);
        std::cout << std::setw(13) << std::fixed << std::setprecision(2) << basicSalary;
        gotoxy(51, row);
        std::cout << std::setw(11) << std::fixed << std::setprecision(2) << allowances;
        gotoxy(63, row);
        std::cout << std::setw(11) << std::fixed << std::setprecision(2) << deductions;
        gotoxy(75, row);
        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << netSalary;
        
        row++;
        
        if (row >= 22) {
            displayStatusMessage("Press any key to continue...");
            std::cin.get();
            
            clearScreen();
            displayTitle("SALARY REPORT (Continued)", 2);
            displayTitle("========================", 3);
            
            gotoxy(1, 5);
            std::cout << "CODE  NAME                  GRADE  BASIC SALARY  ALLOWANCES  DEDUCTIONS  NET SALARY";
            gotoxy(1, 6);
            std::cout << "=====================================================================================";
            
            row = 7;
        }
    }
    
    // Display totals
    gotoxy(1, row + 1);
    std::cout << "=====================================================================================";
    gotoxy(1, row + 2);
    std::cout << "TOTALS:";
    gotoxy(37, row + 2);
    std::cout << std::setw(13) << std::fixed << std::setprecision(2) << totalBasic;
    gotoxy(51, row + 2);
    std::cout << std::setw(11) << std::fixed << std::setprecision(2) << totalAllowances;
    gotoxy(63, row + 2);
    std::cout << std::setw(11) << std::fixed << std::setprecision(2) << totalDeductions;
    gotoxy(75, row + 2);
    std::cout << std::setw(10) << std::fixed << std::setprecision(2) << totalNet;
    
    waitForKeyPress();
}
