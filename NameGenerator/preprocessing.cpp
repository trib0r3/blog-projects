#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cerr << "USAGE: " << argv[0] << " [dictionary_to_add]\n";
		exit(1);
	}

	ifstream in_dict;
	in_dict.open(argv[1]);
	if (!in_dict.is_open())
	{
		cerr << "Cannot open dictionary!\n";
		exit(1);
	}

	// preprocessing
	map <int, fstream*> files;
	map <int, fstream*>::iterator it;
	std::string buffer;
	while (!in_dict.eof())
	{
		in_dict >> buffer;
		int buff_len = buffer.size();
		it = files.find(buff_len);

		// create file if doesnt exists
		if (it == files.end())
		{
			ostringstream ss;
			ss << buff_len;
			files.insert(std::pair<int,fstream*>(buff_len, new fstream(ss.str(), ios::out | ios::app)));
		}

		// add words
		*files[buff_len] << buffer << "\n";
	}

	// clearing
	for (auto& pair : files)
	{
		delete pair.second;
		pair.second = nullptr;
	}
}
