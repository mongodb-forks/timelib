#include "CppUTest/TestHarness.h"
#include "timelib.h"
#include <string.h>

TEST_GROUP(parse_tz)
{
};

TEST(parse_tz, new_york)
{
	int error;
	timelib_tzinfo *tzi = timelib_parse_tzfile("America/New_York", timelib_builtin_db(), &error);
	CHECK(tzi != NULL);
	CHECK(error == TIMELIB_ERROR_NO_ERROR);
	STRCMP_EQUAL("US", tzi->location.country_code);
	DOUBLES_EQUAL( 40, tzi->location.latitude, 1);
	DOUBLES_EQUAL(-74, tzi->location.longitude, 1);
	STRCMP_EQUAL("EST5EDT,M3.2.0,M11.1.0", tzi->posix_string);
	CHECK(!!tzi->bc);
	timelib_tzinfo_dtor(tzi);
}

TEST(parse_tz, utc)
{
	int error;
	timelib_tzinfo *tzi = timelib_parse_tzfile("UTC", timelib_builtin_db(), &error);
	CHECK(tzi != NULL);
	CHECK(error == TIMELIB_ERROR_NO_ERROR);
	STRCMP_EQUAL("??", tzi->location.country_code);
	DOUBLES_EQUAL(  -90, tzi->location.latitude, 1);
	DOUBLES_EQUAL( -180, tzi->location.longitude, 1);
	STRCMP_EQUAL("UTC0", tzi->posix_string);
	LONGS_EQUAL(1, tzi->bit64.typecnt);
	CHECK(!!tzi->bc);
	timelib_tzinfo_dtor(tzi);
}

TEST(parse_tz, us_samoa)
{
	int error;
	timelib_tzinfo *tzi = timelib_parse_tzfile("US/Samoa", timelib_builtin_db(), &error);
	CHECK(tzi != NULL);
	CHECK(error == TIMELIB_ERROR_NO_ERROR);
	STRCMP_EQUAL("SST11", tzi->posix_string);
	CHECK(!tzi->bc);
	timelib_tzinfo_dtor(tzi);
}
