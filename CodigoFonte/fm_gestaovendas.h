#ifndef FM_GESTAOVENDAS_H
#define FM_GESTAOVENDAS_H

#include <QDialog>
#include "conexao.h"

namespace Ui {
class fm_gestaoVendas;
}

class fm_gestaoVendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoVendas(QWidget *parent = nullptr);
    ~fm_gestaoVendas();
    Conexao con;

private slots:

    void on_btn_filtrar_clicked();

    void on_btn_mostrarTodasVendas_clicked();

    void on_brn_relatorioPDF_clicked();

    void on_tw_listaVendas_cellClicked(int row, int column);

private:
    Ui::fm_gestaoVendas *ui;
};

#endif // FM_GESTAOVENDAS_H
