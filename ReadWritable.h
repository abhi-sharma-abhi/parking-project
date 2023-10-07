
#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__
#include <iostream>
namespace sdds {
	class ReadWritable {
	protected:
		bool comma;
	public:
		ReadWritable();
		virtual ~ReadWritable();

		bool isCsv() const;
		void setCsv(const bool value);
		virtual std::istream& read(std::istream& in=std::cin)=0;
		virtual std::ostream& write(std::ostream& out=std::cout) const=0;

		friend std::ostream& operator << (std::ostream& out, ReadWritable& rw);
		friend std::istream& operator >> (std::istream& in, ReadWritable& rw);
	};
}
#endif