#include <bits/stdc++.h>
#include "../../test_runner.h"

using namespace std;

class Date {
public:
    Date() = default;

    explicit Date(int year, int month, int day)
            : year(year), month(month), day(day) {
    }

    int Year() const {
        return year;
    }

    int Month() const {
        return month;
    }

    int Day() const {
        return day;
    }

    time_t AsTimestamp() const {
        std::tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day;
        t.tm_mon = month - 1;
        t.tm_year = year - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

    bool operator<(const Date &rhs) const {
        return make_tuple(year, month, day) < make_tuple(rhs.year, rhs.month, rhs.day);
    }

    bool operator<=(const Date &rhs) const {
        return make_tuple(year, month, day) <= make_tuple(rhs.year, rhs.month, rhs.day);
    }

    bool operator>(const Date &rhs) const {
        return make_tuple(year, month, day) > make_tuple(rhs.year, rhs.month, rhs.day);
    }

    bool operator>=(const Date &rhs) const {
        return make_tuple(year, month, day) >= make_tuple(rhs.year, rhs.month, rhs.day);
    }

    bool operator==(const Date &rhs) const {
        return make_tuple(year, month, day) == make_tuple(rhs.year, rhs.month, rhs.day);
    }

    bool operator!=(const Date &rhs) const {
        return !(*this == rhs);
    }

private:
    int year;
    int month;
    int day;
};

istream &operator>>(istream &is, Date &date) {
    size_t year = 0;
    size_t month = 0;
    size_t day = 0;

    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;

    date = Date(year, month, day);

    return is;
}

int ComputeDaysDiff(const Date &date_to, const Date &date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

struct DateRange {
    Date from;
    Date to;
};

struct IncomeRange {
    IncomeRange() = default;

    IncomeRange(const DateRange &range, double value)
            : range(range), value(value) {}

    DateRange range;
    double value;
};

class BudgetManager {
public:
    double ComputeIncome(const DateRange &range) const {
        double income = 0;
        for (const auto &[date_range, value] : income_ranges) {
            if (date_range.to < range.from || date_range.from > range.to)
                continue;
            auto range_start = max(range.from, date_range.from);
            auto range_end = min(range.to, date_range.to);
            if (range_start == date_range.from && range_end == date_range.to) {
                income += value;
            } else {
                int days_in_period = ComputeDaysDiff(date_range.to, date_range.from);
                int days_in_range = ComputeDaysDiff(range_end, range_start);
                int diff = days_in_period - days_in_range;
                double coeff = static_cast<double>(days_in_period - diff) / days_in_period;
                income += value * coeff;
            }
        }
        return income;
    }

    void Earn(const DateRange &range, size_t value) {
        income_ranges.emplace_back(range, static_cast<double>(value));
    }

    void PayTax(const DateRange &range, size_t percentage = 13) {
        const double tax_coeff = (static_cast<double>(100 - percentage) / 100);
        for (auto &[date_range, value] : income_ranges) {
            if (date_range.to < range.from || date_range.from > range.to)
                continue;
            auto range_start = max(range.from, date_range.from);
            auto range_end = min(range.to, date_range.to);
            if (range_start == date_range.from && range_end == date_range.to) {
                value *= tax_coeff;
            } else {
                IncomeRange income_range = {date_range, value};
                int days_in_period = ComputeDaysDiff(date_range.to, date_range.from);
                int days_in_range = ComputeDaysDiff(range_end, range_start);
                int diff = days_in_period - days_in_range;
                double coeff = static_cast<double>(days_in_period - diff) / days_in_period;
                date_range = {range_start, range_end};
                value *= coeff * tax_coeff;
                if (income_range.range.from < range_start) {
                    int days_before_range = ComputeDaysDiff(range_start, income_range.range.from);
                    int diff = days_in_period - days_before_range;
                    double coeff = static_cast<double>(days_in_period - diff) / days_in_period;
                    DateRange dr {income_range.range.from, range_start};
                    income_ranges.emplace_back(dr, income_range.value * coeff);
                }
                if (income_range.range.to > range_end) {
                    int days_after_range = ComputeDaysDiff(income_range.range.to, range_end);
                    int diff = days_in_period - days_after_range;
                    double coeff = static_cast<double>(days_in_period - diff) / days_in_period;
                    DateRange dr {range_end, income_range.range.to};
                    income_ranges.emplace_back(dr, income_range.value * coeff);
                }
            }
        }
    }

private:
    vector<IncomeRange> income_ranges;
};

void TestComputeIncome() {
    BudgetManager bm;
    bm.Earn({Date(2000, 1, 3), Date(2000, 1, 6)}, 1000);
    {
        double income = bm.ComputeIncome({Date(2000, 1, 3), Date(2000, 1, 6)});
        ASSERT_EQUAL(income, 1000);
        income = bm.ComputeIncome({Date(2000, 1, 3), Date(2000, 1, 5)});
        ASSERT((income - 666.667) < numeric_limits<double>::epsilon());
    }
    bm.Earn({Date(2001, 1, 3), Date(2001, 1, 8)}, 1000);
    {
        double income = bm.ComputeIncome({Date(2001, 1, 3), Date(2001, 1, 8)});
        ASSERT_EQUAL(income, 1000);
        income = bm.ComputeIncome({Date(2001, 1, 3), Date(2001, 1, 7)});
        ASSERT((income - 800) < numeric_limits<double>::epsilon());
    }
}

void TestPayTax() {
    BudgetManager bm;
    bm.Earn({Date(2000, 1, 2), Date(2000, 1, 6)}, 20);
    double income = bm.ComputeIncome({Date(2000, 1, 1), Date(2001, 1, 1)});
    ASSERT_EQUAL(income, 20);
    bm.PayTax({Date(2000, 1, 2), Date(2000, 1, 3)});
    income = bm.ComputeIncome({Date(2000, 1, 1), Date(2001, 1, 1)});
    ASSERT((income - 18.96) < numeric_limits<double>::epsilon());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestComputeIncome);
    RUN_TEST(tr, TestPayTax);
    BudgetManager bm;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string query;
        cin >> query;
        if (query == "Earn") {
            DateRange dateRange{};
            size_t value;
            cin >> dateRange.from >> dateRange.to >> value;
            bm.Earn(dateRange, value);
        } else if (query == "ComputeIncome") {
            DateRange dateRange{};
            cin >> dateRange.from >> dateRange.to;
            cout << bm.ComputeIncome(dateRange) << endl;
        } else if (query == "PayTax") {
            DateRange dateRange{};
            cin >> dateRange.from >> dateRange.to;
            bm.PayTax(dateRange);
        }
    }
}