#include <iostream>
#include "SDL/SDL.h"
#include "People.h"
#include "RollerCoaster.h"
#include "Finances.h"

using namespace std;

People::People() {
	numberInPark = 0;
	fluxConstant = 1;
}

/*	fluxConstant may be changed when a rollercoaster is completed or a shop is placed.
	If there is more construction occurring, people are more likely to enter the park
	and ride the rides. 
*/

/*
People::People(personCounter, maxPreferredRideIntensity, minPreferredRideExcitement, dollarsOnPerson) {
	string nameArray[] =   {"Adrian", "Benjamin", "Camden", "David", "Edwin", "Frankie", 
				"Giuliana", "Heather", "Izzy", "Jack", "Kyle", "Lucinda",
				"Mitch", "Nicholas", "Owen", "Peter", "Quinn", "Ryan", 
				"Sam", "Tyler", "Ursula", "Vaishnav", "William", "Xuanyi",
				"Yucheng", "Zachary"};
	name=nameArray[personCounter()%25];
}

People::~People() {
}
*/

void People::increaseFluxConstant(int determineIncrement) {	// Called whenever a shop is placed or a coaster is built
	fluxConstant += determineIncrement;			// The other classes will call functions that determine how much to increment flux by
								// If a coaster is built, flux will increase by 5; shops, 2;
}

void People::decreaseFluxConstant() {
	fluxConstant -= 1;					// If no construction is done in 15 seconds, fluxConstant drops by 1
}

void People::changeNumberInPark(Finances F1) {			// Runs every 3 seconds; link to Time
	numberInPark += fluxConstant;
	int i;
	if (fluxConstant>0) {
		for (i=0; i<fluxConstant; i++) {
			F1.chargeEntranceFee();
		}
	}
}

void People::goOnRide(RollerCoaster R1, Finances F1) {		// Called when user presses play on ride
	if (rideEntranceFee<7) {
		int riders = rand() % R1.maxPeopleOnRide + 1;
		R1.peopleOnRide = riders;
		int i;
		for (i=0; i<riders; i++) {
			F1.chargeRideEntranceFee(R1);
		}
	} else {
		R1.peopleOnRide = 0;
	}
}

void People::leaveRide(RollerCoaster R1) {			// Called when the ride ends
	R1.peopleOnRide = 0;
}
