#ifndef VARIABLETABLE_H
#define VARIABLETABLE_H
#include <iosfwd>
#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

using var_map = std::map<std::string,long double>;

class variable_table_error : public std::logic_error
{
public:
    explicit variable_table_error (const std::string& message) noexcept
        : std::logic_error{message} {}

    explicit variable_table_error (const char* message) noexcept
        : std::logic_error{message} {}
};

class Variable_Table
{
public:
    ~Variable_Table() = default;
    Variable_Table() = default;
    void insert(const std::string&, long double);
    void remove(const std::string&);
    bool find(const std::string&);
    void set_value(const std::string&, long double);
    long double get_value(const std::string&);
    void list(std::ostream&);
    void clear();
    bool empty();

private:
    var_map variable_table;
};

#endif
