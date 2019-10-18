#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> sentences;
    Sentence<Token> sentence;

    auto it = tokens.begin();
    while (it != tokens.end()) {
        bool is_punct = it->IsEndSentencePunctuation();
        if (is_punct) {
            do {
                sentence.push_back(move(*it));
                ++it;
            } while (it != end(tokens) && it->IsEndSentencePunctuation());
            sentences.push_back(move(sentence));
            sentence.clear();
        } else {
            sentence.push_back(move(*it));
            ++it;
        }
    }

    if (!sentence.empty())
        sentences.push_back(move(sentence));

    return move(sentences);
}