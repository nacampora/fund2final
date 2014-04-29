#include <iostream>
#include "SDL/SDL.h"
#include "RollerCoaster.h"
#include "Finances.h"
#ifndef PEOPLE_H
#define PEOPLE_H

using namespace std;

/* The people class will hold all information
and store all member functions that relate
to the people in the park */

class People {
	protected:
		int numberInPark;			// Number of people in the park
		int fluxConstant;			// Determines the rate at which people enter the park
//		string name;				// The name of the parkgoer
//		int maxPreferredRideIntensity;		// The maximum ride excitement of a ride that this person will ride
//		int minPreferredRideExcitement;		// The minimum ride excitement of a ride that this person will ride
//		int dollarsOnPerson;			// The amount of money that a person brings into the park
        public:
		People();
		void changeNumberInPark(Finances F1);
		void increaseFluxConstant(int);
		void decreaseFluxConstant();
//		People(int personCounter, double maxPreferredRideIntensity, double minPreferredRideExcitement, int dollarsOnPerson);
//		~People();					// Destructor
		void goOnRide(RollerCoaster R1, Finances F1);	// Function to add people up to the maximum number to the specified ride
		void leaveRide(RollerCoaster R1);		// When ride ends, leave ride; reset number on ride to 0
};

#endif
