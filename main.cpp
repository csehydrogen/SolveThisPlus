#include <cstdio>
#include <map>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned long long ull;
ull p2[64], start, target, wall;
map<ull, ull> cache;

inline ull bitget(ull a, int x, int y) { return a & p2[(x << 3) + y]; }
inline void bitunset(ull &a, int x, int y) { a &= ~p2[(x << 3) + y]; }
inline void bitset(ull &a, int x, int y) { a |= p2[(x << 3) + y]; }

void init() {
    for(int i = 0; i < 64; ++i)
        p2[i] = 1ull << i;
}

void input() {
    for(int i = 0; i < 8; ++i) {
        char buf[9];
        scanf("%s", buf);
        for(int j = 0; j < 8; ++j) {
            if(buf[j] == '#')
                bitset(wall, i, j);
            else if(buf[j] == 'a')
                bitset(start, i, j);
            else if(buf[j] == 'b')
                bitset(target, i, j);
            else if(buf[j] == 'c') {
                bitset(start, i, j);
                bitset(target, i, j);
            }
        }
    }
}

ull shift(ull a, int d) {
    int i, j, k;
    if(d == 2) {
        for(i = 1; i < 8; ++i)
            for(j = 0; j < 8; ++j)
                if(bitget(a, i, j) && !bitget(wall, i - 1, j) && !bitget(a, i - 1, j)) {
                    bitunset(a, i, j);
                    bitset(a, i - 1, j);
                }
    } else if(d == 3) {
        for(i = 0; i < 8; ++i)
            for(j = 1; j < 8; ++j)
                if(bitget(a, i, j) && !bitget(wall, i, j - 1) && !bitget(a, i, j - 1)) {
                    bitunset(a, i, j);
                    bitset(a, i, j - 1);
                }
    } else if(d == 0) {
        for(i = 6; i >= 0; --i)
            for(j = 7; j >= 0; --j)
                if(bitget(a, i, j) && !bitget(wall, i + 1, j) && !bitget(a, i + 1, j)) {
                    bitunset(a, i, j);
                    bitset(a, i + 1, j);
                }
    } else { // if(d == 1)
        for(i = 7; i >= 0; --i)
            for(j = 6; j >= 0; --j)
                if(bitget(a, i, j) && !bitget(wall, i, j + 1) && !bitget(a, i, j + 1)) {
                    bitunset(a, i, j);
                    bitset(a, i, j + 1);
                }
    }
    return a;
}

void print(ull a) {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            printf("%c", bitget(a, i, j) ? '0' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

void process() {
    queue<ull> q;
    q.push(start);
    cache[start] = 0;
    while(!q.empty()) {
        ull here = q.front(); q.pop();
        for(int i = 0; i < 4; ++i) {
            ull there = shift(here, i);
            if(!cache.count(there)) {
                q.push(there);
                cache[there] = here;
                if(there == target) return;
            }
        }
    }
}

void output() {
    int i;
    ull t = target, tt;
    vector<char> ans;
    while(t != start) {
        tt = cache[t];
        for(i = 0; i < 4; ++i)
            if(shift(tt, i) == t) {
                ans.push_back("DRUL"[i]);
                break;
            }
        t = tt;
    }
    while(!ans.empty()) {
        printf("%c", ans.back());
        ans.pop_back();
    }
}

int main() {
    init();
    input();
    process();
    output();
    return 0;
}
