#include <iostream>
#include <iomanip>
#include "Time.h"
#include <sstream>

using namespace std;

Time::Time() {
	hour=0;
	day=1;
	month=1;
	year=1;
}

int Time::getDaysInMonth() {
	int daysInMonth[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int daysInMonthLeapYear[]={0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year%4==0) {
		return daysInMonthLeapYear[month];
	} else {
		return daysInMonth[month];
	}
}

/* May need to run this in while loop of driver program */
void Time::incrementHour() {
	hour++;
	incrementDay();
}

void Time::incrementDay() {
	if (hour==24) {
		hour=0;
		day++;
	}
	incrementMonth();
}

void Time::incrementMonth() {
	if (day>getDaysInMonth()) {
		day=1;
		month++;
	}
	incrementYear();
}

void Time::incrementYear() {
	if (month>12) {
		month=1;
		year++;
	}
}

/*
void Time::displayDate() {
//	cout << monthName[2] << endl;
	const char *monthName[] = {"", "January", "February", "March", "April", "May", "June",
				       "July", "August", "September", "October", "November", "December"};
	cout << setw(2) << hour << ":00 " << setw(10) << monthName[month] << " " << setw(2) << day << ", Year " << year << endl;
	incrementDay();
	incrementMonth();
	incrementYear();
}
*/

const char* Time::getDate() {
	string monthName[] = {"", "January", "February", "March", "April", "May", "June",
				  "July", "August", "September", "October", "November", "December"};
	ostringstream convertDay;
	convertDay << day;
	string strDay = convertDay.str();

	ostringstream convertYear;
	convertYear << year;
	string strYear = convertYear.str();

	ostringstream convertHour;
	convertHour << hour;
	string strHour = convertHour.str();

	string strDate = monthName[month] + " " + strDay + ", Year " + strYear + "   " + strHour + ":00";
	const char * date = strDate.c_str();
	return date;


}













