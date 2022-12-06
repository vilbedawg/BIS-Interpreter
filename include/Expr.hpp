#ifndef BIS_EXPR_HPP
#define BIS_EXPR_HPP

#include "Token.hpp"
#include "Typedef.hpp"
#include "Visitor.hpp"
#include <vector>

struct AssignExpr : Expr
{
    Token identifier;
    unique_expr_ptr value;

    AssignExpr(const Token& identifier, unique_expr_ptr value);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct BinaryExpr : Expr
{
    unique_expr_ptr left;
    Token op;
    unique_expr_ptr right;

    BinaryExpr(unique_expr_ptr left, const Token& op, unique_expr_ptr right);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct UnaryExpr : Expr
{
    Token op;
    unique_expr_ptr right;

    UnaryExpr(const Token& op, unique_expr_ptr right);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct IncrementExpr : Expr
{
    enum class Type
    {
        POSTFIX,
        PREFIX
    };

    Type type;
    std::unique_ptr<VarExpr> variable;

    IncrementExpr(std::unique_ptr<VarExpr> variable, Type type);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct DecrementExpr : Expr
{
    enum class Type
    {
        POSTFIX,
        PREFIX
    };

    Type type;
    std::unique_ptr<VarExpr> variable;

    DecrementExpr(std::unique_ptr<VarExpr> variable, Type type);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct CallExpr : Expr
{
    unique_expr_ptr callee;
    Token paren;
    std::vector<unique_expr_ptr> args;

    CallExpr(unique_expr_ptr callee, const Token& paren, std::vector<unique_expr_ptr> args);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct GetExpr : Expr
{
    unique_expr_ptr object;
    Token identifier;

    GetExpr(unique_expr_ptr object, const Token& identifier);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct SetExpr : Expr
{
    unique_expr_ptr object;
    Token identifier;
    unique_expr_ptr value;

    SetExpr(unique_expr_ptr object, const Token& identifier, unique_expr_ptr value);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct GroupingExpr : Expr
{
    unique_expr_ptr expression;

    explicit GroupingExpr(unique_expr_ptr expression);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct LiteralExpr : Expr
{
    std::any literal;

    explicit LiteralExpr(std::any literal);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct LogicalExpr : Expr
{
    unique_expr_ptr left;
    Token op;
    unique_expr_ptr right;

    LogicalExpr(unique_expr_ptr left, const Token& op, unique_expr_ptr right);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct SuperExpr : Expr
{
    Token keyword;
    Token method;

    SuperExpr(const Token& keyword, const Token& method);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct ThisExpr : Expr
{
    Token keyword;

    explicit ThisExpr(const Token& keyword);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct VarExpr : Expr
{
    Token identifier;

    explicit VarExpr(const Token& identifier);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

struct ListExpr : Expr
{
    Token opening_bracket;
    std::vector<unique_expr_ptr> items;

    ListExpr(const Token& opening_bracket, std::vector<unique_expr_ptr> items);
    std::any accept(ExprVisitor<std::any>& visitor) const override;
};

#endif // BIS_EXPR_HPP