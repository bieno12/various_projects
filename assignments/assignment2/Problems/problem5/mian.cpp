#include <iostream>
#include "Universe.h"
#include <vector>
#include <conio.h>

//enabling virtual sequences in cmd
#ifdef _WIN32
#include <windows.h>
#include "CSIcommands.h"

HANDLE stdout_handle;
HANDLE stdin_handle;
DWORD originalOutMode;
DWORD originalInMode;
void enable_virtual_seq()
{
	stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(stdin_handle, &originalInMode);
	GetConsoleMode(stdout_handle, &originalOutMode);



	SetConsoleMode(stdin_handle, (originalInMode 
		& ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT))
		| ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_WINDOW_INPUT);

	SetConsoleMode(stdout_handle, (originalOutMode) | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void restore_settings()
{
	FlushConsoleInputBuffer(stdin_handle);
	SetConsoleMode(stdin_handle, originalInMode);
	SetConsoleMode(stdout_handle, originalOutMode);
}
#endif
	
#define SIZE 40

void get_intialstate(Universe & uni)
{
	uni.display();
	int x = 0, y = 0;
	char input = getch();
	while(input != 'z')
	{

		switch(input)
		{
			case 'a':
			case 'A':
				if(x > 0) x--;
			break;
			case 'd':
			case 'D':
				if(x < SIZE - 1) x++;
			break;
			case 'w':
			case 'W':
				if(y > 0) y--;

			break;
			case 's':
			case 'S':
				if(y < SIZE - 1) y++;
			break;
			case ' ':
				uni.set_cell(x,y, !uni.cell_at(x,y));
			break;

		}
		//highlight the current selected cell

		uni.set_highlight(x, y);
		uni.display();
		std::cout << "press z when you are done";
		input = getch();
	}
	uni.set_highlight(-1, -1);
}
int main()
{

	#ifdef _WIN32
	enable_virtual_seq();
	#endif


	std::cout << CSI_HIDE_CURSOR;
	


	Universe uni(SIZE, 3.0);
	uni.set_cell(10,10, 1);
	uni.set_cell(10,11, 1);
	uni.set_cell(10,12, 1);
	get_intialstate(uni);
	// cells[12][10] = 1;
	// cells[11][11] = 1;


	uni.run(100);
	std::cout << CSI_SHOW_CURSOR;
	#ifdef _WIN32
	restore_settings();
	#endif

}