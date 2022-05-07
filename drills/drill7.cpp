
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

struct Token {
    char kind;
    double value;
    string name;

    // all token must have a kind property but not value or name
    //defining three constructors
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, double val) : kind(ch), value(val) {}
    Token(char ch, string s) : kind(ch), name(s) {}
};

class Token_stream {
    bool full;
    Token buffer;
public:
    //Constructor
    Token_stream() : full(0), buffer(0) {}

    Token get();

    void unget(Token t) {
        buffer = t;
        full = true;
    }

    void ignore(char);
};

//abbreviations
const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = '?';
const char exponent = '^';


Token Token_stream::get() {
    // Checking the buffer
    if (full) {
        full = false;
        return buffer;
    }
    // Processing next token
    char ch;
    cin >> ch;
    switch (ch) {
        case quit:
        case square_root:
        case exponent:
        case let:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case ';':
        case '=':
            return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            //in case of digits we will take all numbers
            cin.putback(ch);
            double val;
            cin >> val;
            return Token(number, val);
        }
        default:
            if (isalpha(ch)) {
                //accumulate the alpha chars
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                cin.putback(ch);
                if (s == "let") return Token(let);
                if (s == "exit") return Token(quit);
                return Token(name, s);
            }
            // if wrong expression insert an error
            error("Bad token");
    }
}

void Token_stream::ignore(char c) {
    //ignore token up to first of c
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin >> ch)
        if (ch == c) return;
}

//struct of variable name,value
struct Variable {
    string name;
    double value;

    Variable(string n, double v) : name(n), value(v) {}
};

vector<Variable> names;

double get_value(string s) {
    //Retrieves a variable value
    // We changed the condition operator from <= to only < to avoid index out of bounds
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined name ", s);
}

void set_value(string s, double d) {
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool is_declared(string s) {
    //Check if given variable name has declared or not
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

Token_stream ts;

double expression();

double primary() {
    // Evaluate the expressions from the user
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("'(' expected");
            // Here we added " return d " to avoid getting into the other cases
            return d;
        }
        case '-':
            return -primary();
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        case square_root: {
            double d = primary();
            if (d < 0) error("Can't sqrt() Imaginary #");
            return sqrt(d);
        }
        default:
            error("primary expected");
    }
}

// function to calculate power of a number taking a base and exponent
double pow(double base, double exp) {
    int x = narrow_cast<int>(exp);

    double n = 1;
    double b;

    if (exp < 0) {
        b = 1 / base;
        x *= -1;
    } else
        b = base;

    for (int i = 0; i < x; ++i)
        n *= b;

    return n;
}

double secondary() {
    //evaluate string to calculate pow of a number
    double left = primary();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '^':
                return pow(left, primary());
            default:
                ts.unget(t);
                return left;
        }
    }
}

double term() {
    //Evaluate string to calculate * or /

    //BUG#3 left from primary to secondary
    double left = secondary();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= primary();
                break;
            case '/': {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                break;
            }
            default:
                ts.unget(t);
                return left;
        }
    }
}

double expression() {
    //Evaluating expression to calculate + or -
    double left = term();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.unget(t);
                return left;
        }
    }
}

double declaration() {
    //check if the vars is declared in the vector or not
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string name = t.name;
    if (is_declared(name)) error(name, " declared twice");
    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", name);
    double d = expression();
    names.push_back(Variable(name, d));
    return d;
}

double statement() {
    //Reading statement from the user
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration();
        default:
            ts.unget(t);
            return expression();
    }
}

void clean_up_mess() {
    //delete buffer
    ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate() {
    //adding constant to vectors
    names.push_back(Variable("pi", 3.14159));
    names.push_back(Variable("e", 2.718281828));
    names.push_back(Variable("k", 1000));
    //Calculating the statements
    while (true)
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get();
            if (t.kind == quit) return;
            ts.unget(t);
            cout << result << statement() << endl;
        }
        catch (runtime_error &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

int main()
//Running the first method
try {
    calculate();
    return 0;
}
catch (exception &e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >> c && c != ';');
    return 1;
}
catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';');
    return 2;
}
