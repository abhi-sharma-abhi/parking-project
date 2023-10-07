
#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__

#include "ReadWritable.h"

namespace sdds {
    class Vehicle : public ReadWritable {
        char* license_plate;
        char* model_make;
        int parking_spot_number;

        bool isInvalid(const char str[]) const;

        protected:

        void deallocate();
        void setEmpty();
        void setMakeModel(const char make_model[]);
        void setLicensePlate(const char plate[]);
        
        public:

        bool isEmpty() const;
        Vehicle();
        Vehicle(const char plate[], const char make_model[]);
        Vehicle(const Vehicle& v2);
        ~Vehicle();

        int getParkingSpot() const;
        void setParkingSpot(const int spot);
        const char* getLicensePlate() const;
        const char* getMakeModel() const;


        Vehicle& operator = (const Vehicle& v2);
        bool operator == (const char plate[]) const;
        bool operator == (const Vehicle& v2) const;


        std::istream& read(std::istream& istr = std::cin);
        std::ostream& write(std::ostream& out = std::cout) const;

        virtual std::ostream& writeType(std::ostream& out = std::cout) const =0;
    };
}
#endif