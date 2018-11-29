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

					int i, numFields;
					char ***structTable;

					numFields		= getNumfields(command[1]);
					structTable 	= getStructtable(command[1]);


					printf("Nome da tabela: %s\n",command[1]);
					printf("Estrutura:\n");
					for(i = 0;i < numFields;i++){
						printf("%s \t|",structTable[0][i]);
					}
					printf("\n");
					for(i = 0;i < numFields;i++){
						printf("%s \t|",structTable[1][i]);
					}
					printf("\n");
				}
				else{
					printf("Tabela não encontrada!\n");
				}
			}
		}
		else if(strcmp(command[0],"insert") == 0){
			if(validateNametable(command[1]) == 0 && validateExisttable(command[1]) == 0){
				insertData(command[1]);
			}
			else{
				printf("A tabela não existe!\n");
				return 0;
			}
		}
		else if(strcmp(command[0],"select") == 0){

			if(validateNametable(command[1]) == 0){
				int i, j, k;
				char ***datas;
				datas		= getDatastable(command[1]);
				printf("%d\n",getNumtables()); 

				if(getNumregs(command[1]) == 0){
					printf("Não há registros salvos na tabela!\n");
				}
				else{
					for(i = 0; i < getNumregs(command[1]);i++){
						for(j = 0;j < getNumfields(command[1]);j++){

						}
					}
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
				return -1003;
			}
		}
		else{
			return -1002;
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

	while(fgets(line, BUFSIZ, file) != NULL){
		numRegs++;
	}

	datas 	= (char ***)malloc(numRegs*sizeof(char));

	for(i = 0;i < numRegs;i++){
		datas[i] = (char **)malloc(numFields*sizeof(char *));
		for(j = 0;j < numFields;j++){
			datas[i][j] = (char *)malloc(100*sizeof(char));
		}
	}

	file  		= fopen(local,"r");
	i = 0;

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