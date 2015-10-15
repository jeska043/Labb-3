/*
 * Calculator.cc
 */
#include "Calculator.h"
#include "Expression.h"
#include "Variable_Table.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

const string Calculator::valid_cmds_("?HUBPTSVXLRINA");
const string Calculator::cmds_with_args_("BPITAR");

/**
 * run: Huvudfunktionen f�r kalkylatorn. Skriver ut hj�lpinformation
 * och l�ser sedan sedan in ett kommando i taget och utf�r det.
 */
void
Calculator::
run()
{
   cout << "V�lkommen till Kalkylatorn!\n\n";
   print_help();

   do 
   {
      try 
      {
	 get_command();
	 if (valid_command()) execute_command();
      }
      catch (const exception& e) 
      {
	 cout << e.what() << '\n';
      }
      // Of�rutsedda undantag avbryter programk�rningen, via main().
   }
   while (command_ != 'S');
}

/**
 * print_help: Skriver ut kommandorepertoaren.
 */
void
Calculator::
print_help()
{
   cout << "  H, ?  Skriv ut denna information\n";
   cout << "  U     Mata in ett nytt uttryck\n";
   cout << "  B     Ber�kna aktuellt uttryck\n";
   cout << "  B n   Ber�kna uttryck n\n";
   cout << "  P     Visa aktuellt uttryck som postfix\n";
   cout << "  P n   Visa uttryck n som postfix\n";
   cout << "  I     Visa aktuellt uttryck som infix\n";
   cout << "  I n   Visa uttryck n som infix\n";
   cout << "  L     Lista alla uttryck som infix\n";
   cout << "  T     Visa aktuellt uttryck som tr�d\n";
   cout << "  T n   Visa uttryck n som ett tr�d\n";
   cout << "  N     Visa antal lagrade uttryck\n";
   cout << "  A n   G�r uttryck n till aktuellt uttryck\n";
   cout << "  R     Radera aktuellt uttryck\n";
   cout << "  R n   Radera uttryck n\n";
   cout << "  V     Lista alla variabler\n";
   cout << "  X     Radera alla variabler\n";
   cout << "  S     Avsluta kalkylatorn\n";
}

/**
 * get_command: L�ser ett kommando (ett tecken), g�r om till versal och lagrar
 * kommandot i medlemmen command_, f�r vidare behandling av andra operationer. 
 * Ingen kontroll g�rs om det skrivits mer, i s� fall skr�p, p� kommandoraden.
 */
void
Calculator::
get_command()
{
   cout << ">> ";
   cin >> command_;
   command_ = toupper(command_);

   if(command_with_arg())
   {
       string adds;
       unsigned n{0};
       getline(cin,adds);

       for(unsigned i = 0; i < adds.size(); ++i)
       {
           if(isdigit(adds[i]))
           {
               n = n*10 + (adds[i] - '0');
           }
       }
       if(n > expression_vector_.size())
       {
           cerr << "Uttryck " << n << " finns inte." << endl;
           number_ = -2;
       }
       else
       {
           if(n != 0)
               number_ = n;
           else
           number_ = -1;
       } 
   }
}

/**
 * valid_command: Kontrollerar om kommandot som finns i medlemmen command_
 * tillh�r den till�tna kommandorepertoraren och returnerar antingen true
 * (giltigt kommando) eller false (ogiltigt kommando).
 */
bool
Calculator::
valid_command() const
{
   if (valid_cmds_.find(command_) == string::npos)
   {
      cout << "Otill�tet kommando: " << command_ << "\n";
      return false;
   }
   return true;
}

bool
Calculator::
command_with_arg() const
{
   if (cmds_with_args_.find(command_) == string::npos)
   {
      return false;
   }
   return true;
}
/**
 * execute_command: Utf�r kommandot som finns i medlemmen command_. Kommandot
 * f�ruts�tts ha kontrollerats med valid_command() och allts� �r ett giltigt 
 * kommando.
 */
void
Calculator::
execute_command()
{
   if (command_ == 'H' || command_ == '?')
      print_help();
   else if (command_ == 'U')
   {
       read_expression(cin);
       expression_vector_.push_back(current_expression_);
   }
   else if (command_ == 'B')
   {
       if(number_ == -1)
           cout << current_expression_.evaluate(VT_) << "\n";
       else
       {
           cout << expression_vector_[number_ - 1].evaluate(VT_) << "\n";
       }
       number_ = -1;
   }
   else if (command_ == 'P')
   {
       if(number_ == -1)
       cout << current_expression_.get_postfix() << "\n";
       else if(number_ == -2)
           number_ = -1;
       else
       {
           cout << expression_vector_[number_ - 1].get_postfix() << "\n";
           number_ = -1;
       }
   }
   else if (command_ == 'T')
       if(number_ == -1)
       current_expression_.print_tree(cout);
       else if(number_ == -2)
           number_ = -1;
       else
       {
           expression_vector_[number_ -1].print_tree(cout);
           number_ = -1;
       }
   else if (command_ == 'V')
   {
       VT_.list(cout);
   }
   else if (command_ == 'X')
       VT_.clear();
   else if (command_ == 'S')
      cout << "Kalkylatorn avlutas, v�lkommen �ter!\n";
   else if (command_ == 'L')
   {
       int n = 1;
       for(auto it = expression_vector_.begin(); it != expression_vector_.end(); ++it)
       {
           cout << n << ": " << it->get_infix() << endl;
           ++n;
       }
   }
   else if (command_ == 'R')
   {
       if(number_ == -1)
       {
       expression_vector_.pop_back();
       current_expression_ = expression_vector_[expression_vector_.size() - 1];
       }
       else if(number_ == -2)
           number_ = -1;
       else
       {
           expression_vector_.erase(expression_vector_.begin()+(number_ - 1));
           number_ = -1;
       }
   }
   else if (command_ == 'I')
   {
       if(number_ == -1)
       cout << current_expression_.get_infix() << endl;
       else if (number_ == -2)
           number_ = -1;
       else
       {
           cout << expression_vector_[number_ - 1].get_infix() << endl;
           number_ = -1;
       }
   }
   else if (command_ == 'N')
   {
       cout << expression_vector_.size() << endl;
   }
   else if (command_ == 'A')
   {
       if(number_ == -1)
           cerr << "A m�ste ta in ett heltal" << endl;
       else if(number_ == -2)
           number_ = -1;
       else
       {
           current_expression_ = expression_vector_[number_ - 1];
           number_ = -1;
       }
       
   }
   else
      cout << "Detta ska inte h�nda!\n";
}

/**
 * read_expression: l�ser ett infixuttryck fr�n instr�mmen is och ger detta 
 * till funktionen make_expression() som returnerar ett objekt av typen 
 * Expression, vilket lagras som "aktuellt uttryck" i current_expression_.
 */
void
Calculator::
read_expression(istream& is)
{
   string infix;

   is >> ws;

   if (getline(is, infix))
   {
      current_expression_ = make_expression(infix);
   }
   else
   {
      cout << "Felaktig inmatning!\n";
   }
}
