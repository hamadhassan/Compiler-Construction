#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <fstream> // For file handling

using namespace std;

enum TokenType
{
    T_INT,
    T_FLOAT,
    T_DOUBLE,
    T_STRING,
    T_BOOL,
    T_CHAR,
    T_TRUE,
    T_FALSE,
    T_ID,
    T_NUM,
    T_IF,
    T_ELSE,
    T_RETURN,
    T_WHILE,
    T_FOR,
    T_SWITCH,
    T_CASE,
    T_BREAK,
    T_CONTINUE,
    T_ASSIGN,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_SEMICOLON,
    T_GT,
    T_LS,
    T_EOF,
    T_COLON,
    T_AGAR, 
    T_PRINT // Token type for print function
};

struct Token
{
    TokenType type;
    string value;
    int line;
    Token(TokenType type, const string &value, int line) : type(type), value(value), line(line) {}
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

            if (isspace(current))
            {
                if (current == '\n')
                    line++;
                pos++;
                continue;
            }

            if (isdigit(current))
            {
                tokens.push_back(Token{T_NUM, consumeNumber(), line});
                continue;
            }

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
                else if (word == "agar") // Handle custom keyword
                    tokens.push_back(Token{T_AGAR, word, line});
                else if (word == "print") // Handle print function
                    tokens.push_back(Token{T_PRINT, word, line});
                else
                    tokens.push_back(Token{T_ID, word, line});
                continue;
            }

            if (current == '"')
            {
                tokens.push_back(Token{T_STRING, consumeStringLiteral(), line});
                continue;
            }

            if (current == '\'')
            {
                tokens.push_back(Token{T_CHAR, consumeCharLiteral(), line});
                continue;
            }

            switch (current)
            {
            case '=':
                tokens.push_back(Token{T_ASSIGN, "=", line});
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
            case '>':
                tokens.push_back(Token{T_GT, ">", line});
                break;
            case '<':
                tokens.push_back(Token{T_LS, "<", line});
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
            pos++; // Consume the decimal point
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
        pos++; // Skip the opening quote
        size_t start = pos;
        while (pos < src.size() && src[pos] != '"')
            pos++;
        pos++;                                     // Skip the closing quote
        return src.substr(start, pos - start - 1); // Exclude quotes
    }

    string consumeCharLiteral()
    {
        pos++; // Skip the opening single quote
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

        pos++; // Skip the closing single quote
        return string(1, literal);
    }
};

class Parser
{
public:
    Parser(const vector<Token> &tokens)
    {
        this->tokens = tokens;
        this->pos = 0;
    }

    void parseProgram()
    {
        while (tokens[pos].type != T_EOF)
        {
            parseStatement();
        }
        cout << "Parsing completed successfully! No Syntax Error" << endl;
    }

private:
    vector<Token> tokens;
    size_t pos;

    void parseStatement()
    {
        if (tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_STRING || tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR)
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
        else if (tokens[pos].type == T_AGAR) // Handle custom keyword
        {
            parseIfStatement(); // Reuse the same method for custom condition
        }
        else if (tokens[pos].type == T_WHILE) // New case for while
        {
            parseWhileStatement();
        }
        else if (tokens[pos].type == T_FOR) // New case for for
        {
            parseForStatement();
        }
        else if (tokens[pos].type == T_SWITCH) // New case for switch
        {
            parseSwitchStatement();
        }
        else if (tokens[pos].type == T_RETURN)
        {
            parseReturnStatement();
        }
        else if (tokens[pos].type == T_PRINT) // Handle print function
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
        parseExpression(); // Condition
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
        parseDeclaration(); // Initialization
        expect(T_SEMICOLON);
        parseExpression();  // Condition
        expect(T_SEMICOLON);
        parseAssignment();  // Increment
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
            parseExpression(); // Optional return value
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
        parseExpression(); // Print argument
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
        if (tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_STRING || tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR)
        {
            TokenType type = tokens[pos].type;
            expect(type); // Consume type
            expect(T_ID); // Consume identifier
            expect(T_ASSIGN); // Consume '='
            parseExpression(); // Consume initial value
            expect(T_SEMICOLON); // Consume ';'
        }
    }

    void parseAssignment()
    {
        expect(T_ID); // Variable identifier
        expect(T_ASSIGN);
        parseExpression();
        expect(T_SEMICOLON); // End of statement
    }

    void parseExpression()
    {
        // Simplified expression parsing
        if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID || tokens[pos].type == T_TRUE || tokens[pos].type == T_FALSE)
        {
            expect(tokens[pos].type); // Expect an identifier or number, etc.
        }
        else
        {
            cout << "Syntax error in expression on line " << tokens[pos].line << endl;
            exit(1);
        }

        // Handle binary operations
        while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS || tokens[pos].type == T_MUL || tokens[pos].type == T_DIV)
        {
            expect(tokens[pos].type); // Consume operator
            if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID || tokens[pos].type == T_TRUE || tokens[pos].type == T_FALSE)
            {
                expect(tokens[pos].type); // Expect another identifier or number, etc.
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
