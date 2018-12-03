#include "command.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCommand(char *command){
	
	int i, j, k, quantidadeEspacos, tamanho; 


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
		k = 0;
		for(i = 0; i < 2;i++){
			for(j = 0; j < strlen(command);j++){
				if(command[k] != ' '){
					cmd[i][j] = command[k];
				}
				else{
					cmd[i][j] = '\0';
					j = strlen(command);
				}
				k++;
			}
		}
		executeCommand(cmd,quantidadeEspacos);
	}
	else if(quantidadeEspacos == 2){
		char cmd[3][30];
		k = 0;
		for(i = 0; i < 3;i++){
			for(j = 0; j < strlen(command);j++){
				if(command[k] != ' '){
					cmd[i][j] = command[k];
				}
				else{
					cmd[i][j] = '\0';
					j = strlen(command);
				}
				k++;
			}
		}
		executeCommand(cmd,quantidadeEspacos);
	}
	else if(quantidadeEspacos == 3){
		char cmd[4][30];
		k = 0;
		for(i = 0; i < 4;i++){
			for(j = 0; j < strlen(command);j++){
				if(command[k] != ' '){
					cmd[i][j] = command[k];
				}
				else{
					cmd[i][j] = '\0';
					j = strlen(command);
				}
				k++;
			}
		}
		executeCommand(cmd,quantidadeEspacos);

	}
	else if(quantidadeEspacos == 4){
		char cmd[5][30];
		k = 0;
		for(i = 0; i < 5;i++){
			for(j = 0; j < strlen(command);j++){
				if(command[k] != ' '){
					cmd[i][j] = command[k];
				}
				else{
					cmd[i][j] = '\0';
					j = strlen(command);
				}
				k++;
			}
		}
		executeCommand(cmd,quantidadeEspacos);
	}
	else{
		return 0;
	}

}
char *errorHandling(int error){
	
	
}