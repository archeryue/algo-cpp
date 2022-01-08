#ifndef __BITMAP_H__
#define __BITMAP_H__

#include <sys/types.h>
#include <vector>

namespace archer {

class Bitmap {
 private:
     unsigned sz;
     unsigned cnt;
     std::vector<u_int8_t> val;
 public:
    Bitmap(unsigned size) : sz(size), cnt(0) {
        unsigned val_sz = (sz / 8) + (sz % 8 == 0 ? 0 : 1);
        val.resize(val_sz, 0);
    }

    void set(unsigned i) {
        if (check(i)) return;
        unsigned val_i = i / 8;
        unsigned offset = i % 8;
        val[val_i] |= (0x01 << offset);
        cnt++;
    }

    void reset(unsigned i) {
        if (!check(i)) return;
        unsigned val_i = i / 8;
        unsigned offset = i % 8;
        val[val_i] &= ~(0x01 << offset);
        cnt--;
    }

    bool check(unsigned i) {
        unsigned val_i = i / 8;
        unsigned offset = i % 8;
        return val[val_i] & (0x01 << offset);
    }

    unsigned count() {
        return cnt;
    }
};

}

#endif
