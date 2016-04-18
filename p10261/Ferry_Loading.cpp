#include <iostream>
#include <queue>
using namespace std;

int w[2005], carnumber, length, sum[2005], maxcar, maxlength, table[2005][10005];
queue<int> q;

void storeinput() {
    cin >> length;
    carnumber=1;
    maxcar=0, maxlength=0;
    while(cin >> w[carnumber] && w[carnumber]!=0) {
        sum[carnumber] = sum[carnumber-1] + w[carnumber];
        carnumber++;
    }
}

void initialize() {
    length *= 100;
    for(int i=0;i<=carnumber;i++) {
        for(int j=0;j<=length;j++) {
            table[i][j]=0;
        }
    }
}

void operation() {
    table[0][0]=1;
    for(int i=1;i<carnumber;i++) {
        for(int j=0;j<=length;j++) {
            if( (j>=w[i] && table[i-1][j-w[i]]==1) || (sum[i]-j<=length && table[i-1][j]==1) ) {
                maxcar=i;
                maxlength=j;
                table[i][j]=1;
                /*cout << "table[" << i << "][" << j << "]: " << table[i][j]
                << " maxcar: " << maxcar << " maxlength: " << maxlength << "\n";*/
            }
        }
    }
    cout << maxcar << "\n";
}

void track(int x, int y) {
    if(x-1<0)
        return;
    if(table[x-1][y]==1 && sum[x]-y<=length){
        track(x-1, y);
        q.push(1);
    } else if(y>=w[x] && table[x-1][y-w[x]]==1) {
        track(x-1, y-w[x]);
        q.push(0);
    }
}

void printoutput() {
    int first;
    if(!q.empty())
        first = q.front();
    while(!q.empty()) {
        int element = q.front();
        if(element == first)
            cout << "port\n";
        else
            cout << "starboard\n";
        q.pop();
    }
}

int main() {
    int numberofcase;
    cin >> numberofcase;
    for(int i=0;i<numberofcase;i++) {
        if(i>0)
            cout << "\n";
        storeinput();
        initialize();
        operation();
        track(maxcar, maxlength);
        printoutput();
    }

    return 0;
}
