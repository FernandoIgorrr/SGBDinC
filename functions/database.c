#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int executeCommand(char command[][30],int tam){

	if(tam == 2){
		if(strcmp(command[0],"create") == 0){
			if(strcmp(command[1],"table") == 0){
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
	else if(tam == 1){
		if(strcmp(command[0],"show") == 0){
			if(strcmp(command[1],"tables") == 0){
				showTables();
			}
			else{
				return -9;
			}
		}
		else if(strcmp(command[0],"insert") == 0){
			int boolean = validateTable(command[1]);
			if(boolean == 1){
					insertData(command[1]);
			}
			else{
				return 0;
			}
		}
		else{
			return -7;
		}
	}
	
}

int createTable(char *name){
	
	int k,i,p,validate,close;
	FILE *file;
	char **types,**names,type[6],nameField[30];
	
	if(validateTable(name)){
			return 0;
	}
	else{
	
		printf("->Digite o número de campos da sua tabela:");
		scanf("%d",&k);
	
		types 		=	(char **)malloc(k*sizeof(char *));
		names		=	(char **)malloc(k*sizeof(char *)); 
	
		for(i = 0;i < k;i++){
	
			setbuf(stdin, NULL);
			printf("Digite o tipo do campo %d:\n",i+1);
			scanf("%[^\n]s",&type);
	
			if(validateType(type)){
			
				setbuf(stdin, NULL);
				printf("Digite o nome do campo %d:\n",i+1);
				scanf("%[^\n]s",&nameField);
			
				if(validateName(nameField,names,i)){
				
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
		while(close != 1){
			printf("Digite o índice do campo para ser primary-key:\n");
			scanf("%d",&p);
		
			if(p == 0){
				validate		=	0;
				close			=	1;
			}
			else{
				if(validatePrimarykey(types,p)){
				validate	=	1;
				close 		=	1;
				}
				else{
					validate	=	0;
					close		=	0;
				}
			}
		}
		if(validate){
			file = fopen(generatorLocal(name),"w");
			fprintf(file,generatorText(name,names,type,types,k,p));
			fclose(file);
		}
		else{
			i = 0;
		}
	
		if(i == k){
			return 1;
		}
		else{
			return 0;
		}
	}
}

char *generatorLocal(char *name){
	
	char *local;
	
	local = malloc(sizeof(char)*(strlen(name)+14));
	
	strcpy(local,"../tables/");
	strcat(local,name);
	strcat(local,".txt");
	
	return local;
	
}

char *generatorText(char *name,char **names,char *type,char **types,int numFields,int primaryKey){
	
		int i;
		char *text,*aux;
		
		text	= malloc(sizeof(char)*strlen(name)+1+sizeof(char)*2*6*numFields+sizeof(char)*30*numFields);
		aux		= malloc(sizeof(char)*6+2);
		
		strcpy(text,name);
		strcat(text,"\n");
		
		for(i = 0;i < numFields;i++){

			strcpy(aux,types[i]);
			
			if((primaryKey-1) == i){
				strcat(aux,"(P)");
			}
			if(i == (numFields-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"\t-\t");
			}
			strcat(text,aux);
		}
		
		for(i = 0;i < numFields;i++){
			strcpy(aux,names[i]);
			if(i == (numFields-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"\t-\t");
			}
			strcat(text,aux);
		}
		return text;
}

int validateType(char *type){
	
	if(strcmp(type,"int") == 0 || strcmp(type,"char") == 0 || strcmp(type,"string") == 0 || strcmp(type,"float") == 0 || strcmp(type,"double")== 0 ){
		return 1;
	}
	else{
		return 0;
	}
	
}
int validateName(char *name,char **names,int tam_m){
	
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

int validatePrimarykey(char **types,int primaryKey){
	
	if(strcmp(types[primaryKey-1],"int") == 0){
		return 1;
	}
	else{
		return 0;
	}
	
}

int validateTable(char *table){
	
	char **tables;
	int	i,b,n	= numTables();
	tables	= getTables();
	
	for(i = 0;i < n;i++){
		if(strcmp(table,tables[i]) == 0){
			return 1;
		}
		else{
			b = 0;	
		}
	}
	if(b == 0){
		return 0;
	}
	
}
int numTables(void){
	
	DIR *dir;
    struct dirent *lsdir;
	int cont = -2;
	
    dir = opendir("..\\tables\\");

    //Conta todos os arquivos e diretórios dentro do diretório
    while ((lsdir = readdir(dir)) != NULL){	
		cont++;
    }
    closedir(dir);
	return cont;
}

void showTables(void){
	
	char **tables	= getTables();
	int i,n			= numTables();
	
	for(i = 0;i < n;i++){
		printf("%s\n",tables[i]);
	}
}
char **getTables(){
	
	DIR *dir;
    struct dirent *lsdir;
	char **tables;
	int n,tam,indice = 0;
	
    dir 	= opendir("..\\tables\\");
	n		= numTables();
	tables 	= (char **)malloc(n*sizeof(char *));
	
	while((lsdir = readdir(dir)) != NULL){
		
		if(indice > 1){
			
			tam = strlen(lsdir->d_name) - 4;
			
			lsdir->d_name[tam] = '\0';
			
			tables[indice-2]	= malloc(tam*sizeof(char));
			
			strcpy(tables[indice-2],lsdir->d_name);
		
		}
		indice++;
	}
	closedir(dir);
	return tables;
}
char **getTableFields(char *table){
	FILE *file
}
int insertData(char *table){
	
	FILE *file;
	char **types,**names,*local;
	int mlc	= strlen(table)+14;
	local	= malloc(mlc*sizeof(char));
	
	*file = fopen(local,"r+");
	
	printf();
	scanf("%[^\n]s",);
	
}