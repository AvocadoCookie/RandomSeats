#include "rsapp.h"
#include <studentsdll.h>

#include <QDebug>
#include <QGridLayout>
#include <QFont>
#include <QLabel>

RSApp::RSApp(QWidget* parent): QMainWindow(parent) {
    ui.setupUi(this);
    setWindowState(Qt::WindowMaximized);

    QFile layout;
    layout.setFileName("layout.txt");
    layout.open(QFile::ReadOnly | QFile::Text);
    QTextStream reader(&layout);
    QString line;
    while(reader.readLineInto(&line)) {
        column.append(line.toInt());
    }
    layout.close();

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

    int columns = 0;
    QFont font = ui.pushButton->font();
    font.setPointSize(25);

    for(int i = 0; i < column.size() - 1; i++) {
        columns += column[i];
        QLabel *label = new QLabel(" ", this);
        label->setFont(font);
        body->addWidget(label, 0, columns + i, Qt::AlignCenter);
        label->show();
    }
    columns += column.last();

    for(int i = 0; i < students.size();) {
        for(int j = 0; j < column.size(); j++) {
            int c = column[j];
            while(c > 0 && i < students.size()) {
                QLabel *label = new QLabel(students[i], this);
                label->setFont(font);
                body->addWidget(label, i / columns, i % columns + j, Qt::AlignCenter);
                label->show();
                i++, c--;
            }
        }
    }
}

void RSApp::on_push_button_clicked() {
    stu.refresh(std::accumulate(column.begin(), column.end(), 0));
    sitDown();
}

RSApp::~RSApp() {}
