#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

typedef struct T_table{
	
	char name[30];
	
	
}table; 

//Fnção que valida se o campo pode ser primary-key ou não
int validatePrimarykey(char **types,int p);

//Fnção que mostra todas as tabelas já criadas
void showTables(void);

//Função que gera a string do local e o nome do arquivo
char *generatorLocal(char *name);

//Função que gera a string que será salva no txt
char *generatorText(char *name, char **names,char *type,char **types,int numFields,int primaryKey);

//Função que cria a tabela
int createTable(char *name);

//Função que válida o tipo
int validateType(char *type);

//Função que vallida o nome do campo
int validateName(char *name,char **names,int tam_m);

//Função que recebe o comando o valida e o executa
int executeCommand(char command[][30],int tam);
#endif