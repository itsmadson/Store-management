#include "product.hpp"

Product::Product(int code, const std::string &name, int quantity, double price)
    : code(code), name(name), quantity(quantity), price(price) {}

int Product::getCode() const
{
    return code;
}

std::string Product::getName() const
{
    return name;
}

int Product::getQuantity() const
{
    return quantity;
}

double Product::getPrice() const
{
    return price;
}

void Product::setCode(int code)
{
    this->code = code;
}

void Product::setName(const std::string &name)
{
    this->name = name;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Product::setPrice(double price)
{
    this->price = price;
}
