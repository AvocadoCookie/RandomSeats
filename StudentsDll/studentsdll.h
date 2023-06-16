#pragma once

#include "studentsdll_global.h"
#include "seat.h"

#include <QFile>
#include <QVector>

class STUDENTSDLL_EXPORT Students {
public:
    Students(QString fileName = "list.txt");
    ~Students();
    inline QVector<QString> getStudents();
    void refresh(const int);

private:
    void arrange(QVector<Seat> &, QVector<QString> &, const int, const int);
    void similarity(const QVector<QString> &, QVector<QString> &, const int);
    QVector<QString> students;
    QFile list;
};
