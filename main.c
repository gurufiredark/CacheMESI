# include <stdio.h>
# include <string.h>
# include <time.h>
# include "processamento.c"

int main (){
    int opcao;
    srand((unsigned)time(NULL));

    // Criacao da memoria PRINCIPAL
    int memPrincipal[QTD_LINHA_PRINCIPAL];
    for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
        memPrincipal[i] = rand() % RANGE_PRINCIPAL_VALORES;
    }
    printf("\n\n---> Imprimindo memoria PRINCIPAL\n");
    for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
        printf("posicao %d -> %d   ", i, memPrincipal[i]);
        if(i%6 == 0){
            printf("\n");
        }
    }

    printf("\n---> Criou lista vazia para memoria Cache 1\n"); // Cria uma lista vazia para memoia Cache
    TipoLista memCache1;
    FLVazia(&memCache1);
    printf("\n---> Criou lista vazia para memoria Cache 2\n"); // Cria uma lista vazia para memoia Cache
    TipoLista memCache2;
    FLVazia(&memCache2);
    printf("\n---> Criou lista vazia para memoria Cache 3\n"); // Cria uma lista vazia para memoia Cache
    TipoLista memCache3;
    FLVazia(&memCache3);

    do{
        printf("\nQual processador vai ser usado:");
        printf("\n1 - Processador 1");
        printf("\n2 - Processador 2");
        printf("\n3 - Processador 3");
        printf("\n4 - Imprimir Caches");
        printf("\n5 - Imprimir Memoria Principal");
        printf("\n0 - Finalizar acessos");
        printf("\n>>> ");
        scanf("%d", &opcao);

        if(opcao == 1){
            printf("\n---> Processador 1\n");
            usaProcessador(&memCache1, 1, memPrincipal, &memCache2, &memCache3);
        }else if(opcao == 2){
            printf("\n---> Processador 2\n");
            usaProcessador(&memCache2, 2, memPrincipal, &memCache1, &memCache3);
        }else if(opcao == 3){
            printf("\n---> Processador 3\n");
            usaProcessador(&memCache3, 3, memPrincipal, &memCache1, &memCache2);
        }else if(opcao == 4){
            printf("\n---> Imprimindo memoria Cache 1\n");
            Imprime(memCache1);
            printf("\n---> Imprimindo memoria Cache 2\n");
            Imprime(memCache2);
            printf("\n---> Imprimindo memoria Cache 3\n");
            Imprime(memCache3);
        }else if(opcao == 5){
            printf("\n\n---> Imprimindo memoria PRINCIPAL\n");
            for(int i=0; i<QTD_LINHA_PRINCIPAL; i++){
                printf("posicao %d -> %d   ", i, memPrincipal[i]);
                if(i%6 == 0){
                    printf("\n");
                }
            }
        }
    }while (opcao != 0);

}