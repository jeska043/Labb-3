#include "Variable_Table.h"

using namespace std;

void Variable_Table::insert(const string& name, long double value)
{
    variable_table.insert(pair<string,long double>(name,value));
}

void Variable_Table::remove(const string& name)
{
    variable_table.erase(name);
}

bool Variable_Table::find(const string& name)
{
    return (! (variable_table.count(name) == 0));
}

void Variable_Table::set_value(const string& name, long double value)
{
    variable_table.find(name)->second = value; 
}

long double Variable_Table::get_value(const string& name)
{
    long double answer{variable_table.find(name)->second};
    return answer;
}

void Variable_Table::list(ostream& os)
{
    for(map<string,long double>::iterator it = variable_table.begin();
        it != variable_table.end(); ++it)
        os << it->first << ": " << it->second << endl;
}

void Variable_Table::clear()
{
    for(map<string,long double>::iterator it{variable_table.begin()};
        it != variable_table.end(); ++it)
        variable_table.erase(it);
}

bool Variable_Table::empty()
{
    return variable_table.empty();
} 
