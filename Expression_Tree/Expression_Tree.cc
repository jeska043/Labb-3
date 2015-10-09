/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
#include <string>
#include <iostream>
#include <typeinfo>
#include <cmath>
using namespace std;

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.

Binary_Operator::Binary_Operator(Expression_Tree* left, Expression_Tree* right)
{
    lhs = left;
    rhs = right;
}

Expression_Tree* Binary_Operator::clone() const
{
    Expression_Tree* p;

    if(typeid(*this) == typeid(Plus))
    {
        p = {new Plus{lhs->clone(),rhs->clone()}};
    }

    if(typeid(*this) == typeid(Minus))
    {
        p = {new Minus{lhs->clone(),rhs->clone()}};
    }

    if(typeid(*this) == typeid(Times))
    {
        p = {new Times{lhs->clone(),rhs->clone()}};
    }

    if(typeid(*this) == typeid(Divide))
    {
        p = {new Divide{lhs->clone(),rhs->clone()}};
    }

    if(typeid(*this) == typeid(Power))
    {
        p = {new Power{lhs->clone(),rhs->clone()}};
    }

    return p;
}

Expression_Tree* Integer::clone() const
{
    Expression_Tree* p{new Integer{value}};
    return p;
}

Expression_Tree* Real::clone() const
{
    Expression_Tree* p{new Real{value}};
    return p;
}

string Binary_Operator::get_postfix() const
 {
    string postfix;
    string str1{lhs->get_postfix()};
    string str2{rhs->get_postfix()};

    postfix.append(str1);
    postfix.append(" ");
    postfix.append(str2);
    postfix.append(" ");
    postfix.append(this->str());

    return postfix;
 }

string Binary_Operator::str() const
{
    string node;

    if(typeid(*this) == typeid(Plus))
    {
        node = "+";
    }

    if(typeid(*this) == typeid(Minus))
    {
        node = "-";
    }

    if(typeid(*this) == typeid(Times))
    {
        node = "*";
    }

    if(typeid(*this) == typeid(Divide))
    {
        node = "/";
    }

    if(typeid(*this) == typeid(Power))
    {
        node = "^";
    }

    return node;
}

Integer::Integer(long long int a)
{
    value = a;
}

Real::Real(long double a)
{
    value = a;
}

long double Integer::evaluate() const
{
    return value;
}

long double Real::evaluate() const
{
    return value;
}

long double Plus::evaluate() const
{
    long double result{lhs->evaluate() + rhs->evaluate()};
    return result;
}

long double Minus::evaluate() const
{
    long double result{lhs->evaluate() - rhs->evaluate()};
    return result;
}

long double Times::evaluate() const
{
    long double result{lhs->evaluate() * rhs->evaluate()};
    return result;
}

long double Divide::evaluate() const
{
    long double result{lhs->evaluate() / rhs->evaluate()};
    return result;
}

long double Power::evaluate() const
{
    long double result{pow(lhs->evaluate(), rhs->evaluate())};
    return result;
}

string Integer::get_postfix() const
{
    string int_string{to_string(value)};
    return int_string;
}

string Real::get_postfix() const
{
    string real_string{to_string(value)};
    return real_string;
}

string Operand::str() const
{
    return this->get_postfix();
}
