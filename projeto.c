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

// Função que verifica se tem letra na entrada
// Primeiro ela verifica se é digito
// Se não for, verifica se o char[i] da entrada não esta dentro do vetor de operadores permitidos
int verificaEntrada(char* entrada)
{
    int i;
    char operadores[8] = { '+', '-', '*', '/', '^', ' ', '(', ')' };

    // Useu strlen -1 para que o último char em um fgets (\n) não seja considerado
    for (i = 0; i < strlen(entrada) - 1; i++)
    {
        if(!isdigit(entrada[i]) && strchr(operadores, entrada[i]) == NULL)
        {
            return 1;            
        }
    }
    
    return 0;
}

// Funcão que checa se o número de parenteses está correto
// A cada '(' é +1 no contador
// A cada ')' é -1 no contador
// Se devolver 0, quer dizer que o número está correto
int verificaParenteses(char* entrada)
{
    int i, contadorParenteses = 0;
    for (i = 0; i < strlen(entrada) - 1; i++)
    {
        if(entrada[i] == '(')
        {
            contadorParenteses ++;          
        }
        else if(entrada[i] == ')')
        {
            contadorParenteses --;
        }
    }
    return contadorParenteses;
}

// Função que verifica se existe espaços entre dois números
int verificaEspacosEntreNumeros(char* entrada)
{
    int i, flagDigito = 0, flagEspaco = 0;
    for (i = 0; i < strlen(entrada) - 1; i++)
    {
        if(isdigit(entrada[i]))
        {
            if(flagEspaco > 0)
            {
                return 0;
            }
            flagDigito++;
        }
        else if(entrada[i] == ' ')
        {
            if(flagDigito > 0)
            {
                flagEspaco++;
            }            
        }
        else 
        {
            flagDigito = 0;
            flagEspaco = 0;
        }
    }
    return 1;
}

// Função que retira apenas os espaçõs a mais, deixando os necessários para separar a expressão do jeito certo
// Por exemplo: 6  + 23  *   0 -> 6 + 23 * 0
// Estou considerando que sempre vai haver espaços para separar números de operadores
// A o aux está ai para controlar quando adicionar espaço na fila
// Por exemplo, aux = 1 pode, então quando for espaço ele cai no else if e adiciona
// virando o aux = 0 (não pode). O aux só vai virar para aux = 1 quando for adicionado mais um número para a fila
void retirarEspacosAMais(char* entrada, Fila* saida)
{
    int i, aux = 0;
    ElementoDeFila c;

    for (i = 0; i < strlen(entrada); i++)
    {
        if(entrada[i] != ' ')
        {
            c.i = entrada[i];
            guarde_na_fila(saida, c);
            aux = 1;
        } 
        else if(aux == 1)
        {
            c.i = entrada[i];
            guarde_na_fila(saida, c);
            aux = 0;
        }
    }
}

void insereEspacos(Fila entrada, Fila* saida)
{
    int i, tamanhoFilaEntrada, flagDigito = 0, flagOperador = 0, flagEspaco = 0;
    ElementoDeFila elementoFila;
    tamanhoFilaEntrada = entrada.posicao_do_ultimo_ElementoDeFila;
    for (i = 0; i < tamanhoFilaEntrada; i++)
    {
        if(isdigit(recupere_um_item_da_fila(entrada).i))
        {
            if(flagOperador > 0)
            {
                elementoFila.i = ' ';
                guarde_na_fila(saida, elementoFila);
                flagOperador = 0;
            }
            flagDigito++;
        }
        else if(recupere_um_item_da_fila(entrada).i != ' ')
        {
            if((flagDigito > 0 || flagOperador > 0))
            {
                elementoFila.i = ' ';
                guarde_na_fila(saida, elementoFila);
                flagDigito = 0;
            }
            flagOperador++;
        }
        else 
        {
            flagOperador = 0;
            flagDigito = 0;
        }
        elementoFila.i = recupere_um_item_da_fila(entrada).i;
        guarde_na_fila(saida, elementoFila);
        remova_um_item_da_fila(&entrada);
    }
    elementoFila.i = '\n';
    guarde_na_fila(saida, elementoFila);
}

// Funcão que recebe um operador e devolve qual número ele representa na tabela
int converterOperador(char o) 
{
    switch (o)
    {
    case '(':
        return 0;
        break;
    
    case '^':
        return 1;
        break;

    case '*':
        return 2;
        break;

    case '/':
        return 3;
        break;
    
    case '+':
        return 4;
        break;

    case '-':
        return 5;
        break;

    case ')':
        return 6;
        break;
    }
}

// Funcão que recebe dois operados (o que está na expressão e o que está na pilha) e devolve se é ou não para desempilhar
// Ela utiliza a funcão 'converterOperador' para auxiliar no resultado
int regraTabela(char exp, char pilha)
{
    int posicaoOpExpressao, posicaoOpPilha;
    int tabela[7][7] = { 0, 0, 0, 0, 0, 0, 2,
                         0, 0, 1, 1, 1, 1, 1,
                         0, 0, 1, 1, 1, 1, 1,
                         0, 0, 1, 1, 1, 1, 1,
                         0, 0, 0, 0, 1, 1, 1,
                         0, 0, 0, 0, 1, 1, 1,
                         0, 0, 0, 0, 0, 0, 0 };
                        
    posicaoOpExpressao = converterOperador(exp); //0
    posicaoOpPilha = converterOperador(pilha); // 4
    return tabela[posicaoOpPilha][posicaoOpExpressao];
}

// Função que recebe uma fila e printa ela no console
void printaFila(Fila f)
{
    printf("\n");
    while (f.posicao_do_ultimo_ElementoDeFila >= 0)
    {
        printf("%c", recupere_um_item_da_fila(f).i);
        remova_um_item_da_fila(&f);
    }
    printf("\n");
}

int main() {
    char entrada[100];
    int guardaraPilha, i;
    Pilha operadores;
    Fila expressao, saida, intermediaria;
    ElementoDePilha elementoPilha;
    ElementoDeFila elementoFila;

    // Recebe a expressão
    printf("Digite a expressão: ");
    fgets(entrada, sizeof(entrada), stdin);
    fflush(stdin);

    // Inicializa a pilha e as filas necessárias
    inicialize_a_pilha(&operadores);
    inicialize_a_fila(&expressao);
    inicialize_a_fila(&saida);
    inicialize_a_fila(&intermediaria);

    while(verificaParenteses(entrada) != 0)
    {
        printf("Foi encontrado um número incorreto de parênteses\n");
        printf("Digite a expressão novamente: ");
        fgets(entrada, sizeof(entrada), stdin);
        fflush(stdin);
    }

    while(verificaEntrada(entrada))
    {
        printf("Foi encontrado um char não permitido na expressão\n");
        printf("Digite a expressão novamente: ");
        fgets(entrada, sizeof(entrada), stdin);
        fflush(stdin);
    }

    while(verificaEspacosEntreNumeros(entrada) == 0)
    {
        printf("Foi encontrado espaços entre números\n");
        printf("Digite a expressão novamente: ");
        fgets(entrada, sizeof(entrada), stdin);
        fflush(stdin);
    }

    retirarEspacosAMais(entrada, &intermediaria);

    insereEspacos(intermediaria, &expressao);

    // Loop que vai acontecer até não existir mais elementos na fila de expressão e na pilha de operadores
    while (!(expressao.posicao_do_ultimo_ElementoDeFila <= 0 && operadores.posicao_do_ultimo_elemento < -1))
    {
        if(isdigit(recupere_um_item_da_fila(expressao).i))
        {
            elementoFila.i = recupere_um_item_da_fila(expressao).i;
            guarde_na_fila(&saida, elementoFila);
            remova_um_item_da_fila(&expressao);
        } 
        // Condição que ajuda a controlar os espaçõs necessários    
        else if(recupere_um_item_da_fila(expressao).i == ' ' && saida.vetor_de_ElementoDeFilas[saida.posicao_do_ultimo_ElementoDeFila].i != ' ')
        {
            elementoFila.i = ' ';
            guarde_na_fila(&saida, elementoFila);
            remova_um_item_da_fila(&expressao);
        }
        else if(recupere_um_item_da_fila(expressao).i != ' ')
        {
            if(expressao.posicao_do_ultimo_ElementoDeFila > 0)
            {                  
                // Loop para ajudar passar por todos operadores na pilha          
                for (i = operadores.posicao_do_ultimo_elemento; i >= 0; i--)
                {
                    guardaraPilha = regraTabela(recupere_um_item_da_fila(expressao).i, recupere_um_item_da_pilha(operadores).i);
                    // Se o 'guardaraPilha' == 2 quer dizer que encontramos '(' com ')'
                    if(guardaraPilha == 2)
                    {
                        remova_um_item_da_pilha(&operadores);
                        remova_um_item_da_fila(&expressao);
                        remova_um_item_da_fila(&expressao);
                        continue;
                    }
                    // Se 'guardaraPilha' == 1 quer dizer que True
                    else if(guardaraPilha == 1) 
                    {

                        elementoFila.i = recupere_um_item_da_pilha(operadores).i;
                        guarde_na_fila(&saida, elementoFila);
                        remova_um_item_da_pilha(&operadores);
                        // Essa codição checa se o último elemento da fila de saída é um espaço. Se não for, adiciona um
                        if(saida.vetor_de_ElementoDeFilas[saida.posicao_do_ultimo_ElementoDeFila].i != ' ')
                        {
                            elementoFila.i = ' ';
                            guarde_na_fila(&saida, elementoFila);
                        }
                        continue;
                    }
                    break;
                }
                // No final de cada loop dos operadores, adicinamos o operador da fila de expressão na pilha de operadores
                elementoPilha.i = recupere_um_item_da_fila(expressao).i;
                guarde_na_pilha(&operadores, elementoPilha);
                remova_um_item_da_fila(&expressao); 
            }
            // Só vai cair aqui se não existir mais elementos na fila de expressão, então adicionamos um espaço e adicionamos o operador da pilha
            else 
            {
                elementoFila.i = ' ';
                guarde_na_fila(&saida, elementoFila);
                elementoFila.i = recupere_um_item_da_pilha(operadores).i;
                guarde_na_fila(&saida, elementoFila);
                remova_um_item_da_pilha(&operadores);
            }
        }
        // Retira da fila de expressão caso o último elemento da mesma ja for um espaço, não sendo necessário colocar mais um
        else
        {
            remova_um_item_da_fila(&expressao);
        }
    }
    printaFila(saida);
}