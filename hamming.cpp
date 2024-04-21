#include <iostream>
#include <vector>

using namespace std;

class Hamming {
public:
    static vector<int> encode(vector<int> message) {
        vector<int> result;
        // leave space for parity bits
        int r = 0;
        for (int i = 0; i < message.size(); ) {
            if (result.size() == (1 << r) - 1) {
                result.push_back(0);
                r++;
            } else {
                result.push_back(message[i++]);
            }
        }
        // calculate and fill the parity bits
        for (int i = 0; i < r; i++) {
            int count = 0;
            for (int j = (1 << i) - 1; j < result.size(); j += (1 << (i + 1))) {
                for (int k = 0; k < (1 << i); k++) {
                    if (j + k < result.size()) {
                        count += result[j + k];
                    }
                }
            }
            result[(1 << i) - 1] = count % 2;
        }
        return result;
    }

    static int bad_bit(vector<int> message) {
        int bad = 0;
        int r = 0;
        while ((1 << r) < message.size()) {
            int step = (1 << r);
            int count = 0;
            for (int i = step - 1; i < message.size(); i += step * 2) {
                for (int j = 0; j < step; j++) {
                    if (i + j < message.size()) {
                        count += message[i + j];
                    }
                }
            }
            if (count % 2 != 0) {
                bad += step;
            }
            r++;
        }
        return bad - 1;
    }
};

void test(vector<int> message, int bad_bit_index) {
    cout << "message : ";
    for (int i = 0; i < message.size(); i++) {
        cout << message[i] << " ";
    }
    cout << endl << "encoded : ";
    vector<int> encoded = Hamming::encode(message);
    for (int i = 0; i < encoded.size(); i++) {
        cout << encoded[i] << " ";
    }
    cout << endl;
    cout << "check bad bit : " << endl;
    cout << "bad bit index : " << Hamming::bad_bit(encoded) << endl;
    cout << "change endoded[" << bad_bit_index << "] to " << (encoded[bad_bit_index] == 0 ? 1 : 0) << endl;
    encoded[bad_bit_index] = (encoded[bad_bit_index] == 0 ? 1 : 0);
    cout << "bad bit index : " << Hamming::bad_bit(encoded) << endl;
}

int main() {
    cout << "testcase 0 : " << endl;
    vector<int> message = {1, 0, 0, 1, 1, 0, 1, 0};
    test(message, 3);
    test(message, 9);
    // write more testcases
    cout << "testcase 1 : " << endl;
    message = {1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1};
    test(message, 12);
    test(message, 15);
    test(message, 0);
    return 0;
}
