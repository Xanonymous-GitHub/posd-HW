#pragma once

#include <regex>
#include <string>
#include <unordered_set>

class Scanner {
private:
    std::string input_;
    std::string::size_type index_{0};

    static const std::unordered_set<std::string> COLLECTABLE_TOKENS_;
    static const std::regex COLLECTABLE_TOKEN_REG_EXPS_;
    static const std::regex COLLECTABLE_FLOATING_POINT_TOKEN_REG_EXPS_;
    static const std::regex BLANK_CHAR_REG_EXPS_;

    void skipBlankChars_() {
        while (index_ < input_.size() && std::regex_match(input_.substr(index_, 1), BLANK_CHAR_REG_EXPS_)) {
            ++index_;
        }
    }

    std::string scanNextCollectableTokenByRegEx_(const std::regex &regEx) {
        if (isDone()) {
            throw ScannerTouchedTheEdgeException{"Scanner is done."};
        }

        auto match = std::smatch{};

        if (std::regex_search(input_.cbegin() + index_, input_.cend(), match, regEx)) {
            index_ += match.length() + match.position();
            return match.str();
        }

        return match.str();
    }

public:
    Scanner(const std::string &input) : input_{input} {}

    std::string next() {
        skipBlankChars_();
        auto scannedToken = scanNextCollectableTokenByRegEx_(COLLECTABLE_TOKEN_REG_EXPS_);
        if (scannedToken.empty()) {
            throw ScannerTouchedTheEdgeException{"Could not find any general token."};
        }
        return scannedToken;
    }

    double nextDouble() {
        skipBlankChars_();
        auto scannedToken = scanNextCollectableTokenByRegEx_(COLLECTABLE_FLOATING_POINT_TOKEN_REG_EXPS_);
        if (scannedToken.empty()) {
            throw ScannerTouchedTheEdgeException{"Could not find any float token."};
        }
        return std::stod(scannedToken);
    }

    bool isDone() {
        return index_ >= input_.size();
    }

    class ScannerTouchedTheEdgeException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};

const std::unordered_set<std::string> Scanner::COLLECTABLE_TOKENS_ = {
    "Circle",
    "Rectangle",
    "Triangle",
    "CompoundShape",
    "Vector",
    "(",
    ")",
    ",",
};

const std::regex Scanner::COLLECTABLE_TOKEN_REG_EXPS_ = std::regex{
    R"((Circle|Rectangle|Triangle|CompoundShape|Vector|\(|\)|,))",
    std::regex_constants::ECMAScript | std::regex_constants::optimize,
};

const std::regex Scanner::COLLECTABLE_FLOATING_POINT_TOKEN_REG_EXPS_ = std::regex{
    R"((\d+\.\d+|\d+))",
    std::regex_constants::ECMAScript | std::regex_constants::optimize,
};

const std::regex Scanner::BLANK_CHAR_REG_EXPS_ = std::regex{
    R"((\s+))",
    std::regex_constants::ECMAScript | std::regex_constants::optimize,
};
