#include "Variable_Table.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;

int main()
{
Variable_Table VT1;
cout << "Sätter in x=5 och y=10 i VT1." << endl;
VT1.insert("x",5);
VT1.insert("y",10);
cout << "Skriver ut VT1 med list:" << endl;
VT1.list(cout);
VT1.remove("x");
cout << "Tar bort x från VT1 med remove." << endl;
cout << "Skriver ut VT1 med list:" << endl;
VT1.list(cout);
cout << "Kollar med find om y finns i tabellen." << endl;
if(VT1.find("y"))
    cout << "FINNS" << endl;
else
    cout << "FINNS EJ" << endl;

cout << "Kollar med find om x finns i tabellen." << endl;
if(VT1.find("x"))
    cout << "FINNS" << endl;
else
    cout << "FINNS EJ" << endl;

cout << "Ändrar y:s värde med set_value till 13.37" << endl;
VT1.set_value("y",13.37);
cout << "Skriver ut VT1 med list:" << endl;
VT1.list(cout);

cout << "Kör get_value på y och skriver ut det:" << endl;
cout << VT1.get_value("y") << endl;

cout << "Kör empty() på VT1:" << endl;
if(VT1.empty())
    cout << "TOM TABELL" << endl;
else
    cout << "TABELL EJ TOM" << endl;

cout << "Kör clear() på VT1." << endl;
VT1.clear();
cout << "Kör empty() på VT1:" << endl;
if(VT1.empty())
    cout << "TOM TABELL" << endl;
else
    cout << "TABELL EJ TOM" << endl;


return 0;
}
