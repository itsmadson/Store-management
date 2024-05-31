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
const string INVENTORY_FILE = "inventory.txt"; //make string of txt file

//this function echo frame and name of menu
void displayFrame(const string &title)
{
    cout << "**************************************\n";
    cout << "*  " << setw(33) << left << title << " *\n";
    cout << "**************************************\n";
}

//read product from inventory
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

//write product on inventory
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

//this function show us our inventory 
void displayInventory()
{
    displayFrame("Inventory");
    cout << "| Code |    Name    | Qty |   Price  |\n";
    cout << "+------+------------+-----+----------+\n";
    for (const auto &p : inventory)
    {
        cout << "| " << left << setw(4) << p.code << " | "
             << setw(8) << p.name << "   | " << setw(4) << p.quantity << "| "
             << fixed << setprecision(2) << setw(6) << p.price << " |\n";
    }
    cout << "+------+------------+-----+----------+\n";
}

//it gets all information from user & call the save inventory function to write that on our txt file
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
    cout << "hoooraaa,ur product added successfully.\n";
}

//detect which product user want to edit with (code) and then it find that row then change that and save it to inventory with our saveinventory function
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
        cout << "updated successfully.\n";
    }
    else
    {
        cout << "Product not found.\n";
    }
}

//find row of product with code, and then erase that line and save that
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

//i have nothing to say for this ZAYAS, brighter than day
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

/*this function make invoice cart, first it ask for product that customer buy.
and then find row of that product then check for quantity (maybe we dont have that quantity user want)
and then get customer name & find price of that product and + together and make total price

*/
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

//brighter than day, i just use ANSI yellow color code for terminal echo, and ask for which menu user want to go and call that function relative to it
int main()
{
    loadInventory();
    cout << "\033[33m";
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
