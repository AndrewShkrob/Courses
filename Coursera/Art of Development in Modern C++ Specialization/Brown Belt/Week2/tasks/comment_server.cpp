#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

using namespace std;

enum class HttpCode {
    Ok = 200,
    NotFound = 404,
    Found = 302,
};

string to_string(const HttpCode &code) {
    switch (code) {
        case HttpCode::Ok:
            return "OK";
        case HttpCode::NotFound:
            return "Not found";
        case HttpCode::Found:
            return "Found";
        default:
            throw invalid_argument("");
    }
}

class HttpResponse {
public:
    explicit HttpResponse(HttpCode code = HttpCode::NotFound) : code(code) {};

    HttpResponse &AddHeader(string name, string value) {
        headers.emplace_back(move(name), move(value));
        return *this;
    }

    HttpResponse &SetContent(string a_content) {
        content = move(a_content);
        return *this;
    }

    HttpResponse &SetCode(HttpCode a_code) {
        code = a_code;
        return *this;
    }

    friend ostream &operator<<(ostream &output, const HttpResponse &resp);

private:
    using HttpHeader = pair<string, string>;
    HttpCode code;
    vector<HttpHeader> headers;
    string content;
};

ostream &operator<<(ostream &output, const HttpResponse &resp) {
    output << "HTTP/1.1 " << to_string(static_cast<int>(resp.code)) << " " << to_string(resp.code) << "\n";
    for (const auto &[header_name, header_val] : resp.headers) {
        output << header_name << ": " << header_val << "\n";
    }
    if (!resp.content.empty()) {
        output << "Content-Length: " << resp.content.size() << "\n\n";
        output << resp.content;
    } else {
        output << "\n";
    }
    return output;
}

struct HttpRequest {
    string method, path, body;
    map<string, string> get_params;
};

class CommentServer {
private:
    struct LastCommentInfo {
        size_t user_id, consecutive_count;
    };
private:
    vector<vector<string>> comments_;
    std::optional<LastCommentInfo> last_comment;
    unordered_set<size_t> banned_users;

public:
    HttpResponse ServeRequest(const HttpRequest &req) {
        HttpResponse result;
        if (req.method == "POST") {
            result = move(Post(req));
        } else if (req.method == "GET") {
            result = move(Get(req));
        }
        return result;
    }

private:
    pair<string, string> SplitBy(const string &what, const string &by) {
        size_t pos = what.find(by);
        if (by.size() < what.size() && pos < what.size() - by.size()) {
            return {what.substr(0, pos), what.substr(pos + by.size())};
        } else {
            return {what, {}};
        }
    }

    template<typename T>
    T FromString(const string &s) {
        T x;
        istringstream is(s);
        is >> x;
        return x;
    }

    pair<size_t, string> ParseIdAndContent(const string &body) {
        auto[id_string, content] = SplitBy(body, " ");
        return {FromString<size_t>(id_string), content};
    }

    HttpResponse Post(const HttpRequest &req) {
        HttpResponse result;
        if (req.path == "/add_user") {
            result = move(AddUser(req));
        } else if (req.path == "/add_comment") {
            result = move(AddComment(req));
        } else if (req.path == "/checkcaptcha") {
            result = move(CheckCaptcha(req));
        } else {
            result.SetCode(HttpCode::NotFound);
        }
        return result;
    }

    HttpResponse Get(const HttpRequest &req) {
        HttpResponse result;
        if (req.path == "/user_comments") {
            result = move(UserComments(req));
        } else if (req.path == "/captcha") {
            result = move(Captcha(req));
        } else {
            result.SetCode(HttpCode::NotFound);
        }
        return result;
    }

    HttpResponse AddUser(const HttpRequest &) {
        HttpResponse result;
        comments_.emplace_back();
        result.SetCode(HttpCode::Ok).SetContent(to_string(comments_.size() - 1));
        return result;
    }

    HttpResponse AddComment(const HttpRequest &req) {
        HttpResponse result;
        auto[user_id, comment] = ParseIdAndContent(req.body);

        if (!last_comment || last_comment->user_id != user_id) {
            last_comment = LastCommentInfo{user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
            banned_users.insert(user_id);
        }

        if (banned_users.count(user_id) == 0) {
            comments_[user_id].push_back(string(comment));
            result.SetCode(HttpCode::Ok);
        } else {
            result.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
        }
        return result;
    }

    HttpResponse CheckCaptcha(const HttpRequest &req) {
        HttpResponse result;
        if (auto[id, response] = ParseIdAndContent(req.body); response == "42") {
            banned_users.erase(id);
            if (last_comment && last_comment->user_id == id) {
                last_comment.reset();
            }
            result.SetCode(HttpCode::Ok);
        } else {
            result.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
        }
        return result;
    }

    HttpResponse UserComments(const HttpRequest &req) {
        HttpResponse result;
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string response;
        for (const string &c : comments_[user_id]) {
            response += c + '\n';
        }
        result.SetCode(HttpCode::Ok).SetContent(response);
        return result;
    }

    HttpResponse Captcha(const HttpRequest &req) {
        HttpResponse result;
        result.SetCode(HttpCode::Ok).SetContent(
                "What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
        return result;
    }
};