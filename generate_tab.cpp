#include <iostream>
#include <bitset>

using namespace std;


// Показатель связности
#define C(p) ( \
    (!p[1] && (p[2] || p[3])) + \
    (!p[3] && (p[4] || p[5])) + \
    (!p[5] && (p[6] || p[7])) + \
    (!p[7] && (p[0] || p[1]))   \
)

// Показатель концевых точек
#define N(p) min ( \
    (p[0] || p[1]) + (p[2] || p[3]) + (p[4] || p[5]) + (p[6] || p[7]), \
    (p[1] || p[2]) + (p[3] || p[4]) + (p[5] || p[6]) + (p[7] || p[0])  \
)


int main() {
    bitset<512> tab;
    bitset<8> cur;

    for (short i = 0; i < 256; ++i, cur = i) {
        short cur_N = N(cur);
        if (C(cur) == 1 && 2 <= cur_N && cur_N <= 3) {
            if (((cur[1] || cur[2] || !cur[4]) && cur[3]) == 0) tab[i*2] = true;
            if (((cur[5] || cur[6] || !cur[0]) && cur[7]) == 0) tab[i*2+1] = true;
        }
    }

    cout << tab;

    return 0;
}