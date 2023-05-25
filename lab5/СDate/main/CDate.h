#pragma once
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
	CDate& operator++();

	CDate& operator--();

	CDate operator++(int);

	CDate operator--(int);

	CDate& operator-=(const CDate& Date);

	CDate& operator+=(const CDate& Date);

	bool operator!=(const CDate& Date);

	bool operator==(const CDate& Date);

	bool operator>=(const CDate& date);

	bool operator>(const CDate& date);

	bool operator<=(const CDate& date);

	bool operator<(const CDate& date);

	CDate(unsigned day, Month month, unsigned year);

	CDate(unsigned timestamp = 0);

	unsigned GetDay() const;

	Month GetMonth() const;

	unsigned GetYear() const;

	unsigned GetTimestamp() const;

	WeekDay GetWeekDay() const;

	bool IsValid(unsigned day, Month month, unsigned year) const;

private:
	unsigned m_timestamp;
};

std::ostream& operator<<(std::ostream& os, const CDate& Date);

std::istream& operator>>(std::istream& is, CDate& Date);
//---------------------------------------------------------------------------------------Доделать
CDate operator+(const CDate& date, long int day);

CDate operator-(const CDate& date, long int day);

long int operator-(const CDate& leftDate, const CDate& rightDate);
//---------------------------------------------------------------------------------------