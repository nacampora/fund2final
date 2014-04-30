#include <iostream>
#include "SDL/SDL.h"
#ifndef TIME_H
#define TIME_H

using namespace std;

/* Time will keep track of day, month, year, and hour.
Hours will tick with every second, but aside from this,
the calendar will function normally. */

class Time {
	private:
		int hour;
		int day;
		int month;
		int year;
	public:
		Time();
//		void displayDate();
		const char* getDate();
		void incrementHour();
		void incrementDay();
		void incrementMonth();
		void incrementYear();
		int getDaysInMonth();
};

#endif
