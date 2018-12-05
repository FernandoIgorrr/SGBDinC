#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

//struct para armazenar os dados das tabelas
typedef struct Tuple_t{

	unsigned int primaryKey;
	char **line;

}tuple;

//Função que recebe o comando o valida e o executa
int executeCommand(char command[][30],int quantidadeEspacos);

//Função que cria a tabela
int createTable(char *name);

			// FUNÇOES GENERATOR's //

//Função que gera a string do local do arquivo
char *generatorLocal(char *name,char locale[],int arg);

//Função que gera a string que será salva no arquivo onde conterá a estrutura da tabela
char *generatorText(char *name,char **names,char *type,char **types,int numFields,int primaryKey);

//Funçao que gera a string de dados que ser salva no arquivo
char *generatorData(tuple t, char *nameTable);

			// FIM DAS FUNÇOES GENERATOR's //

			//----------------------//

			// FUNÇOES GET's //

//Função que retorna o nome de todas as tabelas já criadas
char **getTables();

//Função que pega o nomes das tabelas que guardam os dados
char **getTablesdata();

//Função que retorna o número de tabelas já criadas
int getNumtables();

//Funçao que conta o numero de tabelas que armazenam dados
char **getTablesdata();

//Função que pega o número de campos de uma tabela
int getNumfields(char *nameTable);

//Função que conta o número de registros de uma tabela
int getNumregs(char *nameTable);

//Função que a estrutura da tabela
char ***getStructtable(char *nameTable);

//Função que pega todos os registros em uma tabela
char ***getDatastable(char *nameTable);

//Funçao que pega todos os registros que passaram por determinado filtro
char ***getSearchtable(char *nameTable,char *nameField, char *value, char *option);

//Funçao que conta o numero de registros que passaram por determinado filtro
int getNumregsFiltered(char *nameTable,char *nameField, char *value, char *option);

//Funçao que pega o indice do campo dado
int getNumfieldname(char *nameTable, char *nameField);

//Funçao que pega o indice do campo que é a chave primária da tabela
int getNumfieldPrimaryKey(char *nameTable);

//Funçao que pega o tamanho do maior nome dos campos da tabela
int getBiggestfieldname(char *nameTable);

//Funçao que pega o tamanho do maior dado da tabela
int getBiggestvalue(char *nameTable);

				// FIM DAS FUNÇOES GET's //
		//-----------------------------------------------//


//Função que insere os dados no arquivo
int insertData(char *nameTable);

//Função que mostra todas as tabelas
void showTables();

//Funçao que printa arrays de dados
void showLines(char *nameTable,int type,char *nameField,char *value,char *option);

//FUnçao que deleta tupla escolhhida por Chave Primria do arquivo
void deleteReg(char *nameTable,char *primaryKey);

				// FUNÇOES VALIDATE's //

//Função que valida se o nome da tabela está disponível ou se é grande demais
int validateNametable(char *name);

//Funçao que valida se a tabela ja existe (com todas os seus arquivos necessarios)
int validateExisttable(char *nameTable);

//Função que valida o nome do campo
int validateNamefield(char **names,char *name,int tam);

//Função que valida o tipo do campo
int validateTypefield(char *type);

//Função que valida se os tipos são apropriados para criação da tabela
int validateStructtable(char **types,int numFields);

//Função que valida a primaryKey
int validateTypeprimarykey(char **types,int primaryKey);

//Função que valida se a chave primária já existe 
int validatePrimaryKey(char *nameTable,unsigned primaryKey);

//Funçoes que valida o simbolo da pesquisa
int validateSymbol(char *symbol);

//Funçoes que valida a pesquisa 
int validateSearch(char *nameTable, char *nameField, char* symbol);

//Funçoes que valida o valor da pesquisa (depende do campo que se esta pesquisando)
int validateValue(char *value,int type);

//Funçao que valida se o nome do campo ja existe
int existeNamefield(char *nameTable, char *nameField);

			// FIM DAS FUNÇOES VALIDATE's //
	//----------------------------------------------//

//Funçao que contas os digitos de num inteiro
int countDigits(int num);

#endif