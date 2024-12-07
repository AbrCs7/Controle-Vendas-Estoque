#ifndef FM_NOVAVENDA_H
#define FM_NOVAVENDA_H

#include <QDialog>
#include "conexao.h"
#include <QTableWidget>
#include <QDate>
#include <QString>



namespace Ui {
class fm_novavenda;
}

class fm_novavenda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_novavenda(QWidget *parent = nullptr);
    ~fm_novavenda();
    Conexao con;
    int contlinhas;
    void resetaCampos();
    double calculaTotal(QTableWidget *tw, int coluna);
    static QString g_idprod, n_idprod, g_prod, g_qtde, g_valuni, g_valtotal;
    static bool alterou, alterou2;
    void removerLinhas(QTableWidget *tw);


private slots:
    void on_txt_codproduto_returnPressed();

    void on_btn_excluirproduto_clicked();

    void on_btn_editarproduto_clicked();

    void on_btn_finalizarvenda_clicked();

    void on_btn_orcamento_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::fm_novavenda *ui;
    int idVenda;
};

#endif // FM_NOVAVENDA_H
