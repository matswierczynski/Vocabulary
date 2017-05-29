#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include<Scheduler.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void level_words(int il_slow);
    ~MainWindow();


private:
    Scheduler *sched;
    Ui::MainWindow *ui;
    bool pierwsze_wywolanie;


private slots:
    void on_NoweSlowko_clicked();


    void on_pushButton_clicked();
    void on_Dobierz_literke_clicked();
    void on_ZatwierdzSlowo_clicked();
    void on_Podsumuj_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_actionWczytaj_s_ownik_triggered();
    void on_actionO_Qt_2_triggered();
};

#endif // MAINWINDOW_H
