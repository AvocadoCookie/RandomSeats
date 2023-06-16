#include "studentsdll.h"
#include <algorithm>
#include <cstdio>

#include <QTextStream>
#include <QRandomGenerator>

bool cmpSimilarity(QPair<QString, int> a, QPair<QString, int> b) {
	return a.second > b.second;
}

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

void Students::refresh(const int column) {
	const int size = students.size();
	QVector<Seat> seats(size);
	QVector<QString> newStudents(size);
	for(int i = 0; i < size; i++) {
		seats[i] = Seat(i / column, i % column);
	}
	if(size % 2) {
		arrange(seats, newStudents, size / 2, column);
	}
	for(int i = size / 2 - 1; i >= 0; i--) {
		arrange(seats, newStudents, i, column);
		arrange(seats, newStudents, size - i - 1, column);
	}
	similarity(students, newStudents, column);
	students = newStudents;
}


void Students::similarity(const QVector<QString> &s, QVector<QString> &_s, const int column) {
	int size = s.size();
	if(size < column) {
		return;
	}
	QVector<QPair<QString, int>> pairs(size);
	for(int i = 0; i < size; i++) {
		pairs[i] = QPair<QString, int>(_s[i], 0);
	}
	int L;
	do {
		L = 0;
		int length = 0;
		std::sort(pairs.begin(), pairs.end(), cmpSimilarity);
		while(length < size && pairs[length++].second);
		for(int i = 0; i < length / 3; i++) {
			int a = QRandomGenerator::global()->bounded(0, length - 1);
			int b = QRandomGenerator::global()->bounded(0, length - 1);
			std::swap(_s[_s.indexOf(pairs[a].first)], _s[_s.indexOf(pairs[b].first)]);
		}
		for(int i = 0; i < size; i++) {
			int index = s.indexOf(_s[i]), l = 0;
			int toCheck[] = {index - column - 1, index - column, index - column + 1, index - 1, index + 1, index + column - 1, index + column, index + column + 1};
			int _toCheck[] = {i - column - 1, i - column, i - column + 1, i - 1, i + 1, i + column - 1, i + column, i + column + 1};
			pairs[i].second = 0;
			for(int m : _toCheck) {
				for(int n : toCheck) {
					if(m >= 0 && m < size && n >= 0 && n < size && s[n] == _s[m]) {
						l++;
						break;
					}
				}
			}
			L += l;
			pairs[i] = QPair<QString, int>(_s[i], l);
		}
	} while(L >= 8);
}

void Students::arrange(QVector<Seat> &seats, QVector<QString> &newStudents, const int index, const int column) {
	if(seats.size() > 1) {
		int rankTot = 0;
		for(QVector<Seat>::Iterator i = seats.begin(); i != seats.end(); i++) {
			i->setRank(index / column, index % column);
			rankTot += i->getRank();
		}
		std::sort(seats.begin(), seats.end());
		int random = QRandomGenerator::global()->bounded(1, rankTot);
		for(QVector<Seat>::Iterator i = seats.begin(); i != seats.end(); i++) {
			if(random <= i->getRank()) {
				newStudents[i->getRow() * column + i->getColumn()] = students[index];
				seats.erase(i);
				break;
			} else {
				random -= i->getRank();
			}
		}
	} else {
		newStudents[seats[0].getRow() * column + seats[0].getColumn()] = students[index];
	}
}

inline QVector<QString> Students::getStudents() {
	return students;
}
