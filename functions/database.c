#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int executeCommand(char command[][30],int tam){
	
	int i = strcmp(command[0],"create");
	int j = strcmp(command[1],"table");
	if(tam == 2){
		if(i == 0){
			if(j == 0){
				createTable(command[2]);
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}
	}
	
}

int createTable(char *name){
	
	int k,i,dim = strlen(name);
	FILE *file;
	char *local,**types,**names,type[6],nameField[30];
	
	local = malloc(dim+sizeof(char)*14);
	
	strcpy(local,"../tables/");
	strcat(local,name);
	strcat(local,".txt");
	printf("\n|%s|\n",name);
	printf("->Digite o número de campos da sua tabela:");
	scanf("%d",&k);
	
	types 		=	(char **)malloc(k*sizeof(char *));
	names		=	(char **)malloc(k*sizeof(char *)); 
	
	for(i = 0;i < k;i++){
	
		setbuf(stdin, NULL);
		printf("Digite o tipo do campo %d:\n",i+1);
		scanf("%[^\n]s",&type);
	
		if(validType(type)){
			
			setbuf(stdin, NULL);
			printf("Digite o nome do campo %d:\n",i+1);
			scanf("%[^\n]s",&nameField);
			
			if(validName(nameField,names,i)){
				
				types[i]	=	(char *)malloc(6*sizeof(char)); 
				names[i]	=	(char *)malloc(30*sizeof(char)); 
				
				strcpy(types[i],type);
				strcpy(names[i],nameField);
			
			}
			else{
				i--;
			}
		}
		else{
			i--;
		}
	}	
	
		file = fopen(local,"w");
		
		char *text,*aux;
		
		text = malloc(sizeof(char)*dim+1+sizeof(char)*2*6*k+sizeof(char)*30*k);
		aux = malloc(sizeof(char)*6+2);
		
		strcpy(text,name);
		strcat(text,"\n");
		
		for(i = 0;i < k;i++){
			strcpy(aux,types[i]);
			if(i == 0){
				strcat(aux,"\t-\t");
				
			}
			else if(i == (k-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"\t-\t");
			}
			strcat(text,aux);
		}
		
		strcat(text,"\n");
		
		for(i = 0;i < k;i++){
			strcpy(aux,names[i]);
			if(i == 0){
				strcat(aux,"\t-\t");
				
			}
			else if(i == (k-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"\t-\t");
			}
			strcat(text,aux);
		}
		
		fprintf(file,text);
		fclose(file);
	
	/*for(i = 0;i < k;i++){
		printf("%s - ",types[i]);
	}
	printf("\n");
	for(i = 0;i < k;i++){
		printf("%s - ",names[i]);
	}
	printf("\n %d -- %d",i,k);
	*/
	if(i == k){
		return 1;
	}
	else{
		return 0;
	}

	
}
int validType(char *type){
	
	if(strcmp(type,"int") == 0 || strcmp(type,"char") == 0 || strcmp(type,"string") == 0 || strcmp(type,"float") == 0 || strcmp(type,"double")== 0 ){
		return 1;
	}
	else{
		return 0;
	}
	
}
int validName(char *name,char **names,int tam_m){
	
	int l;
	int v = 0;
	int tam = strlen(name);

	for(l = 0;l < tam;l++){
		if(name[l] ==  ' '){
			v++;
		}
	}
	
	for(l = 0;l < tam_m;l++){
		if(strcmp(names[l],name) == 0){
			v++;
		}	
	}
		
	if(v != 0){
		return 0;
	}
	else{
		return 1;
	}
	
}