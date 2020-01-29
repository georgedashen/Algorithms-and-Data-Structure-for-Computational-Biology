//filename: local_alignment.cpp
//to get a alignment score of two DNA string using local align with score matrix

#include <iostream>
#include <cstring>
#include <stack>

#define maxsize 10000

using namespace std;

int local_align(char*s, char *t, int**A, int &x, int &y)//return the max_score and [x,y] can store the position
{
	//alignment initiation
    int m = strlen(s)+1;//an extra row with zeros
    int n = strlen(t)+1;//an extra column with zeros

    int Max_score = 0;

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            int match = 0;
            if(s[i-1]==t[j-1])
                match=1;
            else match = -2;
            int gap = -2;
            A[i][j] = max(max(A[i-1][j-1]+match,0),max(A[i-1][j]+gap,A[i][j-1]+gap));
            if(A[i][j]>Max_score)//tracking the max_score
            {
                Max_score = A[i][j];
                x = i;//row position
                y = j;//col position
            }
        }
    }

    return Max_score;
}

int global_align(char*s, char *t, int**A)
{
    //alignment initiation
    int m = strlen(s)+1;//an extra row with zeros
    int n = strlen(t)+1;//an extra column with zeros

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            int match = 0;
            if(s[i-1]==t[j-1])
                match=1;
            else match = -2;
            int gap = -2;
            A[i][j] = max(A[i-1][j-1]+match,max(A[i-1][j]+gap,A[i][j-1]+gap));
        }
    }

    return A[m-1][n-1];
}

char* substring(char *s, int start, int num)
{
    int n = strlen(s);
    char *tmp = new char[n];
    for(int i=0;i<num;i++)
    {
        tmp[i] = s[start+i];
    }
    tmp[num] = '\0';

    return tmp;
}

int main()
{
    char *s = new char[maxsize];
    char *t = new char[maxsize];
    s =(char*)"CTCTTATATACTTACGCTTAACGCGCCATCCGTCGGTGTAAATCTCGCGCGCATACGCTCTGTAGATTCCCTTTGTTATCGAAAGCACAGTCGTGGGATGTAGCGCCACACCCCTTCTGTCTTCGGGCGCGGATCAAGTGTACGGGGCACCCTCGTCAGCTAGCTAATCTCTACACAGTACCCCTGCAGGTCCAGGAAACGCTGCCAGCCTATATAGCCATAGGACCCACCGCATTGTCGCCGGCCCCAACCCTGAACCGTGCGATCTTATAGCCGTCAGTTTCGCTAGCGCTGGTCATTCAGAGATGGTGTATAGTCATGATGTACTGCGATCCCAGCCGATTATCCGAATCCAAGCACTTTGGTAGACGTCCTAGGTGAGGGATAAACCCCCTCTGGCATTTCGAATAGCAGAAGTTATGGGACCGACAAGCAGCACTTAGGTGGCAGGCATGGTGAAGTTCTGCATCCATTCGATCACCACCCTGTAAATTTGGCCTGGTATTGATCGGTTCAAAGCAGAGTTCTCATCTAGGAGCAATTGGACTACGGGCGCCATCTCCAAATGATCCGCTACGGGAGGCATGGGCTAACAGTGAAGTCTAACAAAGTCCTAACGTCAGTAGCCGACAACGCACTACTCGTAGTTCGCCGACAAGGAGCGCTTCATCGCGGCCCTATGCGCCGGGGTCCCTTACCATATGCCATAGATTCCTCCGGCTCCTGCACAAGCTAACAGGTTGGAAAATCCTGCTTCGACTAGCAGAGTTGTTACCTAGCATGTTGGATGCCTGAACTGCTCAATCCACAATAGCGGATTCGGAGTTCTTAAATGCTTAAATGCAAGGCGGGCCCATCCAAGGCCATCCGAGTGGCGCGGCCTATTGTTGACGTATCCCGGCACGATACTCAATCACAGCCCGGTCGCACAAGGGCATGGAACAAGTAGGCCCGCCCCAGGAGTCGTGATGCAGCTGGCCAGGGAAAAATATATTAGGTAGTCGATTGCGAAGGGAGACATGAAGAGGGGCAGCTTCGTTGTTTTGAAATATACTTAGGGGTGAGGCACAAAGCCTCGTATACGCGGAGGACGACACGTAAGCGTCGTGACGTCTTTATGCAAAGACCGAGCTCGGAGATAGTATTCATGAAATTGGAGGTCTAGTTTGTTAGAAACATTGCCGCTAAGCTCGCACAGCAGTAAAAAGCACGGGTAGGAGTAAGGGAAGGAAAATTTTCTGCTAGGGAATGCTGCCCCCGGACCTCGGAAGGCGGTACAGGGCTGGGTGCTAGGGTAAGGCTCGCGTTGGAACGTGTACCCCAGTCTGCGTGCAATATATGGACCACCGCTTAGGCGCACGTACTAGAGATTAAGAATCAAGTCTCGTAAGTTACAGCTACGGTAGTTATACGTCTACGTGAAACATCTCCCCCCGAGAAAATTTGCACCGCGCTGTAGGTACAGGGGTAATGAGAGTAAATAGAAATCCTCTGCTGTAGCAGTACGTCGCCCTAGGTACCTAGTCATTCTACCCCGAAGTTCATCTCGAGCCCGCGCCGGTGTACTTCTTCTGATAAGTGGGGGCGTGCGGTCCAGAACCAGCTAGCGACAGTCCCACCATTCGGCCGCGTCAGACACTCGCTGTAGTCGTACCAGCGATTTCGTGAGCCGACGTCTACCTAACGGAACCTAGTCACCGAAATTCAGGTCTGCGTGAGGCGGACACACGCTTCAAAATTTAGTTGTAGCAGATACAAAGGATATATCACGCCTCACCCGAAGAGTGGACTAGGCGTTAGCTCACTGCCACATACACCGACAACCATTACTTGCATACCGCACTAGCGCTTCGAACGTATGTGAAAGTGTGCGCGTGTACAAGTCGAGCCTTGTTCCGGCACGCGGTAGGAAGATGGAGAAGAGCATCCCTTTCTACGGGCTATCTTCCCCTTGATCGCGTCTGTGTAAAGAGTAAAATTGGTGCATCGTGACCATCGACTAGGTTGCAAGTGTGATAGTCGTTATGTACAAGCCCGGAATTGTTGTGGAAACATAGAAGCTCTATTATATCATGCCTTGTTTCAATAAAGAGGCGGTTGTGGAGGGGCGCCGGACGAATGGTCACACTGGACCCCACATATGCCCCAGTATGCTAACTGGCTGGGGTAGTGGAACAAGTCCAATGCAGAGGACAAAGTCGCCACGGGCAGTACCTGAAATACCCGGTCCCCTACGACAGTATAACGTAAGATACGATGGATATCGAGGGGGTTATCTGCCGTTCTTAAACTAAGTCGGCGGATGTGAGCGGTGGCGCTATTGGATCGTGGAGATCCCAAAGTCACTTACTGTTAGTTAGCAAGTAACAATAAACGCCCCCAGCGCAACTTCGTAGCTAGAAGCCTGCTGTTCGCTAAATACGCTAGGACGCTTCCAGAGTGTAGGCCTAGTATAGTGCGCTTTGTAAAGCCAAGGGTCCAATTGAACGCCCAATGGTAGATCCCAAAACTCAAGTAACTGAAAGAGCGTGGAAAGAATCTATTGGTTAGTTATCTGCGAGGTATAGGTCCCACGTCTGGGACGTTGCGTGCATGGGGGGCCGGGGAACCGGCGCCTCCCGGAGCAACACCGCTACATATATCCGCTGCAAAATGCTAGGCTGTGGGACACAACAGGCTGCCGTATGGGTCAAATTGGAGGATAAGGCTAGAGTGTCTGTAGTAACTACCCATAGTACTCTTGCGATTAACAGTATAAGCGCTTTCGAATAGGATCGCGGGGGGGGTCTGGCCGGCTCCGGACGAGTCATAACACGTCTGCATATCTTAGGACGGCGGTTTGTATACCCGTTGTATGCAGCGTATTAGAAAGCCCCTCTCCTTCTCCTTGGTCCAGCCTAGCGTGTCCTCATCCAGGTTAAATCGCCCGACTCTAGTGCACCAGGCGTTCACCTACGTCGGGACACACGAGGCCGTGTTTTCCCCGCCGAAATCTACCCTTTTGGAATCGATTCGAGCAGTTATAAAACCTACCACCTAAATCGGACTATATGCTATCCATTGACGCACACTGTTAGTCTACAGCGAAGGCGCAATCCAAAACTGTGCCTGAACGGTACATTATTTACACATGATATCAAATTCAGAGGGCTTAGTCTTACCTTTCCTAAGTGTCGCATGTGGCTTATCTGAACGTTCTTTCGAAAGCACGGAAGTTTCACTATCGGCTCACACCTCAGTTACTATCTAAATGGCATCTGTGGGTTGTAGGGGTTGAGAAGTCGCAGGGAGGGTATCTTACTTCTTGTTCGCGAAACAAAGTGGTGTGGAAGCTGCCGAGGCATACGTCCCTCCATCAACGTGTGCTGTCACAGCCTTTAGACCCCCGCATGCCACAACTGGTTGGGGGGAAGGATAAGCAGGACACGTCACTCTTTGGCCGCAAAGGACCCGAAACATATCACGGGAACAAGAGCACGTCTTCTTAAATAGTTGGAAACAGCGATCATAGTGATTGGGCTAATTCGTAGTCCGGAAGTCTCAATGCTTGCGACACAGACTTCGATTGGGCTTTTTCTGATTATAGAGAAGTACACAAACGGCAGATGAAGGCGGCAGCCCCACTGTTCATCTTCCCTATTTAAACTCACAACCGGTGTGCCGAAAATGACGGGAACGGAGGGGCGATTTCCTAGACGCAGCGACGAAGCGAACCAGCAAATAATTTAAGCTCATATTCTTGGTGGCGCAACGCCAGTAGCAAGTTTATGAGTTCTAGGTCCGAGGGAGCTGGCACAACAATCAGCGACGCTCCGAACCATTTGCCGCTCGCGTAAGCCTTAACTGTTCTTGGCCGTTGTCGAATGACCCTAGGCCCGCAGGGAGACGAACCTATCATATTCTCCGCTGCATATAAATCGAGGACCAGTATTGGTGTAGTGCACGCAGATATCCTCGGCGAAGCGTGGAGAACTATCTGTCACGGCAGATACTCAATTTACGGTGGTCTTTAATCCCCCTCCTCTCGGCGATGGAGGCGACCCATTTCCGCAGTTACGAGGATCGTTTTAACCATTTTATATATCAAATGTGAGCAGCGACCATCGATCGCCCACGGGTACTGCTAACGGAGTGGTCCTTGGCACAGCATGAGACGGCGAACACTCCGAGAGTCAAGCCATCATTTCAAAATCGGTTTGGTAGGGCCCGATGTAACCTAGGTACTCGGCAGACGAGTTTGGAGTTTGCCACATGAAAATCGCAGGCTCCCCCGACCACTCGGGCAGGGACCGCTTAAGTCGCAAGGTATGGGCCTGAGTGCTCACCAATCATATGACACTTAGTAGAAAATGACCCCGGCTGCGAAGACTGAGTACCCTGCTGAATTATTGCGCGCGTTTGCTTAGTAGGCTAATGCGTCTGCTTCTGAAGGCAGAGTCTTGAGACCATGTGTGGGGGTCTTGATTAACGTACTCACGTATCGACCATGGGTTGTAATGTTCTGTACCACTCAGTAGATTGACCCCGTCGGAATGCCCCGCTGCAACTAACCCGATTTAGTTCGTGAAGGCTTGAAACTCAGTTTCCTAGCACCTTGTTCGTACACGTAGGTCCGAGTCGGGAGACCTATCATCGCCTTTCTCCCCTCAGTGTCTATCCGCACATGCTGAAGTGTGCATCCGATTAATACCAACTAAAGCCGCTGTGCAGTATTCCGCCTCCTGCGCGTCAACATCGATGAGGGGGCGCCAAGGCAAATGACCAGCCCAATTACAGCCAGTCGCAGGGGTCGGGACCATCTACTCCATTACGACTTCCAGTGGACAAGAAAGCGTATCTGACGAATCTGAGTGTACCACGTCAATGTACGCTCATATACGGGTGTTCCGCCTGAATTTATTCAAATATGTAGCGGAATCTTCGATGCGATCGCTTGTATAACTGCACCACGGCTAGACGTGATTGATGGGTTACGGTACGTTACCCTATACTACTGCTCGTGCAAGGGTTATCCTGGCCGTGATTCAGCTAGTAATCTTATTTGTTAAACATGCTATAAACAAATTAGCATGCTTCACACAGTTACGTCACTGCGACAGGGGGCACATACTCCCAGGGACCAGCGCATGATTCCAGGTTTCGCAGTAACGCGTGCCAAAAAGCCCGGTACAGCAGGTAAGTTCCTAACATACCATGTGGTGTAACGAAGACGCATAGGTAATGTGCCGCAGCGGTGGGACTAAAGTAGTGGTAACGCTCTGAGCGGAGTTTACCTAAGTAAAGCAGAGAACTTTCTAGCAATCCCACGTAGCCTTGATTCAAAGCTTAAGTTTGCCTTATTATTCCGACCCTACTATACGCGTAGGCGTCCCCCTCGCCACTCATGTCTTCGGACGCTCCCGATCGGACCAGAATGAGTAGTCCGTACTAAGGTCCTTACCAGCAGCCGGGCCCATAATAATGCGGTAACCCAGAATCTAGAGGGGCAGCAAACAATTTCCCTCAGCTTGTAGGTCGCATGACGACTAGGCGCGGTAACAGCCACCATCCCGCGGTATCGTGTTTAGCGTTTACCAGCCATTTGTATCTAATTAAGGTCGATCGTCACCGATTACTGCAAAGTGAGTAAGGGCACAGGCAGCCTACTTCCTGGCTGTTATACCACGGTCCTGAAAATAGCCATCCACATGGACCAGAAGCCCTTCTACGTTAAATGACTGTTTAGTATTCTATGCCCGCTGCTTAGTCCATGTCGATGCTTGGAGTTTCTCCATGTCATATGACAGGGCTTTCCAAGGTCCTTAGGGAGCCTTCTGTTTAGGTTGTAATGTAATTAAGCGTACGTATATAGTACGACAATCGATTTGCAGTAGCGTACGTCAGATCGGGTTGACGTTGGAGTTTTCGTTGGAGGACGAACCAAAGGAATCGTTATACGGGACGATAGCTTGCCAGTAGCCCTCTCCGGCTCATATAGTAGCACCCACAACACGCTCGTATGTGGTCGCAGGAGTCCTCACGCGGCTGCCACGTTCGGGAACATTGCGAGTCACCTATGTGGTCTCTGGACCCCTGCGCCGAAGATTGGTTCGTTACTGACAACGTACATCCCTATATACCCGCATTGGTCAATGCCACACTCTGAAGGAGGGTCGGGCGCGTAATAAATCCAGAATAGTACAGTCCGTACCTCACCAGGCTCATGAAGTAGGGTCCCACCAGGGAAGTGAATCAGGCCAACCCGCGGAGGTATGAAACTTATTTGGCACGGCGGGTAATCTAATTGATCCTCTCAATTTAGGGTAGATAGGATGGTTCCTTAGGTAGATGAAGCCAGTAGCCTAAACAAGCATTCCGTCCTTCTATGGTTGAGTCATGTCGTCTTATGGATTATATCTTATACCAGCGGGCTCGCCCGAGATTGGTGACCGGTAAGTGTCGCGTATTATTGCTGCGAACGCCTACGGATACGCATAAATTTGTCTAGCCTGGGCTAGATCGGCCTCATGTGAGGTAGCTGGGAACATGTACGACCCCGATGGTGCCCGGAGTATGTCAACAAGGTGTTGATGCAGCCGCATCCAAACGTGCTAGGACCTCCTACTCGTACCGTTGGAGGGGGTGGTTATTCGGGGAGAGTCTCGAACGTTTGATAGCCTGACGTGCATAGACACAATGGGCATACAACTTTGCCTATTCTCCGCGGTCCTGTGGACGCGCGCGGGTGCATACCGGACTCCTCATCCAAAAGGGGTCTACCTTATCGACTCCTCTGCAGAGCATAGTATCACCGCGATAGTAATTCGCGTAGGTCTCAACAAACACAGAGCACACATAGCACATACGGCCGTTTGAAACTGGTAGGTGCGAACATGTCAAACCAGAGTCACTACAGAACCGGTCAGCTCGAGTCTCAGAGCCTTCGACTATTCGGAGGCCTGAGCTGTGCTAGCGTTGCCGTAATCCCTACGTCCGTTTTATACCAGACTGCACAGCTAGTGTGCAGGTATGACAAATACGGTTTCAGTATTCGATCATCTTAATAAGTTAGCGGATAGATGGAACCAGACCTTGTCGGCGGCCACTACCCCTTTCGAATGATCAGAGATACACCACGTCCGCCATTCAAAAGGGTTAGATACAACGTACAGGCGCCACGTAGCCTTGGTTGGCACATCAGTCATAATGTGAATTGCCCGAATTGGTTACAAGTCTCCTTTGCGTGCTTGCTTATAGGTGTATGCGTCATTATAACCAACAACTGGAGCGACGGGGTGTCAGCCGGCAGATTCCCTATCCGCCGCTGCAGGCGTAGCAGCGTCCGTGAATTGAAAATGGTAACTAGACGAGTCGCATCGTGTCAGCCCAGCTTCCCATGTAATCCGGGCTAAGCGCTCGGTAAAACCGGAGCTTTAATTTTGGCAGGTTGGGTCTAGCAGTCCAACCGAACCATAAACTTGCATGTTCTTGCAAACTCAGTTCCTCCGACGAAGGTAATGAGGATTCACCTGCAGTCGCCGTGGTCGGTGTTGGTGGACGCTTATTGTTCAGCTCACGGAGTCCTTCTCGAACAGTTCCCTAAAGCCCGACACCGCTATCGACAACCTTTAGTACGAGACCGTTTGTCTTACCAGACTTTGTTGCCCGGGGGCAGTAGATCCGGCGTGTCCTGCGTCCTTGACTGTCCTATTAGCCTACTCCTGTATAAGGGGCGCGTCTGTGTATGCTTCGCGGTAGGTCTTTGGGTTCATTGACAAAATATTAGGGCATATGTGACGGATCGCGAATACCGTCAGAGATTAGTTATCTGGTTAGTGGCCGGCTACCTTAGAGGTCTGAAATTATATCATTTAAATTATAGTTGGTGACGTTTCTCTACACGCATAATGCATATCAGCAATTAGCGACACCCCCGGACCAGTTAGCCCTAAAAGGCGCGTGCAAGCGGCAATTGCGAAAGGGCTGAATCCCAGTTGGCAGCGGGGCGTCCAAAGCGCTCCGCCCCCGGAACATTTTATGGCGAACTGTACGCCCATAATACACTTCGTCGCGACGATTGGTACTTAGAAGAGTCTGGTCGTCAGGAGATGGCGTCTCACGAATGGCGATAAGTGGATCGTATAGCCACTCACAGTGGTGCAAAACTTGTCAGGGTCGGCTCTCTCAGTGCGACACGAGGAGGAGTAATCACTCGTCTTCGTAGGACTCGAAGGCCGAGAGAGATTAATCATTTGTCGGTACGCGGTGGAGCGGTTCACTCTACGCCACCGGCGCCGATCACTAAGAAGGGACCGAAGCTACCAGGCATATTAAGTAACATGCCGTTAAATGTATAGAGTTATCTCAAGACTCTGACTCTATACTGTGTCCGCATTCAATTCTCCTTAGTTGTCGTCCGTCATGCTTCTTCTCCAGGACATGAAGAAGACGCGACTTCATACACTAGTGATGTAGGCTACCGTCTAATCAGCGCTAATCCGTAATGGTTATGGTAGCCCCAG";
    t =(char*)"GCATTAAATCCAGAGATATCAAACCCTCCCTCGGCCAAGTTCTTGAATTGGGTTCCTTCAGGAAACTGATCGTCCGACCCCGTGGAGGGAAACCCATTCGCACGGTTGGGGAGTCTAACGGATCCTCTTATCACAGGCGATTAGTCACGATGGCATTCTTAGTAGGAAGCCAGTAGTCTAAACGAGCATTCCGTCCGCTCTATGTGTCCGAACTCTGTTCGGCCTATCGGCTTAATTTCATATGCGGGCGTCGTTGCCGAGTCTGTTGACGGGTAGAGTTGCGTATTATTGCACGAAGATCTACGAATACGCTAAAACTTTATCTACGGCCTGGGTTTGGTGACCTTCATGTGAGGTAGCTCGAGCATGTCGACCGCGACTGGTGCCTAGGTATGAACAATAAAGTGTTGCTACTTGCCGGAATCCAATCGTCCTAGTCACTCGTACTACGAACCCGCCTGTAAGTTGTGGTATTCGGACAACGATCCACAAATGTAGGAACAGCACTGCATCGTGCCATAGACATAACGGAGCATAAATTTCCCCAACTTGCCTGGTTCTGTTGACGCGCGCGGCGTCGTCAGTTGACTCTCATGCAAGAGGTCCACTTTGCTACGGTCTCTGCGGAGCAGTAGTACACCTCGATAGCGATTCGTGGAGGCTCGGTACAAAACATTGGAGCACACATAGTAGAATACGGCCGTACGGAAACTGTACGTGTCGAACGTCGCAAATAGGGTTAACCACCAAAATGCCGTTCTGACCTCAGAGCTGGGTCTTTCTGGAGGGCCATGATTGTGCATAGCCATCACCGTAATCCCTACGTCCGGTTTCAGCAGGACTGACCAGCTAATCATGTATGACGAATACGGTTTCAGCATGATATCCTAGCTAAGTTTAGGCGGACAAGAGGAACAACCTTACGGCGGCACTACCCCTTTTGAATGATCACTGATACACCACGATGCCGTTACTGTGAGGTCGGTAGCGGTAAGGCACACGTTTGGCGCTACGGCTGGCGAATCATTTCACCAATGTGAATTGACCCGAGATTAGTTACAACTCGTTTGCATACTTGTCTTACGGGGTATTGCTGTCCTTTAACAGTAAATGGAACGACACGAGCGTCGCACGCCAGACCTCTCTGTCTGCCGCTGCGGCTGTACCACGTCTTTGTGATTGAAGATGGGGCTAGACGGGACGCGTATGTCAGCACGAAGCCTTCCATTGTACATCTGTGCGTAGCGTCCGGTAGAATCGGAGCTTTATTTTGACAGGTGGAGATCTGCTACCCAACCCAACCTAAGCTCCCGGTTATCTTGCAGACTCGGATTCTTGCCCGACGAGGTGAATGCGGCTCATTGTCGTAGTCGCTGTTTTGGCGACGGGAACCTTTTTGCATCAGCTGGGAATCCTTGAACATTCCATAACAGCCCGCATCGCATCGAACATCTTTAAACCAGACCGTCTGCCTTACCAGGCTCTGTTGCCCGTGCGCAGTCAGACTCGCGGCGTCCTTCGGCCTTCGACCGGTACCTTCTAAGCCGCACTCCAATATCTATAGGTGGTGCGTTGCGACATGATTTCGCGGTGACCTACTGGGTTCGCTAACAAATATAAGGCCAATGCGACGGATCGCTGGAACACGTTCAGACAAGAGTCGCCTGGTCCAGTCGCCGGCTACCCTTGTTCTGAAATTAGTCCGCTAATGTAGTTGGTGGCGTTTCTCCTACCCGCACGACACATATTAGCAATTAGTCTACACCCCCAGATCCAAGTCAGGCCCTCCAGGTGGTGCAAACGGCGCCTGCACAGGGCCTGCATACGGCTGGAAGTGAGGAGTCCCAAAGCCTCCCCCGTTCCCGGAGGCATTTTGTATGGCAATGTGACGGCCCGTTAATACCGCGCACGGCGATGGTAAAAGAAGGTCTGGTTCAGGATATGTGCAATCGCGCATAGGTAGTAAGTCGATCGTATTGCTACCGCACAATAGCGTAAAGGCATGCATTAGGTCGGTCTTTAGTGTGACACAGGACGAGTAATCTTGATCTTTACAGTACTCGATGGCCTAACGAGATGAAGCCATTTAGTCGTACGTGGCTGTTAGCGGTCTCGACTTAAACAGCCCCAGCGTCCGATATTAAGAAGGTCACGGAAGCCTACCGGCTTTCAAGCACCATACAGTTTAAAGCGGGACTAAGTTATCCCACACTTGACTCTGCACATGTGTCCAGGTCTAATCCTCCTTAGTTGTCGCCCGCGCTTCTTATCAAGGAACACTGCAGAAGACTCGACTTCAAATTCTAGTTAAGCAGCCACCGCTAGGACTCGGCACTAATGCCGTAATATTTATAGCCCAAGCCTTGTGAGGTATATCGTACCAATAGATTGAGGAGTTGAATATGTTGTCAACCCATCCTCCGCACGCCAACGGTGACTAGATCTACATCTCGCACGGTTCAGCATGTTGGCTAGACGATCCGCTCACGCTTGGGTCTACTCCCTCGTTGTGACGTTCCACGCACTATTAGGCGACGATTCTGTATGGATCTGTACCTCTCCCCGATATCTTTTCGAGAGTTTTTGAACCCAGTCGGATCAATAGAGTGTCGACCTCTTTTCCGTGGACTCGGGTCCGGTTAACATATATGTAGCTGATAGCAAACTAAACTCGGAACTGCGACCCCGTTGATGCCGATACAGAAGCTACTCACCCGCGGCTGACCTTAGACGTCGCGGTCCCGCAACTTTGGAGCACAGCTATTGACTAGATCTGCGGAGACGCCAAAGCTGGCGATCTTCCTACAGCCTGTAATAGTGTCACCGTTGCGTGAGATGGTGCCAAAGGATAATATCTCAACGCCCATAGAGAGGTATCGGCCCATGGTCATGCGCCGGACATATGATAACCTCTATGTTTTAGGAAAATCCGGTTATTTAGACGATTGGCACAGTAGCTAACCTCAGATTACCCCTATGGCACTACCATGTACGAAACGGCAAGGACGCGCATTAGCATAATAGTAAAGTGGCAGTCATCCCACTGGTCCAGTGGGAGGCAATAGGAAACACAATCTGATCACCTAGGTGGCGCGAAACCTGCATTAATTTCAACGTCACCACCGTCCAGAGTCTTAAGATAAAGCGCTGAGGGTGGCTTCGAACGCTCACATCTAATTGACTCCGTTATATGTATGTCTGCTACCCATGCTCTGTGTATGGTAAGCGACTACATGCAGTTTTCGAATCTCTAGATCTCCTACGAGTACTGCCGACCTCCTATAATGGGCGGACATCCTTTAATGTACAGAAACTACGTTGTTCCGCCCCCGATAATGGATAGACGCAGTACAGTATAGTGGGCTCTGGGCACCCGAAAGGGTATGCGGCTGATATGAATCCGTGCGACCGTAATACTAAGCTTGCGGACTAATATTTCCCGAAGGAGATTAAACATAATTAGAAGTCAACGGTGTCGCGAGTTTGTGTGTGTTGGTTACGTTGTGCTGACTCTGCGACGTCTGTTTCGAATAACCTGAGGGAAAGCCTTGATAACCCAGAATTCGCAGGCTACGACAGGCCACTCGACACTCGGGAATTCAAGAGCTGGTGAGACCAGCTACTCACCTTCGTGGGGTATACGCCAAATAATTTAGTCGTCCTGACGGACCCCAATGGCCCTGCATCGCGCGTAGTTAGACGGAACTCTGAACGGGCGTGACCAAGGGGGGCACGTGCATCATTATCGTAAGAATTGTTGCATGTTCATACTATTCGCCTATTTGATTACGGGACACGGGAGTGATCCTCGATGCTAAACCACATATTTCGTTCCTATACTAGGCACCCAACGGCCATCGCAAATTGCGCCTACACTTATAGTTCAGGCGCGATTAGAATAACTTAAGGCTAGGGATCTTGCCTAGTGGCTTCACGAAACCGGCCTTCGTTAGGTGACGCAAACTTCGGCGTGTCGATAGAGATCACTATTTGACGCATTTATATGAGTGCATCCATGAGGCTAGACTCACGTACAGGTCGTACCACTTATAAATGGAATGAACATTACGGCGTCATAGCGTTTAGTTAGACTTTGCTTCGCAAGGGAATCACTACAGCATTATTCGTTAATTACATGACAGCGGGACGCGTCGTGGGGTTCAAAAAGCCGTTCTTTGAGGCGATCGCGTGTACCAGCGGTGAGGAAGAACGGGTATGGCACTACTTGCTCACCGGGTGAAGTACAATAGATGTGTTGCGAGACATTCAGCATTGACCTTGGTCAGCTTGTGGCTGTTTATTGTCCCCTTGTCATGGCCGCTCTATTGTGAGCCGAGGAGGCAGTTTCCTTTGGAGAGTACGAACGTAACCCATAGACGCAACGCTTAGCACCACTTGTGCATGCGCGGTAAGGGGTTCGATTTCATCGAGCAGGCTCCAACGGGGCTGTTTTCTCGTTGTTCGACATGCTCTGGCCTATGGCCTATTAAATGTGGGCGTTGGATCCCGCGCCCAAGAGTGCGCTTCCATATGGGCGGAAGCCCTCCCCAACCGGAGGTAGGGCAGGGAGACTGCACTAAGCTATTAACTGGAGCTAGACCGAAGTATAATTCCCTTAGTTTCACGGCGCCCGCGGCACCATGAGGGCATCTGGGCGCTTACAGGCGTTGTCCTCAGGCGATTCATCCTGGACGAGCTTTATTTGAGATAGTGAACAAAAGTGCCCCACAACGCCAGCTCTGGGGCCCTGTCAGCCCGTAGATGGTGACGAGTGGAGCAGAACCCTTTGCGCTTCGCTCACAAGATAAATACCCACAGTGAAATGCGAGCTTTTAATGGAGCTGCTGACTAGCGTTCTCCACGCCAACCCGTAGGTTATGTTGGACTGATTGCCTCAGCGAATCGACGCCACAGCCCCGAGGGGAGTTACCTACAGCATATCCTAAGGCAATTACATAAGCCGTATGTTACGCTTAGGTCCCGTATACAGTACCCGATAGAAGTACGTCGAGTGCGATAGGACATCCTTTCTGGGAGTAGGTAGGGGCTACAGCTGACCACGGCTCTCCTGAGAGCATGGCGGCTGAGGTAATTTTGTTACTGATTTTGCATGCAATAACCAAGTCCATCTACTGAGCGAAGACTGAATAGGCGGTGTGGCTCAGGCTTACTTGGTCAGCTTTTGAGTACCACAGTCATACGGGTAGCAGATTTGCTGGAGAACTGGATAGTTCTCCCCTCTAGGGGACTACAGCGCCATCATAGACATGTAGTACTCTTGTCCTGTTCCAAGACATGTGGGGCTCCGGGCGCTCTGTACCGGGAAAATACCATTATGGTCTCAATCATCGCAGGGCATCATACGTAACCGTCGGAAGTTAAGGCCCCGAGCCAATGCCGGTCAATCGACTACACAAACTTAAATTGGTGGGTTTCAATATATGTGGTGAAAATAAGTTCGAAGAGGCATTGGGCACCTAAAACCTCTGACATATCGAACACATGCTTACCTCACAGACTAAATCTTACGCGGCTACGTCTGTCACACGCTCATTGTTAGATCGGTTGCCAGCGCGAACCCACATCCAGACGCTGAGCCTGAGAGAGACATCCGGGGCGTTACGCTATGGGCGATGAGCGTCAGTCCCTTTATTAGCGATTATCGGCTCCAAATGTCACTCGAAGAATCGGCATTGTCGTTTTTCCCGCCTGTAGCTCTTGTTCGCAGGGTATTACAAAACTACGGGACGCTTGAGACGTGTGATCCGGGAAGGTCCAAAACCTGGCATAGCGCCGGGTTGGTCCCGTTGTGGGAGTCGTATAGTGGTTATGTCGTACGAATGCAAGTTTCAATGCTATCTTGCATTTCCGAATGGTCCTCAATTTCACTCAAGTGGATCAAGAGGTGTTTCTCGGGTAGTGGTTATGCTGCGACTTTAGAAACTAGTCGCCTAGCCTCGGCCGCTGGCGGGGGAACAGGGAGGTCCGTGTAATTCCGGTTAGTTAAGTCGTTGGAGGCTTATATTTGTCGGTCAGTTTCATCAGCTAGCGCTTCAATTGGTCGTTACGACGTTCTGTGCCATAAAGTATCAAATATACATTGGTTCGCATTCGCACATCTAAACAGACAGCGGGTTCGTTCTAACGTAATCCGCCTCCCCGATATTCATACAAAGAGTTTCTTATGACAACAACCGAGACTTTACCATGCGCTATTCTACGCAGATGGTTTAAGCATATTGCGGGGCTTGCGAAGGTCAGATCGATGGATCTAATCCAGGCGTATGGGTGGACCCTTGTGCCAGGACACTCGCATTCGAGGGATTCCGGCCATCATGAGGTTAATCTAGACAGGCTGCGATTGGACGGAGGTCGTAGCTCCTCAAATGCCGAAACACGTTGTTTGTCACGTATTGGATGCGTGGTTGCCAAGAACTCTCGCAACAAGTATCCGGGCGGGGTGCCAGTGAACAAGGCACTCTCTTGAACGGCACTTTCATAACGGGCACGAAAGAACTGCTGTGGACCTCGGGACCATAAATGTTGCAACGCGTCCAGTTGCACGCTTCAAGCCCCGAGCCACAAGTCGGAAAGGCTAATTCGAGCTTTGCAAGTTTATGGAAACCCCGCTGTATATCCTAACAACCATCATGGCAATACTATGAAGATACGGACACCAGGGCGCCAGCAGCCTTTCATGTCTTCTCAGGCCTTCCGGCTCAAGCACAGTAGCAGCTCTGCATGTGGCACACGGGGCAGCTGACCATCCCCTCTCCTACTCTATGACGGGGAGAATAGAAACAGGCGTTAGGGATGCGACGGGTCTGTGTTGATCAATGACACGTCGTCGGAAAAAGGGGCTCTTGCAGCATTTTACAAACTAATGGAAGGACACACGAACAATTGACTTATCTAGCTTCCGGGATCGCCTTGCATGTGAGCGGTATCTCTGTACTGTGCACCGCCACGGTACGTGCGTACGCACTGTAGACGTGTTTGGAAGGCTCCGGATCATGGAAGGGCTCTCTGATACGCTCCGATCGTCCATTGCCGCGGTCCGGCGCTCCGACTAGGAGGAGATACGGCACCTGGGGATGGTTCTGTTCCCCCACTTTCTAATTAATAATCGGATGACCGTTTCCTTTAAGTCGCTCTCGTGGTCGGAACTTACATCGGATCGTATGTACACTTCATTGCGTGTGTTCGCCATCGCAAAGACAAGGATCTATATGAAAAGACTTACAGCACGATACGCTTACCCCAATCAAGTGATGATGGCATTCAAGTGATAGATCACAATATTCTTCGTCACCAAGGACAGATAGCAGCGGGCTAACGATTTCCGAATCGGGGATAGTCCAGTTCAAGATTAGACCGTAACGTATGAAGCGCTCGCTACCGTTCACGCGCACCTCGCCGTCGCCAAGCACAAAGATTCACCAATGTGTAGCAAGCGCTATCGTCAAAGGTAGATAGTAAAAATAGGTATTTTTTGCCAAAACTTAACCTTAGGGTTGAGGGCGGAGATGTCCATTAAAGAAATCATTCTATGCCACTAATAGCTCAGTGGAGAATCGTATAGGGTGGAATGGACATCGTGACGCTGTGGTACTGCTGTACTCCTACCAAAGTAAGAACGCAATCATTGTCCAGCCTTGCTCGCAAAGTTTGGATTTACCAGCGTCGTGCCTCATATGCACTTTGCGGAACAAAGGTTCCGTAAATTTTACATGCATGACAACAGGTCCATCAAGCTACGAGTATAAGCTAGACGCCCCTTACCTACCACCGCCAAAGAGGTCCTGGTCATTATCCCCGCATTGGAAGAGCCTATCGGCGCTTTTCGTTGAGTTTCAGTCCATTGGCCGAAAATGCTTTGTTTCTGAAGTCCGTGAGTAAGTTATTACACTTGTTGTCTCGCCCAAACTCAAGGGAGTGACGCCGTACGTTAAAATCGTTGCCTTTGGAGCTCGAAACGAGTGCGTGCCGAGATTCCCCACGTCGTTCTTCATGTCCATGACTAACTCATTCTGTTGTCTGTATGTCACAACAATTCGGTATTTGGGCCACACACCTCATTCGGAAATACAGCATACCCGCATAGCGGTATCTCTTGGATTCATTAATCGTAGTTAACTCACTATAACGCGCGCCGGGCGCGATGAATTGACAACGGTCTACCTCTAACCGGGGACGAGCCCGCGGTGCAAGCGACAAGTTGGAGACTCTGGTAGTTGCTTAATCTAATGGTTGAAGGGTTATGACATTCATTCTCTCCAATGTCCAAGCGGCTTATCAATGCGCACATCGCCGACTCACATGGCCGGGACTGGATCATCAAACGTCGTATGGACAGAGTATAGCTTCGCGACAGATCATGTCGGCCTATTATCGCACAGCGGCGTTCGGAGGCTGTTCGACACAGACGGGGCCACTAGTAGACGTGATATCCAGCTCAATGTCCAGCGCCCGACCGGGAGCACGGAATAGTGGAATATTCCTAAGACTGTGGCCTAATCACCCCTTTAAACAGTCTACTGGTGAGATCCTGTTATTATTCTTATGTGAGTCTGGAGGAGCTTCCGGCGATGACAGGGTGGAGGCTTATTCGAGAGGACACGTCCTGAAGGAGCATTAGTTACGGCAATCGGATCGGCTCATCAATACTAGCATGCGCACGAGCATGCCAAGAAACTCTACACAGTCAGCGCATTGGCGGGCGAACTTTTACATTGGAATGGCGTGTCTAGATTTCATGGAGCATATTACATGTAATAACAACAATCACATAATAACGGATCGCACAGGTGCGGCGACCCGACGGATCTGAACAGCGCTTTGAGACCTAGTTCTATCTACGGGGCAGGATGGCTAGGAAAAACTCAGGATTCTAAGGGTTGCTTCCTCTTGGAACCACCGAGGTCGGTTTGCAGTTCGACGGCCAGATGTTTCTGCTTACGAATAGTAACTGTATTCTCAAAGGAATTATTACACTATAGATTCCAGATACAGACTCTAGTATTAAGGCAACAATAGTCCAGATTGATTCCGCAATACAGAGTGGTTAAGTTCATCCTGCATGTTAGTAGCGGGGTCGGCAAATGTATTGTGATCGATGATGGACAGAACGAATGGGGAGCTGCGTTTCGTCGATAGGTCCCATGACAGGAGGTAGTTGTACTATGCTTAAGAGAGTTAATTGTCTTACACTACCACCGACCAGTGCCCCACCGTGCACTGGTTGCGCGAGCACAAGCCATTCCAGGACAACAGTGTGGACCTGTAGAAGTTACCTGCCGCCCACCTTCCCTCCATAACGTTAGAAAAGGATGGGGCTCTTACTGCCGACCCGAGCCCATGGAGGCTCTGGGTTTATGCTAACTGCGCTGTGACAAGATTGTATCCTGTTACAAAGCAGAGGCCGGTGGTCTTTTGTTGTGTAACTTATAATGACCCGAGGACACACACTTAAACTGTAGTCTTAGTTTAGAACAAATCGGGAACTCTCCTCCTAATTCCCTTGATTGTCGTCGCGTTCTAGCCTCGCCCATGACAGAATCTATAGACAACTCTGATACATACAAATGGTGTTAATGGAGTTCCGGGCA";
    //char *s = "AATCCGTTCGGA";
    //char *t = "TTCGGATACGTACG";
    /////////////////////////////////////////////////////
	//define a penalty matrix
    //if match +1
    //mismatch(substitution) -2
    //linear gap -2
	/////////////////////////////////////////////////////
    int m = strlen(s)+1;//an extra row with zeros
    int n = strlen(t)+1;//an extra column with zeros

    int **A = new int *[m];
    for (int i=0;i<m;i++)
        {A[i] = new int[n];}

    for(int i=0;i<m;i++){A[i][0]=0;}//initiate the first row with zeros
    for(int j=1;j<n;j++){A[0][j]=0;}//initiate the first column with zeros

    int max_score =0;
    int row_idx = 0;
    int col_idx = 0;
    max_score = local_align(s,t,A,row_idx,col_idx);//get the position of max_score (row_idx, col_idx)
    cout << max_score << endl;

    int row_end = 0;
    int col_end = 0;
    int i=row_idx;
    int j=col_idx;

    //Keep going down to find the end of alignment when s or t reaches its end
    while(i<m-1 && j<n-1)//start from the maximum score position
    {
        int step_max = max(A[i+1][j],max(A[i+1][j],A[i+1][j+1]));
        if(A[i+1][j+1]==step_max){i++;j++;}
        else if(A[i+1][j]==step_max){i++;}
        else{j++;}
        if(i==m-1||j==n-1) {row_end=i;col_end=j;}
    }
    cout << "row_end:" << row_end << ' ' << "col_end:" << col_end << endl;

    stack<char> s_stack;//use stack for backtracking and reverse output of alignment
    stack<char> t_stack;
    m = row_end;//the end index is the position in score matrix, not the position of string, string_position = matrix_position -1
    n = col_end;//same as above

    while(m&&n)//backtracking to get the starting position of s and t
    {
        if(A[m][n]==A[m-1][n]-2)
        {
            s_stack.push(s[m-1]);
            t_stack.push('-');
            m--;
        }
        else if(A[m][n]==A[m][n-1]-2)
        {
            t_stack.push(t[n-1]);
            s_stack.push('-');
            n--;
        }
        else
        {
            t_stack.push(t[n-1]);
            s_stack.push(s[m-1]);
            m--; n--;
        }
    }

    int row_start = m;//Notice that the break condition makes the row_start index can be used directly as the string index
    int col_start = n;//same as above

    cout << "row_start:" << row_start << ' ' << "col_start:" << col_start << endl;
    cout << s[row_start] << "--->" << s[row_end-1] << endl;
    cout << t[col_start] << "--->" << t[col_end-1] << endl;

    while(!s_stack.empty()){s_stack.pop();}
    while(!t_stack.empty()){t_stack.pop();}

    //Use the information of row_start, row_end to get the suffix of s
    char *s1 = substring(s,row_start,row_end-row_start);
    //Use the information of col_start, col_end to get the prefix of t
    char *t1 = substring(t,col_start,col_end-col_start);
    m = strlen(s1)+1;
    n = strlen(t1)+1;

    int **B = new int *[m];
    for (int i=0;i<m;i++)
        {B[i] = new int[n];}

    for(int i=0;i<m;i++){B[i][0]=0;}//initiate the first row with zeros
    for(int j=1;j<n;j++){B[0][j]=0;}//initiate the first column with zeros

    max_score = global_align(s1,t1,B);
    m--;n--;//the last index of matrix should be length-1
    cout << B[m][n] << endl;

    while(m||n)//backtracking
    {
        if(m==0)
        {
            t_stack.push(t1[n-1]);
            s_stack.push('-');
            n--;
        }
        else if(n==0)
        {
            s_stack.push(s1[m-1]);
            t_stack.push('-');
            m--;
        }
        else if(B[m][n]==B[m-1][n]-2)
        {
            s_stack.push(s1[m-1]);
            t_stack.push('-');
            m--;
        }
        else if(B[m][n]==B[m][n-1]-2)
        {
            t_stack.push(t1[n-1]);
            s_stack.push('-');
            n--;
        }
        else
        {
            t_stack.push(t1[n-1]);
            s_stack.push(s1[m-1]);
            m--; n--;
        }
    }

    while(!s_stack.empty()){cout << s_stack.top(); s_stack.pop();}
    cout << endl; cout << endl;
    while(!t_stack.empty()){cout << t_stack.top(); t_stack.pop();}

    return 0;
}
