#include <stdio.h>
#include <string.h>

// Definição da struct Territorio conforme os requisitos do sistema
// Esta estrutura agrupa os dados relacionados a um único território
struct Territorio {
    char nome[30];  // Armazena o nome do território (limite de 29 caracteres + '\0')
    char cor[10];   // Armazena a cor do exército dominante (limite de 9 caracteres + '\0')
    int tropas;     // Armazena a quantidade total de tropas no local
};

int main() {
    // Declaração de um vetor (array) de structs capaz de armazenar 5 territórios distintos
    struct Territorio lista_territorios[5];
    
    // --- CADASTRO DOS TERRITÓRIOS (ENTRADA DE DADOS) ---
    printf("=========================================\n");
    printf("      CADASTRO DE TERRITORIOS - WAR      \n");
    printf("=========================================\n\n");
    
    // Laço 'for' para iterar e preencher cada uma das 5 posições do vetor
    for (int i = 0; i < 5; i++) {
        printf("--- Territorio %d de 5 ---\n", i + 1);
        
        // Uso do %29[^\n] com espaço antes para ignorar 'Enters' pendentes no buffer 
        // e permitir a leitura de nomes compostos com segurança.
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", lista_territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf(" %9[^\n]", lista_territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &lista_territorios[i].tropas);
        
        printf("\n"); // Linha em branco para melhor usabilidade e organização visual
    }
    
    // --- EXIBIÇÃO DOS DADOS (SAÍDA DE DADOS) ---
    // A execução ocorre em milissegundos após o cadastro, cumprindo o requisito de desempenho.
    printf("=========================================\n");
    printf("          TERRITORIOS CADASTRADOS        \n");
    printf("=========================================\n");
    
    // Laço 'for' para percorrer o vetor e imprimir as informações coletadas
    for (int i = 0; i < 5; i++) {
        // Alinhamento à esquerda (%-20s) para manter a tabela visualmente organizada
        printf("Territorio: %-20s | Cor: %-10s | Tropas: %d\n", 
               lista_territorios[i].nome, 
               lista_territorios[i].cor, 
               lista_territorios[i].tropas);
    }
    
    printf("=========================================\n");
    
    return 0;
}
