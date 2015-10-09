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
// ATT GÖRA!


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
   //virtual void             print(std::ostream&) const = 0;
    virtual Expression_Tree* clone() const = 0;
};

class Binary_Operator : public Expression_Tree
{
public:
    Binary_Operator(Expression_Tree*, Expression_Tree*);
    //long double evaluate() const override;
    std::string get_postfix() const override;
    std::string str() const override;
    //void print(std::ostream&) const override;
    Expression_Tree* clone() const override;

protected:
    Expression_Tree* lhs;
    Expression_Tree* rhs;
};

class Operand : public Expression_Tree
{
public:
    //long double evaluate() const override;
    // std::string get_postfix() const override;
    std::string str() const override;
    //void print(std::ostream&) const override;
    //Expression_Tree* clone() const override;
};

/*
class Assign : public Binary_Operator
{
public:
Assign(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
};
*/
class Plus : public Binary_Operator
{
public:
Plus(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
    long double evaluate() const override;
};
/*
class Minus : public Binary_Operator 
{
public:
Minus(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
};

class Times : public Binary_Operator
{
public:
Times(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
};

class Divide : public Binary_Operator
{
public:
Divide(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
};

class Power: public Binary_Operator
{
public:
Power(Expression_Tree* lhs, Expression_Tree* rhs) : Binary_Operator{lhs, rhs} {};
};
*/
class Integer : public Operand
{
public:
    Integer(long long int);
    long double evaluate() const override;
    std::string get_postfix() const override;
    Expression_Tree* clone() const override;

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

private:
    long double value;
};
/*
class Variable : public Operand
{
public:
    Variable(std::string);
    long double evaluate() const override;
private:
    std::string value;
};
*/
#endif
