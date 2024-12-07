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
    // Sinaliza que houve alteração
    fm_novavenda::alterou = true;

    // Captura os valores digitados
    QString quantidadeStr = ui->txt_edita_quantidade->text();
    QString precoStr = ui->txt_edita_precoUnitario->text();

    // Substitui vírgulas por pontos
    quantidadeStr.replace(",", ".");
    precoStr.replace(",", ".");

    // Converte os valores para double usando QString::toDouble
    bool quantidadeOk, precoOk;
    double quantidade = quantidadeStr.toDouble(&quantidadeOk);
    double precoUnitario = precoStr.toDouble(&precoOk);

    // Valida a conversão
    if (!quantidadeOk || !precoOk || quantidade <= 0 || precoUnitario <= 0) {
        qDebug() << "Erro: Quantidade ou preço unitário inválidos!";
        return; // Não prossiga se os valores forem inválidos
    }

    // Atualiza as variáveis globais
    fm_novavenda::g_qtde = QString::number(quantidade, 'f', 2);
    fm_novavenda::g_valuni = QString::number(precoUnitario, 'f', 2);

    // Calcula o valor total
    double valorTotal = quantidade * precoUnitario;
    fm_novavenda::g_valtotal = QString::number(valorTotal, 'f', 2);

    // Debug: Mostra os valores finais
    qDebug() << "Valores atualizados - Quantidade:" << fm_novavenda::g_qtde
             << ", Preço Unitário:" << fm_novavenda::g_valuni
             << ", Valor Total:" << fm_novavenda::g_valtotal;

    close();
}




void fm_editarprodutovenda::on_btn_edita_cancela_clicked()
{
    fm_novavenda::alterou = false;
    close();
}

