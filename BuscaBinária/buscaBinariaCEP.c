#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{
    char logradouro[72];
    char bairro [72];
    char cidade[72];
    char uf[72];
    char sigla[72];
    char cep[8];
    char lixo[2];
};

int main(int argc, char** argv){
    FILE *f;
    int inicio, fim, meio, c, qt;
    Endereco e;

    f = fopen("cep_ordenado.dat", "rb");

    c = 0;
    inicio = 0;
    
    fseek(f, 0, SEEK_END);
    fim = (ftell(f)/sizeof(Endereco)) - 1;
    
    if(argc != 2){
        fprintf(stderr, "Uso incorreto: %s [CEP]", argv[0]);
        return 1;
    }
    
    printf("Tamanho da estrutura: %ld\n", sizeof(Endereco));
    
    while(inicio <= fim){
        c++;
        meio = (inicio + fim)/2;

        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        qt = fread(&e, sizeof(Endereco), 1, f);

        if(strncmp(argv[1], e.cep, 8) == 0){
            printf("CEP encontrado!\n");
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.72s\n%.8s", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
            break;        
        }else if(strncmp(argv[1], e.cep, 8) < 0){
            fim = meio - 1;
        }else{
            inicio = meio + 1;
        }
    }

    printf("\nTotal Lido: %d", c);
    fclose(f);
    
    return 0;
}