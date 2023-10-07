
#include <iostream>
#include "Vehicle.h"
#include "Utils.h"

namespace sdds {

    // Constructors
    Vehicle::Vehicle() {
        setEmpty();
    }

    Vehicle::Vehicle(const char plate[], const char make_model[]) {
        setEmpty();
        if (isInvalid(plate) || isInvalid(make_model)) return;
        setLicensePlate(plate);
        setMakeModel(make_model);
        setParkingSpot(0);
    }

    // Copy object
    Vehicle::Vehicle(const Vehicle& v2) {
        setEmpty();
        if (v2.isEmpty()) return;

        setCsv( (v2.isCsv()) ? true : false);
        setLicensePlate(v2.getLicensePlate());
        setMakeModel(v2.getMakeModel());
        setParkingSpot(v2.getParkingSpot());
    }

    Vehicle& Vehicle::operator = (const Vehicle& v2) {
        deallocate();
        setEmpty();
        if (v2.isEmpty()) return *this;

        setCsv((v2.isCsv()) ? true : false);
        setLicensePlate(v2.getLicensePlate());
        setMakeModel(v2.getMakeModel());
        setParkingSpot(v2.getParkingSpot());
        return *this;
    }

    // Destructor
    Vehicle::~Vehicle() {
        deallocate();
    }

    void Vehicle::deallocate() {
        delete[] license_plate;
        delete[] model_make;
    }
    void Vehicle::setEmpty() {
        license_plate = nullptr;
        model_make = nullptr;
        parking_spot_number = 0;
    }

    bool Vehicle::isEmpty() const {
        if (isInvalid(license_plate) || isInvalid(model_make) || parking_spot_number < 0) return true;
        return false;
    }

    bool Vehicle::isInvalid(const char str[]) const {
        if (str == nullptr || strlen(str) == 0) return true;
        return false;
    }

    const char* Vehicle::getLicensePlate() const {
        return license_plate;
    }

    void Vehicle::setLicensePlate(const char plate[]) {
        int len = strlen(plate);
        if (isInvalid(plate) || len < 1 || len > 8) {
            deallocate();
            setEmpty();
            return;
        }
        if (license_plate != nullptr) delete[] license_plate;
        license_plate = strcpy(plate);
        toUpper(license_plate);
    }
    
    const char* Vehicle::getMakeModel() const {
        return model_make;
    }

    void Vehicle::setMakeModel(const char make_model[]) {
        int len = strlen(make_model);
        if (isInvalid(make_model) || len < 2 || len > 60) {
            deallocate();
            setEmpty();
            return;
        }
        if (model_make != nullptr) delete[] model_make;
        model_make = strcpy(make_model);
    }

    // public functions

    int Vehicle::getParkingSpot() const {
        return parking_spot_number;
    }

    void Vehicle::setParkingSpot(const int spot) {
        parking_spot_number = spot;
    }

    bool Vehicle::operator == (const char plate[]) const {
        char* tmp = strcpy(plate);
        toUpper(tmp);
        bool ans = strcmp(license_plate, tmp);
        delete[] tmp;
        return ans;
    }
    bool Vehicle::operator == (const Vehicle& v2) const {
        return *this == v2.license_plate;
    }

    std::istream& Vehicle::read(std::istream& istr) {

        deallocate();
        setEmpty();
        if (comma) {
            char delim = ',';
            istr >> parking_spot_number;
            istr.ignore(1000, delim);

            license_plate = new char[9];
            license_plate[8] = '\0';
            istr.getline(license_plate, 8, delim);
            toUpper(license_plate);

            model_make = new char[61];
            model_make[60] = '\0';
            istr.getline(model_make, 60, delim);
            if (istr.fail()) {
                setEmpty();
            }

        } else {

            std::cout << "Enter License Plate Number: ";
            char* plate = new char[10];
            std::cin >> plate;
            while (strlen(plate) > 8 || strlen(plate) < 1 || isInvalid(plate)) {
                std::cout << "Invalid License Plate, try again: ";
                std::cin >> plate;
            }
            setLicensePlate(plate);
            delete[] plate;

            std::cout << "Enter Make and Model: ";
            char* make = new char[60];
            // std::cin >> make;
            std::cin.ignore();
            std::cin.getline(make, 60);
            while (strlen(make) > 60 || strlen(make) < 2 || isInvalid(make))
            {
                std::cout << "Invalid Make and model, try again: ";
                std::cin.getline(make, 60);
                // std::cin >> make;
            }
            setMakeModel(make);
            delete[] make;

            if (std::cin.fail()) {
                deallocate();
                setEmpty();
            }
        }
        return istr;
    }

    std::ostream& Vehicle::write(std::ostream& out) const {
        if (isEmpty()) {
            return out;
        } else {
            writeType(out);
        }

        if (comma) {
            out << parking_spot_number << "," <<
                    license_plate << "," <<
                    model_make << ",";
        } else {
            out << "Parking Spot Number: ";
            if (parking_spot_number == 0) out << "N/A";
            else out << parking_spot_number;
            out << '\n';
            out << "License Plate: " << license_plate << '\n';
            out << "Make and Model: " << model_make << '\n';
        }
        return out;

    }

}

