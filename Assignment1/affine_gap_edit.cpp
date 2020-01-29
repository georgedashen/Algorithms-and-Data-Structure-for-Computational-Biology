//filename: affine_gap.cpp
//use BLOSUM62 and definition of affine gap as a + b(L1-1)

#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>

int pos(char aa)
{
    char *amino = (char*)"ARNDCQEGHILKMFPSTWYV";
    for(int i=0;i<20;i++)
    {
        if(aa == amino[i]) return i;
    }
}

using namespace std;

int main()
{
    char *s = (char*)"DVKVDDRQHGRINCPCNSRPKPPLVLLPKWQAKGLFRPFPDPNHRPKDWSFGCFEFIRFRRWNRHTDYAIGSNLMHSYYIHMAWI";
    char *t = (char*)"DVKVDDRQHGRINCAEYHTFCNSRPKPPLVLLPKWQAFLSLFRPFPWSFGCFEFIRFRRWNGSYYIHMAMI";
    //char *s = "MAGKAAC";
    //char *t = "AACRLLV";

    int BLOSUM62[20][20];
    ifstream f("B62.txt");//a file containing the BLOSUM62 matrix with row21 and colomn 21 filled with 11
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            {f>>BLOSUM62[i][j];}

    //checking if BLOSUM62 matrix stored correctly
	/*for(int i=0;i<21;i++)
    {
        for(int j=0;j<21;j++)
            {cout << BLOSUM62[i][j] << ' ';}
        cout << endl;
    }*/

    int m = strlen(s)+1;
    int n = strlen(t)+1;

    int **A = new int *[m];//score matrix
    int **R = new int *[m];//A matrix tracking the row penalty
    int **C = new int *[m];//A matrix tracking the column penalty

    for(int i=0;i<m;i++)
    {
        A[i] = new int[n];
        R[i] = new int[n];
        C[i] = new int[n];
    }

    for(int i=0;i<m;i++){A[i][0]=0; R[i][0]=0; C[i][0]=0;}//initiate the first row and column with zeros
    for(int j=1;j<n;j++){A[0][j]=0; R[0][j]=0; C[0][j]=0;}//initiate the first row and column with zeros

    int max_score = 0;
    int row_idx = 0;//row index for max_score
    int col_idx = 0;//column index for max_score

    int match = 0;//matching score from BLOSUM62
    int gap = -11;//gap penalty
    int ext = -1;//extension penalty
    int step_max = 0;//store the result from comparison

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            match = BLOSUM62[pos(s[i-1])][pos(t[j-1])];//match or mismatch
            step_max = max(max(A[i-1][j-1]+match,0),max(R[i-1][j-1]+match,C[i-1][j-1]+match));//which score is the maximum
            A[i][j] = step_max;
            R[i][j] = max(A[i-1][j]+gap,R[i-1][j]+ext);
            C[i][j] = max(A[i][j-1]+gap,C[i][j-1]+ext);

            if(A[i][j]>max_score)//tracking index
            {
                max_score = A[i][j];
                row_idx = i;
                col_idx = j;
            }
        }
    }

    cout << endl;
    cout << max_score << endl;
    cout << row_idx << ' ' << col_idx << endl;

    if(!max_score) {cout << "No Match!" << endl; return 0;}

    stack<char> s_stack;
    stack<char> t_stack;
    m = row_idx;
    n = col_idx;
    while(A[m][n]||A[m+1][n]||A[m][n+1])//backtracking
    {
        match = BLOSUM62[pos(s[m-1])][pos(t[n-1])];
        if(A[m][n] == A[m-1][n-1]+match)
        {
            s_stack.push(s[m-1]);
            t_stack.push(t[n-1]);
            m--; n--;
        }
        else if(A[m][n] == R[m-1][n-1]+match)
        {
            s_stack.push(s[m-1]);
            t_stack.push('-');
            m--;
        }
        else if(A[m][n] == C[m-1][n-1]+match)
        {
            s_stack.push('-');
            t_stack.push(t[n-1]);
            n--;
        }
        else{s_stack.push(s[m-1]);t_stack.push(t[n-1]);m--;n--;}
    }

    while(!s_stack.empty()){cout << s_stack.top(); s_stack.pop();}
    cout << endl;
    while(!t_stack.empty()){cout << t_stack.top(); t_stack.pop();}

    return 0;
}
