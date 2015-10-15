/*
 * Expression.cc
 */
#include "Expression.h"
#include "Expression_Tree.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <typeinfo>
#include "Variable_Table.h"
using namespace std;

Expression::Expression(const Expression& e)
{
    if(e.tree_top == nullptr)
    {
        tree_top = nullptr;
    }
    else
    {
        tree_top = e.tree_top->clone();
    }
}
/*
 * evaluate()
 */
long double Expression::evaluate(Variable_Table& VT) const
{
    if(tree_top == nullptr)
    {
        return 0;
    }
    long double result{tree_top->evaluate(VT)};
    return result;
}

/*
 * get_postfix()
 */
std::string Expression::get_postfix() const
{
    if(tree_top == nullptr)
    {
        return "";
    }
    else
    {
        return tree_top->get_postfix();
    }
}

/*
 * empty()
 */
bool Expression::empty() const
{
    bool is_empty{tree_top == nullptr};
    return is_empty;
}

/*
 * print_tree()
 */
void Expression::print_tree(std::ostream& o_stream) const
{
    tree_top->print(o_stream,2);
}

/*
 * swap(other)
 */
void Expression::swap(Expression& rhs)
{
    Expression_Tree* p{this->tree_top};
    this->tree_top = rhs.tree_top;
    rhs.tree_top = p;
}

/*
 * swap(x, y)
 */
void swap(Expression& lhs, Expression& rhs)
{
    lhs.swap(rhs);
}

string Expression::get_infix() const
{
    string infix{tree_top->get_infix()};
    return infix;
}
/*
 * make_expression() definieras efter namnrymden nedan.
 */
Expression make_expression(const string& infix);

// Namrymden nedan inneh�ller intern kod f�r infix-till-postfix-omvandling
// och generering av uttryckstr�d. En anonym namnrymd begr�nsar anv�ndningen
// av medlemmarna till denna fil.
namespace
{
    using std::vector;
    using std::map;
    using std::make_pair;
    using std::string;

    // Teckenupps�ttningar f�r operander. Anv�nds av make_expression_tree().
    const string letters{"abcdefghijklmnopqrstuvwxyz"};
    const string digits{"0123456789"};
    const string integer_chars{digits};
    const string real_chars{digits + '.'};
    const string variable_chars{letters};
    const string operand_chars{letters + digits + '.'};

    // Till�tna operatorer. Anv�nds av make_postfix() och make_expression_tree().
    // Prioritetstabeller, en f�r inkommandeprioritet och en f�r stackprioritet. 
    // H�gre v�rde inom input_prio respektive stack_prio anger inb�rdes prioritetsordning.
    // H�gre v�rde i input_prio j�mf�rt med motsvarande position i stack_prio inneb�r
    // h�gerassociativitet, det motsatta v�nsterassociativitet. Anv�nds av make_postfix(). 
    using priority_table = map<string, int>;

    const vector<string> operators{ "^", "*", "/", "+", "-", "=" };
    const priority_table input_priority{ {"^", 8}, {"*", 5}, {"/", 5}, {"+", 3}, {"-", 3}, {"=", 2} };
    const priority_table stack_priority{ {"^", 7}, {"*", 6}, {"/", 6}, {"+", 4}, {"-", 4}, {"=", 1} };

    // Hj�lpfunktioner f�r att kategorisera lexikala element.
    bool is_operator(char token)
    {
        return find(begin(operators), end(operators), string{token}) != end(operators);
    }

    bool is_operator(const string& token)
    {
        return find(begin(operators), end(operators), token) != end(operators);
    }

    bool is_operand(const string& token)
    {
        return token.find_first_not_of(operand_chars) == string::npos;
    }

    bool is_integer(const string& token)
    {
        return token.find_first_not_of(integer_chars) == string::npos;
    }

    bool is_real(const string& token)
    {
        return token.find_first_not_of(real_chars) == string::npos;
    }

    bool is_identifier(const string& token)
    {
        return token.find_first_not_of(letters) == string::npos;
    }

    // format_infix tar en str�ng med ett infixuttryck och formaterar med ett
    // mellanrum mellan varje symbol; underl�ttar vid bearbetningen i make_postfix.
    std::string format_infix(const std::string& infix)
    {
        auto bos = begin(infix);
        auto eos = end(infix);
        string formated;

        for (auto it = bos; it != eos; ++it)
        {
            if (is_operator(*it) || *it == '(' || *it == ')')
            {
                // Se till att det �r ett mellanrum f�re en operator eller parentes
                if (it != bos && *(it - 1) != ' ' && *(formated.end() - 1) != ' ')
                    formated.append(1, ' ');
                formated.append(1, *it);
                // Se till att det �r ett mellanrum efter en operator eller parentes
                if ((it + 1) != eos && *(it + 1) != ' ')
                    formated.append(1, ' ');
            }
            else
            {
                if (*it != ' ')
                    formated.append(1, *it);
                else if (it != bos && *(it - 1) != ' ')
                    formated.append(1, *it);
            }
        }
     
        return formated;
    }

    // make_postfix tar en infixstr�ng och returnerar motsvarande postfixstr�ng.
    std::string make_postfix(const std::string& infix)
    {
        using std::stack;
        using std::string;
        using std::istringstream;
        using std::find;

        stack<string> operator_stack;
        string        token;
        string        previous_token;
        bool          last_was_operand{false};
        bool          assignment{false};
        int           paren_count{0};

        istringstream is{format_infix(infix)};
        string        postfix;

        while (is >> token)
        {
            if (is_operator(token))
            {
                if (!last_was_operand || postfix.empty() || previous_token == "(")
                {
                    throw expression_error{"operator d�r operand f�rv�ntades"};
                }

                if (token == "=")
                {
                    if (assignment)
                    {
                        throw expression_error{"multipel tilldelning"};
                    }
                    else
                    {
                        assignment = true;
                    }
                }

                while (!operator_stack.empty() && operator_stack.top() != "(" &&
                       input_priority.find(token)->second <=
                       stack_priority.find(operator_stack.top())->second)
                {
                    postfix += operator_stack.top() + ' ';
                    operator_stack.pop();
                }
                operator_stack.push(token);
                last_was_operand = false;
            }
            else if (token == "(")
            {
                operator_stack.push(token);
                ++paren_count;
            }
            else if (token == ")")
            {
                if (paren_count == 0)
                {
                    throw expression_error{"v�nsterparentes saknas"};
                }

                if (previous_token == "(" && !postfix.empty())
                {
                    throw expression_error{"tom parentes"};
                }

                while (!operator_stack.empty() && operator_stack.top() != "(")
                {
                    postfix += operator_stack.top() + ' ';
                    operator_stack.pop();
                }

                if (operator_stack.empty())
                {
                    throw expression_error{"h�gerparentes saknar matchande v�nsterparentes"};
                }
                // Det finns en v�nsterparentes p� stacken
                operator_stack.pop();
                --paren_count;
            }
            else if (is_operand(token))
            {
                if (last_was_operand || previous_token == ")")
                {
                    throw expression_error{"operand d�r operator f�rv�ntades"};
                }

                postfix += token + ' ';
                last_was_operand = true;
            }
            else
            {
                throw expression_error{"otill�ten symbol"};
            }

            previous_token = token;
        }

        if (postfix == "")
        {
            throw expression_error{"tomt infixuttryck!"};
        }

        if (!last_was_operand && !postfix.empty())
        {
            throw expression_error{"operator avslutar"};
        }

        if (paren_count > 0)
        {
            throw expression_error{"h�gerparentes saknas"};
        }

        while (!operator_stack.empty())
        {
            postfix += operator_stack.top() + ' ';
            operator_stack.pop();
        }

        if (!postfix.empty())
        {
            postfix.erase(postfix.size() - 1);
        }

        return postfix;
    }

    // make_expression_tree tar en postfixstr�ng och returnerar ett motsvarande 
    // l�nkat tr�d av Expression_Tree-noder.
    Expression_Tree* make_expression_tree(const std::string& postfix)
    {
        using std::stack;
        using std::string;
        using std::istringstream;

        stack<Expression_Tree*> tree_stack;
        string                  token;
        istringstream           ps{postfix};
        try
        {
            while (ps >> token)
            {
                if (is_operator(token))
                {
                    if (tree_stack.empty()) 
                    {
                        throw expression_error{"felaktig postfix"};
                    }
                    Expression_Tree* rhs{tree_stack.top()};
                    tree_stack.pop();

                    if (tree_stack.empty()) 
                    {
                        throw expression_error{"felaktig postfix"};
                    }
                    Expression_Tree* lhs{tree_stack.top()};
                    tree_stack.pop();

                    if (token == "^")
                    {
                        tree_stack.push(new Power{lhs, rhs});
                    }
                    else if (token == "*")
                    {
                        tree_stack.push(new Times{lhs, rhs});
                    }
                    else if (token == "/")
                    {
                        tree_stack.push(new Divide{lhs, rhs});
                    }
                    else if (token == "+")
                    {
                        tree_stack.push(new Plus{lhs, rhs});
                    }
                    else if (token == "-")
                    {
                        tree_stack.push(new Minus{lhs, rhs});
                    }
                    else if (token == "=")
                    {
                        tree_stack.push(new Assign{lhs, rhs});
                    }
                }
                else if (is_integer(token))
                {
                    tree_stack.push(new Integer{std::stoll(token.c_str())});
                }
                else if (is_real(token))
                {
                    tree_stack.push(new Real{std::stold(token.c_str())});
                }
                else if (is_identifier(token))
                {
                    tree_stack.push(new Variable{token});
                }
                else
                {
                    while (!tree_stack.empty())
                    {
                        delete tree_stack.top();
                        tree_stack.pop();
                    }
                    throw expression_error{"felaktig postfix"};
                }
            }
        }
        catch (const exception& e) 
        {
            cout << e.what() << '\n';
            while (!tree_stack.empty())
            {
                delete tree_stack.top();
                tree_stack.pop();
            }
        }
        // Det ska bara finnas ett tr�d p� stacken om korrekt postfix.

        if (tree_stack.empty())
        {
            throw expression_error{"ingen postfix given"};
        }

        if (tree_stack.size() > 1)
        {
            while (!tree_stack.empty())
            {
                delete tree_stack.top();
                tree_stack.pop();
            }
            throw expression_error{"felaktig postfix"};
        }

        // Returnera tr�det.
        return tree_stack.top();
    }
} // namespace

Expression make_expression(const string& infix)
{
    return Expression{make_expression_tree(make_postfix(infix))};
}
