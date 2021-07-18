#include <iostream>
#include <vector>

using namespace std;

inline bool isDigit(char ch) {
    return ch >= '0' && ch <= '9'; 
}

inline bool isA2F(char ch) {
    return (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

bool parseV4(string& ip) {
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

bool validIP0(string IP, char sp_ch, int sp_cnt, bool (*parse)(string&)) {
    string ip = IP;
    int count = 0;
    bool flag = true;
    while ((flag = parse(ip)) && ip.size() > 0) {
        if (ip[0] == sp_ch) {
            ip.erase(0, 1);
            count++;
        } else {
            return false;
        }
    }
    return ip.size() == 0 && count == sp_cnt && flag;
}

string validIPAddress(string IP) {
    if (IP.length() > 39 || IP.length() < 7) return "Neither";
    for (int i = 0; i < 5; i++) {
        if (IP[i] == '.') return validIP0(IP, '.', 3, parseV4) ? "IPv4" : "Neither";
        if (IP[i] == ':') return validIP0(IP, ':', 7, parseV6) ? "IPv6" : "Neither";
    }
    return "Neither";
}

int main() {
    cout << validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334") << endl;
    cout << validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:73341") << endl;
    cout << validIPAddress("192.168.0.1") << endl;
    cout << validIPAddress("192.168.0.01") << endl;
    cout << validIPAddress("192.168..1") << endl;
    return 0;
}
