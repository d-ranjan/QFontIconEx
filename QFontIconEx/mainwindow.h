/**
** 2021: Year
** 11: Month
** 28: Day of the month
** 28/11/2021: Date
** dranjan: Username
** mainwindow.h: File name
** MainWindow: Class name (if applicable)
** : Contents of environment variable VARIABLE.
**/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qfonticon.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onFontsChaged(int index);
    void loadFontCheetSheet(const QString& qsFontIconPath);
    void initTable();

private:
    Ui::MainWindow* ui;
    QMap<QString, int> m_qmCheetSheet;
};

#endif // MAINWINDOW_H
