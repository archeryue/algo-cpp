#include <iostream>
#include <boost/context/continuation.hpp>

int main() {
    namespace ctx = boost::context;

    int a = 0;
    ctx::continuation lambcc = ctx::callcc(
        [&a](ctx::continuation&& maincc) {
            int b = 1;
            for (;;) {
                maincc = maincc.resume();
                int next = a + b;
                a = b;
                b = next;
            }
            return std::move(maincc);
        });

    for (int i = 0; i < 10; ++i) {
        std::cout << a << " ";
        lambcc = lambcc.resume();
    }
    std::cout << std::endl;
}
