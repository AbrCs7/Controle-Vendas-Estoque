#ifndef PESQUISAPROD_H
#define PESQUISAPROD_H

#include <QDialog>
#include "conexao.h"
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class pesquisaProd;
}

class pesquisaProd : public QDialog
{
    Q_OBJECT

public:
    explicit pesquisaProd(QWidget *parent = nullptr);
    ~pesquisaProd();
    Conexao con;

private:
    Ui::pesquisaProd *ui;
};

#endif // PESQUISAPROD_H
