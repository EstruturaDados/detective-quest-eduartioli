#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa cada sala (nó da árvore binária)
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    struct Sala *esquerda;   // Ponteiro para sala à esquerda
    struct Sala *direita;    // Ponteiro para sala à direita
} Sala;

/**
 * criarSala() - Cria uma nova sala dinamicamente
 * 
 * Parâmetros:
 *   nome: string com o nome da sala a ser criada
 * 
 * Retorno:
 *   Ponteiro para a sala criada
 * 
 * Descrição:
 *   Aloca memória dinamicamente para uma nova sala,
 *   inicializa o nome e define os ponteiros esquerda
 *   e direita como NULL (sem caminhos inicialmente).
 */
Sala* criarSala(const char *nome) {
    // Aloca memória para a nova sala
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    
    // Copia o nome da sala
    strcpy(novaSala->nome, nome);
    
    // Inicializa os ponteiros como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * explorarSalas() - Permite a navegação interativa pela mansão
 * 
 * Parâmetros:
 *   salaAtual: ponteiro para a sala onde o jogador está
 * 
 * Descrição:
 *   Função recursiva que permite ao jogador explorar a mansão.
 *   Exibe o nome da sala atual e oferece opções de movimento.
 *   A exploração continua até alcançar uma sala sem saídas
 *   (nó-folha) ou até o jogador escolher sair.
 */
void explorarSalas(Sala *salaAtual) {
    // Verifica se a sala existe
    if (salaAtual == NULL) {
        printf("Você não pode ir por esse caminho!\n");
        return;
    }
    
    // Exibe a sala atual
    printf("\n==========================================\n");
    printf("Você está em: %s\n", salaAtual->nome);
    printf("==========================================\n");
    
    // Verifica se é uma sala sem saídas (nó-folha)
    if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
        printf("\nEsta sala não possui mais caminhos.\n");
        printf("Fim da exploração!\n");
        return;
    }
    
    // Mostra as opções disponíveis
    printf("\nOpções de movimento:\n");
    if (salaAtual->esquerda != NULL) {
        printf("  [E] - Ir para a esquerda\n");
    }
    if (salaAtual->direita != NULL) {
        printf("  [D] - Ir para a direita\n");
    }
    printf("  [S] - Sair do jogo\n");
    
    // Lê a escolha do jogador
    char escolha;
    printf("\nSua escolha: ");
    scanf(" %c", &escolha);
    
    // Processa a escolha
    switch (escolha) {
        case 'e':
        case 'E':
            if (salaAtual->esquerda != NULL) {
                explorarSalas(salaAtual->esquerda);
            } else {
                printf("\nNão há caminho à esquerda!\n");
                explorarSalas(salaAtual);
            }
            break;
            
        case 'd':
        case 'D':
            if (salaAtual->direita != NULL) {
                explorarSalas(salaAtual->direita);
            } else {
                printf("\nNão há caminho à direita!\n");
                explorarSalas(salaAtual);
            }
            break;
            
        case 's':
        case 'S':
            printf("\nVocê saiu da mansão. Até a próxima, detetive!\n");
            break;
            
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            explorarSalas(salaAtual);
            break;
    }
}

/**
 * liberarArvore() - Libera toda a memória alocada para a árvore
 * 
 * Parâmetros:
 *   sala: ponteiro para a raiz da árvore/subárvore
 * 
 * Descrição:
 *   Percorre a árvore em pós-ordem (esquerda, direita, raiz)
 *   liberando a memória de cada nó.
 */
void liberarArvore(Sala *sala) {
    if (sala == NULL) {
        return;
    }
    
    // Libera primeiro as subárvores
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    
    // Depois libera o nó atual
    free(sala);
}

/**
 * main() - Função principal do programa
 * 
 * Descrição:
 *   Constrói o mapa da mansão (árvore binária) de forma manual,
 *   exibe mensagem de boas-vindas e inicia a exploração a partir
 *   do Hall de Entrada. Ao final, libera toda a memória alocada.
 */
int main() {
    // Mensagem de boas-vindas
    printf("==========================================\n");
    printf("    BEM-VINDO AO DETECTIVE QUEST!\n");
    printf("==========================================\n");
    printf("\nVocê está prestes a explorar uma mansão\n");
    printf("misteriosa em busca de pistas.\n");
    printf("Escolha seus caminhos com sabedoria!\n");
    
    // Construção do mapa da mansão (árvore binária)
    
    // Nível 0 (Raiz) - Hall de Entrada
    Sala *hall = criarSala("Hall de Entrada");
    
    // Nível 1
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    // Nível 2 - Ramificações da Sala de Estar
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *escritorio = criarSala("Escritorio");
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = escritorio;
    
    // Nível 2 - Ramificações da Cozinha
    Sala *despensa = criarSala("Despensa");
    Sala *jardim = criarSala("Jardim");
    cozinha->esquerda = despensa;
    cozinha->direita = jardim;
    
    // Nível 3 - Ramificações da Biblioteca
    Sala *salaSecreta = criarSala("Sala Secreta");
    Sala *salaDeLeitura = criarSala("Sala de Leitura");
    biblioteca->esquerda = salaSecreta;
    biblioteca->direita = salaDeLeitura;
    
    // Nível 3 - Ramificações do Jardim
    Sala *estufa = criarSala("Estufa");
    Sala *gazebo = criarSala("Gazebo");
    jardim->esquerda = estufa;
    jardim->direita = gazebo;
    
    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hall);
    
    // Libera toda a memória alocada
    liberarArvore(hall);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}
