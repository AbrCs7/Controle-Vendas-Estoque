#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao{
public:
    QSqlDatabase bancoDeDados;
    QString local;
    QString banco;
    Conexao(){
        local = qApp->applicationDirPath();
        banco = local+"/db/controlEstoque.db";
        bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    }
    ~Conexao() {
        fechar();
    }

    void fechar() {
        if (bancoDeDados.isOpen()) {
            bancoDeDados.close();
        }
    }
    bool abrir(){

        bancoDeDados.setDatabaseName(banco);

        if(bancoDeDados.open()){
            return true;
        }else{
            return false;
        }
    }
    bool aberto(){
        if(!bancoDeDados.isOpen()){
            return false;
        }else{
            return true;
        }
    }


};

#endif // CONEXAO_H
