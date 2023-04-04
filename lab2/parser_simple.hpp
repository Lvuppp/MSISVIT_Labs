//----------------------------------------------------------------------------
// copyright 2012, 2013, 2014 Keean Schupke
// compile with -std=gnu++11 
// parser_simple.hpp

#ifndef PARSER_SIMPLE_HPP
#define PARSER_SIMPLE_HPP

#include <istream>
#include <stdexcept>

using namespace std;

//----------------------------------------------------------------------------
// Character Predicates

struct char_pred {
    string const name;
    char_pred(string const n) : name(n) {}
    virtual bool operator() (int const c) const = 0;
};

struct is_space : public char_pred  {
    is_space() : char_pred("space") {}
    virtual bool operator() (int const c) const override {
        return ::isspace(c) != 0;
    }
} is_space;

struct is_digit : public char_pred {
    is_digit() : char_pred("digit") {}
    virtual bool operator() (int const c) const override {
        return ::isdigit(c) != 0;
    }
} is_digit;

struct is_upper : public char_pred {
    is_upper() : char_pred("uppercase") {}
    virtual bool operator() (int const c) const override {
        return ::isupper(c) != 0;
    }
} is_upper;

struct is_lower : public char_pred {
    is_lower() : char_pred("lowercase") {}
    virtual bool operator() (int const c) const override {
        return ::islower(c) != 0;
    }
} is_lower;

struct is_alpha : public char_pred {
    is_alpha() : char_pred("alphabetic") {}
    virtual bool operator() (int const c) const override {
        return ::isalpha(c) != 0;
    }
} is_alpha;

struct is_alnum : public char_pred {
    is_alnum() : char_pred("alphanumeric") {}
    virtual bool operator() (int const c) const override {
        return ::isalnum(c) != 0;
    }
} is_alnum;

struct is_print : public char_pred {
    is_print() : char_pred("printable") {}
    virtual bool operator() (int const c) const override {
        return ::isprint(c) != 0;
    }
} is_print;

class is_char : public char_pred {
    int const k;

public:
    explicit is_char(char const c)
        : k(c), char_pred("'" + string(1, c) + "'")  {}
    virtual bool operator() (int const c) const override {
        return k == c;
    }
};

class is_either : public char_pred {
    char_pred const &a;
    char_pred const &b;

public:
    is_either(char_pred const &a, char_pred const& b)
        : a(a), b(b), char_pred("(" + a.name + " or " + b.name + ")") {}
    bool operator() (int const c) const {
        return a(c) || b(c);
    }
};

class is_not : public char_pred {
    char_pred const &a;

public:
    explicit is_not(char_pred const &a) 
        : a(a), char_pred("~" + a.name) {}
    bool operator() (int const c) const {
        return !a(c);
    }
};

is_char const is_minus('-');

//----------------------------------------------------------------------------
// Recursive Descent Parser

struct parse_error : public runtime_error {
    int const row;
    int const col;
    int const sym;
    string const exp;
    parse_error(string const& what, int row, int col, string exp, int sym)
        : runtime_error(what), row(row), col(col), exp(move(exp)), sym(sym) {}
};

class parser {
    streambuf *in;
    int count;
    int row;
    int col;
    int sym;

    void error(string const& err, string const exp) {
        throw parse_error(err, row, col, exp, sym);
    }

    void next() {
        sym = in->sgetc();
        in->snextc();
        ++count;
        if (sym == '\n') {
            ++row;
            col = 1;
        } else if (::isprint(sym)) {
            ++col;
        }
    }

public:
    parser(istream &f) : in(f.rdbuf()), count(0), row(1), col(1), sym(in->sbumpc()) {}

protected:
    int get_col() {
        return col;
    }
    
    int get_row() {
        return row;
    }

    int get_count() {
        return count;
    }
    
    bool accept(char_pred const &t, string *s = nullptr) {
        if (!t(sym)) {
            return false;
        }
        if (s != nullptr) {
            s->push_back(sym);
        }
        next();
        return true;
    }

    bool expect(char_pred const &t, string *s = nullptr) {
        if (!t(sym)) {
            error("expected", t.name);   
        }
        if (s != nullptr) {
            s->push_back(sym);
        }
        next();
        return true;
    }

    bool space(string *s = nullptr) {
        if (accept(is_space)) {
            if (s != nullptr) {
                s->push_back(' ');
            }
            while (accept(is_space));
            return true;
        }
        return false;
    }

    bool number(string *s = nullptr) {
        if (accept(is_digit, s)) {
            while (accept(is_digit, s));
            return true;
        }
        return false;
    }

    bool signed_number(string *s = nullptr) {
        return accept(is_minus, s), number(s);
    }

    bool name(string *s = nullptr) {
        if (accept(is_alpha, s)) {
            while (accept(is_alnum, s));
            return true;
        }
        return false;
    }
};

#endif // PARSER_SIMPLE_HPP
