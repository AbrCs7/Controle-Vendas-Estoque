#include "fm_novavenda.h"
#include "ui_fm_novavenda.h"
#include <QMessageBox>
#include <fm_editarprodutovenda.h>
#include "fm_pesquisarproduto.h"
#include "fm_principal.h"
#include "variaveis_globais.h"
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QDesktopServices>
#include "pesquisaprod.h"
#include <QLocale>

QString fm_novavenda::g_idprod;
QString fm_novavenda::n_idprod;
QString fm_novavenda::g_prod;
QString fm_novavenda::g_qtde;
QString fm_novavenda::g_valuni;
QString fm_novavenda::g_valtotal;
bool fm_novavenda::alterou;
bool fm_novavenda::alterou2;

fm_novavenda::fm_novavenda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_novavenda)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir banco de dados");
        }
    }

    ui->tw_listaprodutos->setColumnCount(5);
    ui->tw_listaprodutos->setColumnWidth(0, 200);
    ui->tw_listaprodutos->setColumnWidth(1, 300);
    ui->tw_listaprodutos->setColumnWidth(2, 100);
    ui->tw_listaprodutos->setColumnWidth(3, 100);
    ui->tw_listaprodutos->setColumnWidth(4, 100);

    QStringList cabecalhos = {"Código", "Produto", "Valor Un.", "Qtde", "Total"};
    ui->tw_listaprodutos->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_listaprodutos->setStyleSheet("QTableView::item:selected { background-color: blue; }");
    ui->tw_listaprodutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listaprodutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaprodutos->verticalHeader()->setVisible(false);

    ui->txt_codproduto->setFocus();
    contlinhas = 0;

}

fm_novavenda::~fm_novavenda()
{
    delete ui;
}

void fm_novavenda::on_txt_codproduto_returnPressed()
{
    QSqlQuery query;
    QString id = ui->txt_codproduto->text();
    double valtot;

    QLocale locale(QLocale::Portuguese, QLocale::Brazil);

    query.prepare("select id_produto,produto,valor_venda from tb_produtos where id_produto="+id);
    if(query.exec()){
        query.first();
        if(query.value(0).toString() != ""){
            ui->tw_listaprodutos->insertRow(contlinhas);
            ui->tw_listaprodutos->setItem(contlinhas,0, new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaprodutos->setItem(contlinhas,1, new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaprodutos->setItem(contlinhas,2,  new QTableWidgetItem(locale.toString(query.value(2).toDouble(), 'f', 2)));
            ui->tw_listaprodutos->setItem(contlinhas,3, new QTableWidgetItem(ui->txt_qtde->text()));
            valtot = ui->txt_qtde->text().toDouble() * query.value(2).toDouble();
            ui->tw_listaprodutos->setItem(contlinhas,4, new QTableWidgetItem(locale.toString(valtot, 'f', 2)));
            ui->tw_listaprodutos->setRowHeight(contlinhas,20);
            contlinhas++;
            ui->lb_totalvenda->setText("R$ " + locale.toString(calculaTotal(ui->tw_listaprodutos, 4), 'f', 2));
        }else{
            QMessageBox::warning(this, "Erro", "Produto não encontrado");
        }
        resetaCampos();
    }else{
        QMessageBox::warning(this, "Erro", "Erro ao inserir novo produto");
    }
}

void fm_novavenda::resetaCampos(){
    ui->txt_codproduto->clear();
    ui->txt_qtde->setText("1");
    ui->txt_codproduto->setFocus();
}

void fm_novavenda::removerLinhas(QTableWidget *tw){
    while(tw->rowCount() > 0){
        tw->removeRow(0);
    }
}

double fm_novavenda::calculaTotal(QTableWidget *tw, int coluna) {
    double total = 0.0; // Inicializa o total
    int totallinhas = tw->rowCount(); // Obtém o número de linhas

    QLocale locale(QLocale::Portuguese, QLocale::Brazil); // Para tratar números no formato BR
    for (int i = 0; i < totallinhas; i++) {
        if (tw->item(i, coluna)) { // Verifica se o item não é nulo
            bool ok;
            double valor = locale.toDouble(tw->item(i, coluna)->text(), &ok); // Tenta converter o texto para double
            if (ok) { // Só soma valores válidos
                total += valor;
            }
        }
    }

    // Arredonda o total para duas casas decimais
    total = std::round(total * 100.0) / 100.0;

    return total; // Retorna o total calculado
}



void fm_novavenda::on_btn_excluirproduto_clicked()
{
    if(ui->tw_listaprodutos->currentColumn() != -1){
        QMessageBox::StandardButton opc = QMessageBox::question(this, "Exclusão", "Confirma Exclusão do Produto?", QMessageBox::Yes|QMessageBox::No);
        if(opc == QMessageBox::Yes){
            ui->tw_listaprodutos->removeRow(ui->tw_listaprodutos->currentRow());
            ui->lb_totalvenda->setText("R$ "+QString::number(calculaTotal(ui->tw_listaprodutos, 4)));
            contlinhas --;
        }
    }else{
        QMessageBox::warning(this, "Erro", "Selecione um produto para excluir");
    }
}


void fm_novavenda::on_btn_editarproduto_clicked()
{
    if (ui->tw_listaprodutos->currentColumn() != -1) {
        int linha = ui->tw_listaprodutos->currentRow();
        QLocale locale(QLocale::Portuguese, QLocale::Brazil);

        // Captura os valores da linha da tabela de vendas
        g_idprod = ui->tw_listaprodutos->item(linha, 0)->text();
        g_prod = ui->tw_listaprodutos->item(linha, 1)->text();
        g_qtde = ui->tw_listaprodutos->item(linha, 3)->text();
        g_valuni = ui->tw_listaprodutos->item(linha, 2)->text();

        // Debugging: Verifique os valores capturados da tabela
        qDebug() << "g_qtde: " << g_qtde;
        qDebug() << "g_valuni: " << g_valuni;

        // Cria a janela de edição do produto
        fm_editarprodutovenda f_editarprodutovenda;
        f_editarprodutovenda.exec();

        // Se a edição foi confirmada (alterada)
        if (alterou) {
            // Substitui a vírgula por ponto (se presente)
            g_qtde.replace(',', '.');
            g_valuni.replace(',', '.');

            // Converte os valores para double
            double valorUnitario = g_valuni.toDouble();
            double quantidade = g_qtde.toDouble();

            // Debugging: Verifique os valores de valorUnitario e quantidade após a conversão
            qDebug() << "Valor Unitário (double): " << valorUnitario;
            qDebug() << "Quantidade (double): " << quantidade;

            // Verifique se as conversões são bem-sucedidas
            if (valorUnitario == 0 || quantidade == 0) {
                qDebug() << "Erro: Quantidade ou preço unitário inválido!";
                return; // Sai da função se algum valor for inválido
            }

            // Calcula o valor total
            double valorTotal = valorUnitario * quantidade;

            // Debugging: Verifique o valor total calculado
            qDebug() << "Valor Total Calculado: " << valorTotal;

            // Atualiza as variáveis globais
            g_valtotal = QString::number(valorTotal, 'f', 2);

            // Atualiza as células da tabela
            ui->tw_listaprodutos->item(linha, 2)->setText(QString::number(valorUnitario, 'f', 2)); // Atualiza o preço unitário
            ui->tw_listaprodutos->item(linha, 3)->setText(QString::number(quantidade, 'f', 2));  // Atualiza a quantidade
            ui->tw_listaprodutos->item(linha, 4)->setText(locale.toString(valorTotal, 'f', 2)); // Atualiza o valor total
            qDebug() << "Valor Total Atualizado: " << g_valtotal;

            // Atualiza o valor total da venda na interface
            ui->lb_totalvenda->setText("R$ " + locale.toString(calculaTotal(ui->tw_listaprodutos, 4), 'f', 2));

            // Debugging: Confirme que a tabela foi atualizada
            qDebug() << "Tabela de produtos atualizada na linha " << linha
                     << ", Produto: " << g_prod
                     << ", Valor Total: " << g_valtotal;
        }
    }
}






void fm_novavenda::on_btn_finalizarvenda_clicked()
{
    if(ui->tw_listaprodutos->rowCount() > 0){
        //int idVenda;
        QString msgFimVenda;
        double total = calculaTotal(ui->tw_listaprodutos, 4);
        QString data=QDate::currentDate().toString("dd/MM/yyyy");
        QString hora = QTime::currentTime().toString("hh:mm:ss");

        QSqlQuery query;
        query.prepare("insert into tb_vendas (data_venda,hora_venda,id_colaborador,valor_total,id_tipo_pagamento) values('"+data+"','"+hora+"',"+QString::number(variaveis_globais::id_colab)+", "+QString::number(total)+", 1)");
        if(!query.exec()){
            QMessageBox::warning(this, "Erro", "Erro ao registrar nova venda");
        }else{
            query.prepare("select id_venda from tb_vendas order by id_venda desc limit 1");
            query.exec();
            query.first();
            idVenda = query.value(0).toInt();
            msgFimVenda = "ID Venda: "+QString::number(idVenda)+"\nValor total: R$"+QString::number(total);

            int totalLinhas = ui->tw_listaprodutos->rowCount();
            int linha = 0;
            while (linha < totalLinhas) {
                QString prod = ui->tw_listaprodutos->item(linha, 1)->text();
                QString qtde = ui->tw_listaprodutos->item(linha, 3)->text();
                QString valUn = ui->tw_listaprodutos->item(linha, 2)->text();
                QString valTot = ui->tw_listaprodutos->item(linha, 4)->text();

                query.prepare("insert into tb_produtosVendas (id_venda, produto, qtde, valor_un, valor_total) values("+QString::number(idVenda)+",'"+prod+"',"+qtde+","+valUn+","+valTot+")");
                query.exec();
                linha++;


            }

            QMessageBox::information(this, "Venda Concluída", msgFimVenda);
            resetaCampos();
            removerLinhas(ui->tw_listaprodutos);
            ui->lb_totalvenda->setText("R$ 0.00");




        }
    }else{
        QMessageBox::warning(this, "Erro", "Não existem produtos nesta venda\nPrimeiro adicione um produto");
    }
}


void fm_novavenda::on_btn_orcamento_clicked()
{
    //depois criar rotina para colocar cliente no pedido
    QString nome = QDir::currentPath()+"/"+QString::number(idVenda)+"_venda.pdf";
    if (!QDir().exists(QDir::currentPath())) {
        QMessageBox::warning(this, "Erro", "Diretório inválido para salvar o PDF.");
        return;
    }


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
    painter.drawText(200, 200, "Orçamento de Venda");
    painter.setFont(QFont("Arial", 10));
    painter.drawText(25, 230, "ID: " + QString::number(idVenda));
    painter.drawText(200, 230, "Data: " + QDate::currentDate().toString("dd/MM/yyyy"));
    painter.drawText(400, 230, "Colaborador: " + QString::number( variaveis_globais::id_colab));

    // Desenho do cabeçalho da tabela
    int poslinha = 300; // Posição inicial
    int saltoLinha = 30;
    int col1 = 25, col2 = 150, col3 = 300, col4 = 400, col5 = 500;

    painter.drawText(col1, poslinha, "Código");
    painter.drawText(col2, poslinha, "Produto");
    painter.drawText(col3, poslinha, "V. Unitário");
    painter.drawText(col4, poslinha, "Qtde");
    painter.drawText(col5, poslinha, "V. Total");

    poslinha += saltoLinha;

    // Desenho das bordas e linhas da tabela
    for (int i = 0; i < ui->tw_listaprodutos->rowCount(); i++) {
        // Dados
        painter.drawText(col1, poslinha, ui->tw_listaprodutos->item(i, 0)->text()); // Código
        painter.drawText(col2, poslinha, ui->tw_listaprodutos->item(i, 1)->text()); // Produto
        painter.drawText(col3, poslinha, ui->tw_listaprodutos->item(i, 2)->text()); // Valor Unitário
        painter.drawText(col4, poslinha, ui->tw_listaprodutos->item(i, 3)->text()); // Quantidade
        painter.drawText(col5, poslinha, ui->tw_listaprodutos->item(i, 4)->text()); // Valor Total

        // Linha de separação
        painter.drawLine(col1 - 5, poslinha + 5, col5 + 100, poslinha + 5);

        poslinha += saltoLinha;
    }

    // Desenho do rodapé
    poslinha += 50; // Espaçamento
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(25, poslinha, "Valor Total: R$ " + QString::number(calculaTotal(ui->tw_listaprodutos, 4)));

    painter.end();

    // Abrir o PDF gerado
    QDesktopServices::openUrl(QUrl::fromLocalFile(nome));
}


void fm_novavenda::on_pushButton_4_clicked()
{

    fm_pesquisarproduto pesquisaprod;
    pesquisaprod.setConexao(con.bancoDeDados);
    pesquisaprod.exec();

    if(alterou2){
        ui->txt_codproduto->setText(n_idprod);
        ui->txt_codproduto->setFocus();
    }
}

