

int max(int a, int b)
{
    return a > b ? a : b;
}

int BuyStocks (int**& market, int n1, int n2, vector<int>& solution)
{
    if (n2<1) return -50;

    if (n1==1){

        int maxStep1=-50;
        int lastItem=-1;
        for (int i = 0; i < n2; ++i) {
            if (market[0][i]>maxStep1){
                maxStep1=market[0][i];
                lastItem=i;
            }
        }
        if (solution.empty()){
            solution.push_back(lastItem);

        }
        return maxStep1;
    }

    int t1=market[n1-1][n2-1]+BuyStocks(market,n1-1,n2-1,solution);
    int t2=market[n1-1][n2-2]+BuyStocks(market,n1-1,n2-2,solution);
    if(t1>t2)
    {
        solution.push_back(n2-1);
    }


    return max(t1,t2);
}