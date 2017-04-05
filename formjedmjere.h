#ifndef FORMJEDMJERE_H
#define FORMJEDMJERE_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
//#include <QStringListModel>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QVariant>
#include <QTreeView>

//#include "../formartikli/formartikli.h"

namespace Ui {
class FormJedmjere;
}

class FormJedmjere : public QMainWindow
{
    Q_OBJECT

public:

     explicit FormJedmjere (QWidget *parent = 0);
     //FormArtikli *objmain2; // creating object for the second window

     ~FormJedmjere();

signals:
   void my_Signal_NazivJm (QStringList);
   void my_SignalJM (QString);

   //  private:
  //      QTextEdit m_text;

private slots:
    void on_actionIzlaz_triggered();

    void on_actionCitaj_triggered();

    void on_actionDodaj_triggered();

    void on_actionBrisi_triggered();

    void on_actionPromijeni_triggered();

    void on_actionPrvi_slog_triggered();

    void on_actionZadnji_slog_triggered();

    void on_actionPrethodni_slog_triggered();

    void on_actionSlijedeci_slog_triggered();

    void Text_toForm(QString ListaForm); //prenosi ime forme

    void on_pushButtonList_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_Opis_returnPressed();

    void pregled_Naz ();

    void pregled_Sif ();

    void pregled_Nazdio ();

    void on_tabWidget_tabBarClicked(int index);

    void on_treeViewJM_doubleClicked(const QModelIndex &index);

    void on_treeViewJM_clicked(const QModelIndex &index);

    void on_lineEditSkroz_selectionChanged();

private:
    Ui::FormJedmjere *ui;
    QString LX;
    QTreeView *treeView;
    QStandardItemModel *standardModel;
    QStandardItem *items;
    QStandardItem *item1;
};

#endif // MAINWINDOW_H
