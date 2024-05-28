#ifndef STORE_HPP
#define STORE_HPP

#include "product.hpp"
#include <vector>
#include <string>

class Store
{
private:
    std::vector<Product> products;

public:
    void addProduct(const Product &product);
    void removeProduct(int code);
    void editProduct(int code, const Product &updatedProduct);
    void purchase(const std::vector<std::pair<int, int>> &cart);
    void loadProductsFromFile(const std::string &filename);
    void saveProductsToFile(const std::string &filename);
    std::vector<Product> getProductsWithLowQuantity(int threshold) const;
    void replenishStock(int code, int quantity);
    void generateInvoice(const std::vector<std::pair<int, int>> &cart, const std::string &filename);
};

#endif // STORE_HPP