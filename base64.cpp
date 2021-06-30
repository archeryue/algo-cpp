#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<char> kTable {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

string Encode(vector<char> bytes) {
	string ret;
	int groupSize = bytes.size() / 3;
	uint32_t buf = 0;
	uint32_t mark = 0xfc000000;
	// 24 bits for a group
	for (int i = 0; i < groupSize; i++) {
		for (int j = 0; j < 3; j++) {
			buf = buf | bytes[3 * i + j];
			buf = buf << 8;
		}
		for (int j = 0; j < 4; j++) {
			uint32_t index = (buf & mark) >> 26;
			ret.push_back(kTable[index]);
			buf = buf << 6;
		}
	}

	int leftCount = bytes.size() % 3; 
	if (leftCount > 0) {
		// handle padding, left 1 or 2
		for (int i = 0; i < 3; i++) {
			if (i < leftCount) {
				buf = buf | bytes[groupSize * 3 + i];
			}
			buf = buf << 8;
		}
		for (int i = 0; i < leftCount + 1; i++) {
			uint32_t index = (buf & mark) >> 26;
			ret.push_back(kTable[index]);
			buf = buf << 6;
		}
		for (int i = 0; i < (3 - leftCount); i++) {
			ret.push_back('=');
		}
	}
	return ret;
}

int main() {
	vector<char> bytes {'A', 'B', 'C'};
	cout << Encode(bytes) << endl;
	bytes = {'s', 'd', 'f', '1', '2'};
	cout << Encode(bytes) << endl;
	return 0;
}
