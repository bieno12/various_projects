#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "consoleAPI.h"
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#define GREEN 0,100,0
#define GREY 50,50,50
#define WHITE 255,255,255


#define UP_ARROW "\x1b[A"
#define DOWN_ARROW "\x1b[B"
#define LEFT_ARROW "\x1b[D"
#define RIGHT_ARROW "\x1b[C"
using std::string;
using std::to_string;
using namespace std;

int width, height;
std::vector<string> lines;

int current_line = 1; int current_col = 1;
bool running = true;
//TODO: deal with line overflow

void arrowup_key();

void arrowdown_key();

void arrowleft_key();

void arrowright_key();

void backspace_key();

void ctrl_z_key();

void line_feed();

bool strcomp(string a, string b)
{
	return a == b;
}
void load_file()
{
	std::fstream file("text.txt", std::ios::in);
	string s;
	while(getline(file, s))
	{
		lines.push_back(s);
	}
	file.close();
}
void save_file()
{
	std::fstream file("text.txt", std::ios::out | std::ios::trunc);

	for(auto s : lines)
		file << s << '\n';
	file.close();
}
void draw_frame()
{
	write("\x1b[s");
	set_bg_color(GREEN);
	set_fg_color(WHITE);
	set_cursor_pos(1,1);
	fill_line(" Text Editor: ");
	reset_text_format();

	set_bg_color(GREEN);
	set_fg_color(WHITE);
	set_cursor_pos(1, height);
	fill_line(string("press ctrl + z to save and exit,"));
	reset_text_format();

	write("\x1b[u");
}

void update_status()
{
	std::stringstream ss;
	hide_cursor();
	write("\x1b[s");
	set_bg_color(GREEN);

	set_fg_color(WHITE);

	string message = string("line: ") + to_string(current_line) + ", col:" + to_string(current_col);
	ss.str("");
	ss <<std::setw(message.size() + 2) << message;
	set_cursor_pos(width - message.size() - 2, height);
	write(ss.str());
	reset_text_format();
	write("\x1b[u");
	show_cursor();
}

void single_key_event(char c)
{
	int x, y;
	get_cursor_pos(&x, &y);

	switch(c)
	{
		case '\r':
		case '\n':
			line_feed();
		break;

		case 127:
		{
			backspace_key();
		}
		break;
		case 26:
			ctrl_z_key();
		break;
		default:
			if(c < 32)
				break;
			//insert a character if not a control character
			if(x < width)
			{
				lines[current_line - 1].push_back(c);
				insert(c);
			}

	}
}

void sequence_key_event(char * input_buffer)
{
	int x, y;
	get_cursor_pos(&x, &y);
	current_col = x;
	//up arrow
	if((strcomp(input_buffer, UP_ARROW)))
	{
		arrowup_key();

	}
	//down arrow
	else if((strcomp(input_buffer, DOWN_ARROW)))
	{
		arrowdown_key();
	}
	//left arrow
	else if(strcomp(input_buffer, LEFT_ARROW))
	{
		arrowleft_key();
	}
	//right arrow
	else if(strcomp(input_buffer, RIGHT_ARROW))
	{
		arrowright_key();
	}
	else
		write(input_buffer);

}
void mainLoop(int w, int h)
{
	std::stringstream ss;
	width = w; height = h;
	intialize_api();
	enter_rawmode();
	set_title("Text Editor");
	switch_to_altbuffer();
	sleep(100);	

	set_console_size(width, height);

	draw_frame();
	set_scrolling_margin(2,height - 1);
	set_cursor_pos(1, 2);
	load_file();
	for(int i = 0; i < lines.size(); i++)
	{
		write(lines[i]);
		if(i < lines.size() - 1)
			write("\n\r");
	}
	current_line = lines.size();
	update_status();

	char input_buffer[128];
	long unsigned int count;
	// std::thread screen(on_screen_change);
	while(running)
	{
		getkey(input_buffer, 128, &count);
		input_buffer[count] = 0;


		if(count == 1)
		{
			single_key_event(input_buffer[0]);
		}
		else
		{
			sequence_key_event(input_buffer);
		}
		if(running)
			update_status();

	}
	exit_rawmode();

}

void backspace_key()
{

	int x, y;
	get_cursor_pos(&x, &y);
	//delete and move left
	if(lines.size())
	{

		if(lines[current_line - 1].size())
		{
			if(x > 1)
			{
				//show that a char is deleted
				go_left();
				write("\x1b[1P");
				//actually delete it
				lines[current_line - 1].pop_back();
			}
			//append the current line with the prev if backspace was pressed at the begin of line
			else
			{
				if(current_line > 1)
				{
					string l = lines[current_line - 1];
					//show that a line is deleted
					delete_line();
					//actually deleted
					lines.erase(begin(lines) + current_line - 1);
					//append the line to the prev
					arrowup_key();
					lines[current_line - 1] += l;
					get_cursor_pos(&x, &y);
					//go to the end of the line;
					set_cursor_pos(lines[current_line - 1].size() + 1, y);
					//redraw the current line
					write_at(1, y, lines[current_line - 1]);

					//draw the last line if there was any
					if(lines.size() > current_line + ((height - 1) - y - 1))
						write_at(1, height - 1, lines[current_line + ((height - 1) - y - 1)]);
				}
			}
		}
		else
		//case of empty line just delete it
		{ 
			if(lines.size() > 1)
			{
				//show that a line is deleted
				delete_line();
				//actually deleted
				lines.erase(begin(lines) + current_line - 1);
				//go up one line
				arrowup_key();
				get_cursor_pos(&x, &y);
				//go to the end of the line;
				set_cursor_pos(lines[current_line - 1].size() + 1, y);
				//draw the last line if there was any
				if(lines.size() > current_line + ((height - 1) - y - 1))
					write_at(1, height - 1, lines[current_line + ((height - 1) - y - 1)]);
			}

		}

	}


}
void line_feed()
{
	//todo: if line_feed was inside of a line, split the line into to lines
	int x, y;
	get_cursor_pos(&x, &y);
	go_down();
	//insert a new line
	lines.insert(begin(lines) + current_line, "");
	//increment the line counter
	current_line++;
	
	if(y == height - 1)
		write("\x1b[1S");

	write("\x1b[1L");

}
void arrowup_key()
{
	int x, y;
	get_cursor_pos(&x, &y);
	if(current_line > 1)
	{
		if(y == 2)
		{
			//scroll up
			current_line--;
			write("\x1b[1T");
			//redraw the line
			write_at(1, y, lines[current_line - 1]);
			set_cursor_pos(min(x,(int)lines[current_line - 1].size() + 1), y);

		}
		else
		{
			current_line--;
			set_cursor_pos(min(x,(int)lines[current_line - 1].size() + 1), y - 1);

		}
	}
}
void arrowdown_key()
{	
	int x, y;
	get_cursor_pos(&x, &y);

	if(current_line < lines.size())
	{
		if( y == height - 1)
		{
			//scroll down
			current_line++;
			write("\x1b[1S");
			//rewrite the line;
			write_at(1, y, lines[current_line - 1]);
			set_cursor_pos(min(x,(int)lines[current_line - 1].size() + 1), y);
		}
		else
		{
			//go to next line
			current_line++;
			set_cursor_pos(min(x,(int)lines[current_line - 1].size() + 1), y + 1);

		}
	}

}
void arrowleft_key()
{
	int x, y;
	get_cursor_pos(&x, &y);
	int inc = 0;
	if(current_col <= 1 )
	{

		if(current_line > 1)
		{
			current_line--;
			if(y != 2)
			{
				set_cursor_pos(lines[current_line - 1].size() + 1, y - 1);
			}
			//draw the newline if we are at the first line in the scrolling margin
			else
			{
				write("\x1b[1T");
				write_at(1, 2, lines[current_line - 1]);
				set_cursor_pos(lines[current_line - 1].size() + 1, y);
			}
		}
	}
	else
	{
		go_left();
		current_col--;
	}
}
void arrowright_key()
{
	int x, y;
	get_cursor_pos(&x, &y);

	if(current_col >= lines[current_line - 1].size() + 1)
	{
		if(current_line < lines.size())
		{
			//go to the next line
			write("\n\r");
			current_line++;
			current_col = 1;
			//draw the newline if we are at the last line in the scrolling margin
			if(y == height - 1)
				write_at(1, y, lines[current_line - 1]);
		}
	}
	else
	{

		go_right();
	}
}

void ctrl_z_key()
{
	running = false; 

	save_file();
	switch_to_mainbuffer();
	exit_rawmode();
}