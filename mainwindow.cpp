#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Slownik.h"
#include<list>
#include<QFileDialog>
#include<QMessageBox>
#include<QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),pierwsze_wywolanie(false)
{
   ui->setupUi(this);

   sched = new Scheduler;
   bool poprawnosc=true;
   poprawnosc = sched->DodajSlownik("C:\\Users\\Matt\\Documents\\Slowka\\Slowka.txt");
   while (poprawnosc==false)
   {
      int war =  QMessageBox::warning(this,"Program slówka","Nie udało się wczytać pliku z danymi.\n\
      Wczytaj swój plik!",QMessageBox::Ok);


       if(war == QMessageBox::Ok)
        {
       QString filename = QFileDialog::getOpenFileName( this,"Wczytaj własny słownik",
                                                        "C://",
                                                        "All files (*.*);;Text file(*.txt)"
                                                        );
        poprawnosc = sched->DodajSlownik(filename.toStdString());
        }
      }


   ui->horizontalSlider_Ilosc_Slow->setMaximum(sched->DajIlosc());
   ui->spin_Ilosc_Slow->setMaximum(sched->DajIlosc());
   ui->page_log->setVisible(true);
   ui->page_data->setVisible(false);
   ui->page_end->setVisible(false);
   ui->Podsumuj->setVisible(false);
   QObject::connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(on_NoweSlowko_clicked()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() //rozpocznij naukę
{
    sched->Rozpocznij(ui->spin_Ilosc_Slow->value(),
                      ui->spin_Ilosc_Poziom->value());
    sched->LosujSlowka();
    ui->page_log->setVisible(false);
    ui->page_data->setVisible(true);

}
void MainWindow::on_NoweSlowko_clicked()
{

    if(pierwsze_wywolanie==true)
    {
       QString pozostalo = QString::fromStdString(sched->Dodaj_do_powtorki());
       ui->lcdNumber_3->display(pozostalo);
       sched->Zdejmij_Ze_Stosu();
    }

    QString pozostalo = QString::fromStdString(sched->Pozostalych_Slowek());
    ui->lcdNumber_2->display(pozostalo);

    if (sched->Zawartosc_listy()==false)
    {
    QString pl_sl=QString::fromStdString(sched->Slowko_PL());
    ui->Pl_Slowko->setText(pl_sl);
    QString ang_sl=QString::fromStdString(sched->Slowko_ANG());
    ui->sl_ang->setText(ang_sl);
    QString punkty=QString::fromStdString(sched->DajPunkty());
    ui->ilepunktow->setText(punkty);
    QString suma=QString::fromStdString(sched->DajSume());
    ui->Suma->setText(suma);
    ui->Odpowiedz->clear();
    pierwsze_wywolanie=true;
    }
    else
    {
        ui->Pl_Slowko->setText("Koniec listy słówek");
        on_Dobierz_literke_clicked();
        ui->ZatwierdzSlowo->setVisible(false);
        ui->Dobierz_literke->setVisible(false);
        ui->NoweSlowko->setVisible(false);
        ui->sl_ang->setVisible(false);
        ui->Odpowiedz->setVisible(false);
        ui->Podsumuj->setVisible(true);
    }
}

void MainWindow::on_Dobierz_literke_clicked()
{
    QString napis = ui->sl_ang->text();
    string po_dobraniu=sched->DajLitere(napis.toStdString());
    QString wyjscie = QString::fromStdString(po_dobraniu);
    QString punkty=QString::fromStdString(sched->DajPunkty());
    QString suma=QString::fromStdString(sched->DajSume());

    if (wyjscie=="Koniec")
    {
        sched->DodajPunkty(false);
        on_NoweSlowko_clicked();
    }
    else
    {
    ui->Suma->setText(suma);
    ui->ilepunktow->setText(punkty);
    ui->sl_ang->setText(wyjscie);
    }

}

void MainWindow::on_ZatwierdzSlowo_clicked()
{
    QString temp = ui->Odpowiedz->toPlainText();
    string odp = temp.toStdString();
    sched->DodajPunkty(sched->SprawdzPoprawnosc(odp));
    on_NoweSlowko_clicked();
}

void MainWindow::on_Podsumuj_clicked()
{
    ui->page_data->setVisible(false);
    ui->page_end->setVisible(true);
    QString suma = QString::fromStdString(sched->DajSume());
    ui->lcdNumber->display(suma);
    ui->lcdNumber_3->display(0);
}

void MainWindow::on_pushButton_2_clicked()   //Przycisk jeszcze raz
{
    sched->Jeszcze_raz();
    ui->page_log->setVisible(true);
    ui->page_data->setVisible(false);
    ui->page_end->setVisible(false);

    ui->ZatwierdzSlowo->setVisible(true);
    ui->Dobierz_literke->setVisible(true);
    ui->NoweSlowko->setVisible(true);
    ui->sl_ang->setVisible(true);
    ui->Odpowiedz->setVisible(true);
    ui->Podsumuj->setVisible(false);

    pierwsze_wywolanie=false;
}

void MainWindow::on_pushButton_3_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionWczytaj_s_ownik_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Wczytaj własny słownik"),
                "C://",
                "All files (*.*);;Text file(*.txt)"
                );

    bool poprawnosc=true;
    sched->UsunSlownik();

    poprawnosc = sched->DodajSlownik(filename.toStdString());
    if (poprawnosc==false)
    {
       int war =  QMessageBox::warning(this,"Program slówka","Nie udało się wczytać pliku z danymi.\n\
       Program kończy działanie",QMessageBox::Ok);
       QCoreApplication::quit();
     }
    pierwsze_wywolanie=false;
    ui->horizontalSlider_Ilosc_Slow->setMaximum(sched->DajIlosc());
    ui->spin_Ilosc_Slow->setMaximum(sched->DajIlosc());
    ui->page_log->setVisible(true);
    ui->page_data->setVisible(false);
    ui->page_end->setVisible(false);
    ui->Podsumuj->setVisible(false);


}


void MainWindow::on_actionO_Qt_2_triggered()
{
    QMessageBox::aboutQt(this,"O Qt");
}
