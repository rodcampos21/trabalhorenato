#include <stdio.h>
#include <string.h>
#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};


int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long posicao, primeiro, ultimo, meio;
	long cont = 0;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	//Operação de leitura após abrir o arquivo
	f = fopen("cep_ordenado.dat","r");
	//Posiciona o indicador de posição do fluxo no final do arquivo e anda 0 bytes de posição
	fseek(f,0,SEEK_END);
	//Atribui o valor do indicador de posição atual em bytes, à variável posição
	posicao = ftell(f);
	//Volta o indicador de posição para a posição inicial, ou seja, início do arquivo
	rewind(f);

	printf("Tamanho do Arquivo: %ld\n", posicao);
	printf("Tamanho do Registro: %ld\n", (long)sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n\n\n\n", posicao/sizeof(Endereco));
	
	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;
	cont=0;
	//Loop para realizar a busca binária
     while(primeiro <= ultimo)
     {	
     	cont++;
         meio = (primeiro + ultimo)/2;
         
         fseek(f, meio * sizeof(Endereco), SEEK_SET);
         
         fread(&e,sizeof(Endereco),1,f);
         
         if(strncmp(argv[1],e.cep,8)==-1){
               ultimo = meio-1;
         }else if(strncmp(argv[1],e.cep,8)== 1){
               primeiro = meio+1;        
         }else{
    			printf("Contador: %ld\n\n", cont);
               return printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);

               break;
         }
      
     }

     
	
	

	rewind(f);
	
	
	
	fclose(f);
}

