#include "Motorcycle.h"

namespace sdds {

    void Motorcycle::setEmpty() {
        hasSideCar = false;
        Vehicle::setEmpty();
    }

    void Motorcycle::deallocate() {
        Vehicle::deallocate();
        setEmpty();
    }

    Motorcycle::Motorcycle() {
        setEmpty();
    }

    Motorcycle::Motorcycle(const char license_plate[], const char make_model[]) {
        setEmpty();
        setLicensePlate(license_plate);
        setMakeModel(make_model);
    }

    Motorcycle::Motorcycle(const Motorcycle& mc) : Vehicle(mc) {
        // setEmpty();
        hasSideCar = mc.hasSideCar;
    }

    Motorcycle::~Motorcycle() {
        deallocate();
    }

    Motorcycle& Motorcycle::operator = (const Motorcycle& mc) {
        deallocate();
        Vehicle::operator=(mc);
        this->hasSideCar = mc.hasSideCar;
        return *this;
    }

    std::ostream& Motorcycle::writeType(std::ostream &out) const {
        if (isCsv()) {
            out << "M,";
        } else {
            out << "Vehicle type: Motorcycle\n";
        }
        return out;
    }

    std::ostream& Motorcycle::write(std::ostream &out) const {
        
        if (isEmpty()) {
            out << "Invalid Motorcycle Object\n";
        } else {
            Vehicle::write(out);
            if (isCsv()) {
                out << hasSideCar;
            } else if (hasSideCar) {
                out << "With Sidecar\n";
            }
        }
        return out;
    }

    std::istream& Motorcycle::read(std::istream &istr) {
        if (isCsv()) {
            Vehicle::read(istr);
            istr >> hasSideCar;
            istr.ignore(1000, '\n');
        } else {
            std::cout << "Motorcycle information entry\n";
            Vehicle::read(istr);

            char in;
            std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            std::cin >> in;
            while (in != 'Y' && in != 'N' && in != 'y' && in != 'n') {
                std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                // std::cin.ignore();
                std::cin >> in;
            }
            hasSideCar = (in == 'Y' || in == 'y') ? true : false;
            // std::cin.ignore(1000, '\n');
        }
        return istr;
    }
}