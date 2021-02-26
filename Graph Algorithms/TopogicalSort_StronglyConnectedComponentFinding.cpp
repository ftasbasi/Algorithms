//
// Created on 10.12.2020.
//
#include <iostream>
#include <climits>
#include <cmath>
#include <utility>
#include <vector>
#include <stack>
using namespace std;
#define ROW 7
#define COLUMN 7
int flag=0;
void addEdge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
}

void CycleDetect(int u,vector<int>adj[],int*& colorIn){
    colorIn[u]=1;//making gray
    int adjSize=adj[u].size();
    for (int j=0;j<adjSize;j++)
    {
        if (colorIn[adj[u][j]]==0){
            CycleDetect(adj[u][j],adj,colorIn);
        }
        if(colorIn[adj[u][j]]==1){
            flag=1;
        }
    }

    colorIn[u]=2;
}
void DFS(int v,vector<int>adj[], vector<bool> &visited, vector<int> &departure, int &time)
{
    visited[v] = true;
    // time++;    // arrival time of vertex v
    int adjSize=adj[v].size();
    for (int j=0;j<adjSize;j++)
    {
        if (!visited[adj[v][j]]){
            DFS(adj[v][j],adj, visited, departure, time);
        }
    }
    // set departure time of vertex v
    departure[++time] = v;
}
void topologicalSORT(int n,vector<int>adj[],vector<int>& topSort){
    int size=n;
    vector<int> departure(size, -1);

    // Mark all the vertices as not visited
    vector<bool> visited(size, false);
    int time = -1;

    // perform DFS on all unvisited vertices
    for(int i = 0; i < size; i++)
        if(!visited[i])
            DFS(i,adj, visited, departure, time);

    // Put vertices in topological order
    for(int i = size - 1; i >= 0; i--){
        topSort.push_back(departure[i]);
    }
}

void transposeGraph(vector<int> adj[],
                    vector<int> transpose[], int v){

    for (int i = 0; i < v; i++){
        int adjSize=adj[i].size();
        for (int j = 0; j < adjSize; j++){


            addEdge(transpose, adj[i][j], i);
        }
    }
}
void fillOrder(int v,vector<int> adj[], bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    int adjSize=adj[v].size();
    for (int j = 0; j < adjSize; j++)
        if (!visited[adj[v][j]])
            fillOrder(adj[v][j],adj, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}
void DFSHelper(int v, vector<int> adj[], bool visited[], vector<int>& tree)
{

    // Mark the current node as visited and print it
    visited[v] = true;
    tree.push_back(v);
    //cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    int adjSize=adj[v].size();
    for (int j = 0; j < adjSize; j++)
        if (!visited[adj[v][j]])
            DFSHelper(adj[v][j],adj, visited,tree);
}
void findSCCs(int size,vector<int> adj[], vector<vector<int>>& scc){

    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[size];
    for(int i = 0; i < size; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < size; i++)
        if(visited[i] == false)
            fillOrder(i,adj,visited,Stack);

    vector<int> transposedAdj[size];
    transposeGraph(adj, transposedAdj, size);

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < size; i++)
        visited[i] = false;

    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        vector<int> tree;
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            DFSHelper(v, transposedAdj ,visited,tree);
            //cout << endl;
        }
        //tree.push_back(v);
        if (!tree.empty()){

            scc.push_back(tree);
        }

        //scc.push_back(v);
    }
}
void SCC_TopSort (int**& graph, int n, vector<vector<int>>& scc, vector<int>& topSort)
{   flag=0;
    int size=n;
    int color[size]={0};
    int *colorOut=color;

    vector<int>adj[size];

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {
            if (graph[i][j]){
                adj[i].push_back(j);
            }
        }
    }

    CycleDetect(0,adj,colorOut);
    if(flag==0){
        //cout<<"NO CYCLE , TOPSORT DAG"<<endl;
        topologicalSORT(size,adj,topSort);

    }
    else{
        //cout<<"CYCLE FOUND , FIND SCCs"<<endl;
        findSCCs(size,adj,scc);

    }


}
int main(){
    int** graphOUT = new int*[ROW];
    vector<vector<int>> sccs;
    vector<int> topologicalSorted;
    for (int i = 0; i < ROW; i++)
        graphOUT[i] = new int[COLUMN];
    //int **arrayin = (int **)malloc(r * c * sizeof(int));
    int graph[ROW][COLUMN]= { { 0, 1 ,0, 1, 0, 0, 0 },

                              { 0, 0, 1, 0, 0, 0, 0 },

                              { 1, 0, 0, 0, 0, 0, 0 },

                              { 0, 0, 0, 0, 1, 0, 0 },

                              { 0, 0, 0, 0, 0, 1, 0 },

                              { 0, 0, 0, 0, 0, 0, 1 },

                              { 0, 0, 0, 0, 1, 0, 0} };

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            graphOUT[i][j]=graph[i][j];
        }
    }


    SCC_TopSort(graphOUT,ROW,sccs,topologicalSorted);

    if(!sccs.empty()) {
        for (int i = 0; i < sccs.size(); i++) {
            for (int j = 0; j < sccs[i].size(); j++) {
                cout << sccs[i][j] << " ";
            }
            cout << endl;
        }
    }
    if(!topologicalSorted.empty()){
        for (int i = 0; i < topologicalSorted.size(); i++) {

                cout << topologicalSorted[i]+1 << " ";
            }

    }


    return 0;
}