#include <bits/stdc++.h>

using namespace std;

class Logger {
public:
    explicit Logger(ostream &output_stream) : os(output_stream) {
    }

    void SetLogLine(bool value) { log_line = value; }

    void SetLogFile(bool value) { log_file = value; }

    void Log(const string &message) {
        if (log_file && log_line) {
            os << file << ':' << line << ' ';
        } else if (log_file) {
            os << file << ' ';
        } else if (log_line) {
            os << "Line " << line << ' ';
        }
        os << message << '\n';
    }

    bool LogLine() {
        return log_line;
    }

    bool LogFile() {
        return log_file;
    }

    void SetFile(const string &filename) {
        file = filename;
    }

    void SetLine(int line_number) {
        line = line_number;
    }

private:
    ostream &os;
    bool log_line = false;
    bool log_file = false;
    string file;
    int line;
};

#define LOG(logger, message)   \
    logger.SetFile(__FILE__);  \
    logger.SetLine(__LINE__);  \
    logger.Log(message);
