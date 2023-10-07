
#include <iostream>
#include "ReadWritable.h"

namespace sdds {

	bool ReadWritable::isCsv() const {
		return comma;
	}

	void ReadWritable::setCsv(const bool value) {
		this->comma = value;
	}

	ReadWritable::ReadWritable() {
		this->comma = false;
	};

	ReadWritable::~ReadWritable() {};

	std::ostream& operator << (std::ostream& out, ReadWritable& rw) {
		return rw.write(out);
	}

	std::istream& operator >> (std::istream& in, ReadWritable& rw) {
		return rw.read(in);
	}
}