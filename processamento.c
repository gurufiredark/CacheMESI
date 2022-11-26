# include <stdio.h>
# include <string.h>
# include <time.h>
# include "toolsFila.c"
# include "toolsPrincipalCache.c"

int usaProcessador(TipoLista *memCache, int p, int *memPrincipal, TipoLista *memCacheAux1, TipoLista *memCacheAux2){

    int posicaoAcessada = 0;
    int alteracao = 0;
    printf("\nQual posicao da memoria PRINCIPAL vai ser acessada");
    printf("\n>>> ");
    scanf("%d", &posicaoAcessada);
    printf("\nHavera alteracao na memoria PRINCIPAL? (1 - sim, 0 - nao)");
    printf("\n>>> ");
    scanf("%d", &alteracao);

    printf("\n---> Cache do processador %d\n", p);
    Imprime(*memCache);
    printf("\n\n---> Pegando posicao %d na memoria PRINCIPAL\n", posicaoAcessada);

    // Cria uma celula com o valor da posicao da PRINCIPAL que foi acessado
    Celula a;
    a.Linha.alteracao = alteracao;
    if(posicaoAcessada % 2 == 0){
        a.Linha.posicaoValor1 = posicaoAcessada;
        a.Linha.posicaoValor2 = posicaoAcessada+1;
        if(alteracao == 1){
            a.Linha.valor1 = rand() % RANGE_PRINCIPAL_VALORES;
            a.Linha.mesi = 'm';
            printf("\n--> Alteracao do valor: %d => %d", memPrincipal[a.Linha.posicaoValor1], a.Linha.valor1);
        }else{
            a.Linha.valor1 = memPrincipal[a.Linha.posicaoValor1];
            a.Linha.mesi = 'e';
        }
        a.Linha.valor2 = memPrincipal[a.Linha.posicaoValor2];
    }else{
        a.Linha.posicaoValor1 = posicaoAcessada-1;
        a.Linha.posicaoValor2 = posicaoAcessada;
        a.Linha.valor1 = memPrincipal[a.Linha.posicaoValor1];
        if(alteracao == 1){
            a.Linha.valor2 = rand() % RANGE_PRINCIPAL_VALORES; 
            a.Linha.mesi = 'm';    
            printf("\n--> Alteracao do valor: %d => %d", memPrincipal[a.Linha.posicaoValor2], a.Linha.valor2);
        }else{
            a.Linha.valor2 = memPrincipal[a.Linha.posicaoValor2];
            a.Linha.mesi = 'e';
        }
    }

    // Busca a celula na memoria cache
    printf("\n--> Buscando celula %d - %d | %d - %d na memoria cache\n", a.Linha.posicaoValor1, a.Linha.valor1, a.Linha.posicaoValor2, a.Linha.valor2);
    Celula* encontrou = buscaNaCache(a, memCache);
    if(encontrou == NULL){ // Se nao encontrou
        printf("\n-> Nao esta na cache");
        a.Linha.mesi == 'm' ? printf(" (WRITE MISS)\n") : printf(" (READ MISS)\n");
        if(memCache->Tamanho < QTD_LINHA_CACHE){ // Se a cache não estiver cheia insere no fim da lista
        
            printf("\n>procurando em outra cache...\n");
            Celula* buscaAux1 = buscaNaCache(a, memCacheAux1);
            if(buscaAux1 != NULL){
                printf("\n>Encontrou na cache auxiliar 1\n");
                if(a.Linha.mesi == 'm'){
                    printf("\n>Ha alteracao, invalidando cache auxiliar 1\n");
                    buscaAux1->Linha.mesi = 's';
                }else{
                    buscaAux1->Linha.mesi = 's';
                    a.Linha.mesi = 's';
                }
            }
            Celula* buscaAux2 = buscaNaCache(a, memCacheAux2);
            if(buscaAux2 != NULL){
                printf("\n>Encontrou na cache auxiliar 2\n");
                if(a.Linha.mesi == 'm'){
                    printf("\n>Ha alteracao, invalidando cache auxiliar 2\n");
                    buscaAux2->Linha.mesi = 's';
                }else{
                    buscaAux2->Linha.mesi = 's';
                    a.Linha.mesi = 's';
                }
            }

            printf("\n> Inserindo na cache\n");
            Insere(a.Linha, memCache);
            ImprimeCaches(p, memCache, memCacheAux1, memCacheAux2);

        }else{ // Se a cache estiver cheia, usa o metodo FIFO
            // reorganizaFifo(memCache);
            printf("\n> Cache cheia, usando o metodo FIFO\n");
            ImprimeCelula(*memCache->Primeiro->Prox);
            if(memCache->Primeiro->Prox->Linha.mesi == 'm'){
                printf("\n> Celula com alteração (write back) procurando em outras caches...\n");
                Celula* buscaAux1 = buscaNaCache(*memCache->Primeiro->Prox, memCacheAux1);
                if(buscaAux1 != NULL){
                    printf("\n>Invalidando linha da cache encontrada no Processador 1\n");
                    buscaAux1->Linha.mesi = 'i';
                }
                Celula* buscaAux2 = buscaNaCache(*memCache->Primeiro->Prox, memCacheAux2);
                if(buscaAux2 != NULL){
                    printf("\n>Invalidando linha da cache encontrada no Processador 2\n");
                    buscaAux2->Linha.mesi = 'i';
                }
            }
            removePrimeiroLista(a, memCache, memPrincipal);
            ImprimeCaches(p, memCache, memCacheAux1, memCacheAux2);
        }
    }else{ // Se encontrou
        printf("\n-> Achou na posicao na cache");
        if(a.Linha.mesi == 'm'){
            printf(" (WRITE HIT)\n");
            encontrou->Linha.mesi = 'm';
        }else{
            printf(" (READ HIT)\n");
        }
        // Em caso de HIT atualiza a memoria cache colocando a celula na ultma posicao e a cache eh impressa
        // reorganizaHit(encontrou, memCache);
        ImprimeCaches(p, memCache, memCacheAux1, memCacheAux2);

        
    }
    
}