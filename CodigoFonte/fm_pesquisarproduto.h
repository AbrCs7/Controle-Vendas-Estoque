#ifndef FM_PESQUISARPRODUTO_H
#define FM_PESQUISARPRODUTO_H

#include <QDialog>
#include <QMessageBox>
#include "fm_novavenda.h"


namespace Ui {
class fm_pesquisarproduto;
}

class fm_pesquisarproduto : public QDialog
{
    Q_OBJECT

public:
    explicit fm_pesquisarproduto(QWidget *parent = nullptr);
    ~fm_pesquisarproduto();
    void setConexao(QSqlDatabase &db);



private slots:
    void on_btn_cancelar_clicked();

    void on_btn_confirmar_clicked();

    void on_btn_pesquisar_clicked();

private:
    Ui::fm_pesquisarproduto *ui;
    QSqlDatabase con;
};

#endif // FM_PESQUISARPRODUTO_H
