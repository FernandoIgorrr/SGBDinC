#include "../functions/man.h"
#include "../functions/command.h"
#include "../functions/database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
	
	man();
	
	char	command[43];
	int		i,k,j = 0;	

	i			=	strcmp(command,"quit");
	
	while(i){
		j++;
		setbuf(stdin, NULL);
		printf("->");	
		scanf("%[^\n]s",&command);
		setbuf(stdin, NULL);
		
		k = getCommand(command);
		//printf("\n\nRETURN %d\n\n",k);	
		i		=	strcmp(command,"quit");
		
	}
}
