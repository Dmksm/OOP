#pragma once
#include "stdafx.h"
enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);

	CDate(unsigned timestamp = 0);

	CDate& operator++();

	CDate& operator--();

	CDate operator++(int);

	CDate operator--(int);

	CDate& operator-=(long int day);

	CDate& operator+=(long int day);

	bool operator==(const CDate& Date) const;

	std::strong_ordering operator<=>(const CDate& date) const;

	unsigned GetDay() const;

	Month GetMonth() const;

	unsigned GetYear() const;

	WeekDay GetWeekDay() const;
	
	CDate operator+(long int day) const;

	CDate operator-(long int day) const;

	long int operator-(const CDate& date) const;

private:
	unsigned m_timestamp;
};

std::ostream& operator<<(std::ostream& os, const CDate& Date);

std::istream& operator>>(std::istream& is, CDate& Date);
