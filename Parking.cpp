
#include "Parking.h"
#include "Utils.h"
#include "Motorcycle.h"
#include "Car.h"

#include <iostream>
#include <iomanip>
#include <fstream>

namespace sdds {

	void Parking::decor(const char str[]) const {
		cout << "---------------------------------" << endl;
		cout << str << endl;
		cout << "---------------------------------" << endl;
	}

	bool Parking::prompt() const {
		char choice;
		cout << "Are you sure? (Y)es/(N)o: ";
		cin.ignore();
		cin >> choice;
		while (choice != 89 && choice != 121 && choice != 110 && choice != 78) {
			cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			cin.ignore();
			cin >> choice;
		}
		return (choice == 89 || choice == 121) ? true : false;
	}

	void Parking::deallocate() {
		delete[] filename;
		for (int i = 1; i <= number_of_spots; i++) {
			if (parking_spots[i]) {
				delete parking_spots[i];
			}
		}
		delete[] parking_spots;
		delete main_menu;
		delete vehicle_menu;
	}

	void Parking::setEmpty() {
		filename = nullptr;
		main_menu = nullptr;
		vehicle_menu = nullptr;
		parking_spots = nullptr;
		fileNameLength = 0;
		parked_vehicles = 0;
		number_of_spots = 0;
	}

	bool Parking::isEmpty() const {
		return (filename == nullptr || fileNameLength == 0);
	}

	void Parking::ParkingStatus() const {
		cout << "****** Valet Parking ******\n";
		cout << "*****  Available spots: ";
		cout << left << setw(4) << number_of_spots - parked_vehicles << " *****" << endl;
	}

	void Parking::ParkVehicle() {
		if (parked_vehicles >= number_of_spots) {
			cout << "Parking is full" << endl;
			return;
		}

		Vehicle *vehicle = nullptr;
		int choice = vehicle_menu->run();
		// cout << "---------------------------------" << endl;
		if (choice == 1) {
			vehicle = new Car();
			cout << endl;
		} else if (choice == 2) {
			vehicle = new Motorcycle();
			cout << endl;
		} else if (choice == 3) {
			cout << "Parking Cancelled" << endl;
			return;
		}

		vehicle->setCsv(false);
		cin >> *vehicle;

		for (int i = 1; i <= number_of_spots; i++) {
			if (!parking_spots[i]) {
				vehicle->setParkingSpot(i);
				parking_spots[i] = vehicle;
				parked_vehicles++;
				break;
			}
		}

		cout << "\nParking Ticket\n";
		cout << *vehicle;

		// cout << "---------------------------------" << endl;
		cout << endl;
	}

	void Parking::ReturnVehicle() {
		// cout << "---------------------------------" << endl;
		std::cout << "Return Vehicle" << endl;

		std::cout << "Enter License Plate Number: ";
		char* plate = new char[10];
		std::cin.ignore();
		std::cin >> plate;
		int len = strlen(plate);
		while (len > 8 || len < 1 || plate == nullptr) {
			std::cout << "Invalid Licence Plate, try again: ";
			cin.ignore();
			std::cin >> plate;
		}
		toUpper(plate);

		int j = -1;
		for (int i = 1; i <= number_of_spots; i++) {
			if (!parking_spots[i]) continue;
			if (strcmp(parking_spots[i]->getLicensePlate(), plate)) {
				j = i;
			}
		}

		if (j == -1) {
			cout << "\nLicense plate " << plate << " Not found\n";
		} else {
			cout << "\nReturning:\n";
			cout << *parking_spots[j];
			delete parking_spots[j];
			parking_spots[j] = nullptr;
			parked_vehicles--;
		}

		delete[] plate;
		// cout << "---------------------------------" << endl;
		cout << '\n';
	}

	void Parking::ListVehicles() const {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 1; i <= number_of_spots; i++) {
			if (!parking_spots[i]) continue;
			cout << *parking_spots[i];
			cout << "-------------------------------" << endl;
		}
	}

	void Parking::FindVehicle() const {
		// cout << "---------------------------------" << endl;
		cout << "Vehicle Search" << endl;
		
		std::cout << "Enter Licence Plate Number: ";
		char* plate = new char[10];
		cin.ignore();
		std::cin >> plate;
		int len = strlen(plate);
		while (len > 8 || len < 1 || plate == nullptr) {
			std::cout << "Invalid Licence Plate, try again: ";
			cin.ignore();
			std::cin >> plate;
		}

		toUpper(plate);

		int j = -1;
		for (int i = 1; i <= number_of_spots; i++) {
			if (!parking_spots[i]) continue;
			if (strcmp(parking_spots[i]->getLicensePlate(), plate)) {
				j = i;
				break;
			}
		}

		if (j == -1) {
			cout << "\nLicense plate " << plate << " Not found\n";
		} else {
			cout << "\nVehicle found:\n";
			cout << *parking_spots[j];
		}

		delete[] plate;
		// cout << "---------------------------------" << endl;
		cout << endl;
	}

	void Parking::SaveDataFile() const {
		if (isEmpty()) return;
		ofstream file(this->filename);
		for (int i = 1; i <= number_of_spots; i++) {
			if (parking_spots[i] && !parking_spots[i]->isEmpty()) {
				bool old = parking_spots[i]->isCsv();
				parking_spots[i]->setCsv(true);
				file << *parking_spots[i] << '\n';
				parking_spots[i]->setCsv(old);
			}
		}
	}

	bool Parking::LoadDataFile() {
		if (isEmpty()) return true;

		bool state = true;
		ifstream file(filename);

		if (file.fail()) return true;

		char vehicleType, ignore;
		while (file >> noskipws >> vehicleType) {
			file >> ignore;

			if (vehicleType == 'M') {
				Motorcycle* vehicle = new Motorcycle();
				state = true;

				bool old = vehicle->isCsv();
				vehicle->setCsv(true);
				file >> *vehicle;
				if (file.bad()) {
					delete vehicle;
					vehicle = nullptr;
					state = false;
				}
				vehicle->setCsv(old);
				int spot = vehicle->getParkingSpot();
				parking_spots[spot] = new Motorcycle(*vehicle);
				delete vehicle;
				parked_vehicles++;
			} else if (vehicleType == 'C') {
				Car* vehicle = new Car();
				state = true;

				bool old = vehicle->isCsv();
				vehicle->setCsv(true);
				file >> *vehicle;
				if (file.bad()) {
					delete vehicle;
					vehicle = nullptr;
					state = false;
				}
				vehicle->setCsv(old);
				int spot = vehicle->getParkingSpot();
				parking_spots[spot] = new Car(*vehicle);
				delete vehicle;
				parked_vehicles++;
				state = true;
			} else {
				state = false;
			}
		}
		return state;
	}

	bool Parking::CloseParking() {
		if (isEmpty()) return true;

		char choice;
		cout << "This will Remove and tow all remaining Vehicles from the Parking!\n";
		cout << "Are you sure? (Y)es/(N)o: ";
		cin >> choice;

		while (choice != 89 && choice != 121 && choice != 110 && choice != 78) {
			cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			cin >> choice;
		}
		if (choice == 110 || choice == 78) {
			return false;
		}
		cout << "Closing Parking\n";
		for (int i = 1; i <= number_of_spots; i++) {
			if (!parking_spots[i]) continue;
			cout << "\nTowing request\n";
			cout << "*********************\n";
			cout << *parking_spots[i];
			delete parking_spots[i];
			parking_spots[i] = nullptr;
		}
		return true;
	}

	bool Parking::ExitParking() const {
		cout << "This will terminate the program!" << endl;
		int resp = prompt();
		if (resp) {
			SaveDataFile();
			cout << "Exiting program!" << endl;						
		}
		return resp;
	}

	Parking::Parking() {
		setEmpty();
	}

	Parking::Parking(const char filename[], const int noOfSpots) {
		setEmpty();
		this->fileNameLength = strlen(filename);
		if (filename == nullptr || this->fileNameLength == 0 || noOfSpots < 10 || noOfSpots > MAX_SPOTS) {
			return;
		}

		this->number_of_spots = noOfSpots;
		parking_spots = new Vehicle *[noOfSpots+1];
		for (int i = 0; i < noOfSpots; i++) {
			parking_spots[i] = nullptr;
		}

		this->filename = strcpy(filename);
		if (!this->LoadDataFile()) {
			cout << "Error in data file\n";
			deallocate();
			setEmpty();
			return;
		}

		main_menu = new Menu("Parking Menu, select an action:", 0);
		*main_menu << "Park Vehicle" <<
				"Return Vehicle" <<
				"List Parked Vehicles" <<
				"Find Vehicle" <<
				"Close Parking (End of day)" <<
				"Exit Program";

		vehicle_menu = new Menu("Select type of the vehicle:", 1);
		*vehicle_menu << "Car" <<
						"Motorcycle" <<
						"Cancel";
	}
	Parking::~Parking() {
		SaveDataFile();
		deallocate();
	}

	int Parking::run() {
		if (isEmpty()) return -1;
		while (true) {
			ParkingStatus();
			int response = main_menu->run();
			switch (response) {
				case 1:
					ParkVehicle(); break;
				case 2:
					ReturnVehicle(); break;
				case 3:
					ListVehicles(); break;
				case 4:
					FindVehicle(); break;
				case 5:
					if (CloseParking()) return isEmpty();
					break;
				case 6:
					if (ExitParking()) return isEmpty();
					break;
				default:
					break;
			};
			cout << "Press <ENTER> to continue....";
			cin.ignore();
			while (cin.get() != '\n');
		}
		return isEmpty();
	}
}
