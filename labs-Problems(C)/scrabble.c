#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scrabble(string s);

int main(void)
{
    string string0 = get_string("Player1: "); //pegando a string de cada player
    string string1 = get_string("Player2: ");
    
    //Comparando a jogada de cada jogador para anunciar um campeao
    if(scrabble(string0)>scrabble(string1))
    { 
        printf("Player1 venceu!!\n");
    }
    else if(scrabble(string0)==scrabble(string1)){
        printf("EMPATE!!\n");
    }
    else
    {
        printf("Player2 venceu!!\n");
    }
}

int scrabble(string s)
{ 
    //funcao que define os pontos de cada jogador
    int pointstotal = 0;
    int Points[26] = {1 , 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};//regra do jogo
    
        for(int i=0, n = strlen(s); i<n;i++)
        { 
            //loop definido pelo tamnahoda string
        int a = tolower(s[i]);//coloca todos os caracteres da string em lowercase e defini estes como inteiros no padrao ASCII
        if(a >= 97 && a <= 122)
    { 
            //filtra apenas caracteres em lowercase
            pointstotal += Points[ a - 97]; //Soma com base nas regras do jogo os pontos por caracter da string ao total
        }
    }
    return pointstotal;
}
