/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
#include <string>
#include <iostream>
using namespace std;

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.

Binary_Operator::Binary_Operator(Expression_Tree* left, Expression_Tree* right)
{
    lhs = left;
    rhs = right;
}

long double Binary_Operator::evaluate() const
{
    return 0; //fixa sen
}

// string Binary_Operator::get_postfix()
// {
//     string postfix;
//     string str1{lhs.get_postfix()};
//     string str2{rhs.get_postfix()};

//     postfix.append(str1);
//     postfix.append(" ");
//     postfix.append(str2);
//     postfix.append(" ");
//     postfix.append(op_symbol);

//     return postfix;
// }
//
// void Binary_Operator::print(ostream& o_stream)
// {
//     o_stream << "inte än";
// }

long double Plus::evaluate() const
{
    cout << "inne i evaluate" << endl;
    return rhs->evaluate() + lhs->evaluate();
}

Integer::Integer(long long int a)
{
    value = a;
}

long double Integer::evaluate() const
{
    return value;
}

Real::Real(long double a)
{
    value = a;
}

long double Real::evaluate() const
{
    return value;
}

Variable::Variable(string a)
{
    value = a;
}

long double Variable::evaluate() const
{
    return 0; //fixa sen
}
