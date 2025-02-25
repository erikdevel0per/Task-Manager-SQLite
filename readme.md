# Gerenciador de Tarefas (SQLite)

## Descrição
Este código é escrito em C++ e utiliza a biblioteca SQLite para criar e manipular um banco de dados. A finalidade principal do programa é gerenciar tarefas, com funcionalidades para adicionar, listar, atualizar e excluir tarefas. Essas operações são feitas com a ajuda do SQLite, um banco de dados relacional leve e embutido, que não exige servidores externos, facilitando seu uso em programas de pequeno e médio porte.

## Linguagem e Tipos de Código
- **Linguagem:** O código foi escrito em C++ e a API SQLite tornam o código voltado para a manipulação direta de dados em um banco relacional.
- **Funcionalidades:** 

Função `executeSQL`
- **Objetivo**:
Essa função serve para executar comandos SQL diretamente no banco de dados SQLite. Ela recebe um banco de dados aberto (um ponteiro `sqlite3* db`) e uma consulta SQL em formato de string (do tipo `string`).

Processo:
Executa a consulta SQL: A função `sqlite3_exec()` é chamada para executar o comando SQL passado. Ela tenta rodar a consulta e, caso haja erro, retorna um código de erro.
Tratamento de Erros: Se a consulta falhar (não retornar `SQLITE_OK`), a mensagem de erro é capturada através de `errMsg` e exibida no console, além de liberar a memória com `sqlite3_free()`.
Retorno:
A função retorna o código de retorno da execução da SQL, que pode indicar sucesso ou erro.

Função `callback`
- **Objetivo**:
A função `callback` é chamada automaticamente toda vez que uma consulta SQL SELECT retorna dados. Ela serve para processar e exibir os resultados da consulta.
Processo:
- Parâmetros:
- `NotUsed`: Um parâmetro de retorno não utilizado nesse caso (é passado `0` na execução da consulta).
- `argc`: O número de colunas retornadas pela consulta.
- `argv`: Um vetor contendo os valores das colunas (um valor por coluna).
- `azColName`: Os nomes das colunas.

- Exibição de Dados: Para cada linha de resultados, a função imprime as colunas com seus respectivos valores no console, no formato:
```properties
<nome da coluna>: <valor>
--------------------------
```

Essa função é crucial para exibir as tarefas do banco de dados quando o usuário escolhe a opção de listar tarefas.

Função `main`
- **Objetivo**:
A função `main` é a função principal que orquestra a execução do programa. Nela, o programa inicializa o banco de dados, exibe um menu de opções, e executa comandos baseados na escolha do usuário. O fluxo de execução segue o ciclo de CRUD (Create, Read, Update, Delete), com o SQLite sendo a ferramenta de manipulação de dados.

**Processo**:
- Abrir Banco de Dados:

- O banco de dados `SQLite` é aberto usando `sqlite3_open()`. Se o banco não existir, ele é criado automaticamente.
**Criar Tabela**:

- A tabela `tasks` é criada se não existir. Ela armazena as informações das tarefas, com os campos `id` (identificador único), `description` (descrição da tarefa) e `status` (status da tarefa).
Menu Interativo:

- Um loop `do-while` exibe o menu para o usuário, oferecendo cinco opções: adicionar, listar, atualizar, excluir e sair.

- O programa solicita a entrada do usuário e executa a ação correspondente com base na opção selecionada.

Operações de Banco de Dados:

- Adicionar Tarefa: Quando o usuário escolhe adicionar uma tarefa, o programa solicita uma descrição e insere essa tarefa no banco de dados com o status "Pendente".
- Listar Tarefas: Quando o usuário escolhe listar as tarefas, uma consulta SQL `SELECT` é executada para recuperar todas as tarefas e a função `callback` exibe os resultados no console.
- Atualizar Tarefa: O usuário pode atualizar o status de uma tarefa específica fornecendo o ID da tarefa e o novo status.
- Excluir Tarefa: O usuário pode excluir uma tarefa do banco de dados fornecendo o ID da tarefa.

Fechar Banco de Dados:
- Ao final da execução, quando o usuário escolhe sair, o banco de dados é fechado com `sqlite3_close()`.

## SQLite

O programa faz uso da biblioteca SQLite (`sqlite3.h`), que é uma solução de banco de dados embutido em C/C++. O SQLite é uma escolha popular em muitas aplicações devido à sua simplicidade e ao fato de que não requer um servidor separado para rodar, sendo ideal para programas menores ou com requisitos de baixo custo.

Operações SQL Utilizadas:
- CREATE TABLE: Criação da tabela `tasks`, com três colunas: `id` (inteiro primário), `description` (texto) e `status` (texto).
- INSERT INTO: Inserção de novas tarefas na tabela.
- SELECT: Recuperação de todas as tarefas do banco de dados.
- UPDATE: Atualização do status de uma tarefa existente.
- DELETE: Exclusão de uma tarefa com base no ID.

## Principais Características e Funcionalidades
- CRUD Básico: O programa permite adicionar, listar, atualizar e excluir tarefas de um banco de dados.
- Interação com o Usuário: O programa interage com o usuário através de um menu de texto simples, permitindo a entrada de dados e exibindo resultados no console.
- Persistência de Dados: Usando SQLite, as tarefas são persistidas em um banco de dados, o que significa que as tarefas não são perdidas quando o programa é fechado.
- Estrutura Simples: O código tem uma estrutura simples, sem dependências complexas, o que facilita sua compreensão e modificação.

## Possíveis Melhorias e Considerações

- Segurança: O código utiliza concatenação de strings para construir consultas **SQL**. Isso pode abrir a porta para **SQL Injection**, uma vulnerabilidade comum. Uma abordagem mais segura seria usar prepared statements.

- Validação de Entrada: O código não valida as entradas do usuário, o que pode causar falhas se o usuário inserir dados incorretos (como texto em campos que devem ser números).

## **Muito Obrigado pela sua atenção!**
- Interface Gráfica: O programa usa uma interface de linha de comando. Seria possível implementar uma interface gráfica para facilitar a interação do usuário.

- Melhoria no Fluxo de Controle: O fluxo de controle poderia ser melhorado para evitar a repetição de código, e também para oferecer feedback ao usuário sobre as operações executadas (como mensagens de sucesso ou erro).

