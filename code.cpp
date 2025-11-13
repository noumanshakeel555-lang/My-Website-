#include <iostream>
#include <string>
#include <vector>
using namespace std;

// List of items available in the menu
string items[] = {"wings", "pizza", "pasta", "rotti", "momos", "nimko"};
// Prices for each item
int price[] = {250, 460, 340, 340, 220, 120};
// Quantity of each item in stock
int qua[] = {20, 60, 34, 34, 22, 12};

// Function declarations
void taking_order();
void repeat_order();

// Function to show the menu to the customer
void display_menu()
{
    cout << "_________________MENU________________" << endl;
    cout << "  Items      |    Price  |  In Stock |" << endl;

    // Loop through all items and show their name, price, and available stock
    for (int i = 1; i <= sizeof(items) / sizeof(items[i]); i++)
    {
        cout << i << ". " << items[i - 1] << "     |    " << price[i - 1]
             << "    |    " << qua[i - 1] << "     |" << endl;
    }

    cout << "_____________________________________" << endl;
    cout << endl;
    cout << "There is discount of 5% on bill if bill exceeds 5000." << endl;
    cout << "There is discount of 10% on bill if bill exceeds 10000." << endl;
    cout << "There is additional tax of 8% on total bill amount." << endl;
    cout << endl;
    cout << "****************Place order*******************" << endl;
}

// Function to calculate bill for one item
float bill_calculator(string ordered_item, int quantity)
{
    float bill = 0;
    int i = 0;

    // Loop through all items to find the one the user entered
    while (i < (sizeof(items) / sizeof(items[0])))
    {
        if (ordered_item == items[i])
        {
            // Check if the requested quantity is available
            if (quantity <= qua[i])
            {
                // Add item cost to total bill and reduce stock
                bill = bill + quantity * price[i];
                qua[i] = qua[i] - quantity;
                return bill;
            }
            else
            {
                // If not enough stock, tell the user
                cout << "Sorry! We have only " << qua[i] << " " << items[i] << " in stock" << endl;
                return bill;
            }
        }
        else
        {
            
            i++;
            continue;
        }
        // If item is not found in menu
            cout << "Item not found in menu. Please enter a valid item name." << endl;
            cout << "Please reorder your items." << endl;

            // Show menu again and restart order process
            display_menu();
            taking_order();
            repeat_order();
    }

    
}

// Function to show bill details
float display_bill(float bill)
{
    int tax = 0, discount = 0;
    cout << endl;
    cout << "****************BILL****************" << endl;
    cout << "Your bill amount is : " << bill << endl;

    // Apply discounts depending on bill amount
    if ((bill > 5000) && (bill <= 10000))
    {
        discount = 0.05 * bill;
        cout << "Your discount is : " << discount << endl;
        cout << "Bill after discount is : " << (bill - discount) << endl;
    }

    if (bill > 10000)
    {
        discount = 0.1 * bill;
        cout << "Your discount is : " << discount << endl;
        cout << "Bill after discount is : " << (bill - discount) << endl;
    }

    // Add 8% tax on bill
    tax = 0.08 * bill;
    cout << "Tax on your bill is : " << tax << endl;
    cout << "Bill + tax is : " << bill + tax << endl;
    cout << "***********************************" << endl;

    return bill + tax - discount;
}

// Function to show what user ordered
void show_order_summary(vector<string> ordered_items, vector<int> quantities)
{
    cout << endl;
    cout << "***********ORDER SUMMARY**********" << endl;
    cout << "Item Name   Quantity" << endl;

    // Display all ordered items and their quantities
    for (int i = 0; i < quantities.size(); i++)
    {
        cout << ordered_items[i] << "         " << quantities[i] << endl;
    }

    cout << "************************************" << endl;
}

// Function to take order from customer
void taking_order()
{
    vector<string> ordered_items;
    vector<int> quantities;
    int quantity = 0;
    float bill = 0;
    string ordered_item;

    // Ask user to enter first item
    cout << "Please enter the item name you want to order : ";
    cin >> ordered_item;
    cout << "Enter the quantity of " << ordered_item << " : ";
    cin >> quantity;

    // Save the ordered item and quantity
    ordered_items.push_back(ordered_item);
    quantities.push_back(quantity);

    do
    {
        // Add the cost of the current item to the total bill
        bill = bill + bill_calculator(ordered_item, quantity);

        // Ask if the user wants to add more items or complete the order
        cout << "Enter other item name you want to order (or 'c' to complete order or 'r' to reorder): ";
        cin >> ordered_item;

        if (ordered_item == "r")
        {
            // Restart the whole ordering process
            bill = 0;
            taking_order();
        }

        if (ordered_item == "c")
        {
            // If user finishes ordering, show bill and order summary
            display_bill(bill);
            show_order_summary(ordered_items, quantities);
            break;
        }

        // Save next item and quantity
        ordered_items.push_back(ordered_item);
        quantities.push_back(quantity);
        cout << "Enter the quantity of " << ordered_item << " : ";
        cin >> quantity;

    } while (ordered_item != "c");
}

// Function to ask if customer wants to order again
void repeat_order()
{
    cout << "Do you want to order again? (y/n) : ";
    char ch;
    cin >> ch;

    if (ch == 'y')
    {
        // If yes, show menu again
        display_menu();
        taking_order();
    }
    else
    {
        cout << "Thank you for visiting us!" << endl;
    }
}

// Main function — program starts here
int main()
{
    display_menu();     // Show the menu first
    taking_order();     // Take user's order
    repeat_order();     // Ask if they want to order again
    return 0;
}
