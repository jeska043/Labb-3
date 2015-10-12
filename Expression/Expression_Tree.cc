/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
#include <string>
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <iomanip>
using namespace std;

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.

Binary_Operator::Binary_Operator(Expression_Tree* left, Expression_Tree* right)
{
    lhs = left;
    rhs = right;
}

Assign::Assign(Expression_Tree* left, Expression_Tree* right)
{
    bool left_variable{typeid(*left) == typeid(Variable)};
    bool right_variable{typeid(*right) == typeid(Variable)};

    if(! (left_variable || right_variable))
        throw expression_error{"'=' måste användas med en variabel på minst en sida"};

    if(left_variable)
    {
        left->assigned_value = right->evaluate();
    }
    else if(right_variable)
    {
        right->assigned_value = left->evaluate();
    }
    
    lhs = left;
    rhs = right;
}

void Binary_Operator::print(ostream& o_stream, int width) const
{
    rhs->print(o_stream, (width + 3));
    o_stream << setw(width+1) << " /" << endl << setw(width) << this->str()
             << endl << setw(width+1) <<  " \\" << endl;
    lhs->print(o_stream, (width + 3));
}

void Integer::print(ostream& o_stream, int width) const
{
    o_stream << setw(width-1) << value << endl;
}

void Real::print(ostream& o_stream, int width) const
{
    o_stream << setw(width-1) << value << endl;
}

void Variable::print(ostream& o_stream, int width) const
{
    o_stream << setw(width-1) << name << endl;
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

    if(typeid(*this) == typeid(Assign))
    {
        p = {new Assign{lhs->clone(),rhs->clone()}};
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

Expression_Tree* Variable::clone() const
{
    Expression_Tree* p{new Variable{name}};
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

    if(typeid(*this) == typeid(Assign))
    {
        node = "=";
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

Variable::Variable(string a)
{
    name = a;
}

long double Integer::evaluate() const
{
    return value;
}

long double Real::evaluate() const
{
    return value;
}

long double Variable::evaluate() const
{
    return assigned_value;
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

long double Assign::evaluate() const
{
    long double result{0};
    if(typeid(*lhs) == typeid(Variable))
    {
        result = rhs->evaluate();
    }
    else
    {
        result = lhs->evaluate();
    }

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

string Variable::get_postfix() const
{
    string var_string{name};
    return var_string;
}

string Operand::str() const
{
    return this->get_postfix();
}

long double Variable::get_value() const
{
    return assigned_value;
}

void Variable::set_value(long double new_value)
{
    assigned_value = new_value;
}
