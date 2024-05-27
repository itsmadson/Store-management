#pragma once
#include <vector>
#include "product.hpp"

class Store
{
public:
    std::vector<Product> products;

    void addProduct(const Product &product);
    void removeProduct(int code);
    void editProduct(int code, const Product &updatedProduct);
    std::vector<Product> getProductsWithLowQuantity(int threshold);
    double purchase(const std::vector<std::pair<int, int>> &cart);
};