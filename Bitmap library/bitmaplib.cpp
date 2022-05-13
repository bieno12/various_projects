#include <iostream>
#include <fstream>


using namespace std;

#pragma pack(push, 1)

struct FILEHEADER
{
	//value should be 'BM' if bitmapfile
	uint8_t type[2];
	//the size of the file
	uint32_t file_size;
	//4 bytes reserved, useless.
	uint8_t reserved[4];
	//the start index of the pixel array of bmp
	uint32_t start_offset;

};
struct BITMAPINFOHEADER{
  uint32_t biSize{};			// size of the header
  int32_t  biWidth{};		// width of image, if negative starts from top left otherwise bottom left
  int32_t  biHeight{};		// height of image.
  uint16_t biPlanes{1};		// number of color planes, must be one.
  uint16_t  biBitCount{}; 	// bits used per pexil, 8 for greyscale, 24 for rgb color
  uint32_t biCompression{};	// compression method used, should be 0 or 3 for uncompressed
  uint32_t biSizeImage{};		// 0 for uncompressed images.
  int32_t biXPelsPerMeter{};	// resolution on x axis for target device. useless in our program
  int32_t biYPelsPerMeter{};	// resolution on y axis
  uint32_t biClrUsed{};		// number of colored used, should be 0
  uint32_t biClrImportant{};	// number of important colors, should be 0
};
#pragma pack(pop)

int read_bitmap(const char * filename, FILEHEADER* fh, BITMAPINFOHEADER* bfh, uint8_t*& data)
{
	ifstream file;

	file.open(filename, ios::binary );
	if(!file.is_open())
	{
		cout << "couldn't open file\n";
		return 1;
	}
	file.read((char *)(fh), sizeof(*fh));
	file.read((char *)(bfh), sizeof(*bfh));
	data = new uint8_t[3 * (bfh->biWidth) * (bfh->biHeight)];
	return 0;
}

class Image
{
private:
	FILEHEADER fh;
	BITMAPINFOHEADER bfh;
	uint8_t status = 1; // not loaded by default
	uint8_t* data;
	uint32_t WIDTH;
	uint32_t HEIGHT;
public:
	Image(const char* filename)
	{
		status = read_bitmap(filename, &fh, &bfh, data);
		WIDTH = bfh.biWidth;
		HEIGHT = bfh.biHeight;
	}



	uint32_t width()
	{
		return WIDTH;
	}
	uint32_t height()
	{
		return HEIGHT;
	}
};
int main()
{
	Image image = Image("sample_image.bmp");
	cout << image.width() << " " << image.height() << endl;
}