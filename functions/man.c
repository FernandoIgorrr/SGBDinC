#include "man.h"
#include <stdio.h>
#include <stdlib.h>

void man(void){
	
	clear();
	
	printf("##########################################################################################################################\n");
	printf("#						  Este é um SGBD em C				 	        	 #\n");
	printf("##########################################################################################################################\n");
	printf("#							Manual							   	 #\n");
	printf("##########################################################################################################################\n");
	printf("##########################################################################################################################\n");
	printf("#														 	 #\n");
	printf("#	create table <nome da tabela>					- Cria uma tabela com o nome dados		 #\n");
	printf("#	show tables 							- Mostra todas as tabelas existentes		 #\n");
	printf("#	show <nome da tabela> 						- Mostra a estrutura da tabela			 #\n");
	printf("#	insert <nome da tabela>	        				- Insere dados na tabela especificada		 #\n");
	printf("#	select <nome da tabela>	        				- Mostra os dados da tabela especificada 	 #\n");
	printf("#	delete <nome da tabela> <chave primária do registro>		- Deleta o registro da tabela especificada 	 #\n");
	printf("#	remove <nome da tabela> 					- Deleta a tabela especificada 	 		 #\n");
	printf("#	search <nome da tabela> <nome da coluna> <valor> (>,>=,<,<=,~)	- Mostra os dados da tabela filtrados 		 #\n");
	printf("#	man								- Mostra o manual do sistema			 #\n");
	printf("#	clear								- Limpa a tela do sistema			 #\n");
	printf("#	quit								- Sair do sistema				 #\n");
	printf("#															 #\n");
	printf("##########################################################################################################################\n\n");
		
}

void clear(){
	system("clear");
}
