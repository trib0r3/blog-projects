#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
	// args processing
	if (argc != 3)
	{
		cerr << "USAGE: " << argv[0] << "[words] [dictionary]\n";
		exit(1);
	}

	int len = atoi(argv[1]);
	if (len < 1)
	{
		cerr << "Size of used words must be at least equ 1\n";
		exit(1);
	}

	ifstream file(argv[2]);
	if (!file.is_open())
	{
		cerr << "Cannot open dictionary!\n";
		exit(1);
	}

	int offset = atoi(argv[2]);
	if (offset < 1)
	{
		cerr << "Error, invalid filename format!\n";
		exit(1);
	}
	offset += 1; // + \n

	// building name
	srand(time(NULL));
	std::string name, buffer;

	file.seekg(0, file.end);
	int words_len = file.tellg() / offset; // calculate amount of words
	cout << file.tellg() << endl;

	for(int i=0; i<len; ++i)
	{
		int index = rand() % words_len; // get random word index
		file.seekg(index*offset, file.beg);

		// read from location
		file >> buffer;
		name += buffer + " ";
	}
	cout << name << endl;
	return 0;
}
