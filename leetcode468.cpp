#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isDigit(char ch) {
        return ch >= '0' && ch <= '9'; 
    }

    bool isA2F(char ch) {
        return (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
    }

    bool parseNum(string& ip) {
        int num = 0;
        int i = 0;
        while (i < ip.length() && isDigit(ip[i])) {
            if (i > 0 && num == 0) return false;
            num = num * 10 + (ip[i] - '0');
            i++;
        }
        ip.erase(0, i);
        return num <= 255 && i > 0;
    }

    bool parseV6(string& ip) {
        int i = 0;
        while (i < ip.length() && (isDigit(ip[i]) || isA2F(ip[i]))) {
            i++;
        }
        ip.erase(0, i);
        return i <= 4 && i > 0;
    }

    string validIPv4(string IP) {
        string ip = IP;
        int count = 0;
        bool flag = true;
        while ((flag = parseNum(ip)) && ip.size() > 0) {
            if (ip[0] == '.') {
                ip.erase(0, 1);
                count++;
            } else {
                return "Neither";
            }
        }
        return (ip.size() == 0 && count == 3 && flag) ? "IPv4" : "Neither";
    }

    string validIPv6(string IP) {
        string ip = IP;
        int count = 0;
        bool flag = true;
        while ((flag = parseV6(ip)) && ip.size() > 0) {
            if (ip[0] == ':') {
                ip.erase(0, 1);
                count++;
            } else {
                return "Neither";
            }
        }
        return (ip.size() == 0 && count == 7 && flag) ? "IPv6" : "Neither";
    }

    string validIPAddress(string IP) {
        if (IP.length() > 39 || IP.length() < 7) return "Neither";
        for (int i = 0; i < 5; i++) {
            if (IP[i] == '.') return validIPv4(IP);
            if (IP[i] == ':') return validIPv6(IP);
        }
        return "Neither";
    }
};

int main() {
    Solution s;
    cout << s.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:73341") << endl;
    return 0;
}