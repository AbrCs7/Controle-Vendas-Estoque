#ifndef FM_GESTAOCOLABORADOR_H
#define FM_GESTAOCOLABORADOR_H

#include <QDialog>
#include "conexao.h"

namespace Ui {
class fm_gestaoColaborador;
}

class fm_gestaoColaborador : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoColaborador(QWidget *parent = nullptr);
    ~fm_gestaoColaborador();
    Conexao con;

private slots:
    void on_btn_novo_novocolab_clicked();

    void on_btn_gravar_novocolab_clicked();

    void on_btn_cancelar_novocolab_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_listacolab_itemSelectionChanged();

    void on_btn_ge_filtro_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::fm_gestaoColaborador *ui;
};

#endif // FM_GESTAOCOLABORADOR_H
