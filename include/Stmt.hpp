#ifndef BIS_STMT_HPP
#define BIS_STMT_HPP

#include "Expr.hpp"
#include "Token.hpp"
#include "Typedef.hpp"
#include "Visitor.hpp"
#include <vector>

struct BlockStmt : Stmt
{
    std::vector<unique_stmt_ptr> statements;

    BlockStmt(std::vector<unique_stmt_ptr> statements);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct ClassStmt : Stmt
{
    Token identifier;
    std::unique_ptr<VarExpr> superclass; // OPTIONAL
    std::vector<std::unique_ptr<FnStmt>> methods;

    ClassStmt(const Token& identifier, std::vector<std::unique_ptr<FnStmt>> methods,
              std::unique_ptr<VarExpr> superclass);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct ExprStmt : Stmt
{
    unique_expr_ptr expression;

    ExprStmt(unique_expr_ptr expr);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct FnStmt : Stmt
{
    Token identifier;
    std::vector<Token> params;
    std::vector<unique_stmt_ptr> body;

    FnStmt(const Token& identifier, std::vector<Token> params, std::vector<unique_stmt_ptr> body);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct IfBranch
{
    unique_expr_ptr condition;
    unique_stmt_ptr statement;

    IfBranch(unique_expr_ptr condition, unique_stmt_ptr statement);
};

struct IfStmt : Stmt
{
    IfBranch main_branch;
    std::vector<IfBranch> elif_branches;
    unique_stmt_ptr else_branch; // OPTIONAL

    IfStmt(IfBranch main_branch, std::vector<IfBranch> elif_branches, unique_stmt_ptr else_branch);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct PrintStmt : Stmt
{
    unique_expr_ptr expression; // OPTIONAL

    explicit PrintStmt(unique_expr_ptr expr);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct ReturnStmt : Stmt
{
    Token keyword;
    unique_expr_ptr expression; // OPTIONAL

    explicit ReturnStmt(const Token& keyword, unique_expr_ptr expr);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct BreakStmt : Stmt
{
    Token keyword;

    explicit BreakStmt(const Token& keyword);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct VarStmt : Stmt
{
    Token identifier;
    unique_expr_ptr initializer; // OPTIONAL

    VarStmt(const Token& identifier, unique_expr_ptr initializer);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct WhileStmt : Stmt
{
    unique_expr_ptr condition;
    unique_stmt_ptr body;

    WhileStmt(unique_expr_ptr condition, unique_stmt_ptr body);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};

struct ForStmt : Stmt
{
    unique_stmt_ptr initializer, body, increment; // OPTIONAL
    unique_expr_ptr condition;                    // OPTIONAL

    ForStmt(unique_stmt_ptr initializer, unique_expr_ptr condition, unique_stmt_ptr increment,
            unique_stmt_ptr body);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
};
#endif // BIS_STMT_HPP