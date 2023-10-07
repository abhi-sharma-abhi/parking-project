#include "Car.h"

namespace sdds {

    bool Car::isEmpty() const {
        return Vehicle::isEmpty();
    }

    void Car::setEmpty() {
        Vehicle::setEmpty();
        carwash = false;
    }

    void Car::deallocate() {
        Vehicle::deallocate();
        setEmpty();
    }

    Car::Car() {
        setEmpty();
    }

    Car::Car(const char license_plate[], const char make_model[]) {
        setEmpty();
        setLicensePlate(license_plate);
        setMakeModel(make_model);
    }

    Car::Car(const Car& car) : Vehicle(car) {
        // setEmpty();
        this->carwash = car.carwash;
    }

    Car::~Car() {
        deallocate();
    }

    Car& Car::operator = (const Car& car) {
        deallocate();
        if (car.isEmpty())
            return *this;
        
        Vehicle::operator=(car);
        this->carwash = car.carwash;
        return *this;
    }

    std::ostream& Car::writeType(std::ostream& out) const {
        if (isCsv()) {
            out << "C,";
        } else {
            out << "Vehicle type: Car\n";
        }
        return out;
    }

    std::ostream& Car::write(std::ostream& out) const {

        if (isEmpty()) {
            out << "Invalid Car Object\n";
        } else {
            Vehicle::write(out);
            if (isCsv())
                out << carwash;
            else {
                if (carwash) out << "With Carwash\n";
                else out << "Without Carwash\n";
            }
        }
        return out;
    }

    std::istream& Car::read(std::istream& istr) {
        if (isCsv()) {
            Vehicle::read(istr);
            istr >> carwash;
            istr.ignore(1000, '\n');
        } else {
            std::cout << "Car information entry\n";
            Vehicle::read(istr);

            char in;
            std::cout << "Carwash while parked? (Y)es/(N)o: ";
            std::cin >> in;
            while (in != 'Y' && in != 'N' && in != 'y' && in != 'n') {
                std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                // std::cin.ignore();
                std::cin >> in;
            }
            carwash = (in == 'Y' || in == 'y') ? true : false;
            // std::cin.ignore(1000, '\n');
        }
        return istr;
    }
}