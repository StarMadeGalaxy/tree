#pragma once

#ifndef _IINPUT_H_
#define _IINPUT_H_

#define INT64_POSITIVE_LENGTH 19	

#include <vector>
#include <conio.h>
#include <windows.h>
#include <iostream>


static double number_input(uint8_t limit = INT64_POSITIVE_LENGTH)
{
	// #include <vector>
	// #define INT64_POSITIVE_LENGTH 19		// long long int -9223372036854775808 to 9223372036854775807
	// #include <conio.h>
	// #include <iostream>

	std::vector<int8_t> number_vector;

	double number_array_integer = 0;
	bool is_negative = false;
	int16_t length = 0;		// length of a number (digit capacity, minus included). Index for digits is [length - 1]


	while (true) {
		int8_t c = _getch();

		if (c > 47 && c < 58 && length < limit) {		//	Allow to enter only digits
			number_vector.push_back(c);
			length++;
			std::cout << (char)c;
		}
		else if (c == '\b' && length > 0) {	// Backspace
			if (is_negative && length == 1) {		// 45 = '-'
				is_negative = false;
				limit--; length--;
				std::cout << "\b \b";
				continue;
			}
			number_vector.pop_back();
			length--;
			std::cout << "\b \b";
		}
		else if (c == 13 && length != 0) {		// Enter breaks down the loop
			if (is_negative && length == 1)/* && !is_vector_outta_ll(number_array)*/ // BETA
				continue;
			break;
		}
		else if (c == 45 && length == 0) {		// Minus for negative number
			limit++; length++;
			is_negative = true;
			std::cout << (char)c;
		}
	}
	// Convert from vector to variable
	for (size_t i = 0; i < number_vector.size(); i++) {
		number_array_integer *= 10;
		number_array_integer += number_vector[i] - 48;
	}

	if (is_negative)
		return number_array_integer * -1;
	return number_array_integer;
}


static void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


static void move_console_cursor(short x, short y)
{
	COORD position = { x, y };
	HANDLE output_window = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output_window, position);
}


static void print_loading_field(int delay, int end_offset)
{
	int offset = 1;
	std::cout << "\n\n[---------------------]";
	move_console_cursor(0, 1);
	for (int i = 0; i < 101; i++) {
		if (i % 5 == 0) {
			move_console_cursor(offset, 2);
			Sleep(delay);
			std::cout << "#";
			offset++;
		}
		Sleep(delay);
		move_console_cursor(end_offset, 2);
		std::cout << i << '%';
	}
}


static void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}


#endif	// _IINPUT_H_
