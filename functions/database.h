#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

//struct para armazenar os dados das tabelas
typedef struct Tuple_t{

	unsigned int primaryKey;
	char **line;

}tuple;

int validateExisttable(char *nameTable);

//Função que conta o número de registros de uma tabela
int getNumregs(char *nameTable);

//Função que pega todos os registros em uma tabela
char ***getDatastable(char *nameTable);

//Função que pega o nomes das tabelas que guardam os dados
char **getTablesdata();

//Função que valida se a chave primária já existe 
int validatePrimaryKey(char *nameTable,unsigned primaryKey);

//Pega o indice do campo que é a chave primária da tabela
int getNumfieldPrimaryKey(char *nameTable);

//Função que insere os dados no arquivo
int insertData(char *nameTable);

//Função que pega o número de campos de uma tabela
int getNumfields(char *nameTable);

//Função que a estrutura da tabela
char ***getStructtable(char *nameTable);

//Função que gera a string que será salva no arquivo onde conterá a estrutura da tabela
char *generatorText(char *name,char **names,char *type,char **types,int numFields,int primaryKey);

//Função que valida a primaryKey
int validateTypeprimarykey(char **types,int primaryKey);

//Função que gera a string do local do arquivo
char *generatorLocal(char *name,char locale[],int arg);

//Função que valida se os tipos são apropriados para criação da tabela
int validateStructtable(char **types,int numFields);

//Função que valida o tipo do campo
int validateTypefield(char *type);

//Função que valida o nome do campo
int validateNamefield(char **names,char *name,int tam);

//Função que mostra todas as tabelas
void showTables();

//Fũnção que retorna o número de tabelas já criadas
int getNumtables();

//Função que retorna o nome de todas as tabelas já criadas
char **getTables();

//Função que cria a tabela
int createTable(char *name);

//Função que valida se o nome da tabela está disponível ou se é grande demais
int validateNametable(char *name);

//Função que recebe o comando o valida e o executa
int executeCommand(char command[][30],int quantidadeEspacos);


int countDigits(int num);
#endif