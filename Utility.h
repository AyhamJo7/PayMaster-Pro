#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <limits>

/**
 * @brief Position cursor at specific coordinates
 * @param x X-coordinate
 * @param y Y-coordinate
 */
void gotoxy(int x, int y);

/**
 * @brief Clear the screen
 */
void clearScreen();

/**
 * @brief Draw a box on the screen
 * @param x1 Left X-coordinate
 * @param y1 Top Y-coordinate
 * @param x2 Right X-coordinate
 * @param y2 Bottom Y-coordinate
 * @param c Character to use for drawing
 */
void drawBox(int x1, int y1, int x2, int y2, char c = '*');

/**
 * @brief Display title centered on screen
 * @param title Title to display
 * @param y Y-coordinate
 */
void displayTitle(const std::string& title, int y);

/**
 * @brief Display status message
 * @param message Message to display
 */
void displayStatusMessage(const std::string& message);

/**
 * @brief Wait for key press
 */
void waitForKeyPress();

/**
 * @brief Get integer input with validation
 * @param prompt Prompt to display
 * @param min_value Minimum allowed value
 * @param max_value Maximum allowed value
 * @return Validated integer input
 */
int getIntInput(const std::string& prompt, int min_value, int max_value);

/**
 * @brief Get float input with validation
 * @param prompt Prompt to display
 * @param min_value Minimum allowed value
 * @param max_value Maximum allowed value
 * @return Validated float input
 */
float getFloatInput(const std::string& prompt, float min_value, float max_value);

/**
 * @brief Get double input with validation
 * @param prompt Prompt to display
 * @param min_value Minimum allowed value
 * @param max_value Maximum allowed value
 * @return Validated double input
 */
double getDoubleInput(const std::string& prompt, double min_value, double max_value);

/**
 * @brief Get string input with validation
 * @param prompt Prompt to display
 * @param min_length Minimum allowed length
 * @param max_length Maximum allowed length
 * @return Validated string input
 */
std::string getStringInput(const std::string& prompt, size_t min_length, size_t max_length);

/**
 * @brief Get character input with validation
 * @param prompt Prompt to display
 * @param valid_chars String containing valid characters
 * @return Validated character input
 */
char getCharInput(const std::string& prompt, const std::string& valid_chars);

/**
 * @brief Get yes/no input
 * @param prompt Prompt to display
 * @return true for 'Y', false for 'N'
 */
bool getYesNoInput(const std::string& prompt);

#endif // UTILITY_H
