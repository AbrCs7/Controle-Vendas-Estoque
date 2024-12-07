#include "fm_gestaocolaborador.h"
#include "ui_fm_gestaocolaborador.h"
#include <QMessageBox>
#include <QtSql>
#include "funcoes_globais.h"

fm_gestaoColaborador::fm_gestaoColaborador(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_gestaoColaborador)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }

    ui->cb_acesso_novocolab->addItem("A");
    ui->cb_acesso_novocolab->addItem("B");
    ui->txt_nome_novocolab->setFocus();

    ui->cb_ge_acesso->addItem("A");
    ui->cb_ge_acesso->addItem("B");


    ui->tw_ge_listacolab->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);

    ui->tw_ge_listacolab->setColumnWidth(0, 80);
    ui->tw_ge_listacolab->setColumnWidth(1, 170);
    QStringList cabecalhos = {"ID" , "Nome"};
    ui->tw_ge_listacolab->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_ge_listacolab->setStyleSheet("QTableView::item:selected { background-color: red; }");
    ui->tw_ge_listacolab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_ge_listacolab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_ge_listacolab->verticalHeader()->setVisible(false);


}

fm_gestaoColaborador::~fm_gestaoColaborador()
{
    delete ui;
}

void fm_gestaoColaborador::on_btn_novo_novocolab_clicked()
{
    ui->txt_nome_novocolab->clear();
    ui->txt_username_novocolab->clear();
    ui->txt_senha_novocolab->clear();
    ui->txt_fone_novocolab->clear();
    ui->cb_acesso_novocolab->setCurrentIndex(0);
    ui->txt_nome_novocolab->setFocus();
}


void fm_gestaoColaborador::on_btn_gravar_novocolab_clicked()
{

    QString aux;

    QString nome = ui->txt_nome_novocolab->text();
    QString username = ui->txt_username_novocolab->text();
    QString senha = ui->txt_senha_novocolab->text();
    QString telefone = ui->txt_fone_novocolab->text();
    QString acesso = ui->cb_acesso_novocolab->currentText();

    QSqlQuery query;
    query.prepare("insert into tb_colaboradores (nome_colab,username_colab,senha_colab,fone_colab,acesso_colab) values"
                  "('"+nome+"','"+username+"','"+senha+"','"+telefone+"','"+acesso+"')");
    if(!query.exec()){
        QMessageBox::critical(this, "Erro", "Erro ao inserir novo colaborador");
    }else{
        QMessageBox::information(this, "Produto Cadastrado", "Colaborador gravado com sucesso");

        ui->txt_nome_novocolab->clear();
        ui->txt_username_novocolab->clear();
        ui->txt_senha_novocolab->clear();
        ui->txt_fone_novocolab->clear();
        ui->cb_acesso_novocolab->setCurrentIndex(0);
        ui->txt_nome_novocolab->setFocus();
    }
}


void fm_gestaoColaborador::on_btn_cancelar_novocolab_clicked()
{
    close();
}


void fm_gestaoColaborador::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        funcoes_globais::removerlinhas(ui->tw_ge_listacolab);
        int contlinhas = 0;
        QSqlQuery query;
        query.prepare("select id_colab,nome_colab from tb_colaboradores order by id_colab");
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_listacolab->insertRow(contlinhas);
                ui->tw_ge_listacolab->setItem(contlinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_listacolab->setItem(contlinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_listacolab->setRowHeight(contlinhas, 20);
                contlinhas++;
            }
        }else{
            QMessageBox::warning(this, "Erro", "Erro ao listar colaboradores");
        }
    }
}


void fm_gestaoColaborador::on_tw_ge_listacolab_itemSelectionChanged()
{
    int id = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(), 0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from tb_colaboradores where id_colab="+QString::number(id));
    if(query.exec()){
        query.first();
        ui->txt_ge_nome->setText(query.value(1).toString());
        ui->txt_ge_username->setText(query.value(2).toString());
        ui->txt_ge_senha->setText(query.value(3).toString());
        ui->txt_ge_fone->setText(query.value(4).toString());
        ui->cb_ge_acesso->setCurrentText(query.value(5).toString());
    }
}


void fm_gestaoColaborador::on_btn_ge_filtro_clicked()
{
    QString busca;
    funcoes_globais::removerlinhas(ui->tw_ge_listacolab);
    if(ui->txt_ge_filtro->text() == ""){
        if(ui->rb_ge_idcolab->isChecked()){
            busca = "Select id_colab,nome_colab from tb_colaboradores order by id_colab";
        }else{
            busca = "Select id_colab,nome_colab from tb_colaboradores order by nome_colab";
        }
    }else{
        if(ui->rb_ge_idcolab->isChecked()){
            busca = "Select id_colab,nome_colab from tb_colaboradores where id_colab="+ui->txt_ge_filtro->text()+" order by id_colab";
        }else{
            busca = "Select id_colab,nome_colab from tb_colaboradores where nome_colab like '%"+ui->txt_ge_filtro->text()+"%' order by nome_colab";
        }
    }
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec()){
        while(query.next()){
            ui->tw_ge_listacolab->insertRow(contlinhas);
            ui->tw_ge_listacolab->setItem(contlinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_ge_listacolab->setItem(contlinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_ge_listacolab->setRowHeight(contlinhas, 20);
            contlinhas++;
        }
    }else{
        QMessageBox::warning(this, "Erro", "Erro ao listar colaboradores");
    }
    ui->txt_ge_filtro->clear();
    ui->txt_ge_filtro->setFocus();
}


void fm_gestaoColaborador::on_btn_ge_salvar_clicked()
{
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this, "Erro", "Selecione um colaborador");
        return;
    }

    QString id = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(), 0)->text();

    QSqlQuery query;
    QString nome = ui->txt_ge_nome->text();
    QString username = ui->txt_ge_username->text();
    QString senha = ui->txt_ge_senha->text();
    QString fone = ui->txt_ge_fone->text();
    QString acesso = ui->cb_ge_acesso->currentText();

    query.prepare("update tb_colaboradores set nome_colab='"+nome+"',username_colab='"+username+"',senha_colab='"+senha+"',fone_colab='"+fone+"',acesso_colab='"+acesso+"' where id_colab="+id);
    if(query.exec()){
        int linha = ui->tw_ge_listacolab->currentRow();
        ui->tw_ge_listacolab->item(linha, 1)->setText(nome);
        QMessageBox::information(this, "Atualizaçao", "Colaborador Atualizado com sucesso");
    }else{
        QMessageBox::warning(this, "Erro", "Erro ao atualizar colaborador");
    }
}


void fm_gestaoColaborador::on_btn_ge_excluir_clicked()
{
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this, "Erro", "Selecione um colaborador");
        return;
    }

    QMessageBox::StandardButton opc = QMessageBox::question(this, "Exclusão", "Confirma Exclusão do Colaborador?", QMessageBox::Yes|QMessageBox::No);
    if(opc == QMessageBox::Yes){
        int linha = ui->tw_ge_listacolab->currentRow();
        QString id = ui->tw_ge_listacolab->item(linha, 0)->text();
        QSqlQuery query;
        query.prepare("delete from tb_colaboradores where id_colab="+id);
        if(query.exec()){
            ui->tw_ge_listacolab->removeRow(linha);
            QMessageBox::information(this, "Deletado", "Colaborador excluído com sucesso");
        }else{
            QMessageBox::warning(this, "Erro", "Colaborador não pode ser excluído");
        }
    }
}

