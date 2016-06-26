#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

int KMP(string& s,int len){ //doing the KMP algorithm
    /*in order to avoid the run time problem
     *I would rather use the <vector> instead of
     *the <array>
     */
    vector<int> Failure_Function;
    Failure_Function.assign(len,-1);
    int j=-1;
    for(int i=1;i<len;i++){
        while(j>=0 && s[i]!=s[j+1]) {
            j = Failure_Function[j];
        }
        if(s[i]==s[j+1])
            j++;
        Failure_Function[i] = j;
    }
    return j;
}

int main(){
    string input="";
    while(getline(cin,input)){
        if(input==".")
            break;
        int len = input.length();
        int f = KMP(input,len);
        if(f==-1)
            cout << "1" ;
        else
            cout << len/(len-f-1);
        cout << "\n";
    }

    return 0;
}
