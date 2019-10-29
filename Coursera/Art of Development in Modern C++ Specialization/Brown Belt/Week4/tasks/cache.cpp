#include "Common.h"

#include <unordered_map>
#include <algorithm>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
            shared_ptr<IBooksUnpacker> books_unpacker,
            const Settings &settings
    ) : settings(settings), books_unpacker(move(books_unpacker)) {}

    BookPtr GetBook(const string &book_name) override {
        lock_guard lock(m);
        auto book = ObtainBook(book_name);
        FitMemory();
        return book;
    }

private:

    BookPtr ObtainBook(const string &book_name) {
        ++current_max_rang;
        optional<BookPtr> book = FindBook(book_name);
        if (!book.has_value()) {
            book = books_unpacker->UnpackBook(book_name);
            cached_books[book_name] = {current_max_rang, *book};
            current_memory += (*book)->GetContent().size();
        }
        return *book;
    }

    optional<BookPtr> FindBook(const string &book_name) {
        if (auto cached_book = cached_books.find(book_name); cached_book != end(cached_books)) {
            cached_book->second.rang = current_max_rang;
            return cached_book->second.book;
        }
        return {};
    }

    void FitMemory() {
        while (current_memory > settings.max_memory) {
            FindAndDeleteLRU();
        }
    }

    void FindAndDeleteLRU() {
        auto lru_it = std::min_element(
                begin(cached_books),
                end(cached_books),
                [](auto &lhs, auto &rhs) {
                    return lhs.second.rang < rhs.second.rang;
                }
        );
        current_memory -= lru_it->second.book->GetContent().size();
        if (lru_it != end(cached_books))
            cached_books.erase(lru_it);
    }

private:
    using Rang = size_t;

    struct Node {
        Rang rang;
        BookPtr book;
    };

    Settings settings;
    shared_ptr<IBooksUnpacker> books_unpacker;
    unordered_map<string, Node> cached_books;
    size_t current_max_rang = 0;
    size_t current_memory = 0;
    mutex m;
};


unique_ptr<ICache> MakeCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const ICache::Settings &settings
) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}