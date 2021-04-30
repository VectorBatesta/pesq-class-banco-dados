#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct indSecNome{
    char nome[26];
    int rrnForte;
};

struct indSecCidade{
    char cidade[21];
    int rrnFraco;
};



int comparaNome(const void * a, const void * b){
    int r = strcmp((*(struct indSecNome*)a).nome,
                   (*(struct indSecNome*)b).nome);
    
    if (r == 0)
        return 0;
    else
        if(r < 0)
            return -1;
        else
            return 1;
}

int comparaCidade(const void * a, const void * b){
    int r = strcmp((*(struct indSecCidade*)a).cidade,
                   (*(struct indSecCidade*)b).cidade);
    
    if (r == 0)
        return 0;
    else
        if(r < 0)
            return -1;
        else
            return 1;
}

char *trimstring(char *string){
    char *fim;

    fim = string + strlen(string) - 1;
    while(fim > string && isspace((unsigned char)*fim))
        fim--;

    fim[1] = '\0';

    return string;
}











void CriarIndicePrimario(FILE * entrada, FILE * FILEindicePrimario){
    rewind(entrada);
    
    char aux;
    int IDint;
    char IDchar[4];
    for(int acharID = 1; acharID <= 500; acharID++){
        for(int RRN = 0; RRN < 500; RRN++){
            for(int i=0; i<3; i++){
                aux = fgetc(entrada);
                IDchar[i] = aux;
            }
            IDchar[3] = '\0';
            IDint = atoi(IDchar);
            
            if (IDint == acharID){
                fprintf(FILEindicePrimario, "%s|%i|#\n", IDchar, RRN);
                break;
            }
            
            while(aux != '\n'){
                aux = fgetc(entrada);
            }
        }
        rewind(entrada);
    }
}

void CriarIndiceSecundarioNome(FILE * entrada, FILE * FILEindiceSecundarioNOME){
    char aux;
    
    rewind(entrada);
    
    aux = fgetc(entrada);
    
    struct indSecNome Nome[500];
    
    for(int linha = 0; linha < 500; linha++){
        Nome[linha].rrnForte = linha;
        fseek(entrada, 2, SEEK_CUR);
        for(int i=0; i<25; i++){
            aux = fgetc(entrada);
            Nome[linha].nome[i] = aux;
        }
        Nome[linha].nome[25] = '\0';
        
        trimstring(Nome[linha].nome);

        while(aux != '\n'){
            aux = fgetc(entrada);
        }
    }
    qsort(Nome, 500, sizeof(struct indSecNome), comparaNome);
    
    for(int i=0; i<500; i++){
        fprintf(FILEindiceSecundarioNOME, "%s|%i|#\n", Nome[i].nome, Nome[i].rrnForte);
    }
}

void CriarIndiceSecundarioCidade(FILE * entrada, FILE * FILEindiceSecundarioCIDADE, FILE * FILEindicePrimario){
    rewind(entrada);
    rewind(FILEindiceSecundarioCIDADE);
    rewind(FILEindicePrimario);
    
    struct indSecCidade Cidade[500];
    
    int linha = 0;
    
    
    
    
    qsort(Cidade, 500, sizeof(struct indSecCidade), comparaCidade);
}











void listarTodosdados(FILE * entrada){
    rewind(entrada);
    
    char aux;
    int posicao;
    
    for(;;){
        if (feof(entrada))
            break;
        posicao = 0;
        printf("ID: ");
        while (posicao < 3){
            aux = fgetc(entrada);
            printf("%c", aux);
            posicao++;
        }
        printf(", NOME: ");
        while (posicao < 28){
            aux = fgetc(entrada);
            printf("%c", aux);
            posicao++;
        }
        printf(", ENDERECO: ");
        while (posicao < 53){
            aux = fgetc(entrada);
            printf("%c", aux);
            posicao++;
        }
        printf(", CIDADE: ");
        while (posicao < 73){
            aux = fgetc(entrada);
            printf("%c", aux);
            posicao++;
        }
        printf(", ESTADO: ");
        while (posicao < 76){
            aux = fgetc(entrada);
            printf("%c", aux);
            posicao++;
        }
        printf("\n");
    }
    
    printf(".\n\n[[APERTE ENTER PARA VOLTAR]]");
    getc(stdin);
    system("cls");
}

int pesquisarPorNome(FILE * entrada, FILE * FILEindiceSecundarioNOME){
    rewind(entrada);
    rewind(FILEindiceSecundarioNOME);
    
    system("cls");
    char pesquisa[50];
    char leitura[50];
    char RRNchar[100];
    int RRN;
    
    printf("Digite o nome para ser pesquisado: ");
    fgets(pesquisa, 25, stdin);
    fflush(stdin);
    
    char aux = 'a';
    int i = -1;
    while(aux != '\n'){
        i++;
        aux = pesquisa[i];
    }
    pesquisa[i] = '\0';
    
    char *ponteiro;
    for(int linha = 0; linha < 500; linha++){
        if (feof(FILEindiceSecundarioNOME))
            return -1;
        ponteiro = NULL;
        fgets(leitura, 26, FILEindiceSecundarioNOME);
        ponteiro = strtok(leitura, "|");
        strcpy(leitura, ponteiro);
        ponteiro = strtok(NULL, "|");
        printf("%s\n", ponteiro);
        strcpy(RRNchar, ponteiro);
        if (strcmp(leitura, pesquisa) == 0)
            break;
    }

    RRN = atoi(RRNchar);
    
    for(int linha = 0; linha < RRN; linha++)
        fseek(entrada, 76, SEEK_CUR);
    
    int posicao = 0;
    printf("ID: ");
    while (posicao < 3){
        aux = fgetc(entrada);
        printf("%c", aux);
        posicao++;
    }
    printf(", NOME: ");
    while (posicao < 28){
        aux = fgetc(entrada);
        printf("%c", aux);
        posicao++;
    }
    printf(", ENDERECO: ");
    while (posicao < 53){
        aux = fgetc(entrada);
        printf("%c", aux);
        posicao++;
    }
    printf(", CIDADE: ");
    while (posicao < 73){
        aux = fgetc(entrada);
        printf("%c", aux);
        posicao++;
    }
    printf(", ESTADO: ");
    while (posicao < 75){
        aux = fgetc(entrada);
        printf("%c", aux);
        posicao++;
    }
    
    printf(".\n\n[[APERTE ENTER PARA VOLTAR]]");
    getc(stdin);
    system("cls");
}

void pesquisarPorCidade(FILE * entrada, FILE * FILEindicePrimario, FILE * FILEindiceSecundarioCIDADE){
    rewind(entrada);
    rewind(FILEindicePrimario);
    rewind(FILEindiceSecundarioCIDADE);
    
    system("cls");
    char pesquisa[21];
    printf("Digite a cidade para ser pesquisada: ");
    scanf("%s", &pesquisa);
    
    char aux;
    int i = 0;
    while(aux != '\n')
        aux = pesquisa[i];
    pesquisa[i] = '\0';
    
}



/*
 * 
 */
int main(int argc, char** argv) {
    char aux;
    
    FILE * entrada;
    entrada = fopen("cadastro.txt", "r");
    if(entrada == NULL){
        printf("ERRO ABERTURA");
    }
    
    FILE * FILEindicePrimario;
    FILEindicePrimario = fopen("indicePrimario.txt", "r");
    if(FILEindicePrimario == NULL){
        FILEindicePrimario = fopen("indicePrimario.txt", "w");
        CriarIndicePrimario(entrada, FILEindicePrimario);
    }

    FILE * FILEindiceSecundarioNOME;
    FILEindiceSecundarioNOME = fopen("indiceSecundarioNOME.txt", "r");
    if(FILEindiceSecundarioNOME == NULL){
        FILEindiceSecundarioNOME = fopen("indiceSecundarioNOME.txt", "w");
        CriarIndiceSecundarioNome(entrada, FILEindiceSecundarioNOME);
    }
    
    FILE * FILEindiceSecundarioCIDADE;
    FILEindiceSecundarioCIDADE = fopen("indiceSecundarioCIDADE.txt", "r");
    if(FILEindiceSecundarioCIDADE == NULL){
        FILEindiceSecundarioCIDADE = fopen("indiceSecundarioCIDADE.txt", "w");
        CriarIndiceSecundarioCidade(entrada, FILEindiceSecundarioCIDADE, FILEindicePrimario);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    
    char escolhachar[2];
    int escolha;

    int termina = 0;
    while(termina != 1){
        printf("====== Amigos do Apolonio ======\n"
                "1 - Listar todos os dados dos amigos\n"
                "2 - Pesquisar por nome\n"
                "3 - Pesquisar por cidade\n"
                "4 - Sair do programa\n"
                "Digita a opcao: ");
        fgets(escolhachar, 2, stdin);
        escolha = atoi(escolhachar);
        fflush(stdin);
        
        switch(escolha){
            case 1:{
                listarTodosdados(entrada);
                break;
            }
            case 2:{
                if (pesquisarPorNome(entrada, FILEindiceSecundarioNOME) == -1){
                    printf("NOME NÃO ENCONTRADO!\n\n[[APERTE ENTER PARA VOLTAR]]");
                    getc(stdin);
                    system("cls");
                }
                break;
            }
            case 3:{
                pesquisarPorCidade(entrada, FILEindicePrimario, FILEindiceSecundarioCIDADE);
                break;
            }
            case 4:{
                termina = 1;
                break;
            }
            default:{
                printf(">>> Selecao errada! Digite entre 1 a 4! <<<\n\n");
                break;
            }
        }
    }
    
    fclose(entrada);
    return (EXIT_SUCCESS);
}
