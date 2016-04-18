#include <iostream>
#include <vector>
using namespace std;

int main(){
    int counter=0;
    int output[50][100][100]={0};
    vector<int> index[50];
    while(true){
        int height=0,width=0;
        char input[100][100]={0};
        cin >> height;
        cin >> width;
        if(height==0||width==0){
            for(int i=0;i<counter;i++){//use some skills to output the result
                if(i!=0) cout << "\n";
                cout << "Field #" << i+1 << ":\n";
                vector<int>::iterator iter = index[i].begin();
                int value[2]={0};
                for(int temp=0;iter!=index[i].end();iter++,temp++){
                    value[temp]=*iter;
                }
                for(int j=0;j<value[0];j++){
                    for(int k=0;k<value[1];k++){
                        if(output[i][j][k]>8) cout << '*';
                        else cout << output[i][j][k];
                    }
                    cout << "\n";
                }
            }
            break;
        }
        index[counter].push_back(height);
        index[counter].push_back(width);
        for(int i=0;i<height;i++){ //to get input value
            for(int j=0;j<width;j++){
                cin >> input[i][j];
            }
        }
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(input[i][j]=='*'){ //if the char is the mine('*'),then we need
                    output[counter][i][j]=10; //to check its eight directions
                    if(i>=1&&j>=1) output[counter][i-1][j-1]++; //upper left
                    if(i>=1&&j>=0) output[counter][i-1][j]++; //upper
                    if(i>=1&&(j+1)<width) output[counter][i-1][j+1]++; //upper right
                    if(i>=0&&j>=1) output[counter][i][j-1]++; //left
                    if(i>=0&&(j+1)<width) output[counter][i][j+1]++; //right
                    if(i+1<height&&j>=1) output[counter][i+1][j-1]++; //lower left
                    if((i+1)<height&&j>=0) output[counter][i+1][j]++; //lower
                    if((i+1)<height&&(j+1)<width) output[counter][i+1][j+1]++; //lower right
                }
            }
        }
        counter++;
    }
    return 0;
}
