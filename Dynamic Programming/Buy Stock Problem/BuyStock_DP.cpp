#define DEBUG
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)
#include <iostream>
#include <random>
#include <ctime>
#include <utility>
#include <climits>
#include <cmath>
#include <vector>
#define TIMESTEP 20
#define STOCKSIZE 101
using namespace std;
// for example usage of DEBUG macros check test.cpp

int max(int a, int b)
{
    return a > b ? a : b;
}
// Function to sort the array in O(N)
int counter=0; //it should be O(n1*n2)
int BuyStocksHelper (int**& market, int n1, int n2, vector<int>& solution,int**& table)
{
    counter++;
    if (n2<1) return -50;
    /*
     *
         if (n2==1 && n1==1){

        return market[0][0];
    }
    if (n1==1 && n2>1){
        int maxStep1=-50;
        for (int i = 0; i < n2; ++i) {
            maxStep1=max(market[0][i],maxStep1);
        }
        return maxStep1;
    }
     *
     * */
    if (n1==1){

        int maxStep1=-50;
        int lastItem=-1;
        for (int i = 0; i < n2; ++i) {
            if (market[0][i]>maxStep1){
                maxStep1=market[0][i];
                table[0][i]=maxStep1;
                lastItem=i;
            }
        }
        if (solution.empty()){
            solution.push_back(lastItem);

        }
        return maxStep1;
    }

    int t1;

    if(table[n1-1][n2-1]==INT_MIN){
        t1=market[n1-1][n2-1]+BuyStocksHelper(market,n1-1,n2-1,solution,table);
        table[n1-1][n2-1]=t1;
    } else{
        t1=table[n1-1][n2-1];
    }

    int t2;
    if (table[n1-1][n2-2]==INT_MIN){
        t2=market[n1-1][n2-2]+BuyStocksHelper(market,n1-1,n2-2,solution,table);
        table[n1-1][n2-2]=t2;
    } else{
        t2=table[n1-1][n2-2];
    }

    if(t1>t2)
    {
        solution.push_back(n2-1);


    }


    return max(t1,t2);
}
int BuyStocks(int**& market, int n1, int n2, vector<int>& solution){

    int** table = new int*[n1];
    for(int i = 0; i < n1; i++){
        table[i] = new int[n2];
        for(int j=0; j<2 ; j++)
        {
            table[i][j] = INT_MIN;
        }
    }

    int t1;

        t1=market[n1-1][n2-1]+BuyStocksHelper(market,n1-1,n2-1,solution,table);

    int t2;

        t2=market[n1-1][n2-2]+BuyStocksHelper(market,n1-1,n2-2,solution,table);

    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            cout<<table[i][j]<<",";
        }
        cout<<endl;
    }
    free(table);
    return max(t1,t2);
}
int main(){

    vector<int> myvector;


    int** A = new int*[TIMESTEP];

    for (int i = 0; i < TIMESTEP; i++)
        A[i] = new int[STOCKSIZE];


   /* int market[TIMESTEP][STOCKSIZE]  = { { 7, 23, -5, -24, 16 },
                       { 5, 21, -4, 10, 23 },
                       { -21, 5, -4, -20, 20 }};
*/
    int market[TIMESTEP][STOCKSIZE]  = { {7, 39, -45, 10, 18, 35, 44, -32, 23, 46, -17, -22, -4, -46, 21, 3, 5, 6, 45, -41, -20, -21, -48, 40, 14, 15, 0, 22, -30, -18, -24, 25, 50, 32, -33, 47, 43, -9, -26, 27, 48, -37, -31, -2, -13, 36, -50, -10, -14, -5, 38, -28, -42, -36, 11, 37, -8, -47, -34, 31, -7, -38, 9, 4, 17, -11, -16, 8, -23, 33, -19, 30, -49, -44, -29, -12, 26, -15, -39, 12, 28, 34, 1, 29, -3, -1, 41, 19, -6, 49, 20, -25, -27, 16, 13, -35, 24, -40, 42, -43, 2},
                                         {7, 11, 39, 48, -26, -19, -34, 31, -23, -10, -8, 30, -41, -33, 4, -16, 28, 13, -36, 20, -22, -28, 5, -46, -14, 36, 34, -15, -7, -11, -44, -25, -32, 14, 24, 8, 40, -1, 18, 1, -49, -50, 2, -18, -21, 25, -39, -27, 29, 19, -47, 22, 9, -4, -5, -3, 33, -37, -42, 42, -9, 44, 6, 47, 15, -17, 38, -38, -20, 45, -12, 10, 3, -24, -45, 32, 46, -2, -30, 43, 41, -6, -29, -31, 23, 49, -13, -48, 16, -40, 37, 12, 50, 17, 26, 35, 21, 0, -35, -43, 27},
                                         {-14, 44, 2, 25, -27, -47, 24, 49, -30, 45, -50, -38, 33, 50, -28, 35, -48, 29, 16, 4, -45, 28, -19, -17, -49, 5, 34, -15, -1, -35, -8, 6, -37, -32, -43, -22, 40, 13, -36, -26, -6, -18, 19, -13, -33, -40, -7, 10, 17, -34, 22, -42, 7, 46, 3, -44, 43, 18, 21, -21, -11, -20, -5, -10, -31, -16, 37, -2, -46, 36, -39, 15, 48, 1, 0, 30, 42, -9, 38, -41, 20, -4, 32, -29, 8, 39, 12, 9, 23, -23, -3, 41, 26, 31, 47, 27, -12, -24, 11, 14, -25},
                                         {6, 17, 47, -24, -20, 24, 43, -39, -14, 9, -50, -22, -2, -32, 45, 3, -42, 30, 41, 35, -13, -17, -27, -11, -8, 7, 31, 8, -43, 27, -7, -9, 44, 23, 15, 25, 32, -28, 12, -34, -36, -18, -33, 34, 50, -12, 20, -31, -19, 33, 5, 37, -1, -23, 40, -40, 28, 11, -29, -41, 39, 46, -35, 16, -3, -38, -26, -21, 14, 42, -10, -30, 19, -44, 49, 22, -6, -5, 1, 2, -47, 38, 21, -46, -25, -4, 4, -37, -49, 18, 26, -45, 48, -48, -16, 29, 13, 10, 0, -15, 36},
                                         {-45, 26, 4, 16, 41, -8, 50, -39, 42, 35, 6, -9, -30, -47, 5, 43, -42, 46, -43, -49, 24, -11, -17, 14, -10, -34, 45, -32, 7, 47, -16, -3, 3, -27, 34, 28, 1, -23, -29, -41, -1, -48, 9, -24, -33, -19, 10, 48, 37, 30, -14, 21, -50, -18, 25, 33, 44, -35, -37, 32, 49, 20, 8, -40, -12, -36, 27, -22, -13, 22, -38, 12, 36, -5, -15, 29, 15, -25, 13, -28, 40, 18, 23, -46, 0, -2, 11, 38, -20, 31, -21, -26, 17, -31, 39, -6, 2, 19, -44, -4, -7},
                                         {-47, 3, -16, 17, -11, 29, 33, 2, -36, 25, -28, -23, 49, -32, 0, -10, -43, -21, 21, -18, 44, 47, -40, -37, 12, -14, -29, -9, -4, -33, 48, -5, -7, 50, 30, 39, -19, 42, -8, -13, -42, 37, -6, 34, -20, -26, -12, 41, 15, 1, -1, 32, -30, 5, -46, 13, 35, -17, 43, 7, 28, 26, 11, -22, 22, 14, 36, -48, 16, 38, -38, -2, 8, 6, 46, 4, 10, 31, -50, 45, -34, 27, 20, -15, -24, 24, -27, 40, -49, -25, 19, 9, -39, -35, -41, 18, -31, -45, -44, 23, -3},
                                         {41, 2, 43, 13, -12, -46, -28, 24, 39, 22, -3, 1, -18, 45, -21, -7, 46, -14, -40, 10, -25, 35, -35, 15, 25, -39, 40, -1, -13, 3, 16, 5, 48, 29, -32, -38, 4, 23, -34, 38, -31, 7, 9, -5, -47, 37, 47, -17, 42, 44, -10, -8, 33, -42, -23, -37, 18, 32, 21, 34, -4, -30, -24, -41, -16, 27, -48, -43, 14, 31, -26, 49, 8, 30, 36, -44, -33, -15, 17, -50, -20, -45, 0, -2, 11, 12, 26, -9, -27, 50, 28, -6, -49, 19, -36, -29, 20, -19, 6, -22, -11},
                                         {-43, -9, -38, 49, -37, 5, -5, 3, -13, 21, -4, 20, 2, 10, 13, 9, 0, 1, 34, -15, -18, 18, -23, 41, 28, 19, 44, -8, -36, 45, -6, 48, -45, -14, -44, -48, -50, 6, -42, 31, -32, 35, -12, 12, 43, 7, 37, 50, 40, -27, 32, 27, 46, -49, -19, -25, 33, -30, -34, 36, 15, -17, 42, -29, 26, 25, -47, -16, 22, -24, 17, 29, -40, 38, -7, 30, 23, 47, -11, -3, -20, -35, 39, -10, -39, -21, 8, -26, 16, -2, -28, -41, -1, -33, 11, -46, 4, 14, 24, -31, -22},
                                         {-4, -30, -42, 2, -48, -2, 0, -40, 1, 7, 13, 42, -18, -9, 20, -7, 26, 12, 41, -34, 33, -25, -16, -49, 48, 47, -26, 11, 34, -35, -22, -1, -33, -11, -28, 27, 43, 29, 46, -5, -45, -8, 38, -10, -14, -3, 50, 25, -6, -29, 3, -50, 22, 5, 10, 44, 32, 17, -13, 35, 31, 39, -32, 15, -24, 49, -12, 23, -19, -17, -27, -23, 9, -15, 40, 16, -36, -21, 6, 14, 4, -37, -44, -41, 28, 37, -43, -46, 18, -20, 19, -39, -38, -47, 24, 21, 30, 8, 36, -31, 45},
                                         {35, 20, -44, -4, 36, 9, 42, -46, -37, 2, -1, -8, -17, -25, -47, 22, -35, 25, -34, -29, 31, -40, 17, 21, -45, 10, -26, 34, 39, -39, 28, -49, 43, -7, -2, 7, -13, -33, -43, 8, 41, -6, -30, 19, 29, -21, -10, 37, -19, 49, 1, -31, 3, 38, 14, 16, 12, -27, 15, -3, -50, -22, 11, 47, -11, -5, 18, 50, 5, -9, -41, -20, 44, 33, 48, 26, 24, -32, -12, 0, -16, 46, -48, -42, -38, -24, -36, -18, 40, -15, 4, 13, -14, 45, 27, 6, -28, 30, 23, -23, 32},
                                         {7, 39, -45, 10, 18, 35, 44, -32, 23, 46, -17, -22, -4, -46, 21, 3, 5, 6, 45, -41, -20, -21, -48, 40, 14, 15, 0, 22, -30, -18, -24, 25, 50, 32, -33, 47, 43, -9, -26, 27, 48, -37, -31, -2, -13, 36, -50, -10, -14, -5, 38, -28, -42, -36, 11, 37, -8, -47, -34, 31, -7, -38, 9, 4, 17, -11, -16, 8, -23, 33, -19, 30, -49, -44, -29, -12, 26, -15, -39, 12, 28, 34, 1, 29, -3, -1, 41, 19, -6, 49, 20, -25, -27, 16, 13, -35, 24, -40, 42, -43, 2},
                                         {7, 11, 39, 48, -26, -19, -34, 31, -23, -10, -8, 30, -41, -33, 4, -16, 28, 13, -36, 20, -22, -28, 5, -46, -14, 36, 34, -15, -7, -11, -44, -25, -32, 14, 24, 8, 40, -1, 18, 1, -49, -50, 2, -18, -21, 25, -39, -27, 29, 19, -47, 22, 9, -4, -5, -3, 33, -37, -42, 42, -9, 44, 6, 47, 15, -17, 38, -38, -20, 45, -12, 10, 3, -24, -45, 32, 46, -2, -30, 43, 41, -6, -29, -31, 23, 49, -13, -48, 16, -40, 37, 12, 50, 17, 26, 35, 21, 0, -35, -43, 27},
                                         {-14, 44, 2, 25, -27, -47, 24, 49, -30, 45, -50, -38, 33, 50, -28, 35, -48, 29, 16, 4, -45, 28, -19, -17, -49, 5, 34, -15, -1, -35, -8, 6, -37, -32, -43, -22, 40, 13, -36, -26, -6, -18, 19, -13, -33, -40, -7, 10, 17, -34, 22, -42, 7, 46, 3, -44, 43, 18, 21, -21, -11, -20, -5, -10, -31, -16, 37, -2, -46, 36, -39, 15, 48, 1, 0, 30, 42, -9, 38, -41, 20, -4, 32, -29, 8, 39, 12, 9, 23, -23, -3, 41, 26, 31, 47, 27, -12, -24, 11, 14, -25},
                                         {6, 17, 47, -24, -20, 24, 43, -39, -14, 9, -50, -22, -2, -32, 45, 3, -42, 30, 41, 35, -13, -17, -27, -11, -8, 7, 31, 8, -43, 27, -7, -9, 44, 23, 15, 25, 32, -28, 12, -34, -36, -18, -33, 34, 50, -12, 20, -31, -19, 33, 5, 37, -1, -23, 40, -40, 28, 11, -29, -41, 39, 46, -35, 16, -3, -38, -26, -21, 14, 42, -10, -30, 19, -44, 49, 22, -6, -5, 1, 2, -47, 38, 21, -46, -25, -4, 4, -37, -49, 18, 26, -45, 48, -48, -16, 29, 13, 10, 0, -15, 36},
                                         {-45, 26, 4, 16, 41, -8, 50, -39, 42, 35, 6, -9, -30, -47, 5, 43, -42, 46, -43, -49, 24, -11, -17, 14, -10, -34, 45, -32, 7, 47, -16, -3, 3, -27, 34, 28, 1, -23, -29, -41, -1, -48, 9, -24, -33, -19, 10, 48, 37, 30, -14, 21, -50, -18, 25, 33, 44, -35, -37, 32, 49, 20, 8, -40, -12, -36, 27, -22, -13, 22, -38, 12, 36, -5, -15, 29, 15, -25, 13, -28, 40, 18, 23, -46, 0, -2, 11, 38, -20, 31, -21, -26, 17, -31, 39, -6, 2, 19, -44, -4, -7},
                                         {-47, 3, -16, 17, -11, 29, 33, 2, -36, 25, -28, -23, 49, -32, 0, -10, -43, -21, 21, -18, 44, 47, -40, -37, 12, -14, -29, -9, -4, -33, 48, -5, -7, 50, 30, 39, -19, 42, -8, -13, -42, 37, -6, 34, -20, -26, -12, 41, 15, 1, -1, 32, -30, 5, -46, 13, 35, -17, 43, 7, 28, 26, 11, -22, 22, 14, 36, -48, 16, 38, -38, -2, 8, 6, 46, 4, 10, 31, -50, 45, -34, 27, 20, -15, -24, 24, -27, 40, -49, -25, 19, 9, -39, -35, -41, 18, -31, -45, -44, 23, -3},
                                         {41, 2, 43, 13, -12, -46, -28, 24, 39, 22, -3, 1, -18, 45, -21, -7, 46, -14, -40, 10, -25, 35, -35, 15, 25, -39, 40, -1, -13, 3, 16, 5, 48, 29, -32, -38, 4, 23, -34, 38, -31, 7, 9, -5, -47, 37, 47, -17, 42, 44, -10, -8, 33, -42, -23, -37, 18, 32, 21, 34, -4, -30, -24, -41, -16, 27, -48, -43, 14, 31, -26, 49, 8, 30, 36, -44, -33, -15, 17, -50, -20, -45, 0, -2, 11, 12, 26, -9, -27, 50, 28, -6, -49, 19, -36, -29, 20, -19, 6, -22, -11},
                                         {-43, -9, -38, 49, -37, 5, -5, 3, -13, 21, -4, 20, 2, 10, 13, 9, 0, 1, 34, -15, -18, 18, -23, 41, 28, 19, 44, -8, -36, 45, -6, 48, -45, -14, -44, -48, -50, 6, -42, 31, -32, 35, -12, 12, 43, 7, 37, 50, 40, -27, 32, 27, 46, -49, -19, -25, 33, -30, -34, 36, 15, -17, 42, -29, 26, 25, -47, -16, 22, -24, 17, 29, -40, 38, -7, 30, 23, 47, -11, -3, -20, -35, 39, -10, -39, -21, 8, -26, 16, -2, -28, -41, -1, -33, 11, -46, 4, 14, 24, -31, -22},
                                         {-4, -30, -42, 2, -48, -2, 0, -40, 1, 7, 13, 42, -18, -9, 20, -7, 26, 12, 41, -34, 33, -25, -16, -49, 48, 47, -26, 11, 34, -35, -22, -1, -33, -11, -28, 27, 43, 29, 46, -5, -45, -8, 38, -10, -14, -3, 50, 25, -6, -29, 3, -50, 22, 5, 10, 44, 32, 17, -13, 35, 31, 39, -32, 15, -24, 49, -12, 23, -19, -17, -27, -23, 9, -15, 40, 16, -36, -21, 6, 14, 4, -37, -44, -41, 28, 37, -43, -46, 18, -20, 19, -39, -38, -47, 24, 21, 30, 8, 36, -31, 45},
                                         {35, 20, -44, -4, 36, 9, 42, -46, -37, 2, -1, -8, -17, -25, -47, 22, -35, 25, -34, -29, 31, -40, 17, 21, -45, 10, -26, 34, 39, -39, 28, -49, 43, -7, -2, 7, -13, -33, -43, 8, 41, -6, -30, 19, 29, -21, -10, 37, -19, 49, 1, -31, 3, 38, 14, 16, 12, -27, 15, -3, -50, -22, 11, 47, -11, -5, 18, 50, 5, -9, -41, -20, 44, 33, 48, 26, 24, -32, -12, 0, -16, 46, -48, -42, -38, -24, -36, -18, 40, -15, 4, 13, -14, 45, 27, 6, -28, 30, 23, -23, 32}
    }
    ;
    for (int i = 0; i < TIMESTEP; ++i) {
        for (int j = 0; j < STOCKSIZE; ++j) {
            A[i][j]=market[i][j];
        }
    }

    cout<<BuyStocks(A,TIMESTEP,STOCKSIZE,myvector)<<endl;
    int zz=myvector.size();
    cout<<"{";
    for (int i = 0; i < zz; ++i) {
        cout<<myvector.at(i);
        if(i+1!=zz) cout<<",";
    }
    cout<<"}"<<endl;

    cout<<counter<<endl;


    return 0;
}