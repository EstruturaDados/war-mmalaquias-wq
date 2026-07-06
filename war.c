#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura que representa cada território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int totalTerritorios;
    
    // Inicializa a semente de números aleatórios usando o tempo atual
    srand(time(NULL));

    printf("=========================================\n");
    printf("     SISTEMA DE ESTRATEGIA - WAR v2      \n");
    printf("=========================================\n\n");

    // Requisito: Alocação Dinâmica definida pelo usuário
    printf("Quantos territorios deseja cadastrar no jogo? ");
    scanf("%d", &totalTerritorios);

    if (totalTerritorios < 2) {
        printf("Erro: Sao necessarios pelo menos 2 territorios para jogar.\n");
        return 1;
    }

    // Alocação dinâmica utilizando calloc (limpa a memória com zeros)
    Territorio* mapa = (Territorio*) calloc(totalTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro fatal: Falha na alocacao de memoria.\n");
        return 1;
    }

    // Executa o cadastro modularizado
    cadastrarTerritorios(mapa, totalTerritorios);

    int continuar = 1;
    while (continuar) {
        exibirMapa(mapa, totalTerritorios);

        int idxAtacante, idxDefensor;
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio ATACANTE (1 a %d): ", totalTerritorios);
        scanf("%d", &idxAtacante);
        printf("Escolha o territorio DEFENSOR (1 a %d): ", totalTerritorios);
        scanf("%d", &idxDefensor);

        // Ajustando para o índice do vetor (0 a N-1)
        idxAtacante--;
        idxDefensor--;

        // Validações de segurança do índice
        if (idxAtacante < 0 || idxAtacante >= totalTerritorios || idxDefensor < 0 || idxDefensor >= totalTerritorios) {
            printf("\n[AVISO] Indices invalidos! Escolha territorios existentes.\n\n");
            continue;
        }

        // Validação técnica: Não atacar a si mesmo ou territórios aliados (mesma cor)
        if (idxAtacante == idxDefensor) {
            printf("\n[AVISO] Um territorio nao pode atacar a si mesmo!\n\n");
            continue;
        }
        if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
            printf("\n[AVISO] Ataque invalido! Voce nao pode atacar um territorio da sua propria cor (%s).\n\n", mapa[idxAtacante].cor);
            continue;
        }
        if (mapa[idxAtacante].tropas < 2) {
            printf("\n[AVISO] O atacante precisa de pelo menos 2 tropas para iniciar um ataque.\n\n");
            continue;
        }

        // Executa a ação de ataque passando os endereços de memória (ponteiros)
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        printf("\nDeseja realizar outro ataque? (1 - Sim / 0 - Nao): ");
        scanf("%d", &continuar);
        printf("\n");
    }

    // Exibição final do estado do mapa
    printf("\n=== ESTADO FINAL DO MAPA ===\n");
    exibirMapa(mapa, totalTerritorios);

    // Liberação da memória alocada dinamicamente
    liberarMemoria(mapa);
    mapa = NULL; // Evita ponteiro solto (dangling pointer)

    printf("\nObrigado por jogar! Memoria liberada com sucesso.\n");
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES MODULARIZADAS ---

/**
 * Cadastra interativamente as informações de cada território no vetor alocado.
 * Recebe o ponteiro base do mapa.
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n--- INICIANDO CADASTRO DOS TERRITORIOS ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d de %d:\n", i + 1, quantidade);
        
        printf("  Nome: ");
        scanf(" %29[^\n]", mapa[i].nome); // Acesso direto via aritmética implícita de array/ponteiro
        
        printf("  Cor do Exercito: ");
        scanf(" %9[^\n]", mapa[i].cor);
        
        printf("  Quantidade de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

/**
 * Exibe de maneira formatada e tabular os dados atuais de todos os territórios.
 */
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n=======================================================\n");
    printf("ID  | %-20s | %-10s | %-6s\n", "TERRITORIO", "COR", "TROPAS");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < quantidade; i++) {
        // Exibição utilizando aritmética de ponteiros para fins didáticos: *(mapa + i)
        printf("%-3d | %-20s | %-10s | %-6d\n", 
               i + 1, 
               (mapa + i)->nome, 
               (mapa + i)->cor, 
               (mapa + i)->tropas);
    }
    printf("=======================================================\n");
}

/**
 * Processa a mecânica de combate entre dois territórios usando ponteiros.
 * Qualquer alteração aqui reflete diretamente na memória principal do mapa.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Rola dados de 1 a 6 para cada lado
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n[BATALHA] %s (%s) atacando %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("[DADOS] Atacante rolou: %d  |  Defensor rolou: %d\n", dadoAtacante, dadoDefensor);

    // Vitória do Atacante
    if (dadoAtacante > dadoDefensor) {
        printf("[RESULTADO] O Atacante VENCEU a batalha e conquistou o territorio!\n");
        
        // Defensor muda de dono (copia a cor do atacante)
        strcpy(defensor->cor, atacante->cor);
        
        // Calcula a transferência de metade das tropas (divisão inteira)
        int tropasTransferidas = atacante->tropas / 2;
        
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("[MOVIMENTACAO] %d tropas se moveram de %s para %s.\n", tropasTransferidas, atacante->nome, defensor->nome);
    } 
    // Vitória do Defensor (Empates favorecem a defesa)
    else {
        printf("[RESULTADO] O Defensor VENCEU ou empatou! O ataque falhou.\n");
        atacante->tropas -= 1;
        printf("[PENALIDADE] %s perdeu 1 tropa. Restam: %d\n", atacante->nome, atacante->tropas);
    }
}

/**
 * Libera a memória previamente alocada pelo malloc/calloc.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}
