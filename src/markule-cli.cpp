#include <boost/filesystem.hpp>
#include <markule.hpp>

namespace fs = boost::filesystem;

using namespace markule;

std::string str(TokenType t) {
    switch(t) {
        case TokenType::none:
            return "none";
        case TokenType::section_header:
            return "section_header";
        case TokenType::section_text:
            return "section_text";
        case TokenType::code:
            return "code";
        default:
            return "...?!";
    }
}


int main() {
    fs::path p{"include/markule.hpp"};

    auto tokens = markule::read_file(p);

    int header_depth = 0;
    for (const auto & t : tokens) {
        switch(t.type) {
            case TokenType::none:
                std::cout << "                I don't know what this is.";
                break;
            case TokenType::section_header:
                std::cout << std::string(header_depth, '#') << " "
                          << t.text << "\n\n";
                break;
            case TokenType::section_text:
                std::cout << t.text << "\n\n";
                break;
            case TokenType::code:
                std::cout << "```c++\n" << t.text << "\n```\n\n";
                break;
            default:
                break;
        }
    }

}
