#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream ss(international_number);
    if (ss.peek() != '+')
        throw invalid_argument("number should starts with '+'");
    ss.ignore(1);
    getline(ss, country_code_, '-');
    if (country_code_.empty())
        throw invalid_argument("country code shouldn't be empty");
    if (ss.eof())
        throw invalid_argument("contains only country_code");
    getline(ss, city_code_, '-');
    if (city_code_.empty())
        throw invalid_argument("city code shouldn't be empty");
    if (ss.eof())
        throw invalid_argument("should also contain local number");
    getline(ss, local_number_);
    if (local_number_.empty())
        throw invalid_argument("local number shouldn't be empty");
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}