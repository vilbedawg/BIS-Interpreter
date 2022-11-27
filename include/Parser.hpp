#ifndef BIS_PARSER_HPP
#define BIS_PARSER_HPP

#include "../include/Logger.hpp"
#include "Expr.hpp"
#include "Token.hpp"
#include "Typedef.hpp"

#include <stdexcept>
#include <vector>

class Parser
{
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<unique_expr_ptr> parse();

private:
    std::vector<Token> tokens;
    unsigned int current{0};

    unique_expr_ptr expression();
    unique_expr_ptr assignment();
    unique_expr_ptr orExpression();
    unique_expr_ptr andExpression();
    unique_expr_ptr equality();
    unique_expr_ptr comparison();
    unique_expr_ptr term();
    unique_expr_ptr factor();
    unique_expr_ptr unary();
    unique_expr_ptr call();
    unique_expr_ptr finishCall(unique_expr_ptr callee);
    unique_expr_ptr primary();
    unique_expr_ptr prefix();
    unique_expr_ptr postfix();
    unique_expr_ptr list();

    template <typename... Args>
    bool match(Args... args);
    
    bool check(TokenType type) const;
    bool isAtEnd() const;
    void synchronize();

    Token consume(TokenType type, std::string msg);
    Token advance();
    Token peek() const;
    Token previous() const;

    class ParseError : public std::runtime_error
    {
    public:
        ParseError() : std::runtime_error("") {}
    };
    ParseError error(const Token& token, const std::string message) const;
};

#endif // BIS_PARSER_HPP