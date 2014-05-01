#include <iostream>
#include "SDL/SDL.h"
#include "Finances.h"

using namespace std;

Finances::Finances() {

	/* All of the following are dollar amounts, except rate */
	balance=10000;
	parkEntranceFee=10;
	stationPrice=10;
	gradualPrice=8;
	steepPrice=12;
	shopPrice=200;
	interestRate=.05;
	currentLoan=1000;
	maxLoan=20000;
	rideEntranceFee=3;
}

int Finances::getBalance() {
	return balance;
}

int Finances::getCurrentLoan() {
	return currentLoan;
}

int Finances::getParkEntranceFee() {
	return parkEntranceFee;
}

void Finances::setBalance(int b) {
	balance = b;
}

void Finances::setCurrentLoan(int l) {
	currentLoan = l;
}

void Finances::setParkEntranceFee(int p) {
	parkEntranceFee = p;
}

int Finances::displayBalance() {
	cout << balance;
}

int Finances::isValidPurchase(int purchase) {
	if (balance>purchase) {
		return 1;
	} else {
		return 0;
	}
}

void Finances::increaseLoan() {
	if (currentLoan<maxLoan) {
		currentLoan+=1000;
		balance+=1000;
	}
}

void Finances::decreaseLoan() {
	if (currentLoan>0) {
		currentLoan-=1000;
		balance-=1000;
	}
}

void Finances::loanInterest() {
	if (time(0)%100==0) {
		balance-=(currentLoan*interestRate);
	}
}

void Finances::increaseEntranceFee() {
	parkEntranceFee+=1;
}

void Finances::decreaseEntranceFee() {
	if (parkEntranceFee!=0) {
		parkEntranceFee-=1;
	}
}

void Finances::chargeEntranceFee() {
	balance+=parkEntranceFee;
}

void Finances::buyStation() {
	balance-=stationPrice;
//	R1.worth+=stationPrice;
}

void Finances::buyGradual() {
	balance-=gradualPrice;
//	R1.worth+=gradualPrice;
}

void Finances::buySteep() {
	balance-=steepPrice;
//	R1.worth+=steepPrice;
}

void Finances::sellCoaster(int coasterWorth) {
	balance+=(coasterWorth)*.8;
}

void Finances::buyShop() {
	balance-=shopPrice;
}

void Finances::sellShop() {
	balance+=(shopPrice*.8);
}

void Finances::chargeRideEntranceFee() {
	balance+=rideEntranceFee;
}
