#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main() {
    int counter=0;//for output use
    double output[1000];
    while(true){
        int number=0;
        cin >> number;
        double expense[number];//input expense
        double positive=0,negative=0,total=0,average=0;
        if(number==0){
            for(int i=0;i<counter;i++){
                cout << "$" << fixed << setprecision(2) << output[i] << "\n";
            }
            break;
        }
        for(int i=0;i<number;i++){
            cin >> expense[i];
            total+=expense[i];
        }
        average=floor(total/number*100+0.5)/100;//there is the most important part
        for(int i=0;i<number;i++){
            if(average>expense[i]){
                positive+=average-expense[i];
                //cout << "positive: " <<  floor((average-expense[i])*100)/100 << "\n";
            }
            else if(average<expense[i]){
                negative+=expense[i]-average;
                //cout << "negative: " <<  floor((expense[i]-average)*100)/100 << "\n";
            }
        }
        if(positive<=negative){
            output[counter]=positive;
        } else if(positive>negative){
            output[counter]=negative;
        }
        counter++;
    }
}
