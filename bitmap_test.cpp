#include <iostream>
#include "bitmap.h"

using namespace std;

int main() {
    archer::Bitmap bitmap(1000);

    for (int i = 0; i < 100; i++) {
        bitmap.set(i * 10);
    }
    cout << bitmap.count() << endl;
    cout << bitmap.check(300) << endl;
    cout << bitmap.check(700) << endl;

    for (int i = 0; i < 50; i++) {
        bitmap.reset(i * 10);
    }
    cout << bitmap.count() << endl;
    cout << bitmap.check(300) << endl;
    cout << bitmap.check(700) << endl;

    for (int i = 50; i < 100; i++) {
        bitmap.reset(i * 10);
    }
    cout << bitmap.count() << endl;
    cout << bitmap.check(300) << endl;
    cout << bitmap.check(700) << endl;
}
