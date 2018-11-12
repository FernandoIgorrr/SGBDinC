#include "command.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCommand(char *command){

	int i,j,tam = strlen(command);
	
	for(i = 0;i < tam;i++){
		if(command[i] == ' '){
			j++;
		}
	}
	if(tam - 13 > 30){
		return -1;
	}
	else{
		if(j == 2){
			char cmd[3][30];
			char *cmd2 = cmd[1];
			char *cmd3 = cmd[2];
			
			for(i = 0;i < 6;i++){
				cmd[0][i]	=	command[i];
			}	
			for(i = 0;i < 5;i++){
				cmd[1][i]	=	command[7+i]; 
			}	
			for(i = 0;i < (tam-(13));i++){
				cmd[2][i]	=	command[13+i]; 
			}
			return executeCommand(cmd,j);
		}
		else if(j == 1){
			char cmd[2][30];
			return executeCommand(cmd,j);
		}
		else if(j == 0){
			char cmd[1][30];
			strcpy(cmd[0],command);
			return executeCommand(cmd,j);
		}
		else{
			return 0;
		}	
	}
}
char *errorHandling(int error){
	
	
}