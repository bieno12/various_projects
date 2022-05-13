#ifndef API
#define API
void write(std::string message);

std::string GetLastErrorAsString();

void intialize_api();

void enter_rawmode();

void exit_rawmode();

void getkey(char * dest, int size,long unsigned int * count);

void clear_screen();

void clear_line();

void set_cursor_pos(int x, int y);

void switch_to_altbuffer();

void switch_to_mainbuffer();

void get_console_size(int * width, int * height);

void set_title(std::string title);

void sleep(int delay);


void set_console_size(int width, int height);

void set_text_format(int format);

void reset_text_format();

void set_fg_color(int r, int g, int b);

void set_bg_color(int r, int g, int b);

void fill_screen(char c);

void get_cursor_pos(int * x, int * y);

void fill_line(char c);

void fill_line(std::string message);

void set_scrolling_margin(int start, int end);

void insert(char c);

void go_left();

void go_right();

void go_up();

void go_down();
void hide_cursor();

void show_cursor();

void save_cursor();

void load_cursor();
void write_at(int x, int y, std::string message);

void delete_line();


#endif