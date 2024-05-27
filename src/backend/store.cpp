#include "store.hpp"

void Store::addProduct(const Product &product)
{
    products.push_back(product);
    // Save products to file
}

void Store::removeProduct(int code)
{
    // Remove product and save to file
}

void Store::editProduct(int code, const Product &updatedProduct)
{
    // Edit product and save to file
}

std::vector<Product> Store::getProductsWithLowQuantity(int threshold)
{
    std::vector<Product> lowQuantityProducts;
    // Find products with quantity below threshold
    return lowQuantityProducts;
}

double Store::purchase(const std::vector<std::pair<int, int>> &cart)
{
    double total = 0.0;
    // Process cart and update product quantities
    return total;
}