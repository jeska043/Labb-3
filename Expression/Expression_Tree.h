/*
 * Expression_Tree.h
 */
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <iosfwd>
#include <string>
#include <stdexcept>

/*
 * expression_error: kastas om ett fel inträffar i en Expression-operation;
 * ett diagnostiskt meddelande ska skickas med.
 */
class expression_error : public std::logic_error
{
public:
    explicit expression_error (const std::string& message) noexcept
        : std::logic_error{message} {}

    explicit expression_error (const char* message) noexcept
        : std::logic_error{message} {}
};


// OBSERVERA: NEDANSTÅENDE ÄR ENDAST KODSKELETT - MODIFIERA OCH KOMPLETTERA!

/*
 * Expression_Tree: Abstrakt, polymorf basklass för alla trädnodklasser.
 */
class Expression_Tree
{
public:
    virtual ~Expression_Tree() = default;
    virtual long double      evaluate() const = 0;
    virtual std::string      get_postfix() const = 0;
    virtual std::string      str() const = 0;
    virtual void             print(std::ostream&, int) const = 0;
    virtual Expression_Tree* clone() const = 0;

    long double assigned_value;
};

class Binary_Operator : public Expression_Tree
{
public:
    Binary_Operator() = default;
    Binary_Operator(Expression_Tree*, Expression_Tree*);
    //long double evaluate() const override;
    std::string get_postfix() const override;
    std::string str() const override;
    void print(std::ostream&, int) const override;
    Expression_Tree* clone() const override;

protected:
    Expression_Tree* lhs;
    Expression_Tree* rhs;
};

class Operand : public Expression_Tree
{
public:
    Operand() = default;
    //long double evaluate() const override;
    // std::string get_postfix() const override;
    std::string str() const override;
    //void print(std::ostream&) const override;
    //Expression_Tree* clone() const override;
};


class Assign : public Binary_Operator
{
public:
    Assign(Expression_Tree*, Expression_Tree*);
    long double evaluate() const override;
};

class Plus : public Binary_Operator
{
public:
Plus(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};

class Minus : public Binary_Operator 
{
public:
Minus(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};

class Times : public Binary_Operator
{
public:
Times(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};

class Divide : public Binary_Operator
{
public:
Divide(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};

class Power: public Binary_Operator
{
public:
Power(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};

class Integer : public Operand
{
public:
    Integer(long long int);
    long double evaluate() const override;
    std::string get_postfix() const override;
    Expression_Tree* clone() const override;
    void print(std::ostream&, int) const override;

private:
    long long int value;
};

class Real : public Operand
{
public:
    Real(long double);
    long double evaluate() const override;
    std::string get_postfix() const override;
    Expression_Tree* clone() const override;
    void print(std::ostream&, int) const override;

private:
    long double value;
};

class Variable : public Operand
{
public:
    Variable(std::string);
    long double evaluate() const override;
    std::string get_postfix() const override;
    Expression_Tree* clone() const override;
    long double get_value() const;
    void set_value(long double);
    void print(std::ostream&, int) const override;
private:
    std::string name;
    long double assigned_value;
};

#endif
