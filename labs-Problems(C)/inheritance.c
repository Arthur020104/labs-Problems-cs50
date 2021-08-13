// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // criando uma nova familia com 3 geracoes
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Criando um novo individuo com `generations`
person *create_family(int generations)
{
    // alocando memoria para uma nova pessoa
    person *pessoa = malloc(sizeof(person));
    
    if(pessoa == NULL)
    {
        return  pessoa;
    }

    // Geração com dados dos pais
    if (generations > 1)
    {
        // chamando recursivamente Recursively create blood type histories for parents
        for(int i = 0; i < 2; i++)
        {
            pessoa->parents[i] = create_family(generations - 1);
        }

        //pegando os alleles(alelos) dos pais aleatoriamenrte
        pessoa->alleles[0] = pessoa->parents[0]->alleles[rand() % 2];
        pessoa->alleles[1] = pessoa->parents[1]->alleles[rand() % 2];
        
    }

    else
    {
        //Setting parents pointers to NULL
        for(int i = 0; i < 2; i++)
        {
            pessoa->parents[i] = NULL;
        }

        // TODO: Randomly assign alleles
        for(int i = 0; i < 2; i++)
        {
            pessoa->alleles[i] = random_allele();
        }
    }

    return pessoa;
    return NULL;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if(p == NULL)
    {
        return;
    }
    else if(p->parents[0] == NULL)
    {
        free(p);
    
    else
    {
        for(int i = 0; i < 2; i++)
        {
          free_family(p->parents[i]);
        }
    }
}

// Print each family member and their alleles.
void print_family(person *p, int generation)tvbbbbbbbbbb opopo0000000000000000032
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
