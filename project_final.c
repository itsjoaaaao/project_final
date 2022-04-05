#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
  float nota1, nota2, nota3;
}Notas;

typedef struct{
	int mat;
	char nome[20];
	Notas notas;
}Cadastro;

int atualiza_posicao_registro(FILE *);
void cadastrar_aluno(int*, FILE *);
void exibir_aluno(FILE *);
void alterar_aluno(FILE *);

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	FILE *parq;
	Cadastro pessoa;
	int pos;//variavel para a posicao 
	int op;
	
	//abrindo o arquivo
	if((parq = fopen("arquivo_escola.bin","r+b")) == NULL){//leitura
		parq = fopen("arquivo_escola.bin", "w+b");//escrita
	}
	if(parq == NULL){
		printf("ERRO na abertura do arquivo!\n");
	}else{
		pos = atualiza_posicao_registro(parq);//recebendo a posicao
		printf("posição: %d\n\n", pos);//checando a posicao
	}

  	//menu do programa
  	do{
    	printf("Digite uma opção:\n");
    	printf("\t[1]-Cadastrar\n");
		printf("\t[2]-Exibir:\n");
		printf("\t[3]-Alterar:\n");
		printf("\t[4]-Excluir:\n");
		printf("\t[5]-Sair:\n");
    	scanf("%d", &op);//lê a opcao desejada
    	setbuf(stdin, NULL);

		system("cls");
		
    	//chamada das funcoes
    	switch(op){
      		case 1:
        		cadastrar_aluno(&pos, parq);
      		break;
      		case 2:
        		exibir_aluno(parq);
      		break;
      		case 3:
      			alterar_aluno(parq);
      		break;
      		case 4:
        		//excluir_aluno(pessoa);
      		break;
      		case 5:
        		printf("Saindo\n...");
      		break;
    }
    
  	}while(op<=4);
	
	fclose(parq);//fechando o arquivo
	
	return 0;
}

int atualiza_posicao_registro(FILE *parq){
	
	Cadastro pessoa;
	int posicao_registro = 0;
	
	do{
		fread(&pessoa, sizeof(Cadastro), 1, parq);//le o arquivo
		if(feof(parq)){
			break;//incio do arquivo ele para
		}
		posicao_registro++;//se não ele incrementa mais uma posicao
	}while(!feof(parq));//enquanto nao tiver no final do arquivo ele faz o loop
	rewind(parq);//volta o inicio do arquivo
	
	return posicao_registro;//retorno da pos
}

//funcao para cadastrar
void cadastrar_aluno(int *pos_ult, FILE *parq){

	Cadastro pessoa;
	pessoa.mat = (*pos_ult)+1;//incrementa 1 na matricula
	
	printf("Matricula: %d\n", pessoa.mat);
		
	printf("Digite seu nome:\n");
	scanf(" %[^\n]", pessoa.nome);
	setbuf(stdin, NULL);
		
	printf("Digite a primeira nota:\n");
	scanf("%f", &pessoa.notas.nota1);
	setbuf(stdin, NULL);
		
	printf("Digite a segunda nota:\n");
	scanf("%f", &pessoa.notas.nota2);
	setbuf(stdin, NULL);
		
  	printf("Digite a primeira nota:\n");
	scanf("%f", &pessoa.notas.nota3);
	setbuf(stdin, NULL);
		
	fwrite(&pessoa, sizeof(Cadastro), 1, parq);//registra no arquivo
	(*pos_ult)++;//incrementação
  	
  	system("cls");
}

//funcao para exibir e cadastrar no arquivo
void exibir_aluno(FILE *parq){

	Cadastro pessoa;
	rewind(parq);
	
	do{
		fread(&pessoa,sizeof(Cadastro),1,parq);//leitura do arquivo
		if(feof(parq)) break;
			if((pessoa.mat)!=0){//se a mat for maior ele exibe
				printf("----Dados dos alunos:----\n");
				printf("\tMatricula: %d\n", pessoa.mat);
				printf("\tNome: %s\n", pessoa.nome);
				printf("\tPrimeira nota: %.1f\n", pessoa.notas.nota1);
  				printf("\tSegunda nota: %.1f\n", pessoa.notas.nota2);
				printf("\tTerceira nota: %.1f\n", pessoa.notas.nota3);
			}
		
	}while(!feof(parq));
  
}


//funcao para alterar
void alterar_aluno(FILE *parq){
	
	Cadastro pessoa;
	int altera;//variavel para busca
	rewind(parq);
	
	printf("Digite a matricula do aluno que você deseja alterar:\n");
	scanf("%d", &altera);
	
	fseek(parq,(altera-1)*sizeof(Cadastro),SEEK_SET);//funcao para buscar no arquivo
	
	printf("Matricula: %d\n", pessoa.mat);
	printf("Digite seu nome:\n");
	scanf(" %[^\n]", pessoa.nome);
	setbuf(stdin, NULL);
		
	printf("Digite a primeira nota:\n");
	scanf("%f", &pessoa.notas.nota1);
	setbuf(stdin, NULL);
		
	printf("Digite a segunda nota:\n");
	scanf("%f", &pessoa.notas.nota2);
	setbuf(stdin, NULL);
		
  	printf("Digite a primeira nota:\n");
	scanf("%f", &pessoa.notas.nota3);
	setbuf(stdin, NULL);
	
	fseek(parq,(altera-1)*sizeof(Cadastro),SEEK_SET);//procura para registrar
	fwrite(&pessoa, sizeof(Cadastro),1,parq);//registro no arquivo
	
	printf("Alterado com sucesso!\n");
	
}
