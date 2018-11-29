#include "command.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCommand(char *command){
	
	int i, j, k, quantidadeEspacos, tamanho, diferenca; 


	tamanho				= strlen(command);
	quantidadeEspacos	= 0;


	for(i = 0;i < tamanho;i++){
		if(command[i] == ' '){
			quantidadeEspacos++;
		}
	}
	if(quantidadeEspacos == 0){
		char cmd[1][30];
		
		strcpy(cmd[0],command);
		executeCommand(cmd,quantidadeEspacos);
	}
	else if(quantidadeEspacos == 1){
		char cmd[2][30];
		i = 0;
		
		while(command[i] != ' '){
			cmd[0][i] = command[i];
			i++;
		}
		cmd[0][i]	= '\0';
		i++;
		j = 0;
		while(command[i] != '\0'){
			cmd[1][j] = command[i];
			i++;
			j++;
		}
		cmd[1][j] = '\0';
		executeCommand(cmd,quantidadeEspacos);
	}
	else if(quantidadeEspacos == 2){
		char cmd[3][30];
		i = 0;
		while(command[i] != ' '){
			cmd[0][i] = command[i];
			i++;
		}
		cmd[0][i]	= '\0';
		j = 0;
		i++;
		while(command[i] != ' '){
			cmd[1][j] = command[i];
			i++;
			j++;
		}
		cmd[1][j]	= '\0';
		k = 0;
		i++;
		while(command[i] != '\0'){
			cmd[2][k] = command[i];
			i++;
			k++;
		}
		cmd[2][k] = '\0';
		executeCommand(cmd,quantidadeEspacos);
	}
	else{
		return 0;
	}

}
char *errorHandling(int error){
	
	
}