#include "formjedmjere.h"
#include "ui_formjedmjere.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTimer>

  FormJedmjere::FormJedmjere(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormJedmjere)
{
      ui->setupUi(this);

    this->resize(600, 500);
    setWindowTitle(tr("Unos i pregled jedinica mjere"));

    //centriranje forme na ekranu
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width()*0.5, center.y()-height()*0.5);

    //postavlja kursor na prvo polje u formi
    QTimer::singleShot(0, ui->lineEdit_Opis, SLOT(setFocus()));
    ui->mainToolBar->setDisabled(true);
    ui->tabWidget->setCurrentIndex(0);

    //deklaracija linije za ListView

    pregled_Naz();
  }

FormJedmjere::~FormJedmjere()
{
    delete ui;

}


void FormJedmjere::on_actionIzlaz_triggered()
{

     close();// exit(true);
}

//ime forme
void FormJedmjere::Text_toForm(QString ListaForm)
{
    LX = ListaForm;
   //qDebug()<<LX;
}


void FormJedmjere::on_actionCitaj_triggered()
{
    QSqlQuery upit;
    upit.exec
      ("SELECT idJedMjere, OpisJM, Kratoznaka FROM jedmjere WHERE idJedMjere='"+ui->id_brojsB->text()+"' ");

     upit.next();

    ui->lineEditNaziv->setText(upit.value(1).toString());
    ui->lineEditSkroz->setText(upit.value(2).toString());
    }



void FormJedmjere::on_actionDodaj_triggered()
{
    QSqlQuery upit;
    upit.prepare("INSERT INTO jedmjere (idJedMjere, OpisJM, Kratoznaka) VALUES (NULL, :OpisJM, :Kratoznaka)");

    upit.bindValue(":OpisJM", ui->lineEditNaziv->text());
    upit.bindValue(":Kratoznaka", ui->lineEditSkroz->text());

    if(!upit.exec())
    {
        QMessageBox::warning(this,"Greška", "Podaci nisu upisani.\n"+ upit.lastError().text());
    }
    else
       {
        QMessageBox::information(this,"Poruka", "Podaci su upisani.");

        upit.exec("SELECT LAST_INSERT_ID() FROM jedmjere");
        upit.next();
        const int lastid = upit.value(0).toInt();
        ui->id_brojsB->setValue(lastid);

        return;
        }
}


void FormJedmjere::on_actionBrisi_triggered()
{
    bool ret = false;
    QSqlQuery upit;
    ret = upit.exec("DELETE FROM jedmjere WHERE idJedMjere='"+ui->id_brojsB->text()+"' ");

    if(!ret)
    {
        QMessageBox::warning(this,"Greška", "Podaci nisu izbrisani.\n"+ upit.lastError().text());

    }
    else
    {
        QMessageBox::information(this,"Poruka", "Podaci su izbrisani.");

     }
}

void FormJedmjere::on_actionPromijeni_triggered()
{
    QSqlQuery upit;

    upit.prepare("UPDATE jedmjere SET OpisJM=:opisjm, Kratoznaka=:koznaka"
                " WHERE idJedMjere='"+ui->id_brojsB->text()+"'");

    upit.bindValue(":opisjm", ui->lineEditNaziv->text());
    upit.bindValue(":koznaka", ui->lineEditSkroz->text());

    QMessageBox::information(this,"", ui->id_brojsB->text());
    //this->close();
    if (upit.exec())
    {
     QMessageBox::information(this,"Poruka", "Podaci su izmijenjeni.");
    }
    else
    {
    QMessageBox::information(this,"Greška", "Podaci NISU izmijenjeni.\n"+ upit.lastError().text());
    }

    //this->close();
}

void FormJedmjere::on_actionPrvi_slog_triggered()
{
    QSqlQuery upit;
    upit.exec
      ("SELECT idJedMjere, OpisJM, Kratoznaka FROM jedmjere WHERE idJedMjere > 0 ");

     if(upit.first()){

    ui->id_brojsB->setValue(upit.value(0).toInt());
    ui->lineEditNaziv->setText(upit.value(1).toString());
    ui->lineEditSkroz->setText(upit.value(2).toString());
    }
}

void FormJedmjere::on_actionZadnji_slog_triggered()
{
    QSqlQuery upit;
    upit.exec
      ("SELECT idJedMjere, OpisJM, Kratoznaka FROM jedmjere WHERE idJedMjere > 0 ");

    if(upit.last()){

    ui->id_brojsB->setValue(upit.value(0).toInt());
    ui->lineEditNaziv->setText(upit.value(1).toString());
    ui->lineEditSkroz->setText(upit.value(2).toString());
    }
}


void FormJedmjere::on_actionPrethodni_slog_triggered()
{
    QSqlQuery upit;
    upit.exec
      ("SELECT idJedMjere, OpisJM, Kratoznaka FROM jedmjere WHERE idJedMjere<'"+ui->id_brojsB->text()+"' "
       "ORDER by idJedMjere DESC");

     upit.next();

    ui->id_brojsB->setValue(upit.value(0).toInt());
    ui->lineEditNaziv->setText(upit.value(1).toString());
    ui->lineEditSkroz->setText(upit.value(2).toString());
}


void FormJedmjere::on_actionSlijedeci_slog_triggered()
{
    QSqlQuery upit;
    upit.exec
      ("SELECT idJedMjere, OpisJM, Kratoznaka FROM jedmjere WHERE idJedMjere>'"+ui->id_brojsB->text()+"' ");

    upit.next();

    ui->id_brojsB->setValue(upit.value(0).toInt());
    ui->lineEditNaziv->setText(upit.value(1).toString());
    ui->lineEditSkroz->setText(upit.value(2).toString());
}

void FormJedmjere::on_pushButtonList_clicked()
{

    switch (ui->comboBox->currentIndex())
    {
    case 0:{

            pregled_Naz();
            break;}

    case 1:{

             pregled_Sif();
             break;}

      case 2:{
             pregled_Nazdio();
        //break;

              }
    }//end switch
}

void FormJedmjere::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:{ ui->label_4->setText("Unesi Naziv jedinice mjere");
             ui->lineEdit_Opis->setText("A"); break;   }
    case 1:{ ui->label_4->setText("Unesi šifru jedinice mjere");
             ui->lineEdit_Opis->setText("1"); break;}
    case 2:{ ui->label_4->setText("Unesi DIO naziva za treženje");
             ui->lineEdit_Opis->setText("A");   }
}}//end switch

void FormJedmjere::on_lineEdit_Opis_returnPressed()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:{

            pregled_Naz();
            break;}

    case 1:{

             pregled_Sif();
             break;}

      case 2:{

              pregled_Nazdio();
        //break;}

              }
    }//end switch
}
//lista po nazivu
void FormJedmjere::pregled_Naz()
{
     QStandardItemModel *model = new QStandardItemModel();
     QSqlQuery upit;
     upit.exec
      ("SELECT LPAD(idJedMjere, 4, '0'), CONCAT(OpisJM, '/', Kratoznaka) FROM jedmjere"
       " WHERE OpisJM>='"+ui->lineEdit_Opis->text()+"' order by OpisJM");

     while (upit.next())
     {
         QList<QStandardItem *> testQList;
         QStandardItem *item = new QStandardItem(upit.value(0).toString());
         testQList.append(item);
         item->setEditable(false);
         QStandardItem *item1 = new QStandardItem(upit.value(1).toString());
         testQList.append(item1);
         item1->setEditable(false);
         model->appendRow(testQList);

      }
     QStringList List;
     List <<"Šifra JM"<<"  Naziv jedinice mjere";
     model->setHorizontalHeaderLabels(QStringList(List));
     ui->treeViewJM->setModel(model);
     ui->treeViewJM->setColumnWidth(0, 80);
  }

// lista po sifri
void FormJedmjere::pregled_Sif()
{
// Get the position
    QStandardItemModel *model = new QStandardItemModel();
    QSqlQuery upit;

    upit.exec
    ("SELECT LPAD(idJedMjere, 4, '0'), CONCAT(OpisJM, '/', Kratoznaka) FROM jedmjere"
             " WHERE idJedMjere>='"+ui->lineEdit_Opis->text()+"' ");

    while (upit.next())
    {
        QList<QStandardItem *> testQList;
        QStandardItem *item = new QStandardItem(upit.value(0).toString());
        testQList.append(item);
        item->setEditable(false);
        QStandardItem *item1 = new QStandardItem(upit.value(1).toString());
        testQList.append(item1);
        item1->setEditable(false);
        model->appendRow(testQList);

     }
    QStringList List;
    List <<"Šifra JM"<<"  Naziv jedinice mjere";
    model->setHorizontalHeaderLabels(QStringList(List));
    ui->treeViewJM->setModel(model);
    ui->treeViewJM->setColumnWidth(0, 80);
 }
//lista po dijelu naziva
void FormJedmjere::pregled_Nazdio()
{
        QString red1;
        red1="%"+ui->lineEdit_Opis->text()+"%";

        QStandardItemModel *model = new QStandardItemModel();
        QSqlQuery upit;

        upit.exec
        ("SELECT LPAD(idJedMjere, 4, '0'), CONCAT(OpisJM, '/', Kratoznaka) FROM jedmjere"
                " WHERE OpisJM LIKE '"+red1+"'");
        while (upit.next())
        {
            QList<QStandardItem *> testQList;
            QStandardItem *item = new QStandardItem(upit.value(0).toString());
            testQList.append(item);
            item->setEditable(false);
            QStandardItem *item1 = new QStandardItem(upit.value(1).toString());
            testQList.append(item1);
            item1->setEditable(false);
            model->appendRow(testQList);

         }
        QStringList List;
        List <<"Šifra JM"<<"  Naziv jedinice mjere";
        model->setHorizontalHeaderLabels(QStringList(List));
        ui->treeViewJM->setModel(model);
        ui->treeViewJM->setColumnWidth(0, 80);
     }

void FormJedmjere::on_tabWidget_tabBarClicked(int index)
{
    int i = index;
    if(i==1) { ui->mainToolBar->setEnabled(true);}
    else {ui->mainToolBar->setDisabled(true);}
}

void FormJedmjere::on_treeViewJM_doubleClicked(const QModelIndex &index)
{
    QStringList slist;

    QAbstractItemModel* mod1=(QAbstractItemModel*)index.model();
    for(int columnIndex = 0; columnIndex < mod1->columnCount(); columnIndex++)
    {
        QModelIndex x=mod1->index(index.row(),columnIndex);

        QString s= x.data().toString();
        slist +=s;

       // QMessageBox::about(this,s,s);
    }

    qDebug()<<slist;
   if (LX =="formartikli")
   {
    emit my_Signal_NazivJm(slist);
    close();
   }// exit(true);

}

void FormJedmjere::on_treeViewJM_clicked(const QModelIndex &index)
{
    QAbstractItemModel* mod1=(QAbstractItemModel*)index.model();
    QModelIndex x=mod1->index(index.row(),0);
    ui->id_brojsB->setValue(x.data().toInt());
}

void FormJedmjere::on_lineEditSkroz_selectionChanged()
{

}
