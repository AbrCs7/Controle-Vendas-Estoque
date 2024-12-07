#include "fm_gestaovendas.h"
#include "ui_fm_gestaovendas.h"
#include <QtSql>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QDesktopServices>

fm_gestaoVendas::fm_gestaoVendas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_gestaoVendas)
{
    ui->setupUi(this);


    ui->tw_listaProdutosVendas->horizontalHeader()->setVisible(true);
    ui->tw_listaProdutosVendas->setColumnCount(5);
    QStringList cabe1={"Movimentação", "Produto", "qtde", "Valor Unitário", "Valor Total"};
    ui->tw_listaProdutosVendas->setHorizontalHeaderLabels(cabe1);
    ui->tw_listaProdutosVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listaProdutosVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_listaProdutosVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaProdutosVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->tw_listaVendas->horizontalHeader()->setVisible(true);
    ui->tw_listaVendas->setColumnCount(6);
    QStringList cabe2={"ID", "Data", "Hora", "Colaborador", "Valor Total", "Tipo Pgto"};
    ui->tw_listaVendas->setHorizontalHeaderLabels(cabe2);
    ui->tw_listaVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listaVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_listaVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listaVendas->setStyleSheet("QTableView::item:selected { background-color: red; }");


    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }
    int contLinhas = 0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas");
    if(!query.exec()){
        QMessageBox::critical(this, "Erro", "Erro ao acessar banco de dados");
    }else{
        query.first();
        do{
            ui->tw_listaVendas->insertRow(contLinhas);
            ui->tw_listaVendas->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 5, new QTableWidgetItem(query.value(5).toString()));

            contLinhas++;
        }while(query.next());
    }

    con.fechar();
}

fm_gestaoVendas::~fm_gestaoVendas()
{
    delete ui;
}


void fm_gestaoVendas::on_btn_filtrar_clicked()
{

    ui->tw_listaProdutosVendas->setRowCount(0);
    ui->tw_listaVendas->setRowCount(0);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }
    int contLinhas = 0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas where data_venda between'"+ui->de_dataini->text()+"' and '"+ui->de_datafim->text()+"'");
    if(!query.exec()){
        QMessageBox::critical(this, "Erro", "Erro ao acessar banco de dados");
    }else{

        if (!query.first()) {
            QMessageBox::information(this, "Aviso", "Nenhum registro encontrado para o intervalo especificado.");
            return;
        }

        do{
            ui->tw_listaVendas->insertRow(contLinhas);
            ui->tw_listaVendas->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 5, new QTableWidgetItem(query.value(5).toString()));

            contLinhas++;
        }while(query.next());
    }
    con.fechar();

}


void fm_gestaoVendas::on_btn_mostrarTodasVendas_clicked()
{
    ui->tw_listaVendas->setRowCount(0);
    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }
    int contLinhas = 0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas");
    if(!query.exec()){
        QMessageBox::critical(this, "Erro", "Erro ao acessar banco de dados");
    }else{
        query.first();
        do{
            ui->tw_listaVendas->insertRow(contLinhas);
            ui->tw_listaVendas->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tw_listaVendas->setItem(contLinhas, 5, new QTableWidgetItem(query.value(5).toString()));

            contLinhas++;
        }while(query.next());
    }
    con.fechar();
}


void fm_gestaoVendas::on_brn_relatorioPDF_clicked()
{
    QString nome = QDir::currentPath()+"/"+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text()+"_venda.pdf";

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome);

    QPainter painter;
    if(!painter.begin(&printer)){
        QMessageBox::warning(this, "Erro", "Erro ao abrir PDF");
        return;
    }


    // Configuração geral
    QFont font("Arial", 10);
    painter.setFont(font);

    // Desenho do cabeçalho
    painter.drawPixmap(25, 25, QPixmap(":/imagens/img/logo.png")); // Logo
    painter.setFont(QFont("Arial", 15, QFont::Bold));
    painter.drawText(200, 200, "Relatório de Venda");
    painter.setFont(QFont("Arial", 10));
    painter.drawText(25, 230, "ID: " + ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 0)->text());
    painter.drawText(200, 230, "Data: " + ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 1)->text());
    painter.drawText(400, 230, "Colaborador: " + ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 3)->text());

    // Desenho do cabeçalho da tabela
    int linha = 300; // Posição inicial
    int saltoLinha = 30;
    int col1 = 25, col2 = 150, col3 = 300, col4 = 400, col5 = 500;

    painter.drawText(col1, linha, "Item");
    painter.drawText(col2, linha, "Produto");
    painter.drawText(col3, linha, "Qtde");
    painter.drawText(col4, linha, "V. Unitário");
    painter.drawText(col5, linha, "V. Total");

    linha += saltoLinha;

    // Desenho das bordas e linhas da tabela
    for (int i = 0; i < ui->tw_listaProdutosVendas->rowCount(); i++) {
        // Dados
        painter.drawText(col1, linha, ui->tw_listaProdutosVendas->item(i, 0)->text()); // Movimentação
        painter.drawText(col2, linha, ui->tw_listaProdutosVendas->item(i, 1)->text()); // Produto
        painter.drawText(col3, linha, ui->tw_listaProdutosVendas->item(i, 2)->text()); // Quantidade
        painter.drawText(col4, linha, ui->tw_listaProdutosVendas->item(i, 3)->text()); // Valor Unitário
        painter.drawText(col5, linha, ui->tw_listaProdutosVendas->item(i, 4)->text()); // Valor Total

        // Linha de separação
        painter.drawLine(col1 - 5, linha + 5, col5 + 100, linha + 5);

        linha += saltoLinha;
    }

    // Desenho do rodapé
    linha += 50; // Espaçamento
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(25, linha, "Valor Total: " + ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 4)->text());

    painter.end();

    // Abrir o PDF gerado
    QDesktopServices::openUrl(QUrl::fromLocalFile(nome));
}

void fm_gestaoVendas::on_tw_listaVendas_cellClicked(int row, int column)
{
    //ui->tw_listaProdutosVendas->clear();
    ui->tw_listaProdutosVendas->setRowCount(0);


    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }
    int contLinhas = 0;
    QSqlQuery query;
    query.prepare("select id_movimentacao,produto,qtde,valor_un,valor_total from tb_produtosVendas where id_venda="+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text());
    if(!query.exec()){
        QMessageBox::critical(this, "Erro", "Erro ao acessar banco de dados: " + query.lastError().text());
    }else{
        query.first();
        do{
            ui->tw_listaProdutosVendas->insertRow(contLinhas);
            ui->tw_listaProdutosVendas->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaProdutosVendas->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaProdutosVendas->setItem(contLinhas, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaProdutosVendas->setItem(contLinhas, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tw_listaProdutosVendas->setItem(contLinhas, 4, new QTableWidgetItem(query.value(4).toString()));

            contLinhas++;
        }while(query.next());
    }
    con.fechar();
}

