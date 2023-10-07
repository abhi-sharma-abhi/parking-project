

#include <iostream>
#include "Menu.h"
#include "Vehicle.h"

#define MAX_SPOTS 100

#ifndef SDDS_PARKING_H__
#define SDDS PARKING_H__

using namespace std;

namespace sdds {
	class Parking {
		char* filename;
		int fileNameLength;
		Menu* main_menu;
		Menu* vehicle_menu;

		int number_of_spots;
		Vehicle** parking_spots;
		int parked_vehicles;

		void decor(const char str[]) const;
		bool prompt() const;

		void deallocate();
		void setEmpty();
		bool isEmpty() const;
		void ParkingStatus() const;
		void ParkVehicle();
		void ReturnVehicle();
		void ListVehicles() const;
		void FindVehicle() const;
		void SaveDataFile() const;

    	bool LoadDataFile() ;
    	bool CloseParking();
		bool ExitParking() const;

	public:
		Parking();
		Parking(const char filename[], const int noOfSpots);
		// Parking(const char filename[], const int indentation=0);
		~Parking();

		// delete copy and assignment functions
		Parking(const Parking& parking) = delete;
      	Parking& operator = (const Parking& parking) = delete;

      	int run();
	};
}

#endif
