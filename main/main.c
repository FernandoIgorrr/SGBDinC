#include "man.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void main(){
	
	man();
	
	char	command[10];
	int		i;	
	
	command[11] =	'\0';
	i			=	strcmp(command,"quit");
	while(i){
		
		printf("SGBD>");	
		scanf("%s",&command);
		
		i			=	strcmp(command,"quit");
		
	}
}
