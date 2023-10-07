#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__

#include "Vehicle.h"

namespace sdds {

    class Car : public Vehicle {

        bool carwash;
        bool isEmpty() const;
        void setEmpty();
        void deallocate();

    public:

        Car();
        Car(const char license_plate[], const char make_model[]);
        Car(const Car &car);
        ~Car();

        Car &operator = (const Car &car);

        std::istream& read(std::istream& istr = std::cin);
        std::ostream& write(std::ostream& out = std::cout) const;
        virtual std::ostream& writeType(std::ostream& out = std::cout) const;

    };
}

#endif