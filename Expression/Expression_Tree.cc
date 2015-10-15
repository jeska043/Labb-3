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
#include "Variable_Table.h"
using namespace std;

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.
string Binary_Operator::get_infix() const
{
    string infix;
    Binary_Operator* p1{dynamic_cast<Binary_Operator*>(lhs)};
    Binary_Operator* p2{dynamic_cast<Binary_Operator*>(rhs)};     
    if((p1 == nullptr) && (p2 == nullptr))
    {
        infix.append(lhs->str());
        infix.append(" ");
        infix.append(this->str());
        infix.append(" ");
        infix.append(rhs->str());
    }

    else if((p1 == nullptr) && (p2 != nullptr))
    {
        infix.append(lhs->str());
        infix.append(" ");
        infix.append(this->str());
        if(typeid(*this) == typeid(Assign))
        {
            infix.append(" ");
            infix.append(rhs->get_infix());
        }
        else
        {
        infix.append(" (");
        infix.append(rhs->get_infix());
        infix.append(")");
        }
    }

    else if((p1 != nullptr) && (p2 == nullptr))
    {
        if(typeid(*this) == typeid(Assign))
        {
            infix.append(lhs->get_infix());
            infix.append(" ");
        }
        else
        {
        infix.append("(");
        infix.append(lhs->get_infix());
        infix.append(") ");
        }
        infix.append(this->str());
        infix.append(" ");
        infix.append(rhs->str());
    }

    else if((p1 != nullptr) && (p2 != nullptr))
    {
        infix.append("(");
        infix.append(lhs->get_infix());
        infix.append(") ");
        infix.append(this->str());
        infix.append(" (");
        infix.append(rhs->get_infix());
        infix.append(")");
    }
    return infix;
}

string Integer::get_infix() const
{
    string infix{to_string(value)};
    return infix;
}

string Real::get_infix() const
{
    string infix{to_string(value)};
    return infix;
}

string Variable::get_infix() const
{
    string infix{name};
    return infix;
}

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

long double Integer::evaluate(Variable_Table& VT) const
{
    return value;
}

long double Real::evaluate(Variable_Table& VT) const
{
    return value;
}

long double Variable::evaluate(Variable_Table& VT) const
{
    if(VT.find(name))
    {
    return VT.get_value(name);
    }
    else
    {
        throw expression_error{"Du kan ej evaluera en variabel som ej tilldelats ett värde."};
    }
}

long double Plus::evaluate(Variable_Table& VT) const
{
    long double result{lhs->evaluate(VT) + rhs->evaluate(VT)};
    return result;
}

long double Minus::evaluate(Variable_Table& VT) const
{
    long double result{lhs->evaluate(VT) - rhs->evaluate(VT)};
    return result;
}

long double Times::evaluate(Variable_Table& VT) const
{
    long double result{lhs->evaluate(VT) * rhs->evaluate(VT)};
    return result;
}

long double Divide::evaluate(Variable_Table& VT) const
{
    long double result{lhs->evaluate(VT) / rhs->evaluate(VT)};
    return result;
}

long double Power::evaluate(Variable_Table& VT) const
{
    long double result{pow(lhs->evaluate(VT), rhs->evaluate(VT))};
    return result;
}

long double Assign::evaluate(Variable_Table& VT) const
{
    long double result{0};
    if((typeid(*lhs) == typeid(*rhs)) || (typeid(*lhs) == typeid(Variable)))
    {
        result = rhs->evaluate(VT);
        if(VT.find(lhs->str()))
            {
                VT.set_value(lhs->str(),result);
            }
            else
            {
                VT.insert(lhs->str(),result);
            }
    }
    else if(typeid(*rhs) == typeid(Variable))
    {
        result = lhs->evaluate(VT);
        VT.insert(rhs->str(),result);
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

long double Variable::get_value(Variable_Table& VT) const
{
    return VT.get_value(name);
}

void Variable::set_value(long double new_value, Variable_Table& VT)
{
    VT.set_value(name,new_value);
}
