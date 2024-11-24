#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

enum TokenType
{
    // Data types
    T_INT,
    T_FLOAT,
    T_DOUBLE,
    T_STRING,
    T_BOOL,
    T_CHAR,

    // Boolean literals
    T_TRUE,
    T_FALSE,

    // Identifiers and literals
    T_ID,  // Variable or function names
    T_NUM, // Numeric literals

    // Keywords
    T_IF,
    T_ELSE,
    T_RETURN,
    T_WHILE,
    T_FOR,
    T_SWITCH,
    T_CASE,
    T_BREAK,
    T_CONTINUE,

    // Assignment
    T_ASSIGN, // =

    // Arithmetic operators
    T_PLUS,  // +
    T_MINUS, // -
    T_MUL,   // *
    T_DIV,   // /

    // Comparison operators
    T_EQUAL_EQUAL,   // ==
    T_NOT_EQUAL,     // !=
    T_GREATER,       // >
    T_LESS,          // <
    T_GREATER_EQUAL, // >=
    T_LESS_EQUAL,    // <=

    // Logical operators
    T_AND, // &&
    T_OR,  // ||

    // Parentheses and braces
    T_LPAREN, // (
    T_RPAREN, // )
    T_LBRACE, // {
    T_RBRACE, // }

    // Other tokens
    T_SEMICOLON, // ;
    T_COLON,     // :
    T_EOF,       // End of file

    // Custom tokens (if needed for your specific language or project)
    T_AGAR, // Custom keyword
    T_PRINT // Custom print function
};

struct Token
{
    TokenType type;
    string value;
    int line;
    Token(TokenType type, const string &value, int line) : type(type), value(value), line(line) {}
};

struct Symbol
{
    TokenType type;
    string name;
    string value;
    int line;

    Symbol() : type(T_INT), name(""), value(""), line(0) {}

    Symbol(TokenType t, const string &n, const string &v, int l)
        : type(t), name(n), value(v), line(l) {}
};

class SymbolTable
{
private:
    unordered_map<string, Symbol> table;

public:
    bool insert(const string &name, const Symbol &symbol)
    {
        if (table.find(name) != table.end())
        {
            return false; // Symbol already exists
        }
        table[name] = symbol;
        return true;
    }

    bool update(const string &name, const string &value)
    {
        if (table.find(name) == table.end())
        {
            return false; // Symbol doesn't exist
        }
        table[name].value = value;
        return true;
    }

    Symbol *lookup(const string &name)
    {
        auto it = table.find(name);
        if (it != table.end())
        {
            return &(it->second);
        }
        return nullptr;
    }

    void display()
    {
        cout << "\nSymbol Table Contents:" << endl;
        cout << "Name\tType\tValue\tLine" << endl;
        cout << "--------------------------------" << endl;
        for (const auto &entry : table)
        {
            const Symbol &symbol = entry.second;
            cout << symbol.name << "\t";

            string typeStr;
            switch (symbol.type)
            {
            case T_INT:
                typeStr = "int";
                break;
            case T_FLOAT:
                typeStr = "float";
                break;
            case T_DOUBLE:
                typeStr = "double";
                break;
            case T_STRING:
                typeStr = "string";
                break;
            case T_BOOL:
                typeStr = "bool";
                break;
            case T_CHAR:
                typeStr = "char";
                break;
            default:
                typeStr = "unknown";
                break;
            }

            cout << typeStr << "\t" << symbol.value << "\t" << symbol.line << endl;
        }
    }
};

class Lexer
{
private:
    string src;
    size_t pos;
    int line;

public:
    Lexer(const string &src)
    {
        this->src = src;
        this->pos = 0;
        this->line = 1;
    }

    vector<Token> tokenize()
    {
        vector<Token> tokens;
        while (pos < src.size())
        {
            char current = src[pos];

            // Handle whitespace and new lines
            if (isspace(current))
            {
                if (current == '\n')
                    line++;
                pos++;
                continue;
            }

            // Handle numeric literals
            if (isdigit(current))
            {
                tokens.push_back(Token{T_NUM, consumeNumber(), line});
                continue;
            }

            // Handle keywords and identifiers
            if (isalpha(current))
            {
                string word = consumeWord();
                if (word == "int")
                    tokens.push_back(Token{T_INT, word, line});
                else if (word == "float")
                    tokens.push_back(Token{T_FLOAT, word, line});
                else if (word == "double")
                    tokens.push_back(Token{T_DOUBLE, word, line});
                else if (word == "string")
                    tokens.push_back(Token{T_STRING, word, line});
                else if (word == "bool")
                    tokens.push_back(Token{T_BOOL, word, line});
                else if (word == "true")
                    tokens.push_back(Token{T_TRUE, word, line});
                else if (word == "false")
                    tokens.push_back(Token{T_FALSE, word, line});
                else if (word == "char")
                    tokens.push_back(Token{T_CHAR, word, line});
                else if (word == "if")
                    tokens.push_back(Token{T_IF, word, line});
                else if (word == "else")
                    tokens.push_back(Token{T_ELSE, word, line});
                else if (word == "return")
                    tokens.push_back(Token{T_RETURN, word, line});
                else if (word == "while")
                    tokens.push_back(Token{T_WHILE, word, line});
                else if (word == "for")
                    tokens.push_back(Token{T_FOR, word, line});
                else if (word == "switch")
                    tokens.push_back(Token{T_SWITCH, word, line});
                else if (word == "case")
                    tokens.push_back(Token{T_CASE, word, line});
                else if (word == "break")
                    tokens.push_back(Token{T_BREAK, word, line});
                else if (word == "continue")
                    tokens.push_back(Token{T_CONTINUE, word, line});
                else if (word == "agar")
                    tokens.push_back(Token{T_AGAR, word, line});
                else if (word == "print")
                    tokens.push_back(Token{T_PRINT, word, line});
                else
                    tokens.push_back(Token{T_ID, word, line});
                continue;
            }

            // Handle string literals
            if (current == '"')
            {
                tokens.push_back(Token{T_STRING, consumeStringLiteral(), line});
                continue;
            }

            // Handle char literals
            if (current == '\'')
            {
                tokens.push_back(Token{T_CHAR, consumeCharLiteral(), line});
                continue;
            }

            // Handle comments
            if (current == '/' && peekNext() == '/')
            {
                consumeComment();
                continue;
            }

            // Handle operators and other symbols
            switch (current)
            {
            case '=':
                if (peekNext() == '=') // Handle ==
                {
                    pos++;
                    tokens.push_back(Token{T_EQUAL_EQUAL, "==", line});
                }
                else
                {
                    tokens.push_back(Token{T_ASSIGN, "=", line});
                }
                break;
            case '!':
                if (peekNext() == '=') // Handle !=
                {
                    pos++;
                    tokens.push_back(Token{T_NOT_EQUAL, "!=", line});
                }
                else
                {
                    cout << "Unexpected character " << current << " at line " << line << endl;
                    exit(1);
                }
                break;
            case '&':
                if (peekNext() == '&') // Handle &&
                {
                    pos++;
                    tokens.push_back(Token{T_AND, "&&", line});
                }
                else
                {
                    cout << "Unexpected character " << current << " at line " << line << endl;
                    exit(1);
                }
                break;
            case '|':
                if (peekNext() == '|') // Handle ||
                {
                    pos++;
                    tokens.push_back(Token{T_OR, "||", line});
                }
                else
                {
                    cout << "Unexpected character " << current << " at line " << line << endl;
                    exit(1);
                }
                break;
            case '>':
                if (peekNext() == '=') // Handle >=
                {
                    pos++;
                    tokens.push_back(Token{T_GREATER_EQUAL, ">=", line});
                }
                else
                {
                    tokens.push_back(Token{T_GREATER, ">", line});
                }
                break;
            case '<':
                if (peekNext() == '=') // Handle <=
                {
                    pos++;
                    tokens.push_back(Token{T_LESS_EQUAL, "<=", line});
                }
                else
                {
                    tokens.push_back(Token{T_LESS, "<", line});
                }
                break;
            case '+':
                tokens.push_back(Token{T_PLUS, "+", line});
                break;
            case '-':
                tokens.push_back(Token{T_MINUS, "-", line});
                break;
            case '*':
                tokens.push_back(Token{T_MUL, "*", line});
                break;
            case '/':
                tokens.push_back(Token{T_DIV, "/", line});
                break;
            case '(':
                tokens.push_back(Token{T_LPAREN, "(", line});
                break;
            case ')':
                tokens.push_back(Token{T_RPAREN, ")", line});
                break;
            case '{':
                tokens.push_back(Token{T_LBRACE, "{", line});
                break;
            case '}':
                tokens.push_back(Token{T_RBRACE, "}", line});
                break;
            case ';':
                tokens.push_back(Token{T_SEMICOLON, ";", line});
                break;
            case ':':
                tokens.push_back(Token{T_COLON, ":", line});
                break;
            default:
                cout << "Unexpected character " << current << " at line " << line << endl;
                exit(1);
            }
            pos++;
        }

        tokens.push_back(Token{T_EOF, "", line});
        return tokens;
    }

    string consumeNumber()
    {
        size_t start = pos;
        while (pos < src.size() && isdigit(src[pos]))
            pos++;
        if (pos < src.size() && src[pos] == '.')
        {
            pos++;
            while (pos < src.size() && isdigit(src[pos]))
                pos++;
        }
        return src.substr(start, pos - start);
    }

    string consumeWord()
    {
        size_t start = pos;
        while (pos < src.size() && isalnum(src[pos]))
            pos++;
        return src.substr(start, pos - start);
    }

    string consumeStringLiteral()
    {
        pos++;
        size_t start = pos;
        while (pos < src.size() && src[pos] != '"')
            pos++;
        pos++;
        return src.substr(start, pos - start - 1);
    }

    string consumeCharLiteral()
    {
        pos++;
        if (pos >= src.size() || src[pos] == '\'')
        {
            cout << "Syntax error: empty or invalid char literal at line " << line << endl;
            exit(1);
        }

        char literal = src[pos];
        pos++;

        if (pos >= src.size() || src[pos] != '\'')
        {
            cout << "Syntax error: expected closing single quote at line " << line << endl;
            exit(1);
        }

        pos++;
        return string(1, literal);
    }

    void consumeComment()
    {
        pos += 2;
        while (pos < src.size() && src[pos] != '\n')
        {
            pos++;
        }
    }

    char peekNext()
    {
        return pos + 1 < src.size() ? src[pos + 1] : '\0';
    }
};

class Parser
{
private:
    vector<Token> tokens;
    size_t pos;
    SymbolTable symbolTable;

public:
    Parser(const vector<Token> &tokens) : tokens(tokens), pos(0) {}

    void parseProgram()
    {
        while (tokens[pos].type != T_EOF)
        {
            parseStatement();
        }
        cout << "Parsing completed successfully! No Syntax Error" << endl;
        symbolTable.display();
    }

private:
    void parseStatement()
    {
        if (tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT || tokens[pos].type == T_DOUBLE ||
            tokens[pos].type == T_STRING || tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR)
        {
            parseDeclaration();
        }
        else if (tokens[pos].type == T_ID)
        {
            parseAssignment();
        }
        else if (tokens[pos].type == T_IF)
        {
            parseIfStatement();
        }
        else if (tokens[pos].type == T_WHILE)
        {
            parseWhileStatement();
        }
        else if (tokens[pos].type == T_FOR)
        {
            parseForStatement();
        }
        else if (tokens[pos].type == T_SWITCH)
        {
            parseSwitchStatement();
        }
        else if (tokens[pos].type == T_RETURN)
        {
            parseReturnStatement();
        }
        else if (tokens[pos].type == T_PRINT)
        {
            parsePrintStatement();
        }
        else if (tokens[pos].type == T_LBRACE)
        {
            parseBlock();
        }
        else
        {
            cout << "Syntax error: unexpected token " << tokens[pos].value << " on line " << tokens[pos].line << endl;
            exit(1);
        }
    }

    void parseWhileStatement()
    {
        expect(T_WHILE);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        expect(T_LBRACE);

        while (tokens[pos].type != T_RBRACE)
        {
            parseStatement();
        }

        expect(T_RBRACE);
    }

    void parseForStatement()
    {
        expect(T_FOR);
        expect(T_LPAREN);

        parseDeclaration();
        expect(T_SEMICOLON);    
        cout<<"Compile"<<endl;


        parseExpression();
        expect(T_SEMICOLON);

        parseAssignment();
        expect(T_RPAREN);

        expect(T_LBRACE);

        while (tokens[pos].type != T_RBRACE)
        {
            parseStatement();
        }

        expect(T_RBRACE);
    }

    void parseSwitchStatement()
    {
        expect(T_SWITCH);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        expect(T_LBRACE);

        while (tokens[pos].type == T_CASE)
        {
            parseCaseStatement();
        }

        expect(T_RBRACE);
    }

    void parseCaseStatement()
    {
        expect(T_CASE);
        parseExpression();
        expect(T_COLON);
        parseStatement();
    }

    void parseReturnStatement()
    {
        expect(T_RETURN);
        if (tokens[pos].type != T_SEMICOLON)
        {
            parseExpression();
        }
        expect(T_SEMICOLON);
    }

    void parseIfStatement()
    {
        expect(T_IF);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        expect(T_LBRACE);

        while (tokens[pos].type != T_RBRACE)
        {
            parseStatement();
        }

        expect(T_RBRACE);

        if (tokens[pos].type == T_ELSE)
        {
            expect(T_ELSE);
            expect(T_LBRACE);
            while (tokens[pos].type != T_RBRACE)
            {
                parseStatement();
            }
            expect(T_RBRACE);
        }
    }

    void parsePrintStatement()
    {
        expect(T_PRINT);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        expect(T_SEMICOLON);
    }

    void parseBlock()
    {
        expect(T_LBRACE);
        while (tokens[pos].type != T_RBRACE)
        {
            parseStatement();
        }
        expect(T_RBRACE);
    }

    void parseDeclaration()
    {
        TokenType varType = tokens[pos].type;
        expect(varType);

        // Store identifier token
        Token idToken = tokens[pos];
        expect(T_ID);

        expect(T_ASSIGN);

        // Store value token
        Token valueToken = tokens[pos];
        parseExpression();

        // Create and insert symbol
        Symbol symbol(varType, idToken.value, valueToken.value, idToken.line);
        if (!symbolTable.insert(idToken.value, symbol))
        {
            cout << "Error: Variable '" << idToken.value << "' already declared at line "
                 << idToken.line << endl;
            exit(1);
        }

        expect(T_SEMICOLON);
    }

    void parseAssignment()
    {
        // Store identifier token
        Token idToken = tokens[pos];
        expect(T_ID);

        // Check if variable exists
        Symbol *symbol = symbolTable.lookup(idToken.value);
        if (!symbol)
        {
            cout << "Error: Variable '" << idToken.value << "' not declared at line "
                 << idToken.line << endl;
            exit(1);
        }

        expect(T_ASSIGN);

        // Store new value
        Token valueToken = tokens[pos];
        parseExpression();

        // Update symbol table
        symbolTable.update(idToken.value, valueToken.value);

        expect(T_SEMICOLON);
    }

    void parseExpression()
    {
        // Parse the first operand (numbers, identifiers, booleans, or strings)
        if (tokens[pos].type == T_NUM ||
            tokens[pos].type == T_ID ||
            tokens[pos].type == T_TRUE ||
            tokens[pos].type == T_FALSE ||
            tokens[pos].type == T_STRING) // Handles strings
        {
            expect(tokens[pos].type);
        }
        else
        {
            cout << "Syntax error in expression on line " << tokens[pos].line << endl;
            exit(1);
        }

        // Handle binary and comparison operations
        while (pos < tokens.size() &&
               (tokens[pos].type == T_PLUS ||
                tokens[pos].type == T_MINUS ||
                tokens[pos].type == T_MUL ||
                tokens[pos].type == T_DIV ||
                tokens[pos].type == T_EQUAL_EQUAL ||  
                tokens[pos].type == T_NOT_EQUAL ||    
                tokens[pos].type == T_LESS ||         
                tokens[pos].type == T_GREATER ||      
                tokens[pos].type == T_LESS_EQUAL ||   
                tokens[pos].type == T_GREATER_EQUAL)) 
        {
            expect(tokens[pos].type); // Consume operator

            // Parse the next operand after the operator
            if (tokens[pos].type == T_NUM ||
                tokens[pos].type == T_ID ||
                tokens[pos].type == T_TRUE ||
                tokens[pos].type == T_FALSE ||
                tokens[pos].type == T_STRING) // Handles strings
            {
                expect(tokens[pos].type);
            }
            else
            {
                cout << "Syntax error in expression on line " << tokens[pos].line << endl;
                exit(1);
            }
        }
    }

    void expect(TokenType type)
    {
        if (tokens[pos].type != type)
        {
            cout << "Syntax error: expected token of type " << type << ", but got " << tokens[pos].value << " on line: " << tokens[pos].line << endl;
            exit(1);
        }
        pos++;
    }
};

int main(int argc, char *argv[])
{
    // Check if the user provided a filename
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <source_file>" << endl;
        return 1;
    }

    // Open the source file provided as a command line argument
    ifstream file(argv[1]);
    if (!file)
    {
        cerr << "File " << argv[1] << " not found." << endl;
        return 1;
    }

    string input;
    string line;
    // Read the file line by line
    while (getline(file, line))
    {
        input.append(line);
        input.append("\n");
    }
    file.close();

    cout << "Complete code" << endl;
    cout << input << endl;

    // Main Parsing
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parseProgram();

    return 0;
}
