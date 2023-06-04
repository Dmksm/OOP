#include "stdafx.h"
#include "CDate.h"

const unsigned LEAP_YEARS_NUMBER_IN_400_YEARS = 97;
const unsigned LEAP_YEARS_NUMBER_IN_100_YEARS = 24;
const unsigned DAYS_IN_MONTH_COUNT[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const unsigned MAX_VALID_TIMESTAMP = 2932896;

struct DWMY
{
	unsigned day;
	WeekDay week;
	Month month;
	unsigned year;
};

void CheckValidOperationResult(unsigned timestamp, long int day)
{
	if (((day > 0) && (timestamp <= MAX_VALID_TIMESTAMP - day) ||
		((day < 0) && (timestamp >= -day))))
	{
		return;
	}
	throw std::invalid_argument("Overflow!");
}

bool ÑheckLeapYear(unsigned year)
{
	if (year % 400 == 0)
	{
		return true;
	}

	if (year % 100 == 0)
	{
		return false;
	}

	if (year % 4 == 0)
	{
		return true;
	}
	return false;
}

bool IsValid(unsigned day, Month month, unsigned year)
{
	unsigned daysCountInCurrYear = DAYS_IN_MONTH_COUNT[static_cast<unsigned>(month) - 1];
	if (ÑheckLeapYear(year) && month == Month::FEBRUARY)
	{
		++daysCountInCurrYear;
	}
	if (year < 1970 || year > 9999 || day < 1 || day > daysCountInCurrYear)
	{
		return false;
	}

	return true;
}

unsigned GetLeapYearCount(unsigned year)
{
	unsigned leapYearCount = 0;

	leapYearCount += LEAP_YEARS_NUMBER_IN_400_YEARS * ((unsigned)year / 400);
	year %= 400;

	leapYearCount += LEAP_YEARS_NUMBER_IN_100_YEARS * ((unsigned)year / 100);
	year %= 100;

	leapYearCount += (unsigned)year / 4;
	return leapYearCount;
}

unsigned ToTimestamp(unsigned day, Month month, unsigned year)
{
	if (!IsValid(day, month, year))
	{
		throw std::invalid_argument("Invalid day or year!");
	}

	unsigned timestamp = (year - 1970) * 365;
	const unsigned NUMBER_OF_LEAP_YEARS_SINCE_1970 = 477;
	timestamp += GetLeapYearCount(year) - NUMBER_OF_LEAP_YEARS_SINCE_1970;

	unsigned currMonth = static_cast<unsigned>(month) - 1;
	for (unsigned numMonth = 0; numMonth < currMonth; numMonth++)
	{
		timestamp += DAYS_IN_MONTH_COUNT[numMonth];
	}
	if (ÑheckLeapYear(year) && static_cast<unsigned>(month) < static_cast<unsigned>(Month::MARCH))
	{
		--timestamp;
	}

	timestamp += --day;

	return timestamp;
}

unsigned GetLeapYearDayCount(unsigned day)
{
	unsigned leapYearDayCount = 0;
	const unsigned FIRST_LEAP_YEAR_DAY = 789;
	if (day >= FIRST_LEAP_YEAR_DAY)
	{
		++leapYearDayCount;
		day -= FIRST_LEAP_YEAR_DAY - 1;

		leapYearDayCount += LEAP_YEARS_NUMBER_IN_400_YEARS * 
			((unsigned)day / ToTimestamp(1, Month::JANUARY, 1970 + 400));
		day %= ToTimestamp(1, Month::JANUARY, 1970 + 400);

		leapYearDayCount += LEAP_YEARS_NUMBER_IN_100_YEARS * 
			((unsigned)day / ToTimestamp(1, Month::JANUARY, 1970 + 100));
		day %= ToTimestamp(1, Month::JANUARY, 1970 + 100);

		leapYearDayCount += (unsigned)day / ToTimestamp(1, Month::JANUARY, 1970 + 4);
	}

	return leapYearDayCount;
}

unsigned ToYear(unsigned day)
{
	return (day - GetLeapYearDayCount(day)) / 365;
}

DWMY FromTimestamp(unsigned day)
{
	unsigned const Week1970 = 4;
	unsigned nowWeek = (Week1970 + day) % 7;

	unsigned nowYear = 1970 + ToYear(day);
	unsigned nowTimestampYear = day - ToTimestamp(1, Month::JANUARY, nowYear);

	bool isLeapYear = ÑheckLeapYear(nowYear);
	unsigned timestamp = 0; //  âìåñòî now current
	unsigned nowDay = 0, nowMonth = 0;
	for (; nowMonth < 12; nowMonth++)
	{
		timestamp += DAYS_IN_MONTH_COUNT[nowMonth];
		if (isLeapYear && nowMonth == 1)
		{
			if (timestamp == nowTimestampYear)
			{
				nowDay = 28;
				++nowMonth;
				break;
			}
			if ((timestamp + 1) <= nowTimestampYear)
			{
				++timestamp;
			}
		}

		if (timestamp > nowTimestampYear)
		{
			nowDay += nowTimestampYear - (timestamp - DAYS_IN_MONTH_COUNT[nowMonth]);
			++nowMonth;
			break;
		}
	}
	++nowDay;

	DWMY dwmy;
	dwmy.day = nowDay;
	dwmy.week = static_cast<WeekDay>(nowWeek);
	dwmy.month = static_cast<Month>(nowMonth);
	dwmy.year = nowYear;
	return dwmy;
}

std::ostream& operator<<(std::ostream& ostream, const CDate& date)
{
	ostream << date.GetDay() << "." <<
		static_cast<unsigned>(date.GetMonth()) << "." << date.GetYear();
	return ostream;
}

std::istream& operator>>(std::istream& istream, CDate& date)
{
	try
	{
		unsigned day, month, year;
		char ch1, ch2;
		istream >> day >> ch1 >> month >> ch2 >> year;
		if (ch1 != ch2 || ch1 != '.')
		{
			throw std::invalid_argument("Format was be DD.MM.YYYY !");
		}
		date = *(new CDate(day, static_cast<Month>(month), year));
	}
	catch (std::invalid_argument const& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
		istream.setstate(std::ios::failbit);
	}
	return istream;
}

CDate CDate::operator+(long int day) const
{
	CheckValidOperationResult(this->m_timestamp, day);
	return CDate(this->m_timestamp + day);
}

CDate CDate::operator-(long int day) const
{
	return *this + -day;
}

long int CDate::operator-(const CDate& date) const
{
	long int result, k = 1;
	if (this->m_timestamp > date.m_timestamp)
	{
		result = this->m_timestamp - date.m_timestamp;
	}
	else
	{
		k = -1;
		result = date.m_timestamp - this->m_timestamp;
	}
	return result * k;
}

CDate& CDate::operator++()
{
	this->m_timestamp = (*this + 1).m_timestamp;
	return *this;
}

CDate& CDate::operator--()
{
	this->m_timestamp = (*this + -1).m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate oldDate = *this;
	operator++();
	return oldDate;
}

CDate CDate::operator--(int)
{
	CDate oldDate = *this;
	operator--();
	return oldDate;
}

std::strong_ordering CDate::operator<=>(const CDate& date) const
{
	return this->m_timestamp <=> date.m_timestamp;
}

bool CDate::operator==(const CDate& date) const
{
	return this->m_timestamp == date.m_timestamp;
}

CDate& CDate::operator-=(long int day)
{
	this->m_timestamp = (*this - day).m_timestamp;
	return *this;
}

CDate& CDate::operator+=(long int day)
{
	this->m_timestamp = (*this + day).m_timestamp;
	return *this;
}

CDate::CDate(unsigned day, Month month, unsigned year)
	: m_timestamp(ToTimestamp(day, month, year))
{
}

CDate::CDate(unsigned timestamp)
	: m_timestamp(timestamp)
{
}

unsigned CDate::GetDay() const
{
	return FromTimestamp(m_timestamp).day;
}

Month CDate::GetMonth() const
{
	return FromTimestamp(m_timestamp).month;
}

unsigned CDate::GetYear() const
{
	return FromTimestamp(m_timestamp).year;
}

WeekDay CDate::GetWeekDay() const
{
	return FromTimestamp(m_timestamp).week;
}