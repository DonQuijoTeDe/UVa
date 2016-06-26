#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

const long long limit = 2147483647;

long long max(long long x, long long y) {
    return x > y ? x : y;
}

int main() {
    int t, i, j;
    char str[200];
    cin >> t;
    while(t--) {
        cin >> str;
        int slen = strlen(str), i;
        long long DP[200] = {}, tmp = 0;
        for(i = 0; i < slen; i++) {
            if(str[i] == '0') {
                DP[i+1] = max(DP[i+1], DP[i]);
            } else {
                tmp = 0;
                for(j = i; j < slen; j++) {
                    tmp = tmp*10 + str[j]-'0';
                    if(tmp > limit)
                        break;
                    //cout << DP[i]+tmp << " ";
                    DP[j+1] = max(DP[j+1], DP[i]+tmp);
                }
            }
        }
        cout << DP[slen] << "\n";
    }
    return 0;
}
