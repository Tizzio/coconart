#include "Utility.h"

#include <fstream>
using namespace std;

bool Coconart::JsonLoad(Json::Value& root, const string& filename)
{
	std::ifstream t;
	t.open(filename);					// open input file
	if (!t)	{ return false; }			//failed to open file
	t.seekg(0, std::ios::end);			// go to the end
	int length = (int)t.tellg();				// report location (this is the length)
	if (length == 0) { return false; }	//no data
	t.seekg(0, std::ios::beg);			// go back to the beginning
	char* buffer = new char[length];	// allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);				// read the whole file into the buffer
	t.close();

	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, buffer + length, root, false);
	delete buffer;
	if (!parsingSuccessful)
	{
		cout << "Failed to parse JSON" << endl
			<< reader.getFormattedErrorMessages()
			<< endl;
		return false;
	}
	return true;
}