#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_rsapp.h"
#include <StudentsDll.h>

class RSApp: public QMainWindow {
    Q_OBJECT

public:
    RSApp(QWidget *parent = Q_NULLPTR);
    ~RSApp();

private:
    QVector<int> column;
    Students stu;
    Ui::RSAppClass ui;
    void sitDown();

private slots:
    void on_push_button_clicked();
};
