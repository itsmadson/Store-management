#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product
{
private:
    int code;
    std::string name;
    int quantity;
    double price;

public:
    Product(int code, const std::string &name, int quantity, double price);

    int getCode() const;
    std::string getName() const;
    int getQuantity() const;
    double getPrice() const;

    void setCode(int code);
    void setName(const std::string &name);
    void setQuantity(int quantity);
    void setPrice(double price);
};

#endif // PRODUCT_HPP
