#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <ctype.h>
#define MAX  100


struct Dados{

    char uf[3];
    char municipio[MAX];
    int cd;
    int epao;
    int tpd;
    int lb;
    int tsb;
    int asb;
    int apd;
    int epo;
    int total;


};

struct NoArvore{

    Dados *noDados;
    NoArvore *noEsquerdo;
    NoArvore *noDireito;

};

FILE *abreArquivo(const char *nome);
int contaLinhas(const char *nome);
Dados *alocaDados();
Dados *leLinhaDados(FILE *arq);
NoArvore *iniciaArvore(NoArvore *arvore);
NoArvore *alocaNo();
NoArvore *constroiArvore(NoArvore *arvore, NoArvore *pai, FILE *arq);
void printaArvore(NoArvore *raiz);
void liberaArvore(NoArvore *raiz);
int menu();





int main(void){
    menu();
    return 0;
}




int contaLinhas(const char *nome){

    int contador = 0;
    char ah;
    FILE *arq;

    arq = fopen(nome, "r");


    while ((ah = fgetc(arq)) != EOF) {
        if(ah == '\n'){
            contador++;
        }
    }


    fclose(arq);
    return contador;
}





Dados *alocaDados(){

    Dados *dadosLidos;
    dadosLidos = (Dados *) malloc(sizeof(Dados));

    if(!dadosLidos){
        printf("\nMemoria nao alocada!\n");
        return 0;
    }

    return dadosLidos;
}

NoArvore *alocaNo(){
    NoArvore *no;
    no = (NoArvore *) malloc(sizeof(NoArvore));


    if(!no){
        printf("\nMemoria nao alocada!\n");
        return 0;
    }

    no->noDados = NULL;
    no->noDireito = NULL;
    no->noEsquerdo = NULL;
    return no;
}



Dados *leLinhaDados(FILE *arq){

    Dados *dadosLidos;
    dadosLidos = alocaDados();

    if(fscanf(arq,"%c%c", &dadosLidos->uf[0],&dadosLidos->uf[1]) == EOF){
        fclose(arq);
        dadosLidos = NULL;
        printf("\nLido e alocado ate o fim do arquivo!\n");
        return dadosLidos;
    }
    dadosLidos->uf[2] = '\0';
    fscanf(arq,";%[^;]s", dadosLidos->municipio);
    fscanf(arq,";%d", &dadosLidos->cd);
    fscanf(arq,";%d", &dadosLidos->epao);
    fscanf(arq,";%d", &dadosLidos->tpd);
    fscanf(arq,";%d", &dadosLidos->lb);
    fscanf(arq,";%d", &dadosLidos->tsb);
    fscanf(arq,";%d", &dadosLidos->asb);
    fscanf(arq,";%d", &dadosLidos->apd);
    fscanf(arq,";%d", &dadosLidos->epo);
    fscanf(arq,";%d\n", &dadosLidos->total);

    return dadosLidos;
}

FILE *abreArquivo(const char *nome){

    FILE *arq;
    arq = fopen(nome,"r");


    if(!arq){
        printf("\nO arquivo de entrada nao pode ser encontrado!!!\n");
        return 0;
    }

    return arq;

}

NoArvore *constroiArvore(NoArvore *arvore, NoArvore *pai, FILE *arq){

    int comp = 0;
    struct Dados *valor;
    valor = alocaDados();
    valor = leLinhaDados(arq);
    arvore = alocaNo();
    arvore->noDados = alocaDados();
    arvore->noDados = valor;
    if(valor != NULL){

        comp = strcmp(pai->noDados->municipio, arvore->noDados->municipio);
        if(comp > 0 || comp == 0){
            arvore->noEsquerdo = alocaNo();
            arvore->noEsquerdo = constroiArvore(arvore->noEsquerdo, arvore, arq);
        } else {
            arvore->noDireito = alocaNo();
            arvore->noDireito = constroiArvore(arvore->noDireito, arvore, arq);
        }

    } else {
        arvore = alocaNo();
        arvore = NULL;
    }

}

void printaArvore(NoArvore *raiz){

    int comp = 0;

    if(raiz->noEsquerdo == NULL && raiz->noDireito == NULL){
        return;
    } else {
        printf("\n=================");
        printf("\nUnidade Federativa: %s\n", raiz->noDados->uf);
        printf("\nMunicipio: %s\n", raiz->noDados->municipio);
        printf("\nCD: %d\n", raiz->noDados->cd);
        printf("\nEPAO: %d\n", raiz->noDados->epao);
        printf("\nTPD: %d\n", raiz->noDados->tpd);
        printf("\nLB: %d\n", raiz->noDados->lb);
        printf("\nTSB: %d\n", raiz->noDados->tsb);
        printf("\nASB: %d\n", raiz->noDados->asb);
        printf("\nAPD: %d\n", raiz->noDados->apd);
        printf("\nEPO: %d\n", raiz->noDados->epo);
        printf("\nTotal: %d\n", raiz->noDados->total);
        printf("\n=================\n");

        if(raiz->noEsquerdo == NULL){
            printaArvore(raiz->noDireito);
        } else {
            printaArvore(raiz->noEsquerdo);
        }

    }
}

int menu(){

    int opcao = -1;
    int comp = 0;
    int flagImport = 0;
    const char *caminhoDoArquivo = "CFO_UF_municipios_brasil.csv";
    const char *chave = "ACRELANDIA";
    FILE *arquivoCSV;
    struct NoArvore *raiz, *noaux;
    struct Dados *valor;
    raiz = alocaNo();
    arquivoCSV = abreArquivo(caminhoDoArquivo);
    arquivoCSV = abreArquivo(caminhoDoArquivo);
    raiz = alocaNo();
    raiz->noDados = alocaDados();
    raiz->noDados = leLinhaDados(arquivoCSV);

    while(opcao != 0){
        printf("\n\t\tUNB FGA");
        printf("\n\t\tEDA - TSA 3");
        printf("\n\t\tLucas Soares Souza - Matricula: 14/0151257");
        printf("\n\nEscolha uma opcao:");
        printf("\n1 - Importar Dados");
        printf("\n2 - Exibir Relatórios");
        printf("\n3 - Exibir Relatórios de um Estado");
        printf("\n4 - Exibir Relatórios de um Municipio");
        printf("\n0 - Limpar a memoria e sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        __fpurge(stdin);

        switch(opcao){
            case 1:
                system("clear");
                printf("\nImportando Arquivos");
                if(flagImport == 0){
                    flagImport++;
                    raiz->noEsquerdo = constroiArvore(raiz->noEsquerdo, raiz, arquivoCSV);
                } else {
                    printf("\nArquivos ja importados!");
                }
                break;
            case 2:
                system("clear");
                printf("\nDados Cadastrados:");
                printaArvore(raiz);
                    int opc;
                    opc = -1;
                    while(opc != 0){
                        printf("\n0 - Voltar: ");
                        scanf("%d", &opc);
                    }
                system("clear");
                break;
            case 3:
                system("clear");
                printf("\n op3");
                break;
            case 4:
                system("clear");
                printf("\n op4");
                break;
            case 0:
                liberaArvore(raiz);
                printf("\nDados liberados da memória!\n");
                return 0;
                break;
            default:
                system("clear");
                printf("\n outra opcoa");
                break;

        }

    }
}

void liberaArvore(NoArvore *raiz){

    int comp = 0;
    if(raiz->noEsquerdo == NULL && raiz->noDireito == NULL){
        return;
    } else {
        free(raiz->noDados);
        if(raiz->noEsquerdo == NULL){
            liberaArvore(raiz->noDireito);
        } else {
            liberaArvore(raiz->noEsquerdo);
        }
    }
}
