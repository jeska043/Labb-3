/*
 * expression_tree-test.cc
 */
#include "Expression_Tree.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

int main()
{
   cout << fixed << setprecision(2);
   // Ska inte vara m�jligt - Expression_Tree ska vara abstrakt:
   // Expression_Tree* t0{new Expression_Tree};

   Expression_Tree* t1{ new Power{ new Integer{6}, new Real{2} } };
   Expression_Tree* t_int{new Integer{99}};
   Expression_Tree* t_real{new Real{4.5}};
   try
   {
      cout << "t1->evaluate() = " << t1->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag f�ngat: " << e.what() << '\n';
   }

   cout << "t1->get_postfix() = " << t1->get_postfix() << '\n';

   cout << "t1->str() = " << t1->str() << "\n\n";
  cout << "t_int->str() = " << t_int->str() << "\n\n";
  cout << "t_real->str() = " << t_real->str() << "\n\n";

   Expression_Tree* t2{ t1->clone() };

   try
   {
      cout << "t2->evaluate() = " << t2->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag f�ngat: " << e.what() << '\n';
   }
   cout << "t2->get_postfix() = " << t2->get_postfix() << '\n';
   cout << "t2->str() = " << t2->str() << "\n\n";
  
   Expression_Tree* TEST{new Power{new Minus{new Integer{5},new Real{2}},new Integer{2}}};

   try
   {
      cout << "TEST->evaluate() = " << TEST->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag f�ngat: " << e.what() << '\n';
   }
   cout << "TEST->get_postfix() = " << TEST->get_postfix() << '\n';
   cout << "TEST->str() = " << TEST->str() << "\n\n";

Expression_Tree* TEST_CLONE{ TEST->clone() };

   try
   {
      cout << "TEST_CLONE->evaluate() = " << TEST_CLONE->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag f�ngat: " << e.what() << '\n';
   }
   cout << "TEST_CLONE->get_postfix() = " << TEST_CLONE->get_postfix() << '\n';
   cout << "TEST_CLONE->str() = " << TEST_CLONE->str() << "\n\n";

   Expression_Tree* assign1{new Assign{new Variable{"x"}, new Plus{new Integer{1},new Times{new Integer{2},new Integer{4}}}}};
   try
   {
      cout << "assign1->evaluate() = " << assign1->evaluate() << '\n';
   }
   catch (const exception& e)
   {
      cout << "Undantag f�ngat: " << e.what() << '\n';
   }
   cout << "assign1->get_postfix() = " << assign1->get_postfix() << '\n';
   cout << "assign1->str() = " << assign1->str() << endl;
   cout << "assign1->print(cout):" << endl;
   assign1->print(cout);
 
   Variable* var1{new Variable{"y"}};
   cout << "var1->get_value() = " << var1->get_value() << endl;
   cout << "var1->set_value(13.37);" << endl;
   var1->set_value(13.37);
   cout << "var1->get_value() = "<< var1->get_value() << endl;

   return 0;
}
