#include <iostream>
#include <algorithm>
using namespace std;

/* define the structure of Road which
 * contains 3 fields u, v, c
 */
struct Road {
    int u,v,c;
}road[10001];

/*union sets*/
int p[101], Rank[101];

void Init(int n);
int Cmp(Road a, Road b);
int Find(int n);
void Union(int a, int b);
int Kruskal(int V, int E);

int main() {
   int Case;
   cin >> Case;
   for(int i=1;i<=Case;i++) {
       int n,m;
       cin >> n >> m;
       for(int i=0;i<m;i++)
           cin >> road[i].u
               >> road[i].v
               >> road[i].c;
       cout << "Case #" << i << ": " << Kruskal(n,m) << "\n";
   }
}

void Init(int n) {
    for(int i=0;i<n;i++) {
        p[i]=i;
        Rank[i]=0;
    }
}

int Cmp(Road a, Road b) {
    return a.c > b.c;
}

int Find(int n) {
    return p[n]==n ? n:(p[n]=Find(p[n]));
}

/* when we need to do union operation
 * we can try our best to reduce the
 * depth of the forest
 */
void Union(int a, int b) {
    a=Find(a);
    b=Find(b);
    if(Rank[a]>Rank[b])
        p[b]=a;
    else if(Rank[a]<Rank[b])
        p[a]=b;
    else {
        p[a]=b;
        Rank[b]++;
    }
}

int Kruskal(int V, int E) {

    Init(V);

    /* we want to sort the weight in decreasing order
     * so, if Cmp return false means the former operand
     * is smaller than the later one and we need to swap it
     */
    sort(road, road+E, Cmp);

    int capacity=0;
    for(int i=0,j=0;i<E && j<V-1;i++) {

        /* if it will produce a cycle then discard it
         * until it won't produce a cycle
         */
        while(Find(road[i].u)==Find(road[i].v))
            i++;

        Union(road[i].u, road[i].v);

        /*cout << "start:" << road[i].u
             << " end:" << road[i].v
             << " weight:" << road[i].c
             << "\n";
        */

        j++;
        if(j==V-1)
            capacity=road[i].c;

    }

    return capacity;
}
