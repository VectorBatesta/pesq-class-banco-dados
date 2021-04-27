#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE * entrada;
    entrada = fopen("cadastro.txt", "r");
    if(entrada == NULL){
        printf("ERRO ABERTURA");
    }
    
    FILE * indicePrimario;
    indicePrimario = fopen("indicePrimario.txt", "w");
    if(indicePrimario == NULL){
        printf("ERRO ABERTURA");
        return 1;
    }
    
    int IDint;
    char IDchar[4];
    
    for(int acharID = 1; acharID <= 500; acharID++){
        for(int RRN = 0; RRN < 500; RRN++){
            for(int i=0; i<3; i++){
                char aux = fgetc(entrada);
                IDchar[i] = aux;
            }
            IDchar[3] = '\0';
            IDint = atoi(IDchar);
            
            if (IDint == acharID){
                fprintf(indicePrimario, "%s|%i|#\n", IDchar, RRN);
                break;
            }
            
            char aux='a';
            while(aux != '\n'){
                aux = fgetc(entrada);
            }
        }
        rewind(entrada);
    }
    fclose(indicePrimario);
    
    
    FILE * indiceSecundarioNOME;
    indiceSecundarioNOME = fopen("indiceSecundarioNOME.txt", "w");
    if(indiceSecundarioNOME == NULL){
        printf("ERRO ABERTURA");
    }
    
//    for(int acharID = 1; acharID <= 500; acharID++){
//        for(int RRN = 0; RRN < 500; RRN++){
//            for(int i=0; i<3; i++){
//                char aux = fgetc(entrada);
//                IDchar[i] = aux;
//            }
//            IDchar[3] = '\0';
//            IDint = atoi(IDchar);
//            
//            if (IDint == acharID){
//                fprintf(indicePrimario, "%s|%i|#\n", IDchar, RRN);
//                break;
//            }
//            
//            char aux='a';
//            while(aux != '\n'){
//                aux = fgetc(entrada);
//            }
//        }
//        rewind(entrada);
//    }
//    fclose(indicePrimario);
    
    
    
    FILE * indiceSecundarioCIDADE;
    indiceSecundarioCIDADE = fopen("indiceSecundarioCIDADE.txt", "w");
    if(indiceSecundarioCIDADE == NULL){
        printf("ERRO ABERTURA");
    }
    
    
    
    fclose(entrada);
    return (EXIT_SUCCESS);
}
