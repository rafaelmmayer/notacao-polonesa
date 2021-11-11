#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_MAXIMO_DE_PILHA 100
#define TAMANHO_MAXIMO_DE_FILA 100

// Pilha
typedef struct {
    char i;
} ElementoDePilha;

typedef struct {
    ElementoDePilha vetor_de_elementos [TAMANHO_MAXIMO_DE_PILHA];
    int      posicao_do_ultimo_elemento;
} Pilha;

void inicialize_a_pilha (Pilha* p)
{
    (*p).posicao_do_ultimo_elemento=-1;
}

void guarde_na_pilha (Pilha* p, ElementoDePilha e)
{
    (*p).posicao_do_ultimo_elemento++;
    (*p).vetor_de_elementos[(*p).posicao_do_ultimo_elemento] = e;
}

ElementoDePilha recupere_um_item_da_pilha (Pilha p)
{
    return p.vetor_de_elementos[p.posicao_do_ultimo_elemento];
}

void remova_um_item_da_pilha (Pilha* p)
{
    (*p).posicao_do_ultimo_elemento--;
}
// ---------------------------------------------------------------------------------

// Fila
typedef struct {
    char i;
} ElementoDeFila;

typedef struct {
    ElementoDeFila vetor_de_ElementoDeFilas [TAMANHO_MAXIMO_DE_FILA];
    int      posicao_do_ultimo_ElementoDeFila;
} Fila;

void inicialize_a_fila (Fila* p)
{
    (*p).posicao_do_ultimo_ElementoDeFila=-1;
}

void guarde_na_fila (Fila* p, ElementoDeFila e)
{
    (*p).posicao_do_ultimo_ElementoDeFila++;
    (*p).vetor_de_ElementoDeFilas[(*p).posicao_do_ultimo_ElementoDeFila] = e;
}

ElementoDeFila recupere_um_item_da_fila (Fila p)
{
    return p.vetor_de_ElementoDeFilas[0];
}

void remova_um_item_da_fila (Fila* p)
{
    int i;
    
    for (i=1; i<=(*p).posicao_do_ultimo_ElementoDeFila; i++)
        (*p).vetor_de_ElementoDeFilas [i-1]=(*p).vetor_de_ElementoDeFilas [i];

    (*p).posicao_do_ultimo_ElementoDeFila--;
}
// ---------------------------------------------------------------------------------

void retiraEspacoEntrada(char* entrada, Fila* saida)
{
    int tamanhoString, i;
    ElementoDeFila c;
    tamanhoString = strlen(entrada);

    for (i = 0; i < tamanhoString; i++)
    {
        if(entrada[i] != ' ')
        {
            c.i = entrada[i];
            guarde_na_fila(saida, c);
        }
    }
}

int main() {
    char entrada[100];
    Pilha operadores;
    Fila expressao, saida;
    ElementoDePilha aux;

    fgets(entrada, sizeof(entrada), stdin);
    fflush(stdin);

    inicialize_a_pilha(&operadores);
    inicialize_a_fila(&expressao);
    inicialize_a_fila(&saida);

    retiraEspacoEntrada(entrada, &expressao);
    
    for (int i = 0; i <= expressao.posicao_do_ultimo_ElementoDeFila; i++)
    {
        if(isdigit(expressao.vetor_de_ElementoDeFilas[i].i))
        {
            guarde_na_fila(&saida, expressao.vetor_de_ElementoDeFilas[i]);
        }
        else 
        {
            aux.i = expressao.vetor_de_ElementoDeFilas[i].i;
            guarde_na_pilha(&operadores, aux);
        }
    }   
    
}