//
// Created by palo on 17.12.2020.
//
#include <iostream>
#include <climits>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;
#define SIZEE1 4
#define SIZEE2 5
#define SIZEE3 6

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[],int n)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++){
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}



void SingleSourceShortestPath(int**& times, int**& costs, int n, int src, int dest, vector<pair<int,int>>& goodies, vector<int>& cost_path) {

    int parent[n];//array to store constructed shortest path

    int dist[n]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[n]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    parent[src] = -1;
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;

    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    //bool isSet = false;
    // Find shortest path for all vertices
    bool goodieTaken= false;
    int goodieValue = 0;
    for (int count = 0; count < n - 1; count++) {

        goodieTaken = false;

        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, n - 1);


        // Mark the picked vertex as processed

        sptSet[u] = true;
        cost_path.push_back(u);
        for (int i = 0; i < (int)goodies.size(); ++i) {
            if (goodies[i].first == u) {
                dist[u]-=goodies[i].second;
                goodies.erase(goodies.begin()+1);
                goodieTaken= true;
                goodieValue = goodies[i].second;

                break;
            }
        }

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++) {

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            // !sptSet[v] &&

            if ( times[u][v] && dist[u] != INT_MAX
                 && dist[u] + costs[u][v] * times[u][v] < dist[v]) {

                //if (goodieTaken && dist[v]!=INT_MAX ){
                if (goodieTaken && dist[v]!=INT_MAX ){

                    sptSet[v]= false;
                    dist[v] = dist[u] + costs[u][v] * times[u][v] ;

                    if(parent[v] != src)
                    {
                        parent[v] = u;
                    }


                }
                else
                {
                    dist[v] = dist[u] + costs[u][v] * times[u][v];
                    if(parent[v] != src)
                    {
                        parent[v] = u;
                    }
                }




            }
        }


    }
    if(cost_path.at(cost_path.size()-1)!=dest){
        cost_path.push_back(dest);
    }
    vector<int> temp;

    int index = dest;
    while(parent[index] != -1)
    {
        temp.push_back(parent[index]);
        index = parent[index];
    }
    temp.push_back(src);



    for (int k=0;k<parent)
    cost_path.insert(cost_path.begin(), dist[dest]);

}
int main(){
    int** timesOUT1 = new int*[SIZEE1];
    int** costOUT1 = new int*[SIZEE1];

    vector<pair<int,int>> goodiesOUT1;
    vector<int> cost_pathOUT1;
    //vector<vector<int>> sccs;
    //vector<int> topologicalSorted;
    for (int i = 0; i < SIZEE1; i++) {
        timesOUT1[i] = new int[SIZEE1];
        costOUT1[i] = new int[SIZEE1];
    }



    int** timesOUT2= new int*[SIZEE2];
    int** costOUT2=new int*[SIZEE2];

    vector<pair<int,int>> goodiesOUT2;
    vector<int> cost_pathOUT2;
    //vector<vector<int>> sccs;
    //vector<int> topologicalSorted;
    for (int i = 0; i < SIZEE2; i++) {
        timesOUT2[i] = new int[SIZEE2];
        costOUT2[i] = new int[SIZEE2];
    }



    int** timesOUT3 = new int*[SIZEE3];
    int** costOUT3 = new int*[SIZEE3];

    vector<pair<int,int>> goodiesOUT3;
    vector<int> cost_pathOUT3;
    //vector<vector<int>> sccs;
    //vector<int> topologicalSorted;
    for (int i = 0; i < SIZEE3; i++) {
        timesOUT3[i] = new int[SIZEE3];
        costOUT3[i] = new int[SIZEE3];
    }




    int times1[SIZEE1][SIZEE1]= { { 0, 2 ,0, 1},

                               { 2, 0, 1, 2 },

                               { 0, 1, 0, 3 },

                               { 1, 2, 3, 0 } };
    int costs1[SIZEE1][SIZEE1]= { { 0, 10 ,0, 5},

                               { 10, 0, 2, 9 },

                               { 0, 2, 0, 7 },

                               { 5, 9, 7, 0 } };

    goodiesOUT1={  };

    int times2[SIZEE2][SIZEE2]= { { 0, 1, 3, 0, 0 },
                                 { 1, 0, 1, 1, 0 },

                                 { 3, 1, 0, 0, 2 },

                                 { 0, 1, 0, 0, 3 },

                                 { 0 , 0, 2, 3, 0 } };
    int costs2[SIZEE2][SIZEE2]= { { 0, 10, 5, 0, 0 },

                                 { 10, 0, 2, 5, 0 },

                                 { 5, 2, 0, 0, 3 },

                                 { 0, 5, 0, 0, 2 },

                                 { 0, 0, 3, 2, 0} };
    goodiesOUT2={ std::pair<int,int>(2, 10) };

    int times3[SIZEE3][SIZEE3]= { { 0, 1, 2, 0, 0, 0 },

                                  { 1, 0, 1, 3, 2, 0 },

                                  { 2, 1, 0, 0, 3, 0 },

                                  { 0, 3, 0, 0, 3, 4 },

                                  { 0, 2, 3, 3, 0, 2 },

                                  { 0, 0, 0, 4, 2, 0 } };
    int costs3[SIZEE3][SIZEE3]={ { 0, 6, 4, 0, 0, 0 },

                                 { 6, 0, 1, 7, 5, 0 },

                                 { 4, 1, 0, 0, 2, 0 },

                                 { 0, 7, 0, 0, 4, 3 },

                                 { 0, 5, 2, 4, 0, 5 },

                                 { 0, 0, 0, 3, 5, 0 } };

    goodiesOUT3={std::pair<int,int>(2, 10),std::pair<int,int>(3, 5)};



    int n1=SIZEE1;
    int srcOUT1=0;
    int destOUT1=2;

    int n2=SIZEE2;
    int srcOUT2=0;
    int destOUT2=3;

    int n3=SIZEE3;
    int srcOUT3=0;
    int destOUT3=5;



    for (int i = 0; i < SIZEE1; ++i) {
        for (int j = 0; j < SIZEE1; ++j) {
            timesOUT1[i][j]=times1[i][j];
            costOUT1[i][j]=costs1[i][j];
        }
    }

    for (int i = 0; i < SIZEE2; ++i) {
        for (int j = 0; j < SIZEE2; ++j) {
            timesOUT2[i][j]=times2[i][j];
            costOUT2[i][j]=costs2[i][j];
        }
    }
    for (int i = 0; i < SIZEE3; ++i) {
        for (int j = 0; j < SIZEE3; ++j) {
            timesOUT3[i][j]=times3[i][j];
            costOUT3[i][j]=costs3[i][j];
        }
    }
/*
    SingleSourceShortestPath(timesOUT1,costOUT1,n1,srcOUT1,destOUT1,goodiesOUT1,cost_pathOUT1);
    for (int i = 0; i < (int)cost_pathOUT1.size(); ++i) {
        cout<<cost_pathOUT1.at(i)<<" ";
    }


    SingleSourceShortestPath(timesOUT2,costOUT2,n2,srcOUT2,destOUT2,goodiesOUT2,cost_pathOUT2);
    for (int i = 0; i < (int)cost_pathOUT2.size(); ++i) {
        cout<<cost_pathOUT2.at(i)<<" ";
    }

    SingleSourceShortestPath(timesOUT3,costOUT3,n3,srcOUT3,destOUT3,goodiesOUT3,cost_pathOUT3);
        for (int i = 0; i < (int)cost_pathOUT3.size(); ++i) {
        cout<<cost_pathOUT3.at(i)<<" ";
    }




*/


    SingleSourceShortestPath(timesOUT1,costOUT1,n1,srcOUT1,destOUT1,goodiesOUT1,cost_pathOUT1);
    for (int i = 0; i < (int)cost_pathOUT1.size(); ++i) {
        cout<<cost_pathOUT1.at(i)<<" ";
    }

    cout<<endl;
    SingleSourceShortestPath(timesOUT2,costOUT2,n2,srcOUT2,destOUT2,goodiesOUT2,cost_pathOUT2);
    for (int i = 0; i < (int)cost_pathOUT2.size(); ++i) {
        cout<<cost_pathOUT2.at(i)<<" ";
    }
    cout<<endl;
    SingleSourceShortestPath(timesOUT3,costOUT3,n3,srcOUT3,destOUT3,goodiesOUT3,cost_pathOUT3);
    for (int i = 0; i < (int)cost_pathOUT3.size(); ++i) {
        cout<<cost_pathOUT3.at(i)<<" ";
    }
    cout<<endl;



    return 0;
}
