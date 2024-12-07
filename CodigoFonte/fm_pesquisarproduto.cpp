#include "fm_pesquisarproduto.h"
#include "ui_fm_pesquisarproduto.h"
#include "funcoes_globais.h"



fm_pesquisarproduto::fm_pesquisarproduto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_pesquisarproduto)
{
    ui->setupUi(this);




    ui->tw_listaProdutos->setColumnCount(2);



        //funcoes_globais::removerlinhas(ui->tw_listaProdutos);
        int contlinhas = 0;
        QSqlQuery query;
        query.prepare("select id_produto,produto from tb_produtos order by produto");
        if(query.exec()){
            while(query.next()){
                ui->tw_listaProdutos->insertRow(contlinhas);
                ui->tw_listaProdutos->setItem(contlinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                ui->tw_listaProdutos->setItem(contlinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                ui->tw_listaProdutos->setRowHeight(contlinhas, 20);
                contlinhas++;
            }
            ui->tw_listaProdutos->setColumnWidth(0, 150);
            ui->tw_listaProdutos->setColumnWidth(1, 350);
            QStringList cabecalhos = {"Código" , "Produto"};
            ui->tw_listaProdutos->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_listaProdutos->setStyleSheet("QTableView::item:selected { background-color: red; }");
            ui->tw_listaProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_listaProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_listaProdutos->verticalHeader()->setVisible(false);
        }else{
            QMessageBox::warning(this, "Erro", "Erro ao listar produtos");
        }


}

fm_pesquisarproduto::~fm_pesquisarproduto()
{
    delete ui;
}

void fm_pesquisarproduto::on_btn_cancelar_clicked()
{
    fm_novavenda::alterou = false;
    close();
}


void fm_pesquisarproduto::on_btn_confirmar_clicked()
{
    if(ui->tw_listaProdutos->currentColumn() != -1){
        fm_novavenda::alterou2 = true;
        fm_novavenda::n_idprod = ui->tw_listaProdutos->item(ui->tw_listaProdutos->currentRow(),0)->text();
        close();
    }else{
        QMessageBox::warning(this, "Aviso", "Primeiro selecione um item");
    }
}

void fm_pesquisarproduto::setConexao(QSqlDatabase &db) {
    con = db;  // Armazene a conexão passada
}



void fm_pesquisarproduto::on_btn_pesquisar_clicked()
{
    QString busca;
    funcoes_globais::removerlinhas(ui->tw_listaProdutos);
    if(ui->le_pesquisar->text() == ""){
        if(ui->rb_idProduto->isChecked()){
            busca = "Select id_produto,produto from tb_produtos order by id_produto";
        }else{
            busca = "Select id_produto,produto from tb_produtos order by produto";
        }
    }else{
        if(ui->rb_idProduto->isChecked()){
            busca = "Select id_produto,produto from tb_produtos where id_produto="+ui->le_pesquisar->text()+" order by id_produto";
        }else{
            busca = "Select id_produto,produto from tb_produtos where produto like '%"+ui->le_pesquisar->text()+"%' order by produto";
        }
    }
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec()){
        while(query.next()){
            ui->tw_listaProdutos->insertRow(contlinhas);
            ui->tw_listaProdutos->setItem(contlinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaProdutos->setItem(contlinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaProdutos->setRowHeight(contlinhas, 20);
            contlinhas++;
        }
    }else{
        QMessageBox::warning(this, "Erro", "Erro ao listar produto");
    }
    ui->le_pesquisar->clear();
    ui->le_pesquisar->setFocus();
}

