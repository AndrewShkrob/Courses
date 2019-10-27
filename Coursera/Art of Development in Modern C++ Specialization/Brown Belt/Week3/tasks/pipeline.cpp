#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>

using namespace std;

struct Email {
    string from;
    string to;
    string body;
};

class Worker {
public:
    virtual ~Worker() = default;

    virtual void Process(unique_ptr<Email> email) = 0;

    virtual void Run() {
        throw logic_error("Unimplemented");
    }

protected:
    void PassOn(unique_ptr<Email> email) const {
        if (next_worker)
            next_worker->Process(move(email));
    }

    unique_ptr<Worker> next_worker;
public:
    void SetNext(unique_ptr<Worker> next) {
        next_worker = move(next);
    }
};

class Reader : public Worker {
public:

    Reader(istream &is) : input(is) {}

    virtual void Process(unique_ptr<Email> email) {}

    virtual void Run() {
        vector<unique_ptr<Email>> emails;
        while (true) {
            auto email = make_unique<Email>();
            getline(input, email->from);
            getline(input, email->to);
            getline(input, email->body);
            if (input.eof())
                break;
            emails.emplace_back(move(email));
        }
        for (auto &email : emails)
            PassOn(move(email));
    }

private:
    istream &input;
};

class Filter : public Worker {
public:
    using Function = function<bool(const Email &)>;
public:
    Filter(Function filter) : filter_(move(filter)) {}

    virtual void Process(unique_ptr<Email> email) {
        if (filter_(*email))
            PassOn(move(email));
    }

private:
    Function filter_;
};

class Copier : public Worker {
public:
    Copier(string to) : to(move(to)) {}

    virtual void Process(unique_ptr<Email> email) {
        if (email->to == to) {
            PassOn(move(email));
        } else {
            auto copy = make_unique<Email>();
            copy->from = email->from;
            copy->to = to;
            copy->body = email->body;
            PassOn(move(email));
            PassOn(move(copy));
        }
    }

private:
    string to;
};

class Sender : public Worker {
public:
    Sender(ostream &os) : output(os) {}

    virtual void Process(unique_ptr<Email> email) {
        output << email->from << endl;
        output << email->to << endl;
        output << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream &output;
};

class PipelineBuilder {
public:
    explicit PipelineBuilder(istream &in) {
        workers.emplace(make_unique<Reader>(in));
    }

    PipelineBuilder &FilterBy(Filter::Function filter) {
        workers.emplace(make_unique<Filter>(move(filter)));
        return *this;
    }

    PipelineBuilder &CopyTo(string recipient) {
        workers.emplace(make_unique<Copier>(move(recipient)));
        return *this;
    }

    PipelineBuilder &Send(ostream &out) {
        workers.emplace(make_unique<Sender>(out));
        return *this;
    }

    unique_ptr<Worker> Build() {
        while (workers.size() > 1) {
            unique_ptr<Worker> top_w = move(workers.top());
            workers.pop();
            workers.top()->SetNext(move(top_w));
        }
        return move(workers.top());
    }

private:
    stack<unique_ptr<Worker>> workers;
};
