#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

typedef struct T_table{
	
	char name[30];
	
	
}table; 

int executeCommand(char command[][30],int tam);
int createTable(char *name);
int validType(char *type);
int validName(char *name,char **names,int tam_m);

#endif