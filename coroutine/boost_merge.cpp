#include <boost/coroutine/symmetric_coroutine.hpp>
#include <iostream>
#include <vector>

std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b) {
    using symcoro = boost::coroutines::symmetric_coroutine<void>;
    std::vector<int> c;
    std::size_t idx_a = 0, idx_b = 0;
    symcoro::call_type *co_ptr_a, *co_ptr_b; 

    symcoro::call_type coro_a(
        [&](symcoro::yield_type& yield) {
            while (idx_a < a.size()) {
                if (a[idx_a] > b[idx_b]) yield(*co_ptr_b);
                c.push_back(a[idx_a++]);
            }
            while (idx_b < b.size()) c.push_back(b[idx_b++]);
        });

    symcoro::call_type coro_b(
        [&](symcoro::yield_type& yield) {
            while (idx_b < b.size()) {
                if (b[idx_b] > a[idx_a]) yield(*co_ptr_a);
                c.push_back(b[idx_b++]);
            }
            while (idx_a < a.size()) c.push_back(a[idx_a++]);
        });

    co_ptr_a = &coro_a;
    co_ptr_b = &coro_b;
    coro_a();

    return c;
}

int main() {
    std::vector<int> a {1, 3, 6, 9, 11};
    std::vector<int> b {2, 5, 7, 8, 10};
    std::vector<int> c = merge(a, b);
    for (const auto i : c) std::cout << i << " ";
    std::cout << std::endl;
}
