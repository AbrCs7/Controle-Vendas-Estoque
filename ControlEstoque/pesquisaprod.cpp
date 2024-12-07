#include "pesquisaprod.h"
#include "ui_pesquisaprod.h"

pesquisaProd::pesquisaProd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pesquisaProd)
{
    ui->setupUi(this);
}

pesquisaProd::~pesquisaProd()
{
    delete ui;
}
