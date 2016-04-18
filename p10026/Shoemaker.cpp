#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int casenumber=0;
int N=0;

struct Job {
    int id;
    int days;
    int fines;
};

vector<Job> job;

void storeinput () {
    cin >> N;
    vector<Job> temp(N);
    for(int i=0;i<N;i++) {
        temp[i].id = i+1;
        cin >> temp[i].days >> temp[i].fines;
    }
    job = temp;
}

void printoutput() {
    cout << job[0].id;
    for(int i=1;i<N;i++) {
        cout << " " << job[i].id;
    }
    cout << "\n";
}

bool compare(Job j1, Job j2) {
    return j1.fines*j2.days > j2.fines*j1.days;
}

void processing() {
    sort(job.begin(), job.end(), compare);
}

int main() {
    cin >> casenumber;
    for(int i=0;i<casenumber;i++) {
        storeinput();
        processing();
        printoutput();
        if(i<casenumber-1) {
            cout << "\n";
        }
    }

    return 0;
}
