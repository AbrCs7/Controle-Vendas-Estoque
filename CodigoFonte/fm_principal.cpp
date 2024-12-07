#include "fm_principal.h"
#include "ui_fm_principal.h"
#include <QMessageBox>
#include "fm_logar.h"
#include "fm_novavenda.h"
#include "fm_gestaocolaborador.h"
#include "fm_gestaoestoque.h"
#include "fm_gestaovendas.h"
#include "variaveis_globais.h"

int variaveis_globais::id_colab;
QString variaveis_globais::nome_colab;
QString variaveis_globais::acesso_colab;
QString variaveis_globais::username_colab;
bool variaveis_globais::logado;


Fm_principal::Fm_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fm_principal)
{
    ui->setupUi(this);


    variaveis_globais::logado = false;
    cadFechado.addFile(":/imagens/img/cadeado_fechado.png");
    cadAberto->addFile(":/imagens/img/cadeado_aberto.png");

    ui->btn_bloquear->setIcon(cadFechado);
    ui->statusbar->addWidget(ui->btn_bloquear); //inserir btn na barra de status
    ui->statusbar->addWidget(ui->lb_nome);

}

Fm_principal::~Fm_principal()
{
    delete ui;
}

void Fm_principal::on_btn_bloquear_clicked()
{
    if(!variaveis_globais::logado){
        fm_logar f_logar;
        f_logar.exec();

        if(variaveis_globais::logado){
            ui->btn_bloquear->setIcon(*cadAberto);
            ui->lb_nome->setText(variaveis_globais::nome_colab);
        }

    }else{
        variaveis_globais::logado = false;
        ui->btn_bloquear->setIcon(cadFechado);
        ui->lb_nome->setText("Faça o Login");
    }
}


void Fm_principal::on_pushButton_clicked()
{
    if(variaveis_globais::logado){
        fm_novavenda f_novavenda;
        f_novavenda.exec();
    }else{
        QMessageBox::information(this, "Login", "<br> Você precisa fazer o Login para continuar");
    }
}


void Fm_principal::on_actionEstoque_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_colab == "A"){
            fm_gestaoEstoque f_gestaoEstoque;
            f_gestaoEstoque.exec();
        }else{
            QMessageBox::information(this, "Acesso", "<br> Você não possui permissão para acessar essa função");
        }
    }else{
        QMessageBox::information(this, "Login", "<br> Você precisa fazer o Login para continuar");
    }
}


void Fm_principal::on_actionColaboradores_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_colab == "A"){
            fm_gestaoColaborador f_gestaoColaboradores;
            f_gestaoColaboradores.exec();
        }else{
            QMessageBox::information(this, "Acesso", "<br> Você não possui permissão para acessar essa função");
        }
    }else{
        QMessageBox::information(this, "Login", "<br> Você precisa fazer o Login para continuar");
    }
}


void Fm_principal::on_actionVendas_triggered()
{
    if(variaveis_globais::logado){
        if(variaveis_globais::acesso_colab == "A"){
            fm_gestaoVendas f_gestaoVendas;
            f_gestaoVendas.exec();
        }else{
            QMessageBox::information(this, "Acesso", "<br> Você não possui permissão para acessar essa função");
        }
    }else{
        QMessageBox::information(this, "Login", "<br> Você precisa fazer o Login para continuar");
    }
}


void Fm_principal::on_actionSair_triggered()
{
    close();
}

void Fm_principal::showAbout()
{
    // Cria a caixa de mensagem
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("Sobre Plume Calculator");
    aboutBox.setIcon(QMessageBox::NoIcon);

    // Define o ícone personalizado
    QPixmap windowIcon(":/imagens/img/em-formacao.png");
    aboutBox.setWindowIcon(windowIcon);

    // Define o texto formatado com estilos de HTML
    QString aboutText = R"(
        <div align='center' style='font-family: Arial, sans-serif;'>
            <h2 style='color: #2E86C1;'>Sistema de Vendas e Gestão de Estoque</h2>
            <p style='font-size: 14px;'><b>Desenvolvida por</b> <span style='color: #117A65;'>Abraão Rodrigues</span></p>
            <p style='font-size: 13px;'>
                <a href='https://abrportifolio.com/' style='color: #2980B9; text-decoration: none;'><b>Portfólio  |</b></a>
                &emsp;&emsp;&emsp;&emsp; <!-- Espaço equivalente a uma tabulação -->
                <a href='https://github.com/AbrCs7' style='color: #2980B9; text-decoration: none;'><b>  | GitHub</b></a>
            </p>
            <p style='font-size: 14px;'><b>Saiba mais sobre a </b> <span style='color: #8E44AD;'>Plume Design</span></p>
            <p style='font-size: 13px;'>
                <a href='https://plumedesign.online/' style='color: #2980B9; text-decoration: none;'><b>Acesse</b></a>
            </p>
            <hr style='border: none; height: 1px; background-color: #BDC3C7;'>
            <p style='font-size: 12px; color: #7F8C8D;'>© 2024 Plume Design. Todos os direitos reservados.</p>
        </div>
    )";

    // Configurações da caixa de mensagem
    aboutBox.setTextFormat(Qt::RichText); // Permite HTML para formatar o texto
    aboutBox.setText(aboutText);          // Define o texto formatado
    aboutBox.setStandardButtons(QMessageBox::Ok); // Botão para fechar

    // Exibe a caixa de mensagem
    aboutBox.exec();
}


void Fm_principal::on_actionSeparador_triggered()
{
    showAbout();
}

