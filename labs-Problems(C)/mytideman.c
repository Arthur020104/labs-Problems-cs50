#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int MAX = 9;

int boolean(int score[], bool arr[MAX][MAX], int argc);
int wineer(int score[], bool arr[MAX][MAX], string candi[], int argc);
int strgtonum(string s);

int main(int argc, string candi[])
{
    if (argc < 2)
    {
        printf("Falta candidatos!\n");
        return 1;
    }
    if(argc - 1 > MAX)
    {
        printf("[ERROS]Ultrapassou o numero maximo de candidatos.\n");
        return 1;
    }
    bool arr[MAX][MAX];
    int n;
    do
    {
        n = get_int("Number of voters: ");
    }
    while(n < 1 );

    string vote[n][MAX];
    for(int i = 0; i < n; i++)
    {
        int rank = 0;
        for(int j = 0; j < argc - 1; j++)
        {
            rank++;
            vote[i][j] = get_string("Rank %i:",rank);
        }
        printf("\n");
    }


    int score[MAX];
    for(int i = 0; i < MAX; i++)
    {
        score[i] = 0;
    }


    for(int j = 0; j < n; j++)
    {
        for(int f = 0; f < argc - 1; f++)
        {//
        for(int i = 0; i < argc -1; i ++)
        {
            if(strcmp(vote[j][f], candi[i + 1]) == 0)
            {
                score[i] += 9 - f;
            }
        }
        }
    }
    wineer(score, arr, candi, argc);
}

int wineer(int score[], bool arr[MAX][MAX], string candi[], int argc)
{
    boolean(score, arr, argc);

    int w = 0;
    int desemwin[2];
    for(int i = 0; i < argc - 1; i ++)
    {
        int v = 0;
        for(int j = 0; j < argc - 1; j++)
        {
            if(arr[i][j] == true)
            {
                v++;
            }
            if(v == 2)
            {
                printf("The winner is %s\n",candi[i + 1]);
                return 0;
            }
        }
        
       // if(v == 1)
        //{
       //    desemwin[w] = i;
       //     w++;
        //}
    }
   // if(score[desemwin[0]] > score[desemwin[1]])
   // {
   //     printf("The winner is %s\n",candi[desemwin[0] + 1]);
    //}
   // else
   // {
   //     printf("The winner is %s\n",candi[desemwin[1] + 1]);
   // }
    
    return 1;
}
/*
int strgtonum(string s)
{
    int a = 0;
    for(int i=0, n = strlen(s); i<n;i++)//tava usando antes para verificacao de nome atraves da atribuicao da soma dos caracteres em binario(BASEADO NO ASCII)
        {
        a += tolower(s[i]);
        }
    return a;
}
*/

int boolean(int score[], bool arr[MAX][MAX], int argc)
{
    for(int i = 0; i < argc - 1; i++)
    {
        for(int j = 0; j < argc - 1; j++)
        {
            if(score[i] > score[j])
            {
                arr[i][j] = true;
            }
            else
            {
                arr[i][j] = false;
            }
        }
    }
    return 0;
}