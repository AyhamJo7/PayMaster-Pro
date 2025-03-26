#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <limits>
#define NOMINMAX
#include <Windows.h>

// Position cursor at specific coordinates
void gotoxy(int x, int y) {
    COORD c = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Clear the screen
void clearScreen() {
    system("cls");
}

// Draw a box on the screen
void drawBox(int x1, int y1, int x2, int y2, char c) {
    // Draw corners
    gotoxy(x1, y1); std::cout << c;
    gotoxy(x2, y1); std::cout << c;
    gotoxy(x1, y2); std::cout << c;
    gotoxy(x2, y2); std::cout << c;
    
    // Draw horizontal lines
    for (int x = x1 + 1; x < x2; x++) {
        gotoxy(x, y1); std::cout << c;
        gotoxy(x, y2); std::cout << c;
    }
    
    // Draw vertical lines
    for (int y = y1 + 1; y < y2; y++) {
        gotoxy(x1, y); std::cout << c;
        gotoxy(x2, y); std::cout << c;
    }
}

// Display title centered on screen
void displayTitle(const std::string& title, int y) {
    int x = (80 - title.length()) / 2;
    gotoxy(x, y);
    std::cout << title;
}

// Display status message
void displayStatusMessage(const std::string& message) {
    gotoxy(5, 25);
    std::cout << std::string(70, ' ');  // Clear line
    gotoxy(5, 25);
    std::cout << message;
}

// Wait for key press
void waitForKeyPress() {
    displayStatusMessage("Press any key to continue...");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Get integer input with validation
int getIntInput(const std::string& prompt, int min_value, int max_value) {
    int value;
    bool valid = false;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= min_value && value <= max_value) {
                valid = true;
            } else {
                gotoxy(5, 25);
                std::cout << "Value must be between " << min_value << " and " << max_value << ". Press any key to try again...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            gotoxy(5, 25);
            std::cout << "Invalid input. Press any key to try again...";
            std::cin.get();
        }
    } while (!valid);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Get float input with validation
float getFloatInput(const std::string& prompt, float min_value, float max_value) {
    float value;
    bool valid = false;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= min_value && value <= max_value) {
                valid = true;
            } else {
                gotoxy(5, 25);
                std::cout << "Value must be between " << min_value << " and " << max_value << ". Press any key to try again...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            gotoxy(5, 25);
            std::cout << "Invalid input. Press any key to try again...";
            std::cin.get();
        }
    } while (!valid);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Get double input with validation
double getDoubleInput(const std::string& prompt, double min_value, double max_value) {
    double value;
    bool valid = false;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= min_value && value <= max_value) {
                valid = true;
            } else {
                gotoxy(5, 25);
                std::cout << "Value must be between " << min_value << " and " << max_value << ". Press any key to try again...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            gotoxy(5, 25);
            std::cout << "Invalid input. Press any key to try again...";
            std::cin.get();
        }
    } while (!valid);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Get string input with validation
std::string getStringInput(const std::string& prompt, size_t min_length, size_t max_length) {
    std::string value;
    bool valid = false;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt;
        
        std::getline(std::cin, value);
        
        if (value == "0") {
            return "0"; // Exit code
        }
        
        if (value.length() >= min_length && value.length() <= max_length) {
            valid = true;
        } else {
            gotoxy(5, 25);
            std::cout << "Input must be between " << min_length << " and " << max_length 
                      << " characters. Press any key to try again...";
            std::cin.get();
        }
    } while (!valid);
    
    return value;
}

// Get character input with validation
char getCharInput(const std::string& prompt, const std::string& valid_chars) {
    char value;
    bool valid = false;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt;
        
        value = std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        value = std::toupper(value);
        
        if (value == '0') {
            return '0'; // Exit code
        }
        
        if (valid_chars.find(value) != std::string::npos) {
            valid = true;
        } else {
            gotoxy(5, 25);
            std::cout << "Invalid input. Valid characters are: " << valid_chars 
                      << ". Press any key to try again...";
            std::cin.get();
        }
    } while (!valid);
    
    return value;
}

// Get yes/no input
bool getYesNoInput(const std::string& prompt) {
    char value;
    
    do {
        gotoxy(5, 25);
        std::cout << std::string(70, ' ');  // Clear line
        gotoxy(5, 25);
        std::cout << prompt << " (Y/N): ";
        
        value = std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        value = std::toupper(value);
        
        if (value == '0') {
            return false; // Exit code
        }
    } while (value != 'Y' && value != 'N');
    
    return (value == 'Y');
}
