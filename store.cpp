#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Product
{
    string code;
    string name;
    int quantity;
    double price;
};

vector<Product> inventory;
const string INVENTORY_FILE = "inventory.txt";

void displayFrame(const string &title)
{
    cout << "*****************************\n";
    cout << "*  " << setw(23) << left << title << " *\n";
    cout << "*****************************\n";
}

void loadInventory()
{
    ifstream file(INVENTORY_FILE);
    if (file.is_open())
    {
        inventory.clear();
        Product p;
        while (file >> p.code >> p.name >> p.quantity >> p.price)
        {
            inventory.push_back(p);
        }
        file.close();
    }
}

void saveInventory()
{
    ofstream file(INVENTORY_FILE);
    if (file.is_open())
    {
        for (const auto &p : inventory)
        {
            file << p.code << " " << p.name << " " << p.quantity << " " << p.price << endl;
        }
        file.close();
    }
}

void displayInventory()
{
    displayFrame("Inventory");
    cout << "| Code | Name      | Qty | Price  |\n";
    cout << "+-----+----------+-----+--------+\n";
    for (const auto &p : inventory)
    {
        cout << "| " << left << setw(4) << p.code << " | "
             << setw(8) << p.name << " | " << setw(3) << p.quantity << " | "
             << fixed << setprecision(2) << setw(6) << p.price << " |\n";
    }
    cout << "+-----+----------+-----+--------+\n";
}

void addProduct()
{
    Product p;
    cout << "Enter product code: ";
    cin >> p.code;
    cout << "Enter product name: ";
    cin >> p.name;
    cout << "Enter quantity: ";
    cin >> p.quantity;
    cout << "Enter price: ";
    cin >> p.price;
    inventory.push_back(p);
    saveInventory();
    cout << "Product added successfully.\n";
}

void editProduct()
{
    string code;
    cout << "Enter product code to edit: ";
    cin >> code;
    auto it = find_if(inventory.begin(), inventory.end(), [&](const Product &p)
                      { return p.code == code; });
    if (it != inventory.end())
    {
        cout << "Enter new quantity: ";
        cin >> it->quantity;
        cout << "Enter new price: ";
        cin >> it->price;
        saveInventory();
        cout << "Product updated successfully.\n";
    }
    else
    {
        cout << "Product not found.\n";
    }
}

void removeProduct()
{
    string code;
    cout << "Enter product code to remove: ";
    cin >> code;
    auto it = remove_if(inventory.begin(), inventory.end(), [&](const Product &p)
                        { return p.code == code; });
    if (it != inventory.end())
    {
        inventory.erase(it, inventory.end());
        saveInventory();
        cout << "Product removed successfully.\n";
    }
    else
    {
        cout << "Product not found.\n";
    }
}

void manageInventory()
{
    int choice;
    do
    {
        displayFrame("Manage Inventory");
        cout << "1) Add Product\n";
        cout << "2) Edit Product\n";
        cout << "3) Remove Product\n";
        cout << "4) Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addProduct();
            break;
        case 2:
            editProduct();
            break;
        case 3:
            removeProduct();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void createCart()
{
    vector<pair<Product *, int>> cart;
    double totalPrice = 0;
    string input;

    do
    {
        displayInventory();
        cout << "Enter product code or name (or 'done' to finish): ";
        cin >> input;

        if (input == "done")
            break;

        auto it = find_if(inventory.begin(), inventory.end(), [&](const Product &p)
                          { return p.code == input || p.name == input; });

        if (it != inventory.end())
        {
            int qty;
            cout << "Enter quantity: ";
            cin >> qty;
            if (qty <= it->quantity)
            {
                cart.push_back(make_pair(&(*it), qty));
                it->quantity -= qty;
                totalPrice += it->price * qty;
            }
            else
            {
                cout << "Not enough stock. Available: " << it->quantity << endl;
            }
        }
        else
        {
            cout << "Product not found.\n";
        }
    } while (true);

    if (!cart.empty())
    {
        string customerName;
        cout << "Enter customer name: ";
        cin >> customerName;

        displayFrame("Invoice");
        cout << "Customer: " << customerName << endl;
        cout << "+-----+----------+-----+--------+--------+\n";
        cout << "| Code| Name     | Qty | Price  | Total  |\n";
        cout << "+-----+----------+-----+--------+--------+\n";

        for (const auto &item : cart)
        {
            Product *p = item.first;
            int qty = item.second;
            cout << "| " << left << setw(4) << p->code << " | "
                 << setw(8) << p->name << " | " << setw(3) << qty << " | "
                 << fixed << setprecision(2) << setw(6) << p->price << " | "
                 << setw(6) << p->price * qty << " |\n";
        }

        cout << "+-----+----------+-----+--------+--------+\n";
        cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;

        saveInventory();
    }
    else
    {
        cout << "Cart is empty.\n";
    }
}

int main()
{
    loadInventory();

    int choice;
    do
    {
        displayInventory();
        cout << "1) Manage Inventory\n";
        cout << "2) Create Cart\n";
        cout << "3) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            manageInventory();
            break;
        case 2:
            createCart();
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}