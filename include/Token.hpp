#ifndef BIS_TYPES_TOKEN_H
#define BIS_TYPES_TOKEN_H
#include <string>
#include <variant>

struct Token
{
    enum class TokenType
    {
        // Single-character tokens
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SLASH, SEMICOLON, STAR,

        // One or two character tokens
        RIGHT_BRACKET, LEFT_BRACKET, EXCLAMATION, EXCLAMATION_EQUAL, EQUAL,
        EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, MINUS_MINUS, PLUS_PLUS,

        // Literal
        IDENTIFIER, STRING, NUMBER,

        // Keyword
        AND, OR, CLASS, IF, ELSE, _FALSE, _TRUE, FN, FOR,
        WHILE, NIL, PRINT, RETURN, SUPER, THIS, VAR, LAMBDA,

        _EOF
    };

    Token(const TokenType type, const std::string lexeme, const unsigned int line);
    const TokenType m_type;
    const std::string m_lexeme;
    const unsigned int m_line;
};

std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const Token::TokenType type);

#endif


