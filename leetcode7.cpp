#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int reverse(int x) {
	bool pos = x >= 0;
	x = abs(x);
	int ret = 0;
	while (x > 0) {
		if (ret > INT_MAX / 10) return 0;
		ret *= 10;
		ret += x % 10;
		x /= 10;
	}
	return pos ? ret : -ret;
}

int main() {
	cout << reverse(-356) << endl;
	return 0;
}
