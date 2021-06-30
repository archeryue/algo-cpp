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
	// 24 bits for a group
	int groupSize = bytes.size() / 3;
	// padding
	groupSize += bytes.size() % 3 == 0 ? 0 : 1;
	uint32_t buf = 0;
	for (int i = 0; i < groupSize; i++) {
		for (int j = 0; j < 3; j++) {
			if (3 * i + j < bytes.size()) {
				buf = buf | bytes[3 * i + j];
			}
			buf = buf << 8;
		}
		for (int j = 0; j < 4; j++) {
			if ((4 * i + j + 1) * 6 <= bytes.size() * 8) {
				ret.push_back(kTable[buf >> 26]);
			} else {
				ret.push_back('=');
			}
			buf = buf << 6;
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
