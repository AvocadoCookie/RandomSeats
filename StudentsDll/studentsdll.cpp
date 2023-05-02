#include "studentsdll.h"
#include <algorithm>
#include <cstdio>

#include <QTextStream>
#include <QRandomGenerator>

Students::Students(QString fileName) {
	list.setFileName(fileName);
	list.open(QFile::ReadOnly | QFile::Text);
	QTextStream reader(&list);
	QString line;
	while(reader.readLineInto(&line)) {
		students.append(line);
	}
	list.close();
}

Students::~Students() {
	list.open(QFile::WriteOnly | QFile::Text);
	QTextStream writer(&list);
	for(QString str : students) {
		writer << str << endl;
	}
	list.close();
}

void Students::refresh() {
	const int size = students.size();
	QVector<Seat> seats(size);
	QVector<QString> newStudents(size);
	for(int i = 0; i < size; i++) {
		seats[i] = Seat(i / 8, i % 8);
	}
	if(size % 2) {
		arrange(seats, newStudents, size / 2);
	}
	for(int i = size / 2 - 1; i >= 0; i--) {
		arrange(seats, newStudents, i);
		arrange(seats, newStudents, size - i - 1);
	}
	students = newStudents;
}

void Students::arrange(QVector<Seat> &seats, QVector<QString> &newStudents, const int index) {
	if(seats.size() > 1) {
		int rankTot = 0;
		for(QVector<Seat>::Iterator i = seats.begin(); i != seats.end(); i++) {
			i->setRank(index / 8, index % 8);
			rankTot += i->getRank();
		}
		std::sort(seats.begin(), seats.end());
		int random = QRandomGenerator::global()->bounded(1, rankTot);
		for(QVector<Seat>::Iterator i = seats.begin(); i != seats.end(); i++) {
			if(random <= i->getRank()) {
				newStudents[i->getRow() * 8 + i->getColumn()] = students[index];
				seats.erase(i);
				break;
			} else {
				random -= i->getRank();
			}
		}
	} else {
		newStudents[seats[0].getRow() * 8 + seats[0].getColumn()] = students[index];
	}
}

inline QVector<QString> Students::getStudents() {
	return students;
}
