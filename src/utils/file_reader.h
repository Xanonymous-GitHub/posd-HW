#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class FileNotOpenableException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FileReader {
private:
    const std::string _filePath;

public:
    FileReader(const std::string &filePath) : _filePath(filePath) {}

    std::string read() const {
        std::ifstream ifs{_filePath, std::ios::in};

        if (!ifs.is_open()) {
            throw FileNotOpenableException{"Failed to open file."};
        }

        std::stringstream ss;
        ss << ifs.rdbuf();

        const std::string result(ss.str());
        ifs.close();

        return result;
    }
};
