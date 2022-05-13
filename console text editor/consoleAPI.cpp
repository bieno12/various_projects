#include <windows.h>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdarg.h>
#include <iomanip>
#include "consoleAPI.h"
/*
AUTHOR:Zeyad Shahin
DATE: 8/5/2022
PURPOSE: A windows console API that utilizes the new virtual terminal features
		introduced to Windows. Starting from  windows 10.
*/

#define ESC "\x1b"
#define CSI "\x1b["
using std::string;
using std::stringstream;
using std::regex;

bool inRawMode = false;
HANDLE stdout_handle;
HANDLE stdin_handle;
DWORD originalOutMode;
DWORD originalInMode;
int window_width;
int window_height;
stringstream ss;

 
void match_output(string expression, string matched, ...)
{
	va_list valist;
	regex base_regex(expression);
	std::smatch base_match;
	regex_match(matched, base_match, base_regex);
	va_start(valist, matched);

	for(int i = 1; i < base_match.size(); i++)
	{
		int * p = va_arg(valist, int *);
		string numstr = base_match[i].str();
		*p = stoi(numstr);
	}
	va_end(valist);

}
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}
//get the handle and save teh original settings
void intialize_api()
{
	stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(stdin_handle, &originalInMode);
	GetConsoleMode(stdout_handle, &originalOutMode);
}


//change settings to have full control of console, make sure to restore the settings before exiting the app
void enter_rawmode()
{
	SetConsoleMode(stdin_handle, (originalInMode 
		& ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT))
		| ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_WINDOW_INPUT);

	SetConsoleMode(stdout_handle, (originalOutMode) | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	get_console_size(&window_width, &window_height);
	// HWND consoleWindow = GetConsoleWindow();
	// SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}


//restores original settings, it is called when exiting the application gracefully
void exit_rawmode()
{
	FlushConsoleInputBuffer(stdin_handle);
	SetConsoleMode(stdin_handle, originalInMode);
	SetConsoleMode(stdout_handle, originalOutMode);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) | WS_MAXIMIZEBOX | WS_SIZEBOX);
}

//get the key pressed, as in a vt sequence
void getkey(char * dest, int size, DWORD * count)
{
  ReadConsole(stdin_handle, dest, size, count, NULL);
}

//write something to console, could be a message, could be a vt sequence
void write(string message)
{
	WriteConsole(stdout_handle, message.c_str(), message.size(), NULL, NULL);
}

//fill the screen with empty spaces
void clear_screen()
{
	ss.str("");
	ss <<"\x1b[2J";

	write(ss.str());
}

//fill the line with empty spaces
void clear_line()
{
	ss.str("");
	ss << "\x1b[2K";
	write(ss.str());
	
}

void delete_line()
{
	ss.str("");
	ss << CSI << "1M";
	write(ss.str());
}

void fill_line(char c)
{
	//todo: implement a global dimensions variable to not call get_console_size every time
	int x, y;
	x = 1;
	set_cursor_pos(x, y);
	get_console_size(&window_width, &window_height);
	ss.str("");
	ss << std::setw(window_width)  << std::setfill(c) << "";
	write(ss.str());
}
//prints the string and fill the rest with spaces
void fill_line(std::string message)
{
	//todo: implement a global dimensions variable to not call get_console_size every time
	int x, y;
	int width, height;
	get_cursor_pos(&x, &y);
	x = 1;
	set_cursor_pos(x, y);
	ss.str("");
	get_console_size(&window_width, &window_height);
	ss << std::setw(window_width) << std::left << std::setfill(' ') << message;
	write(ss.str());
}

//switch to the alternate buffer
//it is preffered to do so, as not to affect the original buffer
//it is your choice though
void switch_to_altbuffer()
{
	ss.str("");
	ss << CSI <<"?1049h";
	write(ss.str());
	set_cursor_pos(1,1);
}

//return back to the main buffere
void switch_to_mainbuffer()
{
	ss.str("");
	ss << CSI <<"?1049l";
	write(ss.str());
}


//set text format
void set_text_format(int format)
{
	ss.str("");
	ss << CSI << format << "m";
	write(ss.str());
}
void reset_text_format()
{
	ss.str("");
	ss << CSI << "0m";
	write(ss.str());
}
void set_fg_color(int r, int g, int b)
{
	ss.str("");
	ss << "\x1B[" << "38;2;" << r << ";" << g << ";" << b << "m";
	write(ss.str());
	
}

void set_bg_color(int r, int g, int b)
{
	ss.str("");
	ss << "\x1B[" << "48;2;" << r << ";" << g << ";" << b << "m";
	write(ss.str());
}
//set the cursor at the specified position
void set_cursor_pos(int x, int y)
{
	ss.str("");
	ss <<"\x1b[" << y << ";" << x << "H";

	write(ss.str());
}

//get the dimension of console window
void get_cursor_pos(int * x, int * y)
{
	ss.str("");
	ss << CSI << "6n";
	write(ss.str());
	char buffer[32];
	DWORD count;
	getkey(buffer, 32, &count);
	buffer[count] = 0;
	match_output("\x1b\\[(\\d+);(\\d+)R",string(buffer), y, x);
}

//set the title of console window
void set_title(string title)
{
	ss.str("");
	ss <<"\x1b]0;" << title <<  "\x1b\x5C";
	write(ss.str());
}

void sleep(int delay)
{
	Sleep(delay);
}
void get_console_size(int* width, int* height)
{
	CONSOLE_SCREEN_BUFFER_INFO csfi;
	GetConsoleScreenBufferInfo(stdout_handle,&csfi);
	*width = csfi.srWindow.Right - csfi.srWindow.Left;
	*height = csfi.srWindow.Bottom - csfi.srWindow.Top;
}

void set_console_size(int width, int height)
{
	ss.str("");
	ss << CSI << "\e[8;"<< height<< ";" << width <<"t";
	write(ss.str());
}
void fill_screen(char c)
{
	//todo: create a global width and height
	ss.str("");
	get_console_size(&window_width, &window_height);
	ss << std::setw(window_width * window_height) << std::setfill(c) << "";
	write(ss.str());
	set_cursor_pos(1,1);
}


void set_scrolling_margin(int start, int end)
{
	ss.str("");
	ss << CSI << start << ";" << end << "r";
	write(ss.str());	
}

void insert(char c)
{
	ss.str("");
	ss << CSI << "1@";
	ss << c;
	write(ss.str());
}

void go_left()
{
	ss.str("");

	ss << CSI << "1D";

	write(ss.str());

}
void go_right()
{
	ss.str("");

	ss << CSI << "1C";

	write(ss.str());

}
void go_up()
{
	ss.str("");

	ss << CSI << "1A";

	write(ss.str());

}
void go_down()
{
	ss.str("");
	ss << CSI << "1B";
	write(ss.str());
}

void hide_cursor()
{
	ss.str("");
	ss << CSI << "?25l";
	write(ss.str());
}

void show_cursor()
{
	ss.str("");
	ss << CSI << "?25h";
	write(ss.str());
}

void save_cursor()
{
	ss.str("");
	ss << CSI << "s";
	write(ss.str());
}
void load_cursor()
{
	ss.str("");
	ss << CSI << "u";
	write(ss.str());
}

void write_at(int x, int y, std::string message)
{
	save_cursor();
	set_cursor_pos(x, y);
	write(message);
	load_cursor();
}