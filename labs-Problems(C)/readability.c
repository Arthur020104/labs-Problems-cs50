#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int gradelevel(string s, int total[3]);

int main(void)
{
    int total[3];
    string texto = get_string("Digite o texto: ");

    if(gradelevel(texto, total ) < 1)
    {
        printf("Before grade 1 \n");
        printf("%i letter(s)\n%i word(s)\n%i sentences(s)\n", total[1],total[0],total[2]);
    }
    else if(gradelevel(texto, total) > 16)
    {
        printf("Grade 16+ \n");
        printf("%i letter(s)\n%i word(s)\n%i sentences(s)\n", total[1],total[0],total[2]);
    }
    else
    {
        printf("Grade %i \n", gradelevel(texto, total));
        printf("%i letter(s)\n%i word(s)\n%i sentences(s)\n", total[1],total[0],total[2]);
    }


}

int gradelevel(string s, int total[3])
{
    int words = 1;
    int sentences = 0;
    int letras = 0;
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        int a =(s[i]);
        if(s[i]==' ' )
        {
            words++;
        }
        else if(s[i] != ' ' && s[i] != '?' && s[i] != '!' && s[i] != '.' && s[i] != ',' && s[i] != '-' && s[i] != ';' && a!= 39 && a!= 34)
        {
            letras++;
        }
        else if(s[i] == '?' || s[i] == '!' || s[i] == '.')
        {
            sentences++;
        }
    }
        double Si = ((double)sentences/(double)words)*100;
        double l = ((double)letras/(double)words)*100;
        double g = (0.0588 * l) - (0.296 * Si) - 15.8;

        g = round(g);
        total[0] = words;
        total[1] = letras;
        total[2] = sentences;
        return g;
}