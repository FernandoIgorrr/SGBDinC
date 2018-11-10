#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void main(){
	
	char comando[10];
	
	System("cls");
	do{
			scanf("%s",&comando);
		
	}while(!strcmp(comando,"quit"));

		printf("#################################################################");
		printf("#						Esse é um SGBD em C						#");
		printf("#################################################################");
		printf("#								Manual							#");
		printf("#################################################################");
		printf("#################################################################");
		printf("#																#");
		printf("#create table <nome da tabela> - Cria uma tabela com o nome dado#");
		printf("#																#");
		printf("#################################################################");

}