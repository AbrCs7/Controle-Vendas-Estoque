#include "fm_editarprodutovenda.h"
#include "ui_fm_editarprodutovenda.h"
#include "fm_novavenda.h"

fm_editarprodutovenda::fm_editarprodutovenda(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fm_editarprodutovenda)
{
    ui->setupUi(this);
    ui->txt_edita_produto->setText(fm_novavenda::g_prod);
    ui->txt_edita_quantidade->setText(fm_novavenda::g_qtde);
    ui->txt_edita_precoUnitario->setText(fm_novavenda::g_valuni);
}

fm_editarprodutovenda::~fm_editarprodutovenda()
{
    delete ui;
}

void fm_editarprodutovenda::on_btn_edita_confirma_clicked()
{
        QString aux;

    fm_novavenda::alterou = true;
    fm_novavenda::g_qtde = ui->txt_edita_quantidade->text();

    aux = ui->txt_edita_precoUnitario->text();
    std::replace(aux.begin(), aux.end(),',','.');
    fm_novavenda::g_valuni = aux;

    fm_novavenda::g_valtotal = QString::number(ui->txt_edita_quantidade->text().toDouble()*aux.toDouble());
    close();
}


void fm_editarprodutovenda::on_btn_edita_cancela_clicked()
{
    fm_novavenda::alterou = false;
    close();
}

