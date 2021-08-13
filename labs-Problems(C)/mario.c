#include <cs50.h>
#include <stdio.h>

int main(void){
    int n;
    do{
        n=get_int("Height:");
    }
    while(n<1 || n>8);
    int z= n - 1;
     for (int i = 0; i < n; i++){
         int f =5;
        for(int j= 0; j<= i;j++){
            if(f==5){
        for(int h=0;h < z;h++){
            printf(" ");
        }
        f =0;
        z--;
        }
            printf("#");
        }
        int g = 1;
        while(g > 0){
        g--;
        printf("  ");
        for(int j = 0; j <= i;j++){
            printf("#");
            
            }
        printf("\n");
        
    }
    }
}


