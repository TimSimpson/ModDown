#include <markule.hpp>
#include <cctype>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/optional.hpp>


namespace markule {


Line::Line(const std::string & line)
:   line(line)
{}

bool Line::class_keyword() const {
    const auto f = line.find("class");
    return f != std::string::npos;
}

bool Line::starts_with_doc_line() const {
    return starts_with("// --");
}


bool Line::starts_with(const gsl::cstring_span<> text) const {
    return boost::starts_with(line, text);
}

// bool Line::ends_with(const gsl::cstring_span<> text) const;

std::string Line::strip_comment_slashes() const {
    int index = 0;
    if (line.length() >= 2 && line[0] == '/' && line[1] == '/') {
        index = 2;
    }
    while (index < line.length() && std::isspace(line[index])) {
        ++ index;
    }
    return line.substr(index);
}

std::string Line::text() const {
    return line;
}


bool Line::end_class_marker() const {
    const auto f = line.find("};");
    return f != std::string::npos;
}

bool Line::end_marker() const {
    return starts_with("// end-doc");
}

Reader::Reader(const boost::filesystem::path & path)
:   file(path.string())
{}


boost::optional<Line> Reader::read() {
    std::string line;
    if (!std::getline(file, line)) {
        return boost::none;
    } else {
        return Line(line);
    }
}

Tokenizer::Tokenizer()
:   line_number(0),
    m(Mode::outer_space),
    indent_level(0),
    text()
{}

Token Tokenizer::read(const Line & l) {
    ++ line_number;
    switch(m) {
        case Mode::outer_space:
            if (l.starts_with_doc_line()) {
                m = (line_number <= 2
                        ? Mode::big_header : Mode::section_header);
                text.str("");
                text.clear();
            }
            return Token{};
        case Mode::big_header:
        case Mode::section_header:
            if (l.starts_with_doc_line()) {
                const Token t{
                    (m == Mode::big_header
                        ? TokenType::big_header : TokenType::section_header),
                    text.str()
                };
                m = Mode::section_text;
                text.str("");
                text.clear();
                return t;
            } else {
                text << l.strip_comment_slashes();
                return Token{};
            }
        case Mode::section_text:
            if (l.starts_with_doc_line()) {
                m = Mode::unknown_code;
                const Token t{TokenType::section_text, text.str() };
                text.str("");
                text.clear();
                return t;
            } else {
                text << l.strip_comment_slashes();
                return Token{};
            }
        case Mode::unknown_code:
            if (l.class_keyword()) {
                m = Mode::class_code;
            } else {
                m = Mode::nonclass_code;
            }
            text << "    " << l.text();
            return Token{};
        case Mode::class_code:
        case Mode::nonclass_code:
            if (m == Mode::class_code && l.end_class_marker()) {
                text << "    " << l.text();
                m = Mode::outer_space;
                const Token t{TokenType::code, text.str()};
                text.str("");
                text.clear();
                return t;
            } else if (l.end_marker()) {
                m = Mode::outer_space;
                const Token t{TokenType::code, text.str()};
                text.str("");
                text.clear();
                return t;
            } else if (l.starts_with_doc_line()) {
                m = Mode::section_header;
                const Token t{TokenType::code, text.str()};
                text.str("");
                text.clear();
                return t;
            } else {
                text << "    " << l.text();
                return Token{};
            }
        default:
            throw std::exception{};
    }
}

std::vector<Token> read_header_file(const boost::filesystem::path path) {
    Reader reader(path);

    Tokenizer tokenizer;

    boost::optional<Line> line;

    std::vector<Token> tokens;

    while(line = reader.read()) {
        const Token t = tokenizer.read(line.get());
        if (t) {
            tokens.push_back(t);
        }
    }

    tokens.push_back(Token{TokenType::eof, ""});
    return tokens;
}



}   // end namespace
