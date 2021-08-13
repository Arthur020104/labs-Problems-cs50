#include <stdio.h>
#include <cs50.h>

int main(void){
    int ano=0;
    int n;
    int z;
    do{
    n = get_int("Quantas llammas tem essa populacao?(minimo 9)");
    }
    while(n<9 );
    do{
    z = get_int("Para quantas llamas a populacao tem que ir?");
    }
    while(z<n);
    
    while(n<z){
        ano++;
        int gain= n/ 3;
        int perda= n/ 4;
        n +=gain-perda;
    }
    printf("Demorara:%i\n",ano);

}