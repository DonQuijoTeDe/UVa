#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <map>
#include <queue>
using namespace std;

map<string,vector<string> > graph;

bool doublet(string a,string b){//to check whether the two words are doublet
    int counter=0;
    for(int i=0;i<a.length();i++)
        if(a[i]!=b[i] && ++counter>1) return false;
    return true;
}

void buildgraph(vector<string> src){
    for(int i=0;i<src.size();i++)
        for(int j=i+1;j<src.size();j++)
            if(doublet(src[i],src[j])){
                graph[src[i]].push_back(src[j]);
                graph[src[j]].push_back(src[i]);
            }


}

vector<string> breadfirstsearch(string src,string dest){
    queue<string> q;
    map<string,string> parent;
    bool found=false;
    q.push(src);
    parent[src] = "";
    while(!q.empty()){ //the algorithm of BFS
        string v = q.front();
        q.pop();
        for(int i=0;i<graph[v].size();i++){
            if(parent.find(graph[v][i])==parent.end()){
                parent[graph[v][i]] = v;
                q.push(graph[v][i]);
                if(graph[v][i]==dest){
                    found=true;
                    break;
                }
            }
        }
        if(found==true) break;
    }
    vector<string> tempresult;
    if(!found){
        tempresult.push_back("No solution.");
        return tempresult;
    }
    string temp = dest;
    do{
        tempresult.push_back(temp);
        temp = parent[temp];
    }while(tempresult.back()!=src);
    return tempresult;
}

int main(){
    char input[16];
    bool builtgraph[17]={false};
    vector<string> dictionary[17];
    int counter=0;
    while(true){ // build the dictionary
        gets(input);
        if(strlen(input)==0) break;
        dictionary[strlen(input)].push_back(input);
    }
    while(gets(input)){
        counter++;
        if(counter>1) cout << "\n";
        string src,dest;
        stringstream s(input);
        s >> src >> dest;
        if(src.length()!=dest.length()){
            cout << "No solution.\n";
        } else {
            if(!builtgraph[src.length()]){
                builtgraph[src.length()] = true;
                buildgraph(dictionary[src.length()]); //build the graph
            }
            vector<string> results = breadfirstsearch(src,dest); //doing the BFS
            for(int i=results.size()-1;i>=0;i--)
                cout << results[i] << "\n";
        }
    }
    return 0;
}
