#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include "header.h"
using namespace std;

// User Class
// constructor for user class
User::User()
{
    userId = "";
    userName = "";
    Password = "";
    userType = "";
    isLoggedIn = false;
}

// parametrized constructor for user class
User::User(string id, string name, string pass, string type)
{
    userId = id;
    userName = name;
    Password = pass;
    userType = type;
    isLoggedIn = false;
}

// below are getter and setters
bool User::IsLoggedIn()
{
    return isLoggedIn;
}

void User::setUserId(string id)
{
    userId = id;
}
void User::setUserName(string name)
{
    userName = name;
}
void User::setPassword(string pass)
{
    Password = pass;
}
void User::setUserType(string type)
{
    userType = type;
}
string User::getUserId() const
{
    return userId;
}
string User::getUserName() const
{
    return userName;
}
string User::getPassword() const
{
    return Password;
}
string User::getUserType() const
{
    return userType;
}

// below are pure virtual functions
void User::Register()
{
    // Implementation of Register function goes here
}
void User::Login()
{
    // Implementation of Login function goes here
}

//--------------------------------------------------------------------

// Customer Class
int Customer::customercount = 0;
Customer::Customer() : admin_instance(admin_instance)
{
    userId = "";
    userName = "";
    Password = "";
    userType = "";
    isLoggedIn = false;
}
Customer::Customer(string id, string name, string pass, string type) : User(id, name, pass, type) {}

void Customer::setadmin(Admin *admin_instance)
{
    this->admin_instance = admin_instance; // by aggregation
}

void Customer::Register()
{
    // new customer wants to register
    cout << "Enter customerId: ";
    cin >> userId;
    cout << "Enter customerName: ";
    cin >> userName;
    setUserName(userName);
    cout << "Enter password(4-digit): ";
    cin >> Password;
    cout << "Enter userType: ";
    cin >> userType;
    setUserId(userId);
    setPassword(Password);
    setUserType(userType);
    // storing data of new customer to file
    fstream newcustomer;
    newcustomer.open("UserData.txt", ios::app);
    newcustomer << "------------------------------------------New Customer MemberData\n";
    newcustomer << userId << "  " << userName << "   " << Password << "   " << userType << endl;
    newcustomer.close();
    cout << "New Customer has been Registered\n";
}
// method if customer wants to login
void Customer::Login()
{
    cout << "\nCustomer is logged In.\n";
    isLoggedIn = true;
}
// method to view menu
void Customer::ViewMenu(int menu_choice)
{
    admin_instance->ViewMenu(menu_choice);
}
// method to place order
void Customer::PlaceOrder(int menu_choice)
{
    bool flag = false;
    // placing order in student menu
    if (menu_choice == 1)
    {
        admin_instance->ViewMenu(1);
    up:
        cout << "Select items from Student Menu..\n";

        int adding_items = -1;
        // loop untill add items to cart
        while (true)
        {
            cout << "Do u want add item (1=Yes,0=No): ";
            cin >> adding_items;
            if (adding_items == 0)
            {
                break;
            }
            string item_name;
            int quantity;
            cout << "Enter the item name: ";
            cin.ignore();
            getline(cin, item_name);
            cout << "Enter the quantity: ";
            cin >> quantity;
            for (int i = 0; i < 10; i++)
            {
                if (item_name == admin_instance->Stu_menu[i].getItemName())
                {
                    if (quantity <= admin_instance->Stu_menu[i].getQuantityInStock())
                    {
                        string temp = admin_instance->Stu_menu[i].getItemId();
                        flag = true;
                        selected_items_student[i] = quantity;
                        order_instance.AddItem(temp, quantity);
                        admin_instance->Stu_menu->setQuantityInStock(admin_instance->Stu_menu->getQuantityInStock() - quantity);
                        total_price += admin_instance->Stu_menu[i].getPrice() * quantity;
                        break;
                    }
                    else
                    {
                        cout << "Quantity not available" << endl;
                        flag = true;
                    }
                }
            }
            if (flag == false)
            {
                cout << "Item not found" << endl;
            }
        }

        // saving all data to order class
        srand(time(0));
        int x = rand() % 10;
        order_instance.setOrderId(to_string(x));
        order_instance.setCustomerId(userId);
        order_instance.setTotalPrice(total_price);
        order_instance.setOrderStatus("Pending");
    }
    // placing order in faculty menu
    else if (menu_choice == 2)
    {
        int choice;
        cout << "From which menu u want to place order...\n";
        cout << "---------------------\n";
        cout << "|1.Student Menu     |\n";
        cout << "|2.Faculty Menu     |\n";
        cout << "|3.Non-Faculty      |\n";
        cout << "---------------------\n";
        cout << "Enter your choice(1-3): ";
        cin >> choice;
        if (choice == 1)
        {
            goto up;
        }
        else if (choice == 2)
        {
            int adding_items = -1;
            while (true)
            {
                cout << "Do u want add item (1=Yes,0=No): ";
                cin >> adding_items;
                if (adding_items == 0)
                {
                    break;
                }
                string item_name;
                int quantity;
                cout << "Enter the item name: ";
                cin.ignore();
                getline(cin, item_name);
                cout << "Enter the quantity: ";
                cin >> quantity;
                for (int i = 0; i < 10; i++)
                {
                    if (item_name == admin_instance->Fac_menu[i].getItemName())
                    {
                        if (quantity <= admin_instance->Fac_menu[i].getQuantityInStock())
                        {
                            string temp = admin_instance->Fac_menu[i].getItemId();
                            flag = true;
                            selected_items_student[i] = quantity;
                            order_instance.AddItem(temp, quantity);
                            admin_instance->Fac_menu->setQuantityInStock(admin_instance->Fac_menu->getQuantityInStock() - quantity);
                            total_price += admin_instance->Fac_menu[i].getPrice() * quantity;
                            break;
                        }
                        else
                        {
                            cout << "Quantity not available" << endl;
                            flag = true;
                        }
                    }
                }
                if (flag == false)
                {
                    cout << "Item not found" << endl;
                }
            }
            // storing all order in order class
            srand(time(0));
            int x = rand() % 10;
            order_instance.setOrderId(to_string(x));
            order_instance.setCustomerId(userId);
            order_instance.setTotalPrice(total_price);
            order_instance.setOrderStatus("Pending");
        }
        else if (choice == 3)
        {
            goto down;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
    // placing order in non faculty menu
    else if (menu_choice == 3)
    {
        admin_instance->ViewMenu(3);
    down:
        cout << "Select items from Non-Faculty Menu..\n";
        int adding_items = -1;
        while (true)
        {
            cout << "Do u want add item (1=Yes,0=No): ";
            cin >> adding_items;
            if (adding_items == 0)
            {
                break;
            }
            string item_name;
            int quantity;
            cout << "Enter the item name: ";
            cin.ignore();
            getline(cin, item_name);
            cout << "Enter the quantity: ";
            cin >> quantity;
            for (int i = 0; i < 10; i++)
            {
                if (item_name == admin_instance->NF_menu[i].getItemName())
                {
                    if (quantity <= admin_instance->NF_menu[i].getQuantityInStock())
                    {
                        string temp = admin_instance->NF_menu[i].getItemId();
                        flag = true;
                        selected_items_student[i] = quantity;
                        order_instance.AddItem(temp, quantity);
                        admin_instance->NF_menu->setQuantityInStock(admin_instance->NF_menu->getQuantityInStock() - quantity);
                        total_price += admin_instance->NF_menu[i].getPrice() * quantity;
                        break;
                    }
                    else
                    {
                        cout << "Quantity not available" << endl;
                        flag = true;
                    }
                }
            }
            if (flag == false)
            {
                cout << "Item not found" << endl;
            }
        }

        // storing all order in order class
        srand(time(0));
        int x = rand() % 10;
        order_instance.setOrderId(to_string(x));
        order_instance.setCustomerId(userId);
        order_instance.setTotalPrice(total_price);
        order_instance.setOrderStatus("Pending");
    }
    else
    {
        cout << "Invalid choice" << endl;
    }

    int choice = 0;
    // displaying menu to user
    while (choice != 6)
    {
        cout << "------------------------\n";
        cout << "|1.Review Order        |\n";
        cout << "|2.Remove Item         |\n";
        cout << "|3.Calculate Total     |\n";
        cout << "|4.Confirm Order       |\n";
        cout << "|5.Cancel Order        |\n";
        cout << "|6.Back                |\n";
        cout << "------------------------\n";
        cout << "Enter your choice(1-6): ";
        cin >> choice;
        // if user wants to review order
        if (choice == 1)
        {
            order_instance.revieworder();
        }
        // if user wants to remove item
        else if (choice == 2)
        {
            order_instance.RemoveItem();
        }
        // if user wants to calculate total price
        else if (choice == 3)
        {
            order_instance.CalculateTotalPrice();
        }
        // if user wants to confirm order
        else if (choice == 4)
        {
            // staff will process order
            staff_instance.ProcessOrder();
            // then payment process will occur
            order_instance.ConfirmOrder();
        }
        // if user wants to cancel order
        else if (choice == 5)
        {
            order_instance.CancelOrder();
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}
// if user wants to view order history
void Customer::ViewOrderHistory()
{
    order_instance.revieworder();
}
// if user wants to rate item
void Customer::RateItem()
{
    int choice;

    cout << "From which menu u want to rate the item? \n";
    cout << "---------------------\n";
    cout << "|1.Student Menu     |\n";
    cout << "|2.Faculty Menu     |\n";
    cout << "|3.Non-Faculty      |\n";
    cout << "---------------------\n";
    cout << "Enter your choice(1-3): ";
    cin >> choice;
    // rating student menu items
    if (choice == 1)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to rate: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < admin_instance->Stu_itemcount; i++)
        {
            if (admin_instance->Stu_menu[i].getItemName() == name)
            {
                string id = admin_instance->Stu_menu[i].getItemId();
                string customerid = admin_instance->getUserId();
                itemfound = true;
                rating_instance.Rate(name, id, customerid);
                break;
            }
        }
        if (itemfound == false)
        {
            cout << "Item not found" << endl;
        }
    }
    // rating faculty menu items
    else if (choice == 2)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to rate: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < admin_instance->Fac_itemcount; i++)
        {
            if (admin_instance->Fac_menu[i].getItemName() == name)
            {
                string id = admin_instance->Fac_menu[i].getItemId();
                string customerid = admin_instance->getUserId();
                itemfound = true;
                rating_instance.Rate(name, id, customerid);
                break;
            }
        }
        if (!itemfound)
        {
            cout << "Item not found" << endl;
        }
    }
    // rating non faculty menu items
    else if (choice == 3)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to rate: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < admin_instance->NF_itemcount; i++)
        {
            if (admin_instance->NF_menu[i].getItemName() == name)
            {
                string id = admin_instance->NF_menu[i].getItemId();
                string customerid = admin_instance->getUserId();
                itemfound = true;
                rating_instance.Rate(name, id, customerid);
                break;
            }
        }
        if (itemfound == false)
        {
            cout << "Item not found" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}

void Customer::Logout() {}
// operator overloading
void *Customer::operator new[](size_t s)
{
    void *p = ::operator new[](s);
    return p;
}
// destructor for customer
Customer::~Customer()
{
    customercount--;
    delete admin_instance;
}

// -------------------------------------------------------------

// Staff Class
int Staff::staffcount = 0;
// constructor
Staff::Staff() : admin_instance(admin_instance)
{
    userId = "";
    userName = "";
    Password = "";
    userType = "";
    isLoggedIn = false;
}
// parametrized constructor
Staff::Staff(string id, string name, string pass, string type) : User(id, name, pass, type) {}

// using aggregation
void Staff::setadmin(Admin *admin_instance)
{
    this->admin_instance = admin_instance; // by use of aggregation concept
}
// if staff member wants to register
void Staff::Register()
{
    // taking his credentilas
    cout << "Enter staffId: ";
    cin >> userId;
    cout << "Enter staffName: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> Password;
    cout << "Enter userType: ";
    cin >> userType;
    setUserId(userId);
    setUserName(userName);
    setPassword(Password);
    setUserType(userType);
    cout << "New Staff Member has been Registered\n";
    // writing new member to files
    fstream newstaffmember;
    newstaffmember.open("UserData.txt", ios::app);
    newstaffmember << "--------------------------------New Staff MemberData\n";
    newstaffmember << userId << "  " << userName << "   " << Password << "   " << userType << endl;
    newstaffmember.close();
    staffcount++;
}
// if staff member wants to login
void Staff::Login()
{
    cout << "\nStaff Member is logged In.\n";
    isLoggedIn = true;
}
// if staff member wants to view menu
void Staff::ViewMenu()
{
    admin_instance->ViewMenu(0); // by use of aggregation concept
}
// if staff member wants to process order
void Staff::ProcessOrder()
{
    string tempPass, pass1, pass2;
    string tempID, actualid1, actualid2;
    cout << "\nNow a staff member is processing the order placed...\n";
up:
    cout << "Enter login id: ";
    actualid1 = "staff1";
    actualid2 = "staff2";
    pass1 = "1111";
    pass2 = "2222";
    cin >> tempID;
    cout << "Enter password: ";
    cin >> tempPass;
    // validating the staff member
    if ((tempID == actualid1 && tempPass == pass1) || (tempID == actualid2 && tempPass == pass2))
    {
        cout << "Order is being processed\n";
        order_instance.setOrderStatus("Processing");
    }
    else
    {
        cout << "Invalid login id or password\n";
        cout << "Enter valid login id & Password\n";
        goto up;
    }
}
// if staff member wants to add item in menus
void Staff::AddMenuItem()
{
    string id, name, des;
    double price;
    int quantity;
    cout << "Enter Item Id: ";
    cin.ignore();
    getline(cin, id);
    cout << "Enter Item Name: ";
    getline(cin, name);
    cout << "Enter Item Description: ";
    getline(cin, des);
    cout << "Enter Item Price: ";
    cin >> price;
    cout << "Enter Item Quantity: ";
    cin >> quantity;
    cout << "In which menu u want to add new item?\n";
    int selectmenu;
    cout << "---------------------\n";
    cout << "|1.Student Menu     |\n";
    cout << "|2.Faculty Menu     |\n";
    cout << "|3.Non-Faculty      |\n";
    cout << "---------------------\n";
    cout << "Enter your choice(1-3): ";
    cin >> selectmenu;
    // adding item in stdent menu
    if (selectmenu == 1)
    {
        Menu item(id, name, des, price, quantity);
        admin_instance->AddMenuItem(item, selectmenu);
    }
    // adding item in faculty menu
    else if (selectmenu == 2)
    {
        Menu item(id, name, des, price, quantity);
        admin_instance->AddMenuItem(item, selectmenu);
    }
    // adding item in non faculty menu
    else if (selectmenu == 3)
    {
        Menu item(id, name, des, price, quantity);
        admin_instance->AddMenuItem(item, selectmenu);
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// if staff member wants to remove item from menu
void Staff::RemoveMenuItem()
{
    string name, id;
    cout << "Enter Item Id: ";
    cin.ignore();
    getline(cin, id);
    cout << "Enter Item Name: ";
    getline(cin, name);
    cout << "In which menu u want to remove item?\n";
    int selectmenu;
    cout << "---------------------\n";
    cout << "|1.Student Menu     |\n";
    cout << "|2.Faculty Menu     |\n";
    cout << "|3.Non-Faculty      |\n";
    cout << "---------------------\n";
    cout << "Enter your choice(1-3): ";
    cin >> selectmenu;
    // removing item from student menu
    if (selectmenu == 1)
    {
        admin_instance->RemoveMenuItem(id, name, selectmenu);
    }
    // removing item from faculty menu
    else if (selectmenu == 2)
    {
        admin_instance->RemoveMenuItem(id, name, selectmenu);
    }
    // removing item from non faculty menu
    else if (selectmenu == 3)
    {
        admin_instance->RemoveMenuItem(id, name, selectmenu);
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// if staff member wants to logout
void Staff::Logout() {}
// operator overloading
void *Staff::operator new[](size_t s)
{
    void *p = ::operator new[](s);
    return p;
}
// destructor for staff
Staff::~Staff()
{
    staffcount--;
    delete admin_instance;
}

// ------------------------------------------------------------------

// Admin Class
// constructor for admin
Admin::Admin()
{
    userId = "";
    userName = "";
    Password = "";
    userType = "";
    isLoggedIn = false;
}
// parametrized constructor for admin
Admin::Admin(string id, string name, string pass, string type) : User(id, name, pass, type) {}

// if admin wants to register
void Admin::Register()
{
    // taking his credentials
    cout << "Enter adminId: ";
    cin >> userId;
    cout << "Enter adminName: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> Password;
    cout << "Enter userType: ";
    cin >> userType;
    setUserId(userId);
    setUserName(userName);
    setPassword(Password);
    setUserType(userType);
    cout << "New Admin has been Registered\n";
}
// if admin wants to login
void Admin::Login()
{
    cout << "\nAdmin is logged In.\n";
    isLoggedIn = true;
}
// if admin wants to view menu
void Admin::ViewMenu(int choice)
{
    // viewing student menu
    if (choice == 1)
    {
        goto student;
    }
    // viewing faculty menu
    else if (choice == 3)
    {
        goto non_faculty;
    }

    int selectmenu;
    cout << "---------------------\n";
    cout << "|1.Student Menu     |\n";
    cout << "|2.Faculty Menu     |\n";
    cout << "|3.Non-Faculty      |\n";
    cout << "---------------------\n";
    cout << "Enter your choice(1-3): ";
    cin >> selectmenu;
    switch (selectmenu)
    {
    case 1:
    student:
        cout << endl
             << endl
             << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        cout
            << "Item ID"
            << setw(17) << "Item Name"
            << setw(31) << "Item Description"
            << setw(34) << "Price"
            << setw(30) << "Quantity in Stock"
            << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < Stu_itemcount; i++)
        {
            cout << left << setw(15) << Stu_menu[i].getItemId() << setw(25) << Stu_menu[i].getItemName() << setw(40) << Stu_menu[i].getItemDescription()
                 << right << fixed << setprecision(2) << setw(10) << Stu_menu[i].getPrice() << setw(15) << Stu_menu[i].getQuantityInStock() << endl
                 << endl;
        }
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        break;
    case 2:
        cout << endl
             << endl
             << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        cout
            << "Item ID"
            << setw(17) << "Item Name"
            << setw(31) << "Item Description"
            << setw(34) << "Price"
            << setw(30) << "Quantity in Stock"
            << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < Fac_itemcount; i++)
        {
            cout << left << setw(15) << Fac_menu[i].getItemId() << setw(25) << Fac_menu[i].getItemName() << setw(40) << Fac_menu[i].getItemDescription()
                 << right << fixed << setprecision(2) << setw(10) << Fac_menu[i].getPrice() << setw(15) << Fac_menu[i].getQuantityInStock() << endl
                 << endl;
        }
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        break;
    case 3:
    non_faculty:
        cout
            << endl
            << endl
            << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        cout
            << "Item ID"
            << setw(17) << "Item Name"
            << setw(31) << "Item Description"
            << setw(34) << "Price"
            << setw(30) << "Quantity in Stock"
            << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < NF_itemcount; i++)
        {
            cout << left << setw(15) << NF_menu[i].getItemId() << setw(25) << NF_menu[i].getItemName() << setw(40) << NF_menu[i].getItemDescription()
                 << right << fixed << setprecision(2) << setw(10) << NF_menu[i].getPrice() << setw(15) << NF_menu[i].getQuantityInStock() << endl
                 << endl;
        }
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}
// if admin wants to add item in menu
void Admin::AddMenuItem(const Menu &Item, int menu_choice)
{
    // adding item in student menu
    if (menu_choice == 1)
    {
        if (Stu_itemcount < 10)
        {
            Stu_menu[Stu_itemcount] = Item;
            Stu_menu[Stu_itemcount];
            // saving items to file
            filemanager_instance.SaveMenuItemsToFile(Item, menu_choice);
            Stu_itemcount++;
        }
        else
        {
            cout << "Menu is full" << endl;
        }
    }
    // adding item in faculty menu
    else if (menu_choice == 2)
    {
        if (Fac_itemcount < 10)
        {
            Fac_menu[Fac_itemcount] = Item;
            // saving to file
            filemanager_instance.SaveMenuItemsToFile(Item, menu_choice);
            Fac_itemcount++;
        }
        else
        {
            cout << "Menu is full" << endl;
        }
    }
    // adding item in non faculty menu
    else if (menu_choice == 3)
    {
        if (NF_itemcount < 10)
        {
            NF_menu[NF_itemcount] = Item;
            // saving to file
            filemanager_instance.SaveMenuItemsToFile(Item, menu_choice);
            NF_itemcount++;
        }
        else
        {
            cout << "Menu is full" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// if admin wants to remove item from menu
void Admin::RemoveMenuItem(string id, string name, int menu_choice)
{
    int i;
    switch (menu_choice)
    {
    case 1:
        for (i = 0; i < Stu_itemcount; i++)
        {
            if (Stu_menu[i].getItemId() == id && Stu_menu[i].getItemName() == name)
            {
                break;
            }
        }
        if (i == Stu_itemcount)
        {
            cout << "Item not found" << endl;
        }
        else
        {
            for (int j = i; j < Stu_itemcount - 1; j++)
            {
                Stu_menu[j] = Stu_menu[j + 1];
            }
            Stu_itemcount--;
            cout << "Item removed" << endl;
        }
        break;
    case 2:
        for (i = 0; i < Fac_itemcount; i++)
        {
            if (Fac_menu[i].getItemId() == id && Fac_menu[i].getItemName() == name)
            {
                break;
            }
        }
        if (i == Fac_itemcount)
        {
            cout << "Item not found" << endl;
        }
        else
        {
            for (int j = i; j < Fac_itemcount - 1; j++)
            {
                Fac_menu[j] = Fac_menu[j + 1];
            }
            Fac_itemcount--;
            cout << "Item removed" << endl;
        }
        break;
    case 3:
        for (i = 0; i < NF_itemcount; i++)
        {
            if (NF_menu[i].getItemId() == id && NF_menu[i].getItemName() == name)
            {
                break;
            }
        }
        if (i == NF_itemcount)
        {
            cout << "Item not found" << endl;
        }
        else
        {
            for (int j = i; j < NF_itemcount - 1; j++)
            {
                NF_menu[j] = NF_menu[j + 1];
            }
            NF_itemcount--;
            cout << "Item removed" << endl;
        }
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}
// if admin wants to manage inventory
void Admin::ManageInventory()
{
    int choice;
    cout << "Do u want to see Cafe Menu's(1=Yes, 0=No)? ";
    cin >> choice;
    if (choice == 1)
    {
        ViewMenu(0);
    }
    cout << "From which menu u want to update the stock? \n";
    cout << "---------------------\n";
    cout << "|1.Student Menu     |\n";
    cout << "|2.Faculty Menu     |\n";
    cout << "|3.Non-Faculty      |\n";
    cout << "---------------------\n";
    cout << "Enter your choice(1-3): ";
    cin >> choice;
    // manage student inventory
    if (choice == 1)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to update the stock: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < Stu_itemcount; i++)
        {
            if (Stu_menu[i].getItemName() == name)
            {
                Stu_menu[i].updateStock();
                itemfound = true;
                break;
            }
        }
        if (itemfound == false)
        {
            cout << "Item not found" << endl;
        }
    }
    // manage faculty inventory
    else if (choice == 2)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to update the stock: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < Fac_itemcount; i++)
        {
            if (Fac_menu[i].getItemName() == name)
            {
                Fac_menu[i].updateStock();
                itemfound = true;
                break;
            }
        }
        if (itemfound == false)
        {
            cout << "Item not found" << endl;
        }
    }
    // manage non faculty inventory
    else if (choice == 3)
    {
        string name;
        bool itemfound = false;
        cout << "Enter Item's Name u want to update the stock: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < NF_itemcount; i++)
        {
            if (NF_menu[i].getItemName() == name)
            {
                NF_menu[i].updateStock();
                itemfound = true;
                break;
            }
        }
        if (itemfound == false)
        {
            cout << "Item not found" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// if admin wants to manage discount/promotion
void Admin::ManageDiscountPromotion()
{
    int choice;
    cout << "-------------------------------------\n";
    cout << "|1.Add discounts/Promotions         |\n";
    cout << "|2.Remove discounts/Promotions      |\n";
    cout << "-------------------------------------\n";
    cout << "Enter your choice(1-4): ";
    cin >> choice;
    // if admin wants to add discount
    if (choice == 1)
    {
        double discount;
        cout << "Enter the discount percentage: ";
        cin >> discount;
        cout << "From which menu u want to apply discount? \n";
        cout << "---------------------\n";
        cout << "|1.Student Menu     |\n";
        cout << "|2.Faculty Menu     |\n";
        cout << "|3.Non-Faculty      |\n";
        cout << "---------------------\n";
        cout << "Enter your choice(1-3): ";
        cin >> choice;
        // applying discount in student menu
        if (choice == 1)
        {
            cout << "Enter Item's Name u want to apply discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < Stu_itemcount; i++)
            {
                if (Stu_menu[i].getItemName() == name)
                {
                    Stu_menu[i].setPrice(Stu_menu[i].getPrice() - (Stu_menu[i].getPrice() * discount / 100));
                    cout << "Discount added" << endl;
                    break;
                }
            }
        }
        // applying discount in faculty menu
        else if (choice == 2)
        {
            cout << "Enter Item's Name u want to apply discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < Fac_itemcount; i++)
            {
                if (Fac_menu[i].getItemName() == name)
                {
                    Fac_menu[i].setPrice(Fac_menu[i].getPrice() - (Fac_menu[i].getPrice() * discount / 100));
                    cout << "Discount added" << endl;
                    break;
                }
            }
        }
        // applying discount in non faculty menu
        else if (choice == 3)
        {
            cout << "Enter Item's Name u want to apply discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < NF_itemcount; i++)
            {
                if (NF_menu[i].getItemName() == name)
                {
                    NF_menu[i].setPrice(NF_menu[i].getPrice() - (NF_menu[i].getPrice() * discount / 100));
                    cout << "Discount added" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
    // if admin wants to remove discount
    else if (choice == 2)
    {
        double discount;
        cout << "Enter the discount percentage: ";
        cin >> discount;
        int choice;

        cout << "From which menu u want to remove discount? \n";
        cout << "---------------------\n";
        cout << "|1.Student Menu     |\n";
        cout << "|2.Faculty Menu     |\n";
        cout << "|3.Non-Faculty      |\n";
        cout << "---------------------\n";
        cout << "Enter your choice(1-3): ";
        cin >> choice;
        // removing discount from student menu
        if (choice == 1)
        {
            cout << "Enter Item's Name u want to remove discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < Stu_itemcount; i++)
            {
                if (Stu_menu[i].getItemName() == name)
                {
                    Stu_menu[i].setPrice(Stu_menu[i].getPrice() + (Stu_menu[i].getPrice() * discount / 100));
                    cout << "Discount removed" << endl;
                    break;
                }
            }
        }
        // removing discount from faculty menu
        else if (choice == 2)
        {
            cout << "Enter Item's Name u want to remove discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < Fac_itemcount; i++)
            {
                if (Fac_menu[i].getItemName() == name)
                {
                    Fac_menu[i].setPrice(Fac_menu[i].getPrice() + (Fac_menu[i].getPrice() * discount / 100));
                    cout << "Discount removed" << endl;
                    break;
                }
            }
        }
        // removing discount from non faculty menu
        else if (choice == 3)
        {
            cout << "Enter Item's Name u want to remove discount: ";
            string name;
            cin.ignore();
            getline(cin, name);
            for (int i = 0; i < NF_itemcount; i++)
            {
                if (NF_menu[i].getItemName() == name)
                {
                    NF_menu[i].setPrice(NF_menu[i].getPrice() + (NF_menu[i].getPrice() * discount / 100));
                    cout << "Discount removed" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// if admin wants to view order history
void Admin::ViewOrderHistory()
{
    order_instance.revieworder();
}

// if admin wants to add notification
void Admin::AddNotification()
{
    int choice;
    cout << "--------------------------------------\n";
    cout << "|1.Add Notification to Staff         |\n";
    cout << "|2.Add Notification to Customers     |\n";
    cout << "--------------------------------------\n";
    cout << "Enter your choice(1-2): ";
    cin >> choice;
    // adding notification to staff
    if (choice == 1)
    {
        if (notificationcount_staff < 10)
        {
            cout << "Enter notification: ";
            cin.ignore();
            getline(cin, notification_staff[notificationcount_staff]);
            notificationcount_staff++;
            isNotified_staff = true;
            cout << "Notification added" << endl;
        }
        else
        {
            cout << "Notification limit reached" << endl;
        }
    }
    // adding notification to customers
    else if (choice == 2)
    {
        if (notificationcount_customer < 10)
        {
            cout << "Enter notification: ";
            cin.ignore();
            getline(cin, notification_customer[notificationcount_customer]);
            notificationcount_customer++;
            isNotified_customer = true;
            cout << "Notification added" << endl;
        }
        else
        {
            cout << "Notification limit reached" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
void Admin::RemoveNotification()
{
    bool noti_found = false;
    int choice;
    cout << "--------------------------------------\n";
    cout << "|1.Remove Notification to Staff      |\n";
    cout << "|2.Remove Notification to Customers  |\n";
    cout << "--------------------------------------\n";
    cout << "Enter your choice(1-2): ";
    cin >> choice;
    // removind notification to staff
    if (choice == 1)
    {
        if (isNotified_staff == true)
        {
            string notif_to_remove;
            cout << "Enter notification to remove: ";
            cin.ignore();
            getline(cin, notif_to_remove);
            for (int i = 0; i < notificationcount_staff; i++)
            {
                if (notification_staff[i] == notif_to_remove)
                {
                    for (int j = i; j < notificationcount_staff - 1; j++)
                    {
                        notification_staff[j] = notification_staff[j + 1];
                    }
                    noti_found = true;
                    notificationcount_staff--;
                    cout << "Notification removed" << endl;
                    break;
                }
            }
            if (noti_found == false)
            {
                cout << "Notification not found\n";
            }
        }

        else
        {
            cout << "No notification to remove" << endl;
        }
    }
    // removind notification to customers
    else if (choice == 2)
    {
        if (isNotified_customer == true)
        {
            string notif_to_remove;
            cout << "Enter notification to remove: ";
            cin.ignore();
            getline(cin, notif_to_remove);
            for (int i = 0; i < notificationcount_customer; i++)
            {
                if (notification_customer[i] == notif_to_remove)
                {
                    for (int j = i; j < notificationcount_customer - 1; j++)
                    {
                        notification_customer[j] = notification_customer[j + 1];
                    }
                    notificationcount_customer--;
                    cout << "Notification removed" << endl;
                    noti_found = true;
                    break;
                }
            }
            if (noti_found == false)
            {
                cout << "Notification not found\n";
            }
        }

        else
        {
            cout << "No notification to remove" << endl;
        }
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// member fucntion for rating menu items
void Admin::RateMenuItem()
{
    customer_instance.RateItem();
}
void Admin::DisplayFromFile() {}

// displaying from file all the users
void Admin::ViewUsersFromFile()
{
    // file handling
    ifstream fin;
    fin.open("UserData.txt");
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}
// displaying from file menu items
void Admin::ViewMenuItemsFromFile(int menu_choice)
{
    // viewing menu items from student menu
    if (menu_choice == 1)
    {
        ifstream fin;
        fin.open("StudentMenu.txt");
        if (fin.is_open())
        {
            string line;
            while (getline(fin, line))
            {
                cout << line << endl;
            }
        }
        else
        {
            cout << "File not found" << endl;
        }
        fin.close();
    }
    // viewing menu items from faculty menu
    else if (menu_choice == 2)
    {
        ifstream fin;
        fin.open("FacultyMenu.txt");
        if (fin.is_open())
        {
            string line;
            while (getline(fin, line))
            {
                cout << line << endl;
            }
        }
        else
        {
            cout << "File not found" << endl;
        }
        fin.close();
    }
    // viewing menu items from non-faculty menu
    else if (menu_choice == 3)
    {
        ifstream fin;
        fin.open("NonFacultyMenu.txt");
        if (fin.is_open())
        {
            string line;
            while (getline(fin, line))
            {
                cout << line << endl;
            }
        }
        else
        {
            cout << "File not found" << endl;
        }
        fin.close();
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
// member function for displaying orders from file
void Admin::ViewOrdersFromFile()
{
    ifstream fin;
    fin.open("Order.txt");
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}

// member function for displaying ratings from file
void Admin::ViewRatingsFromFile()
{
    ifstream fin;
    fin.open("Rating.txt");
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}
// member function for displaying payments from file
void Admin::ViewPaymentsFromFile()
{
    ifstream fin;
    fin.open("Payment.txt");
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}
// member function for displaying monthly earnings or revenue from file
void Admin::CalculateMonthlyEarnings()
{
    ifstream pay;
    pay.open("Payment.txt");
    if (pay.is_open())
    {
        string line;
        while (getline(pay, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "Error opening Payment.txt file." << endl;
    }
}
// member fucntion if admin wants to logout
void Admin::Logout() {}
// operator overloading
void *Admin::operator new[](size_t s) // operator overloading here
{
    void *p = ::operator new[](s);
    return p;
}

// ------------------------------------------------------------------

// Menu Class
// default constructor
Menu::Menu()
{
    itemId = "";
    itemName = "";
    itemDescription = "";
    Price = 0.0;
    quantityInStock = 0;
}
// parametrized constructor
Menu::Menu(string id, string name, string desc, double price, int quantity)
{
    itemId = id;
    itemName = name;
    itemDescription = desc;
    Price = price;
    quantityInStock = quantity;
}

// below are all getter and setters
void Menu::setItemId(string id)
{
    itemId = id;
}
void Menu::setItemName(string name)
{
    itemName = name;
}
void Menu::setItemDescription(string desc)
{
    itemDescription = desc;
}
void Menu::setPrice(double price)
{
    Price = price;
}
void Menu::setQuantityInStock(int quantity)
{
    quantityInStock = quantity;
}
string Menu::getItemId()
{
    return itemId;
}
string Menu::getItemName()
{
    return itemName;
}
string Menu::getItemDescription()
{
    return itemDescription;
}
double Menu::getPrice()
{
    return Price;
}
int Menu::getQuantityInStock()
{
    return quantityInStock;
}

// member function to update stock of menu items
void Menu::updateStock()
{
    int quantity;
    cout << "Enter the new quantity: ";
    cin >> quantity;
    quantityInStock = quantity;
    cout << "Stock updated" << endl;

    // if user wants to update the price as well
    cout << "Do u want to change the price (1=Yes,0=No)? ";
    cin >> quantity;
    if (quantity == 1)
    {
        cout << "Enter the new price: ";
        cin >> Price;
        cout << "Price updated" << endl;
    }
}

// ------------------------------------------------------------------

// Order Class
// default constructor
Order::Order()
{
    orderId = "";
    customerId = "";
    totalPrice = 0.0;
    orderStatus = "Empty";
}
// parametrized constructor
Order::Order(string id, string custId, int Stu_menu[], double price, string status)
{
    orderId = id;
    customerId = custId;
    totalPrice = price;
    orderStatus = "Empty";
    for (int i = 0; i < 10; i++)
    {
        itemsOrdered[i] = Stu_menu[i];
    }
}

// below the following are getter and setters
void Order::setOrderId(string id)
{
    orderId = id;
}
void Order::setCustomerId(string custId)
{
    customerId = custId;
}
/*void Order::setItemsOrdered(int Stu_menu[])
{
    for (int i = 0; i < 10; i++)
    {
        itemsOrdered[i] = Stu_menu[i];
    }
}*/
void Order::setTotalPrice(double price)
{
    totalPrice = price;
}
void Order::setOrderStatus(string status)
{
    orderStatus = status;
}
string Order::getOrderId()
{
    return orderId;
}
string Order::getCustomerId()
{
    return customerId;
}
/*
int *Order::getItemsOrdered()
{
    return itemsOrdered;
}*/
double Order::getTotalPrice()
{
    return totalPrice;
}
string Order::getOrderStatus()
{
    return orderStatus;
}

// member function which add items to menu or order
void Order::AddItem(string itemname, int quantity)
{
    int a = stoi(itemname);
    itemsOrdered[numItems] = a;
    // cout << itemsOrdered[numItems] << endl;
    quantities[numItems] = quantity;
    numItems++;
    cout << "Item added" << endl;
}

// member function which diplays user curent order
void Order::revieworder()
{
    if (orderStatus == "Empty")
    {
        cout << "First Place your Order\n";
    }
    else
    {
        cout << "Order Id: " << orderId << endl;
        cout << "Customer Id: " << customerId << endl;
        cout << "Items Ordered...." << endl;
        for (int i = 0; i < numItems; i++)
        {
            cout << "Item id: " << itemsOrdered[i] << endl;
            cout << "Quantity: " << quantities[i] << endl;
        }
        if (numItems > 0)
        {
            cout << "Total Price: " << totalPrice << endl;
            cout << "Order Status: " << orderStatus << endl;
        }
        // writing the order in file
        fstream f6;
        f6.open("Order.txt", ios::app);
        if (f6.is_open())
        {
            f6 << "Order Id: " << orderId << endl;
            f6 << "Customer Id: " << customerId << endl;
            f6 << "Items Ordered...." << endl;
            for (int i = 0; i < numItems; i++)
            {
                f6 << "Item id: " << itemsOrdered[i] << endl;
                f6 << "Quantity: " << quantities[i] << endl;
            }
            if (numItems > 0)
            {
                f6 << "Total Price: " << totalPrice << endl;
                f6 << "Order Status: " << orderStatus << endl;
            }
        }
        else
        {
            cout << "File not found" << endl;
        }
    }
}

// if user wants to remove an item from order
void Order::RemoveItem()
{

    bool flag = false;
    int itemid;
    cout << "Enter the item id u want to remove: ";
    cin >> itemid;
    for (int i = 0; i < numItems; i++)
    {
        if (itemsOrdered[i] == itemid)
        {
            for (int j = i; j < numItems - 1; j++)
            {
                itemsOrdered[j] = itemsOrdered[j + 1];
                quantities[j] = quantities[j + 1];
            }
            numItems--;

            flag = true;
            cout << "Item removed" << endl;

            break;
        }
    }
    if (flag == false)
    {
        cout << "Item not found" << endl;
    }
}

// member function which calculates total price of order
void Order::CalculateTotalPrice()
{
    cout << "Total Price: " << totalPrice << endl;
}

// member function which confirms user order
void Order::ConfirmOrder()
{
    // calling procees order function for staff
    payment_instance.ProcessPayment(totalPrice, orderId);
}

// if user wants to cancel the order
void Order::CancelOrder()
{
    setOrderStatus("Empty");
    setTotalPrice(0);
    cout << "Order has been cancelled\n\n";
}

// ------------------------------------------------------------------

// Rating Class

// default constructor
Rating::Rating()
{
    ratingId = "";
    menuItemId = "";
    customerId = "";
    score = 0;
    comment = "";
}
// parametrized constructor
Rating::Rating(string id, string itemId, string custId, int s, string c)
{
    ratingId = id;
    menuItemId = itemId;
    customerId = custId;
    score = s;
    comment = c;
}

// below the following are getter and setters
void Rating::setRatingId(string id)
{
    ratingId = id;
}
void Rating::setMenuItemId(string itemId)
{
    menuItemId = itemId;
}
void Rating::setCustomerId(string custId)
{
    customerId = custId;
}
void Rating::setScore(int s)
{
    score = s;
}
void Rating::setComment(string c)
{
    comment = c;
}
string Rating::getRatingId()
{
    return ratingId;
}
string Rating::getMenuItemId()
{
    return menuItemId;
}
string Rating::getCustomerId()
{
    return customerId;
}
int Rating::getScore()
{
    return score;
}
string Rating::getComment()
{
    return comment;
}

// if customer wants to rate the menu items
void Rating::Rate(string name, string id, string c_id)
{
    int score;
    string comment;
    cout << "Enter the score: ";
    cin >> score;
    cout << "Enter the comment: ";
    cin.ignore();
    getline(cin, comment);
    cout << "Item rated" << endl;
    // writing the ratings to the file
    fstream f6;
    f6.open("Rating.txt", ios::app);
    if (f6.is_open())
    {
        f6 << "Rating Id: " << to_string(rand() % 10) << endl;
        f6 << "Menu Item Id: " << id << endl;
        f6 << "Customer Id: " << c_id << endl;
        f6 << "Score: " << score << endl;
        f6 << "Comment: " << comment << endl;
    }
    else
    {
        cout << "File not found" << endl;
    }
}

// ------------------------------------------------------------------

// Payment Class
// defaulr constructror
Payment::Payment()
{
    paymentId = "";
    orderId = "";
    amountPaid = 0.0;
    paymentStatus = "";
}
// parametrized constructor
Payment::Payment(string id, string oId, double amount, string status)
{
    paymentId = id;
    orderId = oId;
    amountPaid = amount;
    paymentStatus = status;
}

// below are getter and setters
void Payment::setPaymentId(string id)
{
    paymentId = id;
}
void Payment::setOrderId(string oId)
{
    orderId = oId;
}
void Payment::setAmountPaid(double amount)
{
    amountPaid = amount;
}
void Payment::setPaymentStatus(string status)
{
    paymentStatus = status;
}
string Payment::getPaymentId()
{
    return paymentId;
}
string Payment::getOrderId()
{
    return orderId;
}
double Payment::getAmountPaid()
{
    return amountPaid;
}
string Payment::getPaymentStatus()
{
    return paymentStatus;
}

// member function for handling payments
void Payment::ProcessPayment(double price, string orderid)
{
back:
    double amount_returned = 0;
    double customer_paid_money;
    cout << "\nPay money to cashier: ";
    cin >> customer_paid_money;
    if (customer_paid_money < price)
    {
        cout << "Insufficient amount paid\nCheck Your payment amount and try again";
        goto back;
    }
    else if (customer_paid_money >= price)
    {
        amount_returned = customer_paid_money - price;
        setOrderId(orderid);
        setPaymentId("CMS" + to_string(rand() % 20));
        setAmountPaid(price);
        setPaymentStatus("Paid");

        cout << "Payment Details....\n";
        cout << "---------------------------\n";
        cout << "|Payment id: " << getPaymentId() << "        |" << endl;
        cout << "|Order id: " << getOrderId() << "              |" << endl;
        cout << "|Amount Paid: " << getAmountPaid() << "     |" << endl;
        cout << "|Amount Returned: " << amount_returned << " |" << endl;
        cout << "|Payment Status: " << getPaymentStatus() << "     |" << endl;
        cout << "---------------------------\n";
        cout << "Thank you for using our system!\n";
        cout << "Have a nice day!\n\n\n";

        // writing the payment to file
        fstream f5;
        f5.open("Payment.txt", ios::app);
        static double total = 0;
        total += getAmountPaid();
        f5 << "Payment Details....\n";
        f5 << "---------------------------\n";
        f5 << "|Payment id: " << getPaymentId() << "        |" << endl;
        f5 << "|Order id: " << getOrderId() << "              |" << endl;
        f5 << "|Amount Paid: " << getAmountPaid() << "     |" << endl;
        f5 << "|Amount Returned: " << amount_returned << " |" << endl;
        f5 << "|Payment Status: " << getPaymentStatus() << "     |" << endl;
        f5 << "---------------------------\n";
        f5 << "Monthly Revenue: " << total << "     " << endl;
        f5.close();
        exit(0);
    }
}

// ------------------------------------------------------------------
void FileManager::SaveUserToFile()
{
}
void FileManager::SaveMenuItemsToFile(Menu Item, int menu_choice)
{
    ofstream fout;
    if (menu_choice == 1)
    {
        fout.open("StudentMenu.txt", ios::app);
        fout << Item.getItemId() << "         ";
        fout << Item.getItemName() << "    ";
        fout << Item.getItemDescription() << "                ";
        fout << Item.getPrice() << "      ";
        fout << Item.getQuantityInStock() << "    \n";
        fout.close();
    }
    else if (menu_choice == 2)
    {
        fout.open("FacultyMenu.txt", ios::app);
        fout << Item.getItemId() << "         ";
        fout << Item.getItemName() << "    ";
        fout << Item.getItemDescription() << "                ";
        fout << Item.getPrice() << "      ";
        fout << Item.getQuantityInStock() << "    \n";
        fout.close();
    }
    else if (menu_choice == 3)
    {
        fout.open("NonFacultyMenu.txt", ios::app);
        fout << Item.getItemId() << "         ";
        fout << Item.getItemName() << "    ";
        fout << Item.getItemDescription() << "                ";
        fout << Item.getPrice() << "      ";
        fout << Item.getQuantityInStock() << "    \n";
        fout.close();
    }
    else
    {
        cout << "Invalid choice" << endl;
    }
}
void FileManager::SaveOrderToFile(Order order)
{
    ofstream fout;
    fout.open("Order.txt", ios::app);
    fout << order.getOrderId() << "         ";
    fout << order.getCustomerId() << "    ";
    fout << order.getTotalPrice() << "                ";
    fout << order.getOrderStatus() << "      \n";
    fout.close();
}
void FileManager::SaveRatingToFile(Rating rating)
{
    ofstream fout;
    fout.open("Rating.txt", ios::app);
    fout << rating.getRatingId() << "         ";
    fout << rating.getMenuItemId() << "    ";
    fout << rating.getCustomerId() << "                ";
    fout << rating.getScore() << "      ";
    fout << rating.getComment() << "      \n";
    fout.close();
}
void FileManager::SavePaymentToFile(Payment payment)
{
    ofstream fout;
    fout.open("Payment.txt", ios::app);
    fout << payment.getPaymentId() << "         ";
    fout << payment.getOrderId() << "    ";
    fout << payment.getAmountPaid() << "                ";
    fout << payment.getPaymentStatus() << "      \n";
    fout.close();
}
