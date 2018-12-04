#include "database.h"
#include "man.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int executeCommand(char command[][30],int quantidadeEspacos){

	if(quantidadeEspacos == 0){
		if(strcmp(command[0],"man") == 0){
			man();
		}
		else if(strcmp(command[0],"clear") == 0){
			clear();
		}
		else{
			return -1001;
		}		
	}
	else if(quantidadeEspacos == 1){
		if(strcmp(command[0],"show") == 0){
			if(strcmp(command[1],"tables") == 0){
				showTables();
			}
			else{
				if(validateNametable(command[1]) == 0){				

					printf("Nome da tabela: %s\n",command[1]);
					printf("Estrutura:\n");
					showLines(command[1],0,NULL,NULL,NULL);
				}
				else{
					printf("Tabela não encontrada!\n");
				}
			}
		}
		else if(strcmp(command[0],"remove") == 0){
			if(validateNametable(command[1]) == 0){
				
				char *local, *elocal, *plocal;
				FILE *file, *efile, *pfile;

				local 	= generatorLocal(command[1],"tables",0);
				elocal 	= generatorLocal(command[1],"datas",0);
				plocal 	= generatorLocal(command[1],"datas",1);

				remove(local);
				remove(elocal);
				remove(plocal);

			}
			else{
				printf("A tabela não existe!\n");
			}
		}
		else if(strcmp(command[0],"insert") == 0){
			if(validateNametable(command[1]) == 0){
				insertData(command[1]);
			}
			else{
				printf("A tabela não existe!\n");
				return 0;
			}
		}
		else if(strcmp(command[0],"select") == 0){

			if(validateNametable(command[1]) == 0){

				if(getNumregs(command[1]) == 0){
					printf("Não há registros salvos na tabela!\n");
				}
				else{
					showLines(command[1],1,NULL,NULL,NULL);
				}
			}
			else{
				printf("A tabela não existe!\n");
			}
		}
	}
	else if(quantidadeEspacos == 2){
		if(strcmp(command[0],"create") == 0){
			if(strcmp(command[1],"table") == 0){
				createTable(command[2]);
			}
			else{
				printf("Você não quiz dizer \"create table\"?\n");
			}
		}
		else if(strcmp(command[0],"delete") == 0){
			if(validateNametable(command[1]) == 0){
				unsigned primaryKey 	= atoi(command[2]);
				if(validatePrimaryKey(command[1],primaryKey) == 0){
					deleteReg(command[1],command[2]);
				}
				else{
					printf("O valor não foi encontrado!\n");
				}
			}	
			else{	
				printf("Tabela não encontrada!\n");
			}
		}
		else{
			printf("Comando não encontrado\n");
		}
	}
	else if(quantidadeEspacos == 3){
		if(strcmp(command[0],"search") == 0){
			if(validateNametable(command[1]) == 0){
				if(existeNamefield(command[1],command[2])){
					showLines(command[1],2,command[2],command[3],NULL);
				}
				else{
					printf("Não existe essa coluna na tabela %s.\n",command[1]);
				}
			}
			else{
				printf("Tabela não encontrada!\n");
			}
		}
		else{
			printf("Comando não encontrado!\n");
		}
	}
	else if(quantidadeEspacos == 4){
		if(strcmp(command[0],"search") == 0){
			if(validateNametable(command[1]) == 0){
				if(existeNamefield(command[1],command[2])){
					if(validateSymbol(command[4])){
						if(validateSearch(command[1],command[2],command[4])){
							if(validateValue(command[3],validateSearch(command[1],command[2],command[4]))){
								showLines(command[1],3,command[2],command[3],command[4]);
							}
							else{
								printf("O tipo da pesquisa é invalido!\n");
							}
						}
						else{
							printf("O tipo da pesquisa é inválido!\n");
						}
					}
					else{
						printf("O tipo da pesquisa é inválido!\n");
					}
				}
				else{
					printf("Não existe essa coluna na tabela %s.\n",command[1]);
				}
			}
			else{
				printf("Tabela não encontrada!\n");
			}
		}
		else{
			printf("COmando não encontrado!\n");
		}
	}
	else{
		return -333;
	}

}

int createTable(char *nameTable){

	int i, numFields, close, validate, p;
	char  **types, **names, typeField[7], nameField[31];


	if(strlen(nameTable) > 30){
		printf("Nome muito grande para a tabela!\n");
	}
	else{
		if(validateNametable(nameTable)){
			printf("->Digite o número de campos que sua tabela irá ter:\n");
			scanf("%d",&numFields);

			types	= (char **)malloc(numFields*sizeof(char *));
			names	= (char **)malloc(numFields*sizeof(char *));

			for(i = 0;i < numFields;i++){

				setbuf(stdin, NULL);
				printf("Digite o tipo do campo %d:\n",i+1);
				scanf("%[^\n]s",&typeField);

				if(validateTypefield(typeField)){

					setbuf(stdin, NULL);
					printf("Digite o nome do campo %d:\n",i+1);
					scanf("%[^\n]s",&nameField);
			
					if(validateNamefield(names,nameField,i)){
					
						types[i]	=	(char *)malloc(strlen(typeField)*sizeof(char)); 
						names[i]	=	(char *)malloc(strlen(nameField)*sizeof(char)); 
				
						strcpy(types[i],typeField);
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

			if(validateStructtable(types,numFields)){

				while(close != 1){
				
					printf("Digite o índice do campo para ser primary-key:\n");
					scanf("%d",&p);
			
					if(p == 0){
						validate		=	0;
						close			=	1;
					}
					else{
						if(validateTypeprimarykey(types,p)){
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
					FILE *file, *fileData, *pfileData;

					file			= fopen(generatorLocal(nameTable,"tables",0),"w+");
					fileData		= fopen(generatorLocal(nameTable,"datas",0),"w+");
					pfileData		= fopen(generatorLocal(nameTable,"datas",1),"w+");

					fprintf(file,generatorText(nameTable,names,typeField,types,numFields,p));
					fprintf(fileData,"");
					fprintf(pfileData,"");

					fclose(file);
					fclose(fileData);
					fclose(pfileData);
				}
				else{
					return 0;
				}
			}
			else{
				printf("Não foi possível criar a tabela!\n");
				return 0;
			}
		}
		else{
			printf("Já existe uma tabela com esse nome!\n");
		}
	}

}

char *generatorLocal(char *name,char locale[],int arg){
	
	char *local;
	
	local = malloc(sizeof(char)*(strlen(name)+14));
	
	strcpy(local,"../");
	strcat(local,locale);
	strcat(local,"/");

	if(arg == 1){
		strcat(local,"p");
	}
	strcat(local,name);
	strcat(local,".txt");
	
	return local;	

}

char *generatorText(char *name,char **names,char *type,char **types,int numFields,int primaryKey){
	
		int i;
		char *text,*aux;
		char cprimaryKey[2], cnumFields[2];
		
		text	= malloc(sizeof(char)*strlen(name)+1+sizeof(char)*2*6*numFields+sizeof(char)*30*numFields);
		aux		= malloc(sizeof(char)*6+2);

		snprintf(cprimaryKey,2,"%d",primaryKey);
		snprintf(cnumFields,2,"%d",numFields);

		strcpy(text,name);
		strcat(text,"\n");
		strcat(text,cnumFields);
		strcat(text,"\n");
		strcat(text,cprimaryKey);
		strcat(text,"\n");
		for(i = 0;i < numFields;i++){

			strcpy(aux,types[i]);
			
			if(i == (numFields-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"+");
			}
			strcat(text,aux);
		}
		
		for(i = 0;i < numFields;i++){
			strcpy(aux,names[i]);
			if(i == (numFields-1)){
				strcat(aux,"\n");
			}
			else{
				strcat(aux,"+");
			}
			strcat(text,aux);
		}
		return text;

}

char *generatorData(tuple t, char *nameTable){

	char *data ,sprimaryKey[countDigits(t.primaryKey)];
	int i, numFields, numfieldPrimaryKey;

	numfieldPrimaryKey 	= getNumfieldPrimaryKey(nameTable);
	numFields 			= getNumfields(nameTable);

	data = malloc(100*numFields*sizeof(char));
	data[0] = '\0';
	for(i = 0;i < numFields;i++){
	
		if(i == numfieldPrimaryKey - 1){
			sprintf(sprimaryKey, "%d", t.primaryKey);
			strcat(data,sprimaryKey);

			if(i == numFields - 1){
				strcat(data,"\n");				
			}
			else{
				strcat(data,"+");	
			}
		}
		else{
			strcat(data,t.line[i]);
			if(i == numFields - 1){
				strcat(data,"\n");				
			}
			else{
				strcat(data,"+");	
			}
		}
	}
	return data;
}

char **getTables(){

	char	**tables;
	struct	dirent **namelist;
	int 	i, j, tam, numTables;

	numTables = scandir("..//tables//", &namelist, 0, alphasort);
	if (numTables < 0){
		perror("scandir");
	}
	else{
		tables = (char **)malloc((numTables-2)*sizeof(char *));
		for(i = 2; i < numTables;i++){
			tam			= strlen(namelist[i]->d_name) - 4;
			tables[i-2]	= (char *)malloc(tam*sizeof(char));
			for(j = 0;j < tam;j++){
				tables[i-2][j] = namelist[i]->d_name[j];
			}
			tables[i-2][j] = '\0';
		}
	}

	return tables;

}
char **getTablesdata(){

	char	**tablesData;
	struct	dirent **namelist;
	int 	i, j, tam, numTablesdata;

	numTablesdata = scandir("..//datas//", &namelist, 0, alphasort);
	if (numTablesdata < 0){
		perror("scandir");
	}
	else{
		tablesData = (char **)malloc((numTablesdata-2)*sizeof(char *));
		for(i = 2; i < numTablesdata;i++){
			tam			= strlen(namelist[i]->d_name) - 4;
			tablesData[i-2]	= (char *)malloc(tam*sizeof(char));
			for(j = 0;j < tam;j++){
				tablesData[i-2][j] = namelist[i]->d_name[j];
			}
			tablesData[i-2][j] = '\0';
		}
	}

	return tablesData;

}

int getNumtables(){

	struct	dirent **namelist;

	int numTables = scandir("..//tables//", &namelist, 0, alphasort);

	if (numTables < 0){
		perror("scandir");
	}
	else{
		return numTables-2;
	}
}

int getNumtablesdata(){

	struct	dirent **namelist;

	int numTablesdata = scandir("..//datas//", &namelist, 0, alphasort);

	if (numTablesdata < 0){
		perror("scandir");
	}
	else{
		return (numTablesdata-2)/2;
	}
}


int getNumfields(char *nameTable){
	
	if(validateNametable(nameTable) == 0){

		char *local, line[BUFSIZ];
		int c, numFields;
		FILE *file;


		local 		= generatorLocal(nameTable,"tables",0);
		c 			= 0;
		file 		= fopen(local,"r");	

		while(fgets(line, BUFSIZ, file) != NULL){
			c++;
			if(c == 2){
				numFields = atoi(line);
				return numFields;
			}
		}
	}
	else{
		printf("Tabela não encontrada!\n");
		return 0;
	}

}

int getNumregs(char *nameTable){

	FILE *file;
	char *local, line[BUFSIZ];
	int  cont;

	local 		= generatorLocal(nameTable,"datas",0);
	file  		= fopen(local,"r");
	cont 		= 0;

	while(fgets(line, BUFSIZ, file) != NULL){
		cont++;
	}
	return cont;

}	

char ***getStructtable(char *nameTable){
	
	char *types, *names, *local, *table, ***tableStruct, line[BUFSIZ];
	int numFields, c, i, j, k, kk;

	c			= 0;	
	k			= 0;
	kk			= 0;							
	tableStruct = (char ***)malloc(2*sizeof(char **));

	
	local 		= generatorLocal(nameTable,"tables",0);
	
	if(validateNametable(nameTable) == 0){

		table 	= malloc((strlen(nameTable)+4)*sizeof(char));

		FILE *file;
		file 	= fopen(local,"r");
		
		while(fgets(line, BUFSIZ, file) != NULL){
			c++;
			if(c == 2){
				numFields = atoi(line);
			}
			if(c == 4){
				types = malloc(strlen(line)*sizeof(char));
				strcpy(types,line);
			}
			else if(c == 5){
				names = malloc(strlen(line)*sizeof(char));
				strcpy(names,line);
			}
		}

		tableStruct[0] = (char **)malloc(numFields*sizeof(char *));
		tableStruct[1] = (char **)malloc(numFields*sizeof(char *));

		for(i = 0;i < numFields;i++){

			tableStruct[0][i] = (char *)malloc(6*sizeof(char));
			
			for(j = 0;j < strlen(types);j++){
				if(types[k] == '+' || types[k] == '\n'){
					tableStruct[0][i][j] = '\0';
					j = strlen(types);
				}
				else{	
					tableStruct[0][i][j] = types[k];
				}
			k++;
			}
		}

		k 		= 0;
		
		for(i = 0;i < numFields;i++){

			tableStruct[1][i] = (char *)malloc(30*sizeof(char));
			
			for(j = 0;j < strlen(names);j++){
				if(names[k] == '+' || names[k] == '\n'){
					tableStruct[1][i][j] = '\0';
					j = strlen(names);
				}
				else{	
					tableStruct[1][i][j] = names[k];
				}
			k++;
			}
		}
		return tableStruct;
	}
	else{
		printf("Tabela não encontrada!\n");
		return 0;
	}

}

char ***getDatastable(char *nameTable){

	FILE *file, *newfile;
	char *local, line[BUFSIZ], ***datas;
	int i, j, k, a, numRegs, numFields;


	local 		= generatorLocal(nameTable,"datas",0);
	file  		= fopen(local,"r");
	numRegs 	= getNumregs(nameTable);
	numFields 	= getNumfields(nameTable);

	datas 	= (char ***)malloc(numRegs*sizeof(char **));

	for(i = 0;i < numRegs;i++){
		datas[i] = (char **)malloc(numFields*sizeof(char *));
		for(j = 0;j < numFields;j++){
			datas[i][j] = (char *)malloc(200*sizeof(char));
		}
	}
	file  		= fopen(local,"r");
	i 			= 0;

	while(fgets(line, BUFSIZ, file) != NULL){
		k = 0;
		for(j = 0; j < numFields;j++){
			for(a = 0;a < strlen(line);a++){
				if(line[k] == '+' || line[k] == '\n'){
					datas[i][j][a] = '\0';
					a = strlen(line);
				}
				else{
					datas[i][j][a] = line[k];
				}
				k++;
			}
		}	
		i++;
	}
	return datas;

}

char ***getSearchtable(char *nameTable,char *nameField, char *value, char *symbol){

	char ***datas, ***structTable, ***datasFiltered;
	int i, j, k, l, numRegs, numField, numFields, cont;

	datas 			= getDatastable(nameTable);
	structTable 	= getStructtable(nameTable); 
	numRegs 		= getNumregs(nameTable);
	numField 		= getNumfieldname(nameTable,nameField);
	numFields 		= getNumfields(nameTable);
	cont 			= 0;

	if(symbol == NULL){

		for(i = 0;i < numRegs;i++){
			if(strcmp(value,datas[i][numField]) == 0){
				cont++;
			}
		}

		if(cont > 0){

			datasFiltered 	= (char ***)malloc(cont*sizeof(char **));

			for(i = 0;i < cont;i++){
				datasFiltered[i]  	= (char **)malloc(numFields*sizeof(char *));
			}

			for(i = 0;i < cont;i++){
				for(j = 0;j < numFields;j++){
					datasFiltered[i][j]  	= (char *)malloc(100*sizeof(char));
				}
			}
	
			k =	0;

			for(i = 0;i < numRegs;i++){
				if(strcmp(value,datas[i][numField]) == 0){
					for(j = 0;j < numFields;j++){
						strcpy(datasFiltered[k][j],datas[i][j]);
					}
					k++;
				}
			}
			return datasFiltered;
		}
		else{
			printf("-------\n");
			printf("Não existem valores iguais a %s na coluna %s da tabela %s.\n",value,nameField,nameTable);
			printf("-------\n");
		}

	}

	else{
		if(validateSearch(nameTable,nameField,symbol) == 1){

			for(i = 0;i < numRegs;i++){
				if(strstr(datas[i][numField],value) != NULL){
					cont++;
				}
			}

			if(cont > 0){

				datasFiltered 	= (char ***)malloc(cont*sizeof(char **));

				for(i = 0;i < cont;i++){
					datasFiltered[i]  	= (char **)malloc(numFields*sizeof(char *));
				}

				for(i = 0;i < cont;i++){
					for(j = 0;j < numFields;j++){
						datasFiltered[i][j]  	= (char *)malloc(100*sizeof(char));
					}
				}
	
				k =	0;

				for(i = 0;i < numRegs;i++){
					if(strstr(datas[i][numField],value) != NULL){
						for(j = 0;j < numFields;j++){
							strcpy(datasFiltered[k][j],datas[i][j]);
						}
						k++;
					}
				}
				return datasFiltered;
			}
			else{
				printf("Não existem registros parecidos com %s.\n",value);
			}

		}
		else if(validateSearch(nameTable,nameField,symbol) == 2){

			if(strcmp(structTable[0][numField],"float") == 0 || strcmp(structTable[0][numField],"double") == 0){
			
				double numValue, num;
				numValue = atof(value);

				for(i = 0;i < numRegs;i++){
					if(strcmp(symbol,">") == 0){				
						num 	= atof(datas[i][numField]);
						if(num > numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,">=") == 0){
						num 	= atof(datas[i][numField]);
						if(num >= numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<") == 0){
						num 	= atof(datas[i][numField]);
						if(num < numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<=") == 0){
						num 	= atof(datas[i][numField]);
						if(num <= numValue){
							cont++;
						}
					}
				}

				if(cont > 0){

					datasFiltered 	= (char ***)malloc(cont*sizeof(char **));

					for(i = 0;i < cont;i++){
						datasFiltered[i]  	= (char **)malloc(numFields*sizeof(char *));
					}

					for(i = 0;i < cont;i++){
						for(j = 0;j < numFields;j++){
							datasFiltered[i][j]  	= (char *)malloc(100*sizeof(char));
						}
					}

					k = 0;
				
					for(i = 0;i < numRegs;i++){

						if(strcmp(symbol,">") == 0){				
							num 	= atof(datas[i][numField]);
							if(num > numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;
							}
						}
							
						else if(strcmp(symbol,">=") == 0){
							num 	= atof(datas[i][numField]);
							if(num >= numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
							
						else if(strcmp(symbol,"<") == 0){
							num 	= atof(datas[i][numField]);
							if(num < numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
							
						else if(strcmp(symbol,"<=") == 0){
							num 	= atof(datas[i][numField]);
							if(num <= numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
					}
					return datasFiltered;
				}
				else{
					printf("Não existem registros %s que %s.\n",symbol,value);
				}		
			}//FLOAT DOUBLE

			else{
				int numValue, num;
				numValue 	= atoi(value);

				for(i = 0;i < numRegs;i++){
					if(strcmp(symbol,">") == 0){				
						num 	= atoi(datas[i][numField]);
						if(num > numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,">=") == 0){
						num 	= atoi(datas[i][numField]);
						if(num >= numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<") == 0){
						num 	= atoi(datas[i][numField]);
						if(num < numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<=") == 0){
						num 	= atoi(datas[i][numField]);
						if(num <= numValue){
							cont++;
						}
					}
				}

				if(cont > 0){

					datasFiltered 	= (char ***)malloc(cont*sizeof(char **));

					for(i = 0;i < cont;i++){
						datasFiltered[i]  	= (char **)malloc(numFields*sizeof(char *));
					}

					for(i = 0;i < cont;i++){
						for(j = 0;j < numFields;j++){
							datasFiltered[i][j]  	= (char *)malloc(100*sizeof(char));
						}
					}

					k = 0;
				
					for(i = 0;i < numRegs;i++){

						if(strcmp(symbol,">") == 0){				
							num 	= atoi(datas[i][numField]);
							if(num > numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;
							}
						}
							
						else if(strcmp(symbol,">=") == 0){
							num 	= atoi(datas[i][numField]);
							if(num >= numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
							
						else if(strcmp(symbol,"<") == 0){
							num 	= atoi(datas[i][numField]);
							if(num < numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
							
						else if(strcmp(symbol,"<=") == 0){
							num 	= atoi(datas[i][numField]);
							if(num <= numValue){
								for(j = 0;j < numFields;j++){
									datasFiltered[k][j] = datas[i][j];
								}
								k++;	
							}
						}
					}
					return datasFiltered;
				}
				else{
					printf("Não existem registros %s que %s.\n",symbol,value);
				}
			}
		}
	}
}

int getNumregsFiltered(char *nameTable,char *nameField, char *value, char *symbol){

	char ***datas, ***structTable;
	int i, numRegs, numField, cont;


	structTable 	= getStructtable(nameTable);
	datas 			= getDatastable(nameTable);
	numRegs 		= getNumregs(nameTable);
	numField 		= getNumfieldname(nameTable,nameField);
	cont 			= 0;

	if(symbol == NULL){

		for(i = 0;i < numRegs;i++){
			if(strcmp(value,datas[i][numField]) == 0){
				cont++;
			}
		}
	}
	else{
		if(validateSearch(nameTable,nameField,symbol) == 1){
			for(i = 0;i < numRegs;i++){
				if(strstr(datas[i][numField],value) != NULL){
					cont++;
				}
			}
		}
		else if(validateSearch(nameTable,nameField,symbol) == 2){

			if(strcmp(structTable[0][numField],"float") == 0 || strcmp(structTable[0][numField],"double") == 0){
			
				double numValue, num;
				numValue = atof(value);

				for(i = 0;i < numRegs;i++){
					if(strcmp(symbol,">") == 0){				
						num 	= atof(datas[i][numField]);
						if(num > numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,">=") == 0){
						num 	= atof(datas[i][numField]);
						if(num >= numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<") == 0){
						num 	= atof(datas[i][numField]);
						if(num < numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<=") == 0){
						num 	= atof(datas[i][numField]);
						if(num <= numValue){
							cont++;
						}
					}
				}
			}
			else{
				int numValue, num;
				numValue 	= atoi(value);

				for(i = 0;i < numRegs;i++){
					if(strcmp(symbol,">") == 0){				
						num 	= atoi(datas[i][numField]);
						if(num > numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,">=") == 0){
						num 	= atoi(datas[i][numField]);
						if(num >= numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<") == 0){
						num 	= atoi(datas[i][numField]);
						if(num < numValue){
							cont++;
						}
					}
					else if(strcmp(symbol,"<=") == 0){
						num 	= atoi(datas[i][numField]);
						if(num <= numValue){
							cont++;
						}
					}
				}
			}
		}
	}

	return cont;

}

int getNumfieldname(char *nameTable, char *nameField){

	char ***structTable;
	int i, numFields;

	numFields 		= getNumfields(nameTable);
	structTable 	= getStructtable(nameTable);

	for(i = 0;i < numFields;i++){
		if(strcmp(nameField,structTable[1][i]) == 0){
			return i;
		}
	}
	return -1;
}

int getNumfieldPrimaryKey(char *nameTable){
	
	if(validateNametable(nameTable) == 0){

		char *local,line[BUFSIZ];
		FILE *file;
		int c, fieldPrimaryKey;

		local 	= generatorLocal(nameTable,"tables",0);

		file 	= fopen(local,"r");

		c 		= 0;
		while(fgets(line, BUFSIZ, file) != NULL){
			c++;
			if(c == 3){
				fieldPrimaryKey = atoi(line);
			}
		}
		return fieldPrimaryKey;
	}
	else{
		printf("Tabela não encontrada!\n");
	}

}

int getBiggestfieldname(char *nameTable){

	char ***structTable;
	int i, numFields, higher;

	structTable 	= getStructtable(nameTable);
	numFields 		= getNumfields(nameTable);

	higher 			= 0;
	for(i = 0;i < numFields;i++){

		if(strlen(structTable[1][i]) > higher){
			higher = strlen(structTable[1][i]);
		}
	}
	return higher;

}

int getBiggestvalue(char *nameTable){

	char ***dataTable;
	int i, j, numFields, numRegs, higher;

	dataTable 		= getDatastable(nameTable);
	numFields 		= getNumfields(nameTable);
	numRegs 		= getNumregs(nameTable);

	higher 			= 0;

	for(i = 0;i < numRegs;i++){
		for(j = 0;j < numFields;j++){
			if(strlen(dataTable[i][j]) > higher){
				higher = strlen(dataTable[i][j]);
			}
		}
	}
	return higher;
	
}

int insertData(char *nameTable){
		
	if(validateNametable(nameTable) == 0){

		tuple t;
		char ***structTable;
		int i, numFields, numfieldPrimaryKey;

		structTable 		= getStructtable(nameTable);
		numFields 		  	= getNumfields(nameTable);
		numfieldPrimaryKey 	= getNumfieldPrimaryKey(nameTable);

		t.line 				= (char **)malloc((numFields-1)*sizeof(char *));

		for(i = 0;i < numFields;i++){
			
			t.line[i] 		= (char *)malloc(100*sizeof(char));

			setbuf(stdin, NULL);

			if(i == numfieldPrimaryKey - 1){
				printf("Digite o valor do campo %s (Primary-Key):",structTable[1][i]);
				scanf("%d",&t.primaryKey);

				if(validatePrimaryKey(nameTable,t.primaryKey)){

				}
				else{
					printf("Este valor para Primary-Key já foi ultilizado!\n");
					i--;
				}
			}
			else{
				printf("Digite o valor do campo %s:",structTable[1][i]);
				scanf("%[^\n]s",t.line[i]);
			}
			
		}

		char sprimaryKey[countDigits(t.primaryKey)+1];

		sprintf(sprimaryKey, "%d", t.primaryKey);
		strcat(sprimaryKey,"\n");

		FILE *file, *pfile;
		char *local, *plocal;

		local 	= generatorLocal(nameTable,"datas",0);
		plocal 	= generatorLocal(nameTable,"datas",1);

		file 	= fopen(local,"a");
		pfile 	= fopen(plocal,"a");

		generatorData(t,nameTable);

		fprintf(file,generatorData(t,nameTable));
		fprintf(pfile,sprimaryKey);

		fclose(file);
		fclose(pfile);

	}
	else{
		printf("Tabela não encontrada!\n");
		return 0;
	}

}

void showTables(){

	int i, n;

	n = getNumtables();

	printf("Toda(s) a(s) %d Tabela(s):\n",n);

	for(i = 0; i < n;i++){
		printf("%s\n",getTables()[i]);
	}

}

void showLines(char *nameTable,int type,char *nameField,char *value,char *symbol){

	int i, j, numFields, numRegs, higher, len;
	char ***regsORstruct;

	numFields		= getNumfields(nameTable);

	if(type == 0){

		regsORstruct 	= getStructtable(nameTable);
		higher 			= getBiggestfieldname(nameTable);
		numRegs 		= 2;
	}
	else if(type == 1){

		regsORstruct 	= getDatastable(nameTable);
		higher 			= getBiggestvalue(nameTable);
		numRegs 		= getNumregs(nameTable);
	}
	else if(type == 2){

		regsORstruct 	= getSearchtable(nameTable,nameField,value,NULL);
		higher 			= getBiggestvalue(nameTable);
		numRegs 		= getNumregsFiltered(nameTable,nameField,value,NULL);
	}
	else if(type == 3){

		regsORstruct 	= getSearchtable(nameTable,nameField,value,symbol);
		higher 			= getBiggestvalue(nameTable);
		numRegs 		= getNumregsFiltered(nameTable,nameField,value,symbol);
	}

	for(i = 0;i < numRegs;i++){

		for(j = 0;j < numFields*higher + numFields;j++){
			printf("_");
		}
		printf("\n");
		printf("|");

		for(j = 0;j < numFields;j++){
			printf("%s",regsORstruct[i][j]);
			len 	= strlen(regsORstruct[i][j]);
			for(len = strlen(regsORstruct[i][j]); len < higher;len++){
				printf(" ");
			}
			printf("|");
		}
		printf("\n");
		for(j = 0;j < numFields*higher + numFields;j++){
			printf("¯");
		}
		printf("\n");
	}

}

void deleteReg(char *nameTable,char *primaryKey){

	int numFields, numRegs, numField, higher, num ,cont, i, j, k;
	char *local, *plocal, ***datas, *line, newLine[BUFSIZ], aux[BUFSIZ], pKey[100], lineAux[100];
	FILE *file, *pfile;

	higher 		= getBiggestvalue(nameTable);
	local 		= generatorLocal(nameTable,"datas",0);
	plocal 		= generatorLocal(nameTable,"datas",1);
	datas 		= getDatastable(nameTable);
	numFields 	= getNumfields(nameTable);
	numRegs 	= getNumregs(nameTable);
	numField 	= getNumfieldPrimaryKey(nameTable) - 1;

	num 		= (higher+1)*numFields*numRegs;

	line = malloc(num*sizeof(char));

	cont = 0;

	for (i = 0; i < numRegs;i++){
		if(strcmp(primaryKey,datas[i][numField]) == 0){
		
		}
		else{
			for (j = 0; j < numFields;j++){

				for(k = 0;k < strlen(datas[i][j]);k++){
					line[cont] = datas[i][j][k];
					cont++;
				}
				if(j == numFields - 1){
					line[cont] = '\n';
					cont++;
				}
				else{
					line[cont] = '+';
					cont++;
				}		
			}
		}
	}
	file 	= fopen(local,"w");
	fprintf(file,line);
	fclose(file);

	pfile 	= fopen(plocal,"r");

	cont = 0;
	while(fgets(aux, BUFSIZ, pfile) != NULL){
		for (i = 0; i < strlen(aux);i++){
			if(aux[i] == '\n'){
				lineAux[i] = '\0';
			}
			else{
				lineAux[i] = aux[i];
			}		
		}
		if(strcmp(primaryKey,lineAux) == 0){

		}
		else{
			if(cont == 0){
				strcpy(newLine,aux);
			}
			else{
				strcat(newLine,aux);
			}
		}
		cont++;		
	}
	fclose(pfile);
	
	pfile 	= fopen(plocal,"w");
	fprintf(pfile,newLine);
	fclose(pfile);
}

int validateNametable(char *nameTable){

	int i, numTables;

	numTables	= getNumtables();

	if(numTables <= 0){
		return -1;
	}
	else{
		for(i = 0;i < numTables;i++){
			if(strcmp(nameTable,getTables()[i]) == 0){
				return 0;
			}
		}
	}
	return 1;

}

int validateExisttable(char *nameTable){

	int i, numTablesdata;

	numTablesdata	= getNumtablesdata();

	if(numTablesdata <= 0){
		return -1;
	}
	else{
		for(i = 0;i < numTablesdata;i++){
			if(strcmp(nameTable,getTablesdata()[i]) == 0){
				return 0;
			}
		}
	}
	return 1;
}

int validateNamefield(char **names,char *name,int tam){
	int i, n;

	n = strlen(name);
	if(n > 30){
		return 0;
	}
	else{	
		for(i = 0;i<n;i++){
			if(name[i] == '+' || name[i] == '|'){
				return 0;
			}
		}
		for(i = 0;i<tam;i++){
			if(strcmp(names[i],name) == 0){
				return 0;
			}
		}
		return 1;
	}

}

int validateTypefield(char *type){
	if(strcmp(type,"string") == 0 || strcmp(type,"int") == 0 || strcmp(type,"double") == 0 || strcmp(type,"float") == 0 || strcmp(type,"char") == 0){
		return 1;
	}
	else{
		return 0;
	}

}

int validateStructtable(char **types,int numFields){
	int i;

	for(i = 0;i < numFields;i++){
		if(strcmp(types[i],"int") == 0){
			return 1;
		}
	}
	return 0;

}

int validateTypeprimarykey(char **types,int primaryKey){
	
	if(strcmp(types[primaryKey-1],"int") == 0){
		return 1;
	}
	else{
		return 0;
	}
	
}

int validatePrimaryKey(char *nameTable,unsigned primaryKey){

	FILE *file;
	char *local, *aux, line[BUFSIZ];
	int i, dprimaryKey;

	local 	= generatorLocal(nameTable,"datas",1);
	file 	= fopen(local,"r");

	while(fgets(line, BUFSIZ, file) != NULL){
		
		aux 	= malloc((strlen(line)-1)*sizeof(char));

		for(i = 0;i < strlen(line) - 1;i++){
			aux[i] = line[i];
		}
		dprimaryKey = atoi(aux);

		if(dprimaryKey == primaryKey){
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	return 1;

}

int validateSymbol(char *symbol){

	int i;

	if(strcmp(symbol,">") == 0 || strcmp(symbol,">=") == 0 || strcmp(symbol,"<") == 0 || strcmp(symbol,"<=") || strcmp(symbol,"~") == 0){
		return 1;
	}
	else{
		return 0;
	}

}

int validateSearch(char *nameTable, char *nameField, char* symbol){

	char ***structTable;
	int numField;

	numField 		= getNumfieldname(nameTable,nameField);
	structTable 	= getStructtable(nameTable);

	if(strcmp(symbol,"~") == 0){
		if(strcmp(structTable[0][numField],"string") == 0){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(strcmp(structTable[0][numField],"int") == 0 || strcmp(structTable[0][numField],"float") == 0 || strcmp(structTable[0][numField],"double") == 0){
			return 2;
		}
		else{
			return 0;
		}
	}

}

int validateValue(char *value,int type){

	int i, len;

	len 	= strlen(value);

	if(type == 2){
		for(i = 0;i < len;i++){
			if(value[i] < '0' || value[i] > '9'){
				return 0;
			}
		}
	}

	return 1;

}

int existeNamefield(char *nameTable, char *nameField){

	char ***structTable;
	int i, numFields;

	numFields 	= getNumfields(nameTable);
	structTable = getStructtable(nameTable);

	for (i = 0;i < numFields;i++){
		if(strcmp(nameField,structTable[1][i]) == 0){
			return 1;
		}
	}

	return 0;

}

int countDigits(int num){

	int digits = 0;

	if (num == 0){ 
		digits = 1;
    }
    else{
        while (num != 0){
            digits = digits + 1;
            num = num/10;
        }
        return digits;
    }

}