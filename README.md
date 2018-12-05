# SGBDinC
Projeto da disciplina ITP/PTP para criar um sistema gerenciador de banco dados simples em C.

Orientadores: Julio Cesar e Andre Solino

Funcionalidades:
	
 - Cria tabelas e as salvas em arquivos; 
 - Os tipos de dados das tabelas podem ser: int, float, double, char, string;
 - Toda a estrutura da tabela é armazenada em um arquivo para futuros acessos;
 - Mostra toda a estrutura da tabela (quantos campos tem, quem é chave primaria, nomes e tipos dos campos);
 - É obrigatória a escolha de um campo do tipo int para ser chave primária;
 - Lista todas as tabelas existentes;
 - Insere dados na tabela, respeitando os tipos de dados e a chave primária e os salva em arquivos;
 - Lista todos os registros da tabela os pegando através do arquivo que estão salvos;
 - Lista todos os registros da tabela com filtros de >, >=, <, <= e = para valores númericos, = para string e chars e ~ (substring) para strings;
 - Deleta registros da tabela;
 - Deleta a tabela inteira junto com todos os seus dados e registros;
 - Tem um manual que pode ser acessado com o comando "man";
 - Limpa a tela com o comando "clear";
 - Sai do sistema com o comando "quit".

O que faria de forma diferente:
 
 - Melhoraria a modularização de arquivos, pois, apesar do projeto está modularizado poderia ter criado mais arquivos e separada melhor as funções por arquivos;
 - Implementaria mais algumas funções para tratamento de erros e de sucesso com mais menssagens de erros e sucessos mais específicas;
 - Comentaria algumas partes de funções mais complexas que ficaram grandes.

Como compilar o projeto:
 
 - Abra o terminal do seu sistema operacional;
 - Instale o compilador gcc; 
 - Instale o git;
 - Copie o projeto para seu computador com o comando:
		`git clone https://github.com/FernandoIgorrr/SGBDinC.git`
 - Ou baixe pelo link:
		`https://github.com/FernandoIgorrr/SGBDinC/archive/master.zip
 - Navegue até a pasta chamada "main" do projeto;
 - Digite exatamente o comando abaixo:
		`gcc -c ../functions/man.c ../functions/command.c ../functions/database.c`
 - Logo, digite este outro comando:
		`gcc main.c man.o command.o database.o -o main`
 - Agora, apenas digite:
 - Caso for Linux: 
		`./main`
 - Caso for Winsdows:
		`main`
 - Obs.: Não apague nenhuma pasta do projeto mesmo que ela esteja vazia.

 - No projeto foram ultilizadas as bibliotecas <stdio.h> <stdlib.h> <string.h> <dirent.h> e o github.
