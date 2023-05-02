#include "rsapp.h"
#include <studentsdll.h>

#include <QDebug>
#include <QGridLayout>
#include <QFont>
#include <QLabel>

RSApp::RSApp(QWidget* parent): QMainWindow(parent) {
    ui.setupUi(this);
    sitDown();
}

void RSApp::sitDown() {
    QVector<QString> students = stu.getStudents();
    QGridLayout* body = ui.gridLayout;
    if(body->count() != 0) {
        QLayoutItem *child;
        while(child = body->takeAt(0)) {
            body->removeWidget(child->widget());
            child->widget()->setParent(0);
            delete child;
        }
    }
    int i = 0;
    QFont font = ui.pushButton->font();
    font.setPointSize(25);
    for(QString student : students) {
        QLabel *label = new QLabel(student, this);
        label->setFont(font);
        body->addWidget(label, i / 8, i % 8, Qt::AlignCenter);
        label->show();
        i++;
    }
}

void RSApp::on_push_button_clicked() {
    stu.refresh();
    sitDown();
}

RSApp::~RSApp() {}
