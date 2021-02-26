#include <iostream>
#include <climits>
#include <ctime>
#include <utility>
#define DEBUG
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp
int callCounter=0;
int min(int a, int b)
{
    return a < b ? a : b;
}

int Assembly_Rec_Helper (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int line);

std::pair<int,int> Assembly_Rec (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2){
    callCounter = 0;
    int left = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2,  0) + x1;
    int right = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2, 1) + x2;

    if (left < right ) {
        return std::pair<int,int>(left, callCounter);
    }
    else {
        return std::pair<int,int>(right, callCounter);
    }
}

int Assembly_Rec_Helper (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int line)
{
    callCounter++;

    if(n == 0){
        if (line == 0){
            return e1 + a1[0];
        }
        if (line == 1){
            return e2 + a2[0];
        }
    }

    int F0 = INT_MAX;
    int F1 = INT_MAX;
    if(line == 0){
        int a = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2, 0) + a1[n];
        int b = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2,  1) + t2[n-1] + a1[n];
        F0 = min(a,b);
    }
    else if(line == 1){
        int a = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2,  1) + a2[n];
        int b = Assembly_Rec_Helper(a1, a2, n - 1, t1, t2, e1, e2,  0) + t1[n-1] + a2[n];
        F1 = min(a,b);
    }

    return min(F0, F1);
}

int Assembly_Memo_Helper (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int line, int**& table)
{
    callCounter++;

    if(n == 0){
        if (line == 0){
            //table[n][line] = e1 + a1[0];
            return e1 + a1[0];
        }
        if (line == 1){
            //table[n][line] = e2 + a2[0];
            return e2 + a2[0];
        }
    }

    int F0 = INT_MAX;
    int F1 = INT_MAX;
    if(line == 0){
        int a;
        int b;
        if(table[n-1][0] != -1)
        {
            a = table[n-1][0] + a1[n];
        }
        else
        {
            a = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2, 0, table) + a1[n];
            //table[n-1][0] = a;
        }
        if(table[n-1][1] != -1){
            b = table[n-1][1] + t2[n - 1] + a1[n];
        }
        else {
            b = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2, 1, table) + t2[n - 1] + a1[n];
            //table[n-1][1] = b;
        }
        F0 = min(a,b);
        table[n][line] = F0;
    }
    else if(line == 1){
        int a;
        int b;
        if(table[n-1][1] != -1)
        {
            a = table[n-1][1] + a2[n];
        }
        else
        {
            a = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2,  1, table) + a2[n];
            //table[n-1][1] = a;
        }
        if( table[n-1][0] != -1 ){
            b = table[n-1][0] + t1[n-1] + a2[n];
        }
        else{
            b = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2,  0, table) + t1[n-1] + a2[n];
            //table[n-1][0] = b;
        }

        F1 = min(a,b);
        table[n][line] = F1;
    }

    //table[n][line] = min(F0, F1);
    return min(F0, F1);
}

std::pair<int,int> Assembly_Memo (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{
    callCounter = 0;
    /*
     int** a = new int*[rowCount];
    for(int i = 0; i < rowCount; ++i)
        a[i] = new int[colCount];
     */
    int** table = new int*[n];
    for(int i = 0; i < n; i++){
        table[i] = new int[2];
        for(int j=0; j<2 ; j++)
        {
            table[i][j] = -1;
        }
    }
    int left;
    int right;

    left = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2,  0, table) + x1;
    //table[n-1][0] = left;

    right = Assembly_Memo_Helper(a1, a2, n - 1, t1, t2, e1, e2, 1, table) + x2;
    //table[n-1][1] = right;

    if (left < right ) {
        return std::pair<int,int>(left, 4*n-2);
    }
    else {
        return std::pair<int,int>(right, 4*n-2);
    }

}

std::pair<int,int> Assembly_Tab (int*& a1, int*& a2, int n, int*& t1, int*& t2, int e1, int e2, int x1, int x2)
{

    int T1[n], T2[n];
    T1[0] = e1 + a1[0];
    T2[0] = e2 + a2[0];

    for (int i = 1; i < n; ++i) {
        T1[i] = min( T1[i-1] + a1[i],
                     T2[i-1] + t2[i-1] + a1[i]);
        T2[i] = min( T2[i-1] + a2[i],
                     T1[i-1] + t1[i-1] + a2[i]);
    }

    std::pair<int,int> result;
    result.first = min( T1[n-1] + x1,
                        T2[n-1] + x2);
    result.second = n;
    return  result;
}
void print(std::pair<int,int> retVal){

    std::cout<<"<"<<retVal.first<<","<<retVal.second<<">"<<"\n";
}
int main(){

    int a1[] = { 7,9,3,4,8 };
    int a2[] = { 8,5,6,4,5  };
    int t1[] = { 2,3,1,3};
    int t2[] = { 2,1,2,2 };
    int e1 = 2, e2 = 4, x1 = 3, x2 = 6;

    /*
    int a1[] = { 4, 5, 3, 2 };
    int a2[] = { 2, 10, 1, 4  };
    int t1[] = { 7,4,5};
    int t2[] = { 9,2,8 };
    int e1 = 10, e2 = 12, x1 = 18, x2 = 7;
    */
    /*
    int a1[] = { 4,5};
    int a2[] = { 2,10 };
    int t1[] = { 2 };
    int t2[] = { 1 };
    int e1 = 2, e2 = 1, x1 = 1, x2 = 2;
    */
    int n = sizeof(a1) / sizeof(int);
    int *a1in,*a2in,*t1in,*t2in;
    a1in=a1;
    a2in=a2;
    t1in=t1;
    t2in=t2;

    //print(Assembly_Rec(a1in,a2in,n,t1in,t2in,e1,e2,x1,x2));
    //print(Assembly_Memo(a1in,a2in,n,t1in,t2in,e1,e2,x1,x2));
    print(Assembly_Tab(a1in,a2in,n,t1in,t2in,e1,e2,x1,x2));



    return 0;
}