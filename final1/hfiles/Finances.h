#include <iostream>
#include "SDL/SDL.h"
#ifndef FINANCES_H
#define FINANCES_H

#include<time.h>
#include "RollerCoaster.h"

using namespace std;

/* Finances will be integer values. Any construction
will cost money, but revenue may be gained as guests
enter the park, ride rides, or spend money at shops. */

class Finances {
	public:
		int balance;		// Total available money to customize park
		int parkEntranceFee;	// Fee guests pay when they enter the park; user may adjust
		int stationPrice;	// Price to build a station track piece of a coaster
		int gradualPrice;	// Price to build a piece that is either a gradual incline or decline
		int steepPrice;		// Price to build a piece that is either a steep incline or decline
		int shopPrice;		// Price to build a shop
		double interestRate;	// Rate to charge on the interest
		int currentLoan;	// Loan with which the user begins the game
		int maxLoan;		// Maximum loan that the user may take out
		int rideEntranceFee;	// Price to go on a ride

		Finances();
		int getBalance();			// Return the balance
		int getCurrentLoan();			// Return the current loan
		int getParkEntranceFee();		// Return the park entrance fee
		int displayBalance();			// Display the balance
		int isValidPurchase(int purchase);	// Verify that the cost of the action is less than the remaining balance
		void increaseLoan();			// Increase the park loan; CALLED in FinanceWindow
		void decreaseLoan();			// Decrease the park loan; CALLED in FinanceWindow
		void loanInterest();			// Charge interest on the loan; CALLED in Time
		void increaseEntranceFee();		// Increase the fee to enter the park by 1; CALLED in FinanceWindow
		void decreaseEntranceFee();		// Decrease the fee to enter the park by 1; CALLED in FinanceWindow
		void chargeEntranceFee();		// Charge the person entering the park the entrance fee; CALLED in People
		void buyStation();			// Charge the user for building a station piece; CALLED in RollerCoaster
		void buyGradual();			// Charge the user for building a gradual incline or decline piece; CALLED in RollerCoaster
		void buySteep();			// Charge the user for building a steep incline or decline piece; CALLED in RollerCoaster
		void sellCoaster(int);			// Sell coaster for 80% of its build worth, CALLED in RollerCoaster
		void buyShop();				// Buy a shop for the price of a shop; CALLED in Park
		void sellShop();			// Sell a shop for 80% of its worth; CALLED in Park
		void chargeRideEntranceFee(RollerCoaster);		// Charge riders for entering ride; CALLED in RollerCoaster
};

#endif
