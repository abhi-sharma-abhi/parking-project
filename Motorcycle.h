#ifndef SDDS_MOTORCYCLE_H__
#define SDDS_MOTORCYCLE_H__

#include "Vehicle.h"

namespace sdds {

    class Motorcycle : public Vehicle {

        bool hasSideCar;
        void setEmpty();
        void deallocate();

    public:
        Motorcycle();
        Motorcycle(const char license_plate[], const char make_model[]);
        Motorcycle(const Motorcycle &mc);
        ~Motorcycle();

        Motorcycle &operator=(const Motorcycle &mc);

        std::istream &read(std::istream &istr = std::cin);
        std::ostream &write(std::ostream &out = std::cout) const;
        virtual std::ostream &writeType(std::ostream &out = std::cout) const;

    };
}

#endif