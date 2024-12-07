#ifndef FM_EDITARPRODUTOVENDA_H
#define FM_EDITARPRODUTOVENDA_H

#include <QDialog>

namespace Ui {
class fm_editarprodutovenda;
}

class fm_editarprodutovenda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_editarprodutovenda(QWidget *parent = nullptr);
    ~fm_editarprodutovenda();

private slots:
    void on_btn_edita_confirma_clicked();

    void on_btn_edita_cancela_clicked();

private:
    Ui::fm_editarprodutovenda *ui;
};

#endif // FM_EDITARPRODUTOVENDA_H
