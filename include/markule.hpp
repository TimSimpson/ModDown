// --------------------------------------------------------------------
// markule
// --------------------------------------------------------------------
//      Markule is a tool that takes a directory representing a module
//      of C++ code with MarkDown comments and translates it to a
//      single MarkDown file with inline C++ code.
//
//      This allows you to write header files which read like
//      documentation but remain seperated, while offering a combined
//      view that can be rendered as HTML or otherwise styled.
// --------------------------------------------------------------------
#ifndef FILE_MARKULE_HPP
#define FILE_MARKULE_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <gsl/gsl>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>

namespace markule {


// --------------------------------------------------------------------
// Line
// --------------------------------------------------------------------
//      Represents a line of text.
// --------------------------------------------------------------------
class Line {
public:
    Line(const std::string & line);

    bool class_keyword() const;

    bool starts_with_doc_line() const;

    // True if the line starts with the given text.
    bool starts_with(const gsl::cstring_span<> text) const;

    // True if the line ends with the given text.
    bool ends_with(const gsl::cstring_span<> text) const;

    // Removes "// " from the text.
    std::string strip_comment_slashes() const;

    // Just returns the text.
    std::string text() const;

    // Special }; at start of line.
    bool end_class_marker() const;

    // Has "// end-doc"
    bool end_marker() const;

private:
    std::string line;
};

// --------------------------------------------------------------------
// Reader
// --------------------------------------------------------------------
//      Reads from a file.
// --------------------------------------------------------------------

class Reader {
public:
    Reader(const boost::filesystem::path & path);

    boost::optional<Line> read();

private:
    int line_count;
    std::ifstream file;
};

enum class TokenType {
    none,
    section_header,
    section_text,
    code
};

struct Token {
    TokenType type;
    std::string text;

    Token()
    :   type(TokenType::none),
        text()
    {}

    Token(TokenType type, const std::string & text)
    :   type(type), text(text) {
    }

    operator bool() const {
        return type != TokenType::none;
    }
};

enum class Mode {
    outer_space,
    section_header,
    section_text,
    unknown_code,
    class_code,
    nonclass_code,
};

class Tokenizer {
public:
    Tokenizer();

    Token read(const Line & line);

private:
    Mode m;
    int indent_level;
    std::stringstream text;
};

std::vector<Token> read_file(const boost::filesystem::path path);

}   // end namespace

#endif