#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Constants for financial calculations (sales tax and discount thresholds/rates)
const float SALES_TAX_RATE = 0.08f;
const float DISC_THRESH_1 = 5000.0f, DISC_RATE_1 = 0.05f;
const float DISC_THRESH_2 = 10000.0f, DISC_RATE_2 = 0.10f;

// Structures to define data types for Products and Order Items
struct Product
{
    int id;
    string name;
    float price;
    int quantityInStock;
};
struct OrderItem
{
    int productId;
    string productName;
    float price;
    int quantity;
};

// Function prototypes for all modules/functions used in the program
void displayMenu();
void manageProducts(vector<Product> &inventory);
void placeOrder(vector<Product> &inventory);
void addProduct(vector<Product> &inventory);
void viewProducts(const vector<Product> &inventory);
Product *findProductById(vector<Product> &inventory, int id);
void calculateOrderSummary(const vector<OrderItem> &items, float &subtotal, float &discount, float &tax, float &total);
void clearInputBuffer();
void printFloat(float value);

// Main function: Initializes inventory and handles the primary application loop
int main()
{
    vector<Product> inventory = {{101, "Laptop", 85000.0f, 50}, {102, "Mouse", 1200.0f, 200}, {103, "Keyboard", 2500.0f, 150}};
    int choice;
    while (true)
    {
        displayMenu();
        cout << "Enter choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input." << endl;
            clearInputBuffer();
            continue;
        }
        switch (choice)
        {
        case 1:
            manageProducts(inventory);
            break;
        case 2:
            placeOrder(inventory);
            break;
        case 3:
            cout << "Exiting. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice." << endl;
        }
        cout << "\n";
    }
    return 0;
}

// Clears the input buffer after invalid input to prevent infinite loops
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

// Helper function to format and print float values to two decimal places manually (without iomanip)
void printFloat(float value)
{
    int intPart = static_cast<int>(value);
    int decPart = static_cast<int>((value - intPart) * 100 + 0.5f);
    if (decPart == 100)
    {
        intPart++;
        decPart = 0;
    }
    cout << intPart << "." << (decPart < 10 ? "0" : "") << decPart;
}

// Displays the main navigation options
void displayMenu()
{
    cout << "========== E-Commerce Order Management System ==========\n";
    cout << "1. Manage Products\n2. Place an Order\n3. Exit\n";
    cout << "========================================================" << endl;
}

// Manages the submenu for adding and viewing inventory
void manageProducts(vector<Product> &inventory)
{
    int choice;
    while (true)
    {
        cout << "\n--- Product Management Menu ---\n1. Add product\n2. View products\n3. Back to main menu\nEnter choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input." << endl;
            clearInputBuffer();
            continue;
        }
        switch (choice)
        {
        case 1:
            addProduct(inventory);
            break;
        case 2:
            viewProducts(inventory);
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

// Handles user input for new product details and adds it to the inventory vector
void addProduct(vector<Product> &inventory)
{
    Product np;
    cout << "Enter product ID: ";
    cin >> np.id;
    if (findProductById(inventory, np.id))
    {
        cout << "Error: Product ID exists." << endl;
        clearInputBuffer();
        return;
    }
    cout << "Enter name: ";
    clearInputBuffer();
    getline(cin, np.name);
    cout << "Enter price (Rs): ";
    cin >> np.price;
    cout << "Enter quantity in stock: ";
    cin >> np.quantityInStock;
    inventory.push_back(np);
    cout << "Product added successfully!" << endl;
}

// Displays the current inventory list in a formatted, non-aligned table
void viewProducts(const vector<Product> &inventory)
{
    cout << "\n--- Current Inventory ---\n";
    cout << "ID | Name | Price (Rs) | In Stock\n";
    cout << "--------------------------------\n";
    for (const auto &prod : inventory)
    {
        cout << prod.id << " | " << prod.name << " | ";
        printFloat(prod.price);
        cout << " | " << prod.quantityInStock << endl;
    }
}

// Helper function to search the inventory by ID and return a pointer to the product if found
Product *findProductById(vector<Product> &inventory, int id)
{
    for (int i = 0; i < inventory.size(); ++i)
        if (inventory[i].id == id)
            return &inventory[i];
    return nullptr;
}

// Manages the end-to-end order process: item selection, stock check, summary display, and stock reduction
void placeOrder(vector<Product> &inventory)
{
    vector<OrderItem> co;
    int pid, qty;
    char am = 'y';
    while (am == 'y' || am == 'Y')
    {
        viewProducts(inventory);
        cout << "\nEnter product ID to order: ";
        if (!(cin >> pid))
        {
            cout << "Invalid input." << endl;
            clearInputBuffer();
            continue;
        }
        Product *p = findProductById(inventory, pid);
        if (!p)
        {
            cout << "Product not found." << endl;
            continue;
        }
        cout << "Enter quantity: ";
       cin>>qty;

        if (qty > p->quantityInStock || qty <= 0)
            cout << "Error: Invalid quantity or not enough stock." << endl;
        else
        {
            co.push_back({p->id, p->name, p->price, qty});
            p->quantityInStock -= qty; // Update stock immediately upon adding to order
            cout << "Item added." << endl;
        }
        cout << "Add another item? (y/n): ";
        cin >> am;
    }

    if (!co.empty())
    {
        float sub, dis, tax, tot;
        calculateOrderSummary(co, sub, dis, tax, tot); // Calculate financial details
        // Display summary details using the printFloat helper
        cout << "\n========== Order Summary ==========\nItem | Price | Qty | Total\n--------------------------------\n";
        for (const auto &item : co)
        {
            cout << item.productName << " | ";
            printFloat(item.price);
            cout << " | " << item.quantity << " | ";
            printFloat(item.price * item.quantity);
            cout << endl;
        }
        cout << "--------------------------------\n";
        cout << "Subtotal: Rs ";
        printFloat(sub);
        cout << endl;
        cout << "Discount Applied: Rs ";
        printFloat(dis);
        cout << endl;
        cout << "Sales Tax (" << (SALES_TAX_RATE * 100) << "%): Rs ";
        printFloat(tax);
        cout << endl;
        cout << "Total Cost: Rs ";
        printFloat(tot);
        cout << "\n=======================================" << endl;
    }
    else
    {
        cout << "Order cancelled or empty." << endl;
    }
}

// Applies discount rules and calculates final tax and total cost based on the order items
void calculateOrderSummary(const vector<OrderItem> &items, float &subtotal, float &discount, float &tax, float &total)
{
    subtotal = 0.0f;
    for (const auto &item : items)
        subtotal += item.price * item.quantity;
    discount = 0.0f;
    // Determine the highest applicable discount tier
    if (subtotal >= DISC_THRESH_2)
        discount = subtotal * DISC_RATE_2;
    else if (subtotal >= DISC_THRESH_1)
        discount = subtotal * DISC_RATE_1;
    float amountAfterDiscount = subtotal - discount;
    tax = amountAfterDiscount * SALES_TAX_RATE;
    total = amountAfterDiscount + tax;
}
