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
   virtual long double      evaluate() const = 0;
   virtual std::string      get_postfix() const = 0;
   virtual std::string      str() const = 0;
   virtual void             print(std::ostream&) const = 0;
   virtual Expression_Tree* clone() const = 0;
};

class Binary_Operator : public Expression_Tree
{
};

class Operand : public Expression_Tree
{
};

class Assign : public Binary_Operator
{ 
};

class Plus : public Binary_Operator
{ 
};

class Minus : public Binary_Operator 
{
};

class Times : public Binary_Operator
{
};

class Divide : public Binary_Operator
{
};

class Power: public Binary_Operator
{
};

class Integer : public Operand
{
};

class Real : public Operand
{
};

class Variable : public Operand
{
};

#endif
