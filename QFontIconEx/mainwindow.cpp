/**
** 2021: Year
** 11: Month
** 28: Day of the month
** 28/11/2021: Date
** dranjan: Username
** mainwindow.cpp: File name
** MainWindow: Class name (if applicable)
** : Contents of environment variable VARIABLE.
**/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbVersion->setCurrentIndex(2);
    ui->cbType->setCurrentIndex(1);
    QFontIcon::addFont(":/fa-6-solid.ttf");
    loadFontCheetSheet(":/cheetsheet-fa-6-solid.xml");
    initTable();
    connect(ui->cbVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(onFontsChaged(int)));
    connect(ui->cbType, SIGNAL(currentIndexChanged(int)), this, SLOT(onFontsChaged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFontCheetSheet(const QString& qsFontIconPath)
{
    QFile file(qsFontIconPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error in instructions.xml: " << file.errorString();
        return;
    }

    QXmlStreamReader qxmlReader(&file);

    while (!qxmlReader.atEnd() && !qxmlReader.hasError()) {
        if (qxmlReader.readNext() == QXmlStreamReader::StartElement) {
            if (qxmlReader.name() == "icon") {
                auto attributes = qxmlReader.attributes();
                QString qsName = attributes.value("name").toString();
                int nCode = attributes.value("code").toInt(0, 16);
                m_qmCheetSheet.insert(qsName, nCode);
            }
        }
    }
    if (qxmlReader.hasError())
        qDebug() << "Error in instructions.xml: " << qxmlReader.errorString() << qxmlReader.lineNumber();
    file.close();
}

void MainWindow::initTable()
{
    ui->twMain->setIconSize(QSize(32, 32));
    ui->twMain->verticalHeader()->setVisible(true);
    int i = 0;
    QMapIterator<QString, int> itr(m_qmCheetSheet);
    while (itr.hasNext()) {
        itr.next();
        int row = i / 5;
        int col = i % 5;
        if (col == 0) {
            ui->twMain->insertRow(row);
        }
        QTableWidgetItem* twiFontIcon = new QTableWidgetItem(itr.key());
        twiFontIcon->setTextAlignment(Qt::AlignCenter);
        twiFontIcon->setIcon(QFontIcon::icon(itr.value()));
        ui->twMain->setItem(row, col, twiFontIcon);
        i++;
    }
}

void MainWindow::onFontsChaged(int index)
{
    while (ui->twMain->rowCount() != 0) {
        ui->twMain->removeRow(0);
    }
    m_qmCheetSheet.clear();
    int ver = ui->cbVersion->currentIndex() + 4;
    if (ver == 0) {
        ui->cbType->setEnabled(false);
        ui->lbType->setEnabled(false);
        QFontIcon::addFont(":/fa-4.ttf");
        loadFontCheetSheet(":/cheetsheet-fa-4.xml");
    } else {
        ui->cbType->setEnabled(true);
        ui->lbType->setEnabled(true);
        QString qsType = ui->cbType->currentIndex() == 0 ? "regular" : "solid";
        QFontIcon::addFont(QString(":/fa-%1-%2.ttf").arg(ver).arg(qsType));
        loadFontCheetSheet(QString(":/cheetsheet-fa-%1-%2.xml").arg(ver).arg(qsType));
    }
    initTable();
}
