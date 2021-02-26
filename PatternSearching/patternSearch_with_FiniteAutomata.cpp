
#include <iostream>
#include <climits>
#include <cmath>
#include <utility>
#include <vector>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

/* This function builds the TF table
which represents Finite Automata for a
given pattern */
void computeTransFun(char pat[], int M, int**& TF,int alpSIZE,char firstLetter)
{
    int i, lps = 0, x;

    // Fill entries in first row
    for (x = 0; x < alpSIZE; x++)
        TF[0][x] = 0;

    TF[0][pat[0]-firstLetter] = 1;

    // Fill entries in other rows
    for (i = 1; i < M; i++) {
        //cout<<"lps : "<<lps<<endl;
        //cout<<"step i: "<<i<<endl;
        // Copy values from row at index lps
        for (x = 0; x < alpSIZE; x++){
            //cout<<"step x: "<<x<<endl;
            TF[i][x] = TF[lps][x];
        }

        // Update the entry corresponding to this character
        //cout<<"step update entry"<<endl;
        TF[i][pat[i]-firstLetter] = i + 1;


        // Update lps for next row to be filled
        if (i < M) {
            lps = TF[lps][pat[i] - firstLetter];
        }
    }


}

/* Prints all occurrences of pat in txt */
char * search(char txt[], char pat[],char alphabet[])
{
    int M = strlen(pat);
    int N = strlen(txt);
    vector <int> result;
    bool wildcard= false;
    for (int i = 0; i < M; ++i) {
        if (pat[i]=='?'){
            wildcard= true;
        }
    }


    //int TF[M + 1][NO_OF_CHARS];

    char firstLetter=alphabet[0];
    char lastLetter=alphabet[strlen(alphabet)-1];


    int alpSize=0;
    while (firstLetter<=lastLetter){
        firstLetter++;
        alpSize++;
    }
    //cout<<"alphabet length :"<<alpSize<<endl;
    int** TF = new int*[alpSize];

    for (int i = 0; i <= M; i++)
        TF[i] = new int[alpSize];

    if(!wildcard) {
    computeTransFun(pat, M, TF,alpSize,alphabet[0]);

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < alpSize; ++j) {
                cout << TF[i][j] << " ";
            }
            cout << endl;
        }

        // Process txt over FA.
        int i, state=0;
        for (i = 0; i < N; i++)
        {
            state = TF[state][txt[i]-alphabet[0]];


            if (state == M){
                state=0;

                cout<<endl;
                printf ("Pattern found at index %d\n",i-M+2);
            }
        }
    } else{
        for (int i = 0; i < alpSize; ++i) {
            for (int j = 0; j < M; ++j) {
                if (pat[j]=='?'){

                    for (int k = 0; k < alpSize; ++k) {
                        pat[j]=alphabet[k];
                        computeTransFun(pat, M, TF,alpSize,alphabet[0]);




                        // Process txt over FA.
                        int i, state=0;
                        for (i = 0; i < N; i++)
                        {
                            state = TF[state][txt[i]-alphabet[0]];


                            if (state == M){
                                state=0;

                                //cout<<endl;
                                result.push_back(i-M+2);
                                //printf ("Pattern found at index %d\n",i-M+2);
                            }
                        }
                    }

                    break;
                }
            }

        }

    }

    sort(result.begin(), result.end());

    int sizeofRet=result.size()*2+1;

    char * newArray = new char[sizeofRet];
    int ii=0;
    int jj=0;
    while (ii<sizeofRet){
        char c = (char)result[jj];
        newArray[ii]=c;
        newArray[ii+1]=' ';
        ii+=2;
        jj++;
    }

    newArray[sizeofRet-1]='\0';

    return newArray;

}

/* Driver code */
int main()
{
    char txt[] = "ABABABAACBAAABC";
    char pat[] = "A?B";
    char alphabet[]= "AC";



    char *inval=search(txt,pat,alphabet);

    for (int i = 0; i < strlen(inval); ++i) {
        cout<<inval[i];
    }
    return 0;
}