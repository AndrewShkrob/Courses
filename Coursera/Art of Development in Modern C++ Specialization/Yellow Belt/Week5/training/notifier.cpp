#include <iostream>
#include <string>

using namespace std;

class INotifier {
public:
    virtual void Notify(const string &message) const = 0;
};

class SmsNotifier : public INotifier {
public:
    SmsNotifier(const string &phone_number) : phone_number(phone_number) {}

    void Notify(const string &message) const override {
        SendSms(phone_number, message);
    }

private:
    string phone_number;
};

class EmailNotifier : public INotifier {
public:
    EmailNotifier(const string &email) : email(email) {}

    void Notify(const string &message) const override {
        SendEmail(email, message);
    }

private:
    string email;
};