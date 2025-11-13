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

    while (i < (sizeof(items) / sizeof(items[0])))
    {
        if (ordered_item == items[i])
        {
            if (quantity <= qua[i])
            {
                bill = bill + quantity * price[i];
                qua[i] = qua[i] - quantity;
                return bill;
            }
            else
            {
                cout << "Sorry! We have only " << qua[i] << " " << items[i] << " in stock" << endl;
                return bill;
            }
        }
        else
        {
            i++;
            continue;
        }

        cout << "Item not found in menu. Please enter a valid item name." << endl;
        cout << "Please reorder your items." << endl;

        display_menu();
        taking_order();
        repeat_order();
    }

    return bill;
}

// Function to show bill details
float display_bill(float bill)
{
    int tax = 0, discount = 0;
    cout << endl;
    cout << "****************BILL****************" << endl;
    cout << "Your bill amount is : " << bill << endl;

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

    cout << "Please enter the item name you want to order : ";
    cin >> ordered_item;
    cout << "Enter the quantity of " << ordered_item << " : ";
    cin >> quantity;

    ordered_items.push_back(ordered_item);
    quantities.push_back(quantity);

    do
    {
        bill = bill + bill_calculator(ordered_item, quantity);

        cout << "Enter other item name you want to order (or 'c' to complete order or 'r' to reorder): ";
        cin >> ordered_item;

        if (ordered_item == "r")
        {
            bill = 0;
            taking_order();
            return;
        }

        if (ordered_item == "c")
        {
            display_bill(bill);
            show_order_summary(ordered_items, quantities);
            break;
        }

        cout << "Enter the quantity of " << ordered_item << " : ";
        cin >> quantity;
        ordered_items.push_back(ordered_item);
        quantities.push_back(quantity);

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
        display_menu();
        taking_order();
    }
    else
    {
        cout << "Thank you for visiting us!" << endl;
    }
}

int main()
{
    display_menu();
    taking_order();
    repeat_order();
    return 0;
}

