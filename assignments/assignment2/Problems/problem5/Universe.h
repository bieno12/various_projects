#include <iostream>
#include <vector>

class Universe
{
private:
	float m_gps; //generations per sec
	int m_currentGeneration;
	int m_size;
	std::vector<std::vector<bool>> m_grid;
	int m_highlighter_x;
	int m_highlighter_y;
	int count_neighbors(int x, int y);
	bool is_valid(int x, int y);
public:
	Universe(int size, float gps);
	void initialize(std::vector<std::vector<int>> start_grid);
	void reset();
	void next_generation();
	void set_cell(int x, int y, bool value	);
	bool cell_at(int x, int y);
	void display();
	void run(int gens);
	void set_highlight(int x, int y);
};
