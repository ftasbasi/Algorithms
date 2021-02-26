
// Created by palo on 23.12.2020.
//

// C++ Program for Floyd Warshall Algorithm
#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define V 4

/* Define Infinite as a large enough
value.This value will be used for
vertices not connected to each other */
#define INF INT_MAX

// A function to print the solution matrix
void printSolution(int**& dist);
// Print the shortest path
void printPath(vector<int> path)
{
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << " -> ";
    cout << path[n - 1] << endl;
}
vector<int> constructPath(int u,int v, int**& nextIn)
{
    // If there's no path between
    // node u and v, simply return
    // an empty array

    //cout<<"costttt:"<<costFactor<<endl;
    if (nextIn[u][v] == -1)
        return {};
    // Storing the path in a vector
    vector<int> path = { u };
    while (u != v) {
        //cout<<dist[u][v]<<endl;
        u = nextIn[u][v];
        path.push_back(u);
    }

    return path;
}
// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall (int**& dist,int**& next,int v)
{
    /* dist[][] will be the output matrix
    that will finally have the shortest
    distances between every pair of vertices */
    int i, j, k;


    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < v; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < v; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < v; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] <= dist[i][j]){
                    if( i == k ) continue;
                    dist[i][j] = dist[i][k] + dist[k][j];
                    // update parent
                    next[i][j]=next[i][k];
                }
            }
        }
    }

    // Print the shortest distance matrix
    //return dist;

    //printPath(constructPath(uIn,vIn,next));
}

/* A utility function to print solution */
void printSolution(int**& dist)
{
    cout<<"The following matrix shows the shortest distances"
          " between every pair of vertices \n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout<<"INF"<<"     ";
            else
                cout<<dist[i][j]<<"     ";
        }
        cout<<endl;
    }
}

bool isInclude( vector<pair<int,int>> v , pair<int,int> x )
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if( v[i] == x ) return true;
    }
    return false;
}

int minCost(int**& graph, int v, int s1, int s2, int d1, int d2, int A, int B)
{
    int** dist = new int*[v];

    for (int i = 0; i < v; i++)
        dist[i] = new int[v];

    int** next=new int*[v];
    for (int i = 0; i < v; i++)
        next[i] = new int[v];


    /* Initialize the solution matrix same
    as input graph matrix. Or we can say
    the initial values of shortest distances
    are based on shortest paths considering
    no intermediate vertex. */
    for (int i = 0; i < v; i++){
        for (int j = 0; j < v; j++) {
            dist[i][j] = graph[i][j];

            if (dist[i][j]==INF){
                next[i][j]=-1;
            } else{
                next[i][j]=j;
            }
        }
    }
    // Print the solution
    floydWarshall(dist,next,v);


    //buraya kadar all shortest pathleri bulup dist tablosuna koyuyor

    vector<int> path1 = constructPath(s1,d1,next);
    vector<int> path2 = constructPath(s2,d2,next);

    vector<pair<int,int>> pairs1;
    vector<pair<int,int>> pairs2;

    for (unsigned int i = 0; i < path1.size() - 1; i++)
    {
        pair<int,int> temp = make_pair( path1[i] , path1[i+1] );
        pairs1.push_back(temp);
    }

    for (unsigned int i = 0; i < path2.size() - 1; i++)
    {
        pair<int,int> temp = make_pair( path2[i] , path2[i+1] );
        pairs2.push_back(temp);
    }

    int totalCost = 0;

    /*
    for (unsigned int i = 0; i < pairs1.size(); i++)
    {
        std::vector<pair<int,int>>::iterator position = std::find(pairs2.begin(), pairs2.end(), pairs1[i]);
        // if pairs2 contains the item
        if ( position != pairs2.end() )
        {
            totalCost += dist[pairs1[i].first][pairs1[i].second] * B;
            pairs2.erase( position );
        }
        else
        {
            totalCost += dist[pairs1[i].first][pairs1[i].second] * A;
        }
    }


    for (unsigned int i = 0; i < pairs2.size(); i++)
    {
        totalCost += dist[pairs2[i].first][pairs2[i].second] * A;
    }

   */
    int togetherCost = 0;
    for (unsigned int i = 0; i < pairs1.size(); i++)
    {
        // if pairs2 contains the item
        if ( isInclude( pairs2 , pairs1[i] ) )
        {
            togetherCost += dist[pairs1[i].first][pairs1[i].second] * (2*A - B);
            totalCost += dist[pairs1[i].first][pairs1[i].second] * A;
        }
        else
        {
            totalCost += dist[pairs1[i].first][pairs1[i].second] * A;
        }
    }


    for (unsigned int i = 0; i < pairs2.size(); i++)
    {
        totalCost += dist[pairs2[i].first][pairs2[i].second] * A;
    }

    // TOTAL - (2A - B)
    totalCost = totalCost - togetherCost;

    cout << totalCost << endl;

    return totalCost;
}

// Driver code
int main()
{
    /* Let us create the following weighted graph
            10
    (0)------->(3)
        |     /|\
    5 |     |
        |     | 1
    \|/     |
    (1)------->(2)
            3     */
    int** graph = new int*[4];
    for (int i = 0; i < 4; i++)
    {
        graph[i] = new int[4];
    }

    graph[0][0] = 0;
    graph[0][1] = 1;
    graph[0][2] = 2;
    graph[0][3] = INF;
    graph[1][0] = INF;
    graph[1][1] = 0;
    graph[1][2] = 1;
    graph[1][3] = 2;
    graph[2][0] = INF;
    graph[2][1] = INF;
    graph[2][2] = 0;
    graph[2][3] = 1;
    graph[3][0] = INF;
    graph[3][1] = INF;
    graph[3][2] = INF;
    graph[3][3] = 0;

    int s1=0;
    int d1=2;
    int s2=1;
    int d2=3;

    int A = 3,B = 5;


    minCost(graph , 4, s1, s2, d1,  d2,  A,  B);

    /*
    if (s1<s2){
        if (d1>s2){

            constructPath(s1,s2,next,costwithK1,A,dist);
            constructPath(s2,d1,next,costwithK1,B,dist);
            constructPath(s1,d1,next,costwithoutK1,A,dist);
            if (costwithK1<=costwithoutK1){
                constructPath(s1,s2,next,totalCost,A,dist);
                constructPath(s2,d1,next,totalCost,B,dist);
            } else{
                constructPath(s2,d1,next,totalCost,A,dist);
                constructPath(s1,d1,next,totalCost,A,dist);
            }
            constructPath(d1,d2,next,totalCost,A,dist);

        }
    } else{
        if (d2>s1){

            constructPath(s1,s2,next,costwithK1,A,dist);
            constructPath(s2,d1,next,costwithK1,B,dist);
            constructPath(s1,d1,next,costwithoutK1,A,dist);
            if (costwithK1<=costwithoutK1){
                constructPath(s1,s2,next,totalCost,A,dist);
                constructPath(s2,d1,next,totalCost,B,dist);
            } else{
                constructPath(s2,d1,next,totalCost,A,dist);
                constructPath(s1,d1,next,totalCost,A,dist);
            }
            constructPath(d1,d2,next,totalCost,A,dist);

        }
    }

    cout<<"Cost with    K:"<<totalCost<<endl;
    cout<<"Cost without K:"<<seperateCost<<endl;
    */
    return 0;
}