#include <iostream>
#include <sqlite3.h>

using namespace std;

// Função para executar comandos SQL
int executeSQL(sqlite3* db, const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Erro SQL: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

// Função para exibir tarefas armazenadas no banco de dados
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << "--------------------------" << endl;
    return 0;
}

int main() {
    sqlite3* db;
    // Abre o banco de dados (ou cria se não existir)
    int rc = sqlite3_open("tasks.db", &db);
    if (rc) {
        cerr << "Erro ao abrir banco de dados: " << sqlite3_errmsg(db) << endl;
        return rc;
    }

    // Criar tabela de tarefas se não existir
    string createTableSQL = "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, description TEXT, status TEXT);";
    executeSQL(db, createTableSQL);

    int option;
    do {
        // Menu de opções
        cout << "\n1. Adicionar Tarefa";
        cout << "\n2. Listar Tarefas";
        cout << "\n3. Atualizar Tarefa";
        cout << "\n4. Excluir Tarefa";
        cout << "\n5. Sair";
        cout << "\nEscolha uma opção: ";
        cin >> option;
        cin.ignore();

        if (option == 1) {
            // Adiciona uma nova tarefa
            string description;
            cout << "Descrição: ";
            getline(cin, description);
            string sql = "INSERT INTO tasks (description, status) VALUES ('" + description + "', 'Pendente');";
            executeSQL(db, sql);
        } 
        else if (option == 2) {
            // Lista todas as tarefas
            string sql = "SELECT * FROM tasks;";
            sqlite3_exec(db, sql.c_str(), callback, 0, nullptr);
        } 
        else if (option == 3) {
            // Atualiza o status de uma tarefa existente
            int id;
            string status;
            cout << "ID da tarefa: ";
            cin >> id;
            cin.ignore();
            cout << "Novo status: ";
            getline(cin, status);
            string sql = "UPDATE tasks SET status = '" + status + "' WHERE id = " + to_string(id) + ";";
            executeSQL(db, sql);
        } 
        else if (option == 4) {
            // Exclui uma tarefa do banco de dados
            int id;
            cout << "ID da tarefa: ";
            cin >> id;
            string sql = "DELETE FROM tasks WHERE id = " + to_string(id) + ";";
            executeSQL(db, sql);
        }
    } while (option != 5); // Continua até que o usuário escolha sair

    // Fecha o banco de dados ao encerrar o programa
    sqlite3_close(db);
    return 0;
}