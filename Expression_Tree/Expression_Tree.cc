/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
#include <string>
#include <iostream>
#include <typeinfo>
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

    if(typeid(*this) == typeid(Plus))
    {
        postfix.append("+");
    }

    return postfix;
 }

string Binary_Operator::str() const
{
    string node;
    if(typeid(*this) == typeid(Plus))
    {
        node = "+";
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
    long double result{rhs->evaluate() + lhs->evaluate()};
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
