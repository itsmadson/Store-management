#include "store.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

void Store::addProduct(const Product &product)
{
    products.push_back(product);
}

void Store::removeProduct(int code)
{
    products.erase(std::remove_if(products.begin(), products.end(), [code](const Product &p)
                                  { return p.getCode() == code; }),
                   products.end());
}

void Store::editProduct(int code, const Product &updatedProduct)
{
    for (auto &p : products)
    {
        if (p.getCode() == code)
        {
            p = updatedProduct;
            break;
        }
    }
}

void Store::purchase(const std::vector<std::pair<int, int>> &cart)
{
    for (const auto &item : cart)
    {
        int code = item.first;
        int quantity = item.second;
        for (auto &p : products)
        {
            if (p.getCode() == code)
            {
                p.setQuantity(p.getQuantity() - quantity);
                break;
            }
        }
    }
}

void Store::loadProductsFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        products.clear();
        int code, quantity;
        double price;
        std::string name;
        while (file >> code >> name >> quantity >> price)
        {
            Product product(code, name, quantity, price);
            products.push_back(product);
        }
        file.close();
    }
}

void Store::saveProductsToFile(const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (const auto &p : products)
        {
            file << p.getCode() << " " << p.getName() << " " << p.getQuantity() << " " << p.getPrice() << "\n";
        }
        file.close();
    }
}

std::vector<Product> Store::getProductsWithLowQuantity(int threshold) const
{
    std::vector<Product> lowQuantityProducts;
    for (const auto &p : products)
    {
        if (p.getQuantity() < threshold)
        {
            lowQuantityProducts.push_back(p);
        }
    }
    return lowQuantityProducts;
}

void Store::replenishStock(int code, int quantity)
{
    for (auto &p : products)
    {
        if (p.getCode() == code)
        {
            p.setQuantity(p.getQuantity() + quantity);
            break;
        }
    }
}

void Store::generateInvoice(const std::vector<std::pair<int, int>> &cart, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "Sales Invoice\n\n";
        file << "Code\tName\tQuantity\tPrice\tTotal\n";
        double total = 0.0;
        for (const auto &item : cart)
        {
            int code = item.first;
            int quantity = item.second;
            auto product = std::find_if(products.begin(), products.end(), [code](const Product &p)
                                        { return p.getCode() == code; });
            if (product != products.end())
            {
                double price = product->getPrice();
                double itemTotal = price * quantity;
                file << product->getCode() << "\t" << product->getName() << "\t" << quantity << "\t" << price << "\t" << itemTotal << "\n";
                total += itemTotal;
            }
        }
        file << "\nTotal: " << total << "\n";
        file.close();
    }
}