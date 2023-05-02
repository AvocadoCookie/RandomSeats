#include "seat.h"
#include <QtGlobal>

Seat::Seat() {
	row = column = rank = 0;
}

Seat::Seat(int row, int column) {
	this->row = row;
	this->column = column;
	this->rank = 0;
}

Seat::Seat(const Seat &other) {
	printf("a: %d %d %d", other.row, other.column, other.rank);
	row = other.row;
	column = other.column;
	rank = other.rank;
}

Seat::~Seat() {}

inline void Seat::setRank(int toRow, int toColumn) {
	rank = qAbs(row - toRow) + qAbs(column - toColumn);
}

inline int Seat::getRank() {
	return rank;
}

inline int Seat::getRow() {
	return row;
}

inline int Seat::getColumn() {
	return column;
}
