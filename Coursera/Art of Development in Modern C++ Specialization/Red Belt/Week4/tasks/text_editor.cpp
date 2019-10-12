#include <string>
#include <list>

using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() = default;

    void Left() {
        if (cursor != str.begin())
            --cursor;
    }

    void Right() {
        if (cursor != str.end())
            ++cursor;
    }

    void Insert(char token) {
        str.insert(cursor, token);
    }

    void Cut(size_t tokens = 1) {
        Copy(tokens);
        cursor = str.erase(cursor, advance(str, cursor, tokens));
    }

    void Copy(size_t tokens = 1) {
        buffer = {cursor, advance(str, cursor, tokens)};
    }

    void Paste() {
        str.insert(cursor, buffer.begin(), buffer.end());
    }

    string GetText() const {
        return {str.begin(), str.end()};
    }

private:
    list<char> str;
    list<char>::iterator cursor = str.end();
    string buffer;

    template<class Container, class Iterator = typename Container::iterator>
    Iterator advance(const Container &c, Iterator iter, size_t n) {
        while (iter != c.end() && n > 0) {
            ++iter;
            --n;
        }
        return iter;
    }
};