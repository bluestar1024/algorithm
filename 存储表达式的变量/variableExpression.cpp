#include <iostream>
#include <memory>
#include <string>  
#include <cmath>

class SYMBOL
{
private:
    double value;
    std::string name;

public:
    SYMBOL() : value(0), name("unknow") {}
    SYMBOL(std::string name) : value(0), name(name) {}
    SYMBOL(double value) : value(value), name(std::to_string(value)) {}
    void set_value(double in)
    {
        value = in;
    }
    double get_value()
    {
        return value;
    }
    std::string get_name()
    {
        return name;
    }
};

class EXPRESSION
{
private:
    std::shared_ptr<SYMBOL> symbol;
    char op;
    std::shared_ptr<EXPRESSION> a;
    std::shared_ptr<EXPRESSION> b;

public:
    EXPRESSION() : op('\0'), a(nullptr), b(nullptr), symbol(nullptr) {}
    EXPRESSION(std::shared_ptr<SYMBOL> symbol) : op('\0'), a(nullptr), b(nullptr), symbol(symbol) {}
    EXPRESSION(std::shared_ptr<EXPRESSION> a, std::shared_ptr<EXPRESSION> b, char op) : a(a), b(b), op(op), symbol(nullptr) {}
    double get_value()
    {
        if(symbol == nullptr)
        {
            switch(op)
            {
                case '+':
                    return a->get_value() + b->get_value();
                case '-':
                    return a->get_value() - b->get_value();
                case '*':
                    return a->get_value() * b->get_value();
                case '/':
                    return a->get_value() / b->get_value();
                case '^':
                    return pow(a->get_value(), b->get_value());
                default:
                    return -999999999;
            }
        }
        else
            return symbol->get_value();
    }
    std::string toString() const
    {
        if (op == '\0')
        {
            return symbol->get_name();
        }
        else
        {
            return "(" + a->toString() + std::string(1, op) + b->toString() + ")";
        }
    }
};

class VAR
{
private:
    std::shared_ptr<EXPRESSION> expression;
    std::shared_ptr<SYMBOL> symbol;
    VAR(const VAR &a, const VAR &b, char op)
    {
        symbol = nullptr;
        expression = std::make_shared<EXPRESSION>(a.expression, b.expression, op);
    }

public:
    VAR()
    {
        symbol = std::make_shared<SYMBOL>();
        expression = std::make_shared<EXPRESSION>(symbol);
    }
    VAR(std::string name)
    {
        symbol = std::make_shared<SYMBOL>(name);
        expression = std::make_shared<EXPRESSION>(symbol);
    }
    VAR(double value)
    {
        symbol = std::make_shared<SYMBOL>(value);
        expression = std::make_shared<EXPRESSION>(symbol);
    }
    double get_value()
    {
        return expression->get_value();
    }
    void operator=(double value)
    {
        if (symbol == nullptr)
        {
            symbol = std::make_shared<SYMBOL>(value);
            expression = std::make_shared<EXPRESSION>(symbol);
        }
        else
        {
            symbol->set_value(value);
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const VAR &var)
    {
        os << var.expression->toString();
        return os;
    }
    friend VAR operator+(const VAR &in, const VAR &var)
    {
        return VAR(in, var, '+');
    }
    friend VAR operator-(const VAR &in, const VAR &var)
    {
        return VAR(in, var, '-');
    }
    friend VAR operator*(const VAR &in, const VAR &var)
    {
        return VAR(in, var, '*');
    }
    friend VAR operator/(const VAR &in, const VAR &var)
    {
        return VAR(in, var, '/');
    }
    friend VAR operator^(const VAR &in, const VAR &var)
    {
        return VAR(in, var, '^');
    }
};

int main()
{
    VAR loss("loss");
    VAR x("x");
    VAR y("y");
    int z = 5;
    loss = (x + y)*x - z*x + y;
    x = 3;
    y = 4;
    std::cout << "loss = " << loss << std::endl;
    std::cout << "loss.get_value() = " << loss.get_value() << std::endl;
    return 0;
}
