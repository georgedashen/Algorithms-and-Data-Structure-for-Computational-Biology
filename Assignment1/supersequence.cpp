// filename: superseq.cpp
// to find the supersequence between AACCTTGG and ACACTGTGA

#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

void superseq(char *s1, char *s2)
{
    int m = strlen(s1)+1; // an extra row of 0
    int n = strlen(s2)+1; // an extra column of 0

    int **A = new int *[m];
    for (int i=0;i<m;i++)
        {A[i] = new int[n];}

    for(int i=0;i<m;i++)
    {
         for(int j=0;j<n;j++)
            {A[i][j]=0;}
    }//initiate the score matrix with 0

	//find the longest common subsequence
    for(int i=1;i<m;i++)//the firt element to fill in the matrix sits at A[1][1]
    {
        for(int j=1;j<n;j++)
        {
            int match = 0;//default mismatch = 0
            if(s1[i-1]==s2[j-1]) {match=1;}//i-1 and j-1 to ignore the zeros row(column) in matrix
            A[i][j] = max(max(A[i-1][j-1]+match,A[i-1][j]),A[i][j-1]);
        }
    }

    m--;n--;
	//for debug
    /*for (int i=0;i<m;i++){
        for (int j=0;j<n;j++)
    {
        cout << A[i][j];
    }
        cout << endl;
    }
    cout << A[m-1][n-1] << endl;*/

    stack<char> s;//use stack to store the route and for reverse output when backtracking
    while(n||m)
    {
        if(m==0)//reach the first row
        {
            s.push(s2[n-1]);
            n--;
        }
        else if(n==0)//reach the first column
        {
            s.push(s1[m-1]);
            m--;
        }
        else if(A[m][n]==A[m-1][n])//when s2 has a gap
        {
            s.push(s1[m-1]);//output corresponding s1 element
            m--;
        }
        else if(A[m][n]==A[m][n-1])//when s1 has a gap
        {
            s.push(s2[n-1]);//output corresponding s2 element
            n--;
        }
        else if(A[m][n] == A[m-1][n-1]+1)//match
        {
            s.push(s2[n-1]);//output the common element
            m--; n--;
        }
     }

     while(!s.empty()){cout << s.top(); s.pop();}
}

int main()
{
    char *s = "ACGTC";
    char *t = "ATAT";

    superseq(s,t);

    return 0;
}
