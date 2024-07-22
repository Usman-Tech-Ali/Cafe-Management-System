#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <conio.h>
#include "header.h"
using namespace std;
int main()
{

    // By using simple cout statements (sfml) to color the background
    cout << "\033[44m"; // Set background color to blue

    cout << "\n\n\n";
    cout << "\t\t\t.  .   .  .     .                           .           .--.       .-.        .    .                                              .      .-.          .               \n";
    cout << "\t\t\t \\  \\ /  /      |                          _|_         :           |          |\\  /|                                             _|_    (   )        _|_              \n";
    cout << "\t\t\t  \\  \\  /   .-. |  .-. .-. .--.--.  .-.     |   .-.    |     .-.  -|-  .-.    | \\/ | .-.  .--.  .-.   .-.. .-. .--.--.  .-. .--.  |      `-. .  ..--. |   .-. .--.--. \n";
    cout << "\t\t\t   \\/ \\/   (.-' | (   (   )|  |  | (.-'     |  (   )   :    (   )  |  (.-'    |    |(   ) |  | (   ) (   |(.-' |  |  | (.-' |  |  |     (   )|  |`--. |  (.-' |  |  | \n";
    cout << "\t\t\t    ' '     `--'`- `-' `-' '  '  `- `--'    `-' `-'     `--' `-'`- '   `--'   '    ' `-'`-'  `- `-'`- `-`| `--''  '  `- `--''  `- `-'    `-' `--|`--' `-' `--''  '  `-\n";
    cout << "\t\t\t                                                                                                      ._.'                                      ;                     \n";
    cout << "\t\t\t                                                                                                                                             `-'                      \n";
    cout << "\n\n";

    cout << "\033[0m"; // Reset background color
    int staff_index = -1;
    int customer_index = -1;
    // Create an instance of the Admin class
    Admin *admin = new Admin[1]; // operator overloading here
    admin[0].setUserId("admin1");
    admin[0].setUserName("Shoaib");
    admin[0].setPassword("1111");
    admin[0].setUserType("Admin");

    // Create an instance of the Staff class
    Staff *staffMembers = new Staff[2]; // operator overloading here
    int n = 2;
    staffMembers[0].setUserId("staff1");
    staffMembers[0].setUserName("Staff 1");
    staffMembers[0].setPassword("1111");
    staffMembers[0].setUserType("Staff");
    // aggregation here
    staffMembers[0].setadmin(admin);
    staffMembers[1].setUserId("staff2");
    staffMembers[1].setUserName("Staff 2");
    staffMembers[1].setPassword("2222");
    staffMembers[1].setUserType("Staff");
    // aggregation here
    staffMembers[1].setadmin(admin);
    // storing userdata to file
    fstream userdata;
    userdata.open("UserData.txt", ios::app);
    userdata << "SatffData\n";
    userdata << "UserId   Name   Password  Type  \n";
    userdata << staffMembers[0].getUserId() << " " << staffMembers[0].getUserName() << " " << staffMembers[0].getPassword() << " " << staffMembers[0].getUserType() << endl;
    userdata << staffMembers[1].getUserId() << " " << staffMembers[1].getUserName() << " " << staffMembers[1].getPassword() << " " << staffMembers[1].getUserType() << endl;
    userdata.close();

    // Create two instances of the Customer class
    Customer *customers = new Customer[3]; // operator overloading here
    int n2 = 3;
    // setting each customer id,name,pass
    customers[0].setUserId("customer1");
    customers[0].setUserName("Customer 1");
    customers[0].setPassword("1111");
    customers[0].setUserType("Customer");
    customers[0].setadmin(admin);
    customers[1].setUserId("customer2");
    customers[1].setUserName("Customer 2");
    customers[1].setPassword("2222");
    customers[1].setUserType("Customer");
    customers[1].setadmin(admin);
    customers[2].setUserId("customer3");
    customers[2].setUserName("Customer 3");
    customers[2].setPassword("3333");
    customers[2].setUserType("Customer");
    customers[2].setadmin(admin);
    // adding customer data to file
    fstream f;
    f.open("UserData.txt", ios::app);
    f << "--------------------------------------------------\nCustomer Data\n";
    f << "UserId   Name   Password  Type  \n";
    f << customers[0].getUserId() << " " << customers[0].getUserName() << " " << customers[0].getPassword() << " " << customers[0].getUserType() << endl;
    f << customers[1].getUserId() << " " << customers[1].getUserName() << " " << customers[1].getPassword() << " " << customers[1].getUserType() << endl;
    f << customers[2].getUserId() << " " << customers[2].getUserName() << " " << customers[2].getPassword() << " " << customers[2].getUserType() << endl;
    f.close();

    // Create an instance of the  Student Menu class
    Menu Stu_menu[10];
    // int n3 = 3;
    // Setting menu items for students
    Stu_menu[0].setItemId("1");
    Stu_menu[0].setItemName("French Fries");
    Stu_menu[0].setItemDescription("Delicious French Fries");
    Stu_menu[0].setPrice(100);
    Stu_menu[0].setQuantityInStock(10);
    Stu_menu[1].setItemId("2");
    Stu_menu[1].setItemName("Chicken Burger");
    Stu_menu[1].setItemDescription("Delicious Chicken Burger");
    Stu_menu[1].setPrice(200);
    Stu_menu[1].setQuantityInStock(10);
    Stu_menu[2].setItemId("3");
    Stu_menu[2].setItemName("Chicken Pizza");
    Stu_menu[2].setItemDescription("Delicious Pizza");
    Stu_menu[2].setPrice(300);
    Stu_menu[2].setQuantityInStock(10);
    // writing student menu to file
    fstream f2;
    f2.open("StudentMenu.txt", ios::app);
    f2 << "ItemId    ItemName        ItemDescription                  Price      QuantityInStock\n";
    f2.close();
    // admin is adding 3 items to menu
    admin->AddMenuItem(Stu_menu[0], 1);
    admin->AddMenuItem(Stu_menu[1], 1);
    admin->AddMenuItem(Stu_menu[2], 1);

    // Create an instance of the Faculty Menu class
    Menu Fac_menu[10];
    // int n4 = 3;
    // Adding 3 items to faculty menu
    Fac_menu[0].setItemId("1");
    Fac_menu[0].setItemName("Salad");
    Fac_menu[0].setItemDescription("Healthy Salad");
    Fac_menu[0].setPrice(150);
    Fac_menu[0].setQuantityInStock(10);
    Fac_menu[1].setItemId("2");
    Fac_menu[1].setItemName("Steak");
    Fac_menu[1].setItemDescription("Juicy Steak");
    Fac_menu[1].setPrice(250);
    Fac_menu[1].setQuantityInStock(10);
    Fac_menu[2].setItemId("3");
    Fac_menu[2].setItemName("Pasta");
    Fac_menu[2].setItemDescription("Delicious Pasta");
    Fac_menu[2].setPrice(350);
    Fac_menu[2].setQuantityInStock(10);
    // writing faculty menu to file
    fstream f3;
    f3.open("FacultyMenu.txt", ios::app);
    f3 << "ItemId    ItemName        ItemDescription                  Price      QuantityInStock\n";
    f3.close();

    // admin is adding 3 items to menu
    admin->AddMenuItem(Fac_menu[0], 2);
    admin->AddMenuItem(Fac_menu[1], 2);
    admin->AddMenuItem(Fac_menu[2], 2);

    // Create an instance of the Non-Faculty Menu class
    Menu NF_menu[10];
    // int n5 = 3;
    // Adding 3 items to non-faculty menu
    NF_menu[0].setItemId("1");
    NF_menu[0].setItemName("Apple Juice");
    NF_menu[0].setItemDescription("Fresh Apple Juice");
    NF_menu[0].setPrice(50);
    NF_menu[0].setQuantityInStock(10);
    NF_menu[1].setItemId("2");
    NF_menu[1].setItemName("Orange Juice");
    NF_menu[1].setItemDescription("Fresh Orange Juice");
    NF_menu[1].setPrice(50);
    NF_menu[1].setQuantityInStock(10);
    NF_menu[2].setItemId("3");
    NF_menu[2].setItemName("Mango Juice");
    NF_menu[2].setItemDescription("Fresh Mango Juice");
    NF_menu[2].setPrice(50);
    NF_menu[2].setQuantityInStock(10);
    // writing non-faculty menu to file
    fstream f4;
    f4.open("NonFacultyMenu.txt", ios::app);
    f4 << "ItemId    ItemName        ItemDescription                  Price      QuantityInStock\n";
    f4.close();
    // admin is adding 3 items to menu
    admin->AddMenuItem(NF_menu[0], 3);
    admin->AddMenuItem(NF_menu[1], 3);
    admin->AddMenuItem(NF_menu[2], 3);

    int choice1 = 0;
    // takes input from user untill wishes to exit
    while (choice1 != 4)
    {
    a:
        // displaying main-menu to user
        cout << setw(100) << "+--------------------+\n";
        cout << setw(100) << "|1.Administrator     |\n";
        cout << setw(100) << "|2.Staff Member      |\n";
        cout << setw(100) << "|3.Customer          |\n";
        cout << setw(100) << "|4.Exit              |\n";
        cout << setw(100) << "+--------------------+\n";
        cout << setw(100) << "Enter your choice (1-4): ";
        cin >> choice1;
        // if user is an admin
        if (choice1 == 1)
        {
            int loginOrRegister;
            cout << "1. Login\n";
            cout << "2. Register New Admin\n";
            cout << "Enter your choice (1-2): ";
            cin >> loginOrRegister;
            // if user wants to login
            if (loginOrRegister == 1)
            {
            login_admin:
                string inputId;
                string inputPassword;
                char c;
                cout << "Enter adminId: ";
                cin.ignore();
                getline(cin, inputId);
                cout << "Enter 4 digit password: ";
                // logic for storing password secretly
                for (int i = 0; i < 4; i++)
                {
                    c = getch();
                    inputPassword += c;
                    c = '*';
                    cout << c;
                }
                if (inputId == admin[0].getUserId() && inputPassword == admin[0].getPassword())
                {
                    admin[0].Login();
                }
                else
                {
                    cout << "\nLogin failed!\n";
                    goto a;
                }
            }
            // if user wants to register new admin
            else if (loginOrRegister == 2)
            {
                // operator overloading and creating new admin dynamically
                Admin *newAdmin = new Admin[1];
                for (int i = 0; i < 1; i++)
                {
                    newAdmin[i] = admin[i];
                }
                delete[] admin;
                newAdmin[0].Register();
                admin = newAdmin;
                goto login_admin;
            }
            else
            {
                cout << "Invalid choice!\n";
                goto a;
            }

            int choice2 = 0;
            // loop which shows admin his capabilities
            while (choice2 != 17)
            {
                cout << "------------------------------------\n";
                cout << "|1.View Menu                       |\n";
                cout << "|2.Add Menu Item                   |\n";
                cout << "|3.Remove Menu Item                |\n";
                cout << "|4.Manage Inventory                |\n";
                cout << "|5.Manage Discount/Promotion       |\n";
                cout << "|6.View Order History              |\n";
                cout << "|7.Add Notification                |\n";
                cout << "|8.Remove Notification             |\n";
                cout << "|9.Rate Menu Item                  |\n";
                cout << "|10.Display From File              |\n";
                cout << "|11.View Users From File           |\n";
                cout << "|12.View Menu Items From File      |\n";
                cout << "|13.View Orders From File          |\n";
                cout << "|14.View Ratings From File         |\n";
                cout << "|15.View Payments From File        |\n";
                cout << "|16.Calculate Monthly Earnings     |\n";
                cout << "|17.Logout                         |\n";
                cout << "------------------------------------\n";
                cout << "Enter your choice (1-17): ";
                cin >> choice2;
                cin.ignore();
                // if admin wants to view menu
                if (choice2 == 1)
                {
                    admin[0].ViewMenu(0);
                }
                // if admin wants to add new item to menu
                else if (choice2 == 2)
                {
                    string id, name, des;
                    double price;
                    int quantity;
                    cout << "Enter Item Id: ";
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
                    // creating instance menu and passing it necessary things
                    Menu nnew;
                    nnew.setItemId(id);
                    nnew.setItemName(name);
                    nnew.setItemDescription(des);
                    nnew.setPrice(price);
                    nnew.setQuantityInStock(quantity);
                    if (selectmenu == 1)
                    {
                        admin->AddMenuItem(nnew, 1);
                    }
                    else if (selectmenu == 2)
                    {
                        admin->AddMenuItem(nnew, 2);
                    }
                    else if (selectmenu == 3)
                    {
                        admin->AddMenuItem(nnew, 3);
                    }
                    else
                    {
                        cout << "Invalid choice!\n";
                    }
                }
                // if admin wants to remove item from menu
                else if (choice2 == 3)
                {
                    // user input id,name of item to remove
                    string name, id;
                    cout << "Enter Item Id: ";
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
                    if (selectmenu == 1)
                    {
                        admin->RemoveMenuItem(id, name, 1);
                    }
                    else if (selectmenu == 2)
                    {
                        admin->RemoveMenuItem(id, name, 2);
                    }
                    else if (selectmenu == 3)
                    {
                        admin->RemoveMenuItem(id, name, 3);
                    }
                    else
                    {
                        cout << "Invalid choice!\n";
                    }
                }
                // if admin wants to manage inventory
                else if (choice2 == 4)
                {
                    admin[0].ManageInventory();
                }
                // if admin wants to manage discount/promotion
                else if (choice2 == 5)
                {
                    admin[0].ManageDiscountPromotion();
                }
                // if admin wants to view order history
                else if (choice2 == 6)
                {
                    admin[0].ViewOrderHistory();
                }
                // if admin wants to add notification
                else if (choice2 == 7)
                {
                    admin[0].AddNotification();
                }
                // if admin wants to remove notification
                else if (choice2 == 8)
                {
                    admin[0].RemoveNotification();
                }
                // if admin wants to rate menu item
                else if (choice2 == 9)
                {
                    admin[0].RateMenuItem();
                }
                // if admin wants to display from file
                else if (choice2 == 10)
                {
                    goto below;
                    admin[0].DisplayFromFile();
                }
                // if admin wants to view users from file
                else if (choice2 == 11)
                {
                below:
                    admin[0].ViewUsersFromFile();
                }
                // if admin wants to view menu items from file
                else if (choice2 == 12)
                {
                    int selectmenu;
                    cout << "Which menu you want to see?\n";
                    cout << "---------------------\n";
                    cout << "|1.Student Menu     |\n";
                    cout << "|2.Faculty Menu     |\n";
                    cout << "|3.Non-Faculty      |\n";
                    cout << "---------------------\n";
                    cout << "Enter your choice(1-3): ";
                    cin >> selectmenu;
                    // if admin wants to see student menu from file
                    if (selectmenu == 1)
                    {
                        admin[0].ViewMenuItemsFromFile(1);
                    }
                    // if admin wants to see faculty menu from file
                    else if (selectmenu == 2)
                    {
                        admin[0].ViewMenuItemsFromFile(2);
                    }
                    // if admin wants to see non-faculty menu from file
                    else if (selectmenu == 3)
                    {
                        admin[0].ViewMenuItemsFromFile(3);
                    }
                    else
                    {
                        cout << "Invalid choice!\n";
                    }
                }
                // if admin wants to view orders from file
                else if (choice2 == 13)
                {
                    admin[0].ViewOrdersFromFile();
                }
                // if admin wants to view ratings from file
                else if (choice2 == 14)
                {
                    admin[0].ViewRatingsFromFile();
                }
                // if admin wants to view payments from file
                else if (choice2 == 15)
                {
                    admin[0].ViewPaymentsFromFile();
                }
                // if admin wants to calculate monthly earnings
                else if (choice2 == 16)
                {
                    admin[0].CalculateMonthlyEarnings();
                }
                // if admin wants to logout
                else if (choice2 == 17)
                {
                    admin[0].Logout();
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            }
        }

        // if user is a staff member
        else if (choice1 == 2)
        {
            bool stafflogin = false;
            int loginOrRegister;
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "Enter your choice (1-2): ";
            cin >> loginOrRegister;
            // if staff member wants to login
            if (loginOrRegister == 1)
            {
            login_staff:
                string inputId, inputPassword;
                cout << "Enter staffId: ";
                cin >> inputId;
                cout << "Enter 4 digit password: ";
                // logic for storing password secretly
                for (int i = 0; i < 4; i++)
                {
                    char c = getch();
                    inputPassword += c;
                    c = '*';
                    cout << c;
                }
                // cin >> inputPassword;
                for (int i = 0; i < n; i++)
                {
                    if (inputId == staffMembers[i].getUserId() && inputPassword == staffMembers[i].getPassword())
                    {
                        staffMembers[i].Login();
                        stafflogin = true;
                        staff_index = i;
                        break;
                    }
                }
                if (!stafflogin)
                {
                    cout << "\nLogin failed!\n";
                    goto a;
                }
            }
            // if staff member wants to register
            else if (loginOrRegister == 2)
            {
                // creating new staff member dynamically
                Staff *newStaffMembers = new Staff[n + 1];
                for (int i = 0; i < n; i++)
                {
                    newStaffMembers[i] = staffMembers[i];
                }
                delete[] staffMembers;
                newStaffMembers[n].Register();
                staffMembers = newStaffMembers;
                n++;
                goto login_staff;
            }
            else
            {
                cout << "Invalid choice!\n";
            }
            int choice3 = 0;
            // loop which shows staff member his capabilities
            while (choice3 != 5)
            {
                cout << "\n---------------------------\n";
                cout << "|1.View Menu              |\n";
                cout << "|2.Process Order          |\n";
                cout << "|3.Add Menu Item          |\n";
                cout << "|4.Remove Menu Item       |\n";
                cout << "|5.Logout                 |\n";
                cout << "---------------------------\n";
                cout << "Enter your choice (1-5): ";
                cin >> choice3;
                // if staff members wants to view menu
                if (choice3 == 1)
                {
                    staffMembers[staff_index].setadmin(admin);
                    staffMembers[staff_index].ViewMenu();
                }
                // if staff member wants to process order
                else if (choice3 == 2)
                {
                }
                // if staff member wants to add menu item
                else if (choice3 == 3)
                {
                    staffMembers[staff_index].AddMenuItem();
                }
                // if staff member wants to remove menu item
                else if (choice3 == 4)
                {
                    staffMembers[staff_index].RemoveMenuItem();
                }
                // if staff member wants to logout
                else if (choice3 == 5)
                {
                    staffMembers[staff_index].Logout();
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            }
        }
        // if user is a customer
        else if (choice1 == 3)
        {
            bool customerlogin = false;
            int loginOrRegister;
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "Enter your choice (1-2): ";
            cin >> loginOrRegister;
            // if customer wants to login
            if (loginOrRegister == 1)
            {
            login_customer:
                string inputId, inputPassword;
                cout << "Enter customerId: ";
                cin >> inputId;
                cout << "Enter password: ";
                // logic for storing password secretly
                for (int i = 0; i < 4; i++)
                {
                    char c = getch();
                    inputPassword += c;
                    c = '*';
                    cout << c;
                }
                // cin >> inputPassword;
                for (int i = 0; i < n2; i++)
                {
                    if (inputId == customers[i].getUserId() && inputPassword == customers[i].getPassword())
                    {
                        customers[i].Login();
                        customerlogin = true;
                        customer_index = i;
                        break;
                    }
                }
                if (!customerlogin)
                {
                    cout << "\nLogin failed!\n";
                    goto a;
                }
            }
            // if customer wants to register
            else if (loginOrRegister == 2)
            {
                // creating new customer dynamically
                Customer *newCustomers = new Customer[n2 + 1];
                for (int i = 0; i < n2; i++)
                {
                    newCustomers[i] = customers[i];
                }
                // delete[] customers;
                newCustomers[n2].Register();
                customers = newCustomers;
                n2++;
                goto login_customer;
            }
            else
            {
                cout << "Invalid choice!\n";
            }

            int choice4 = 0;
            // loop which shows customer his capabilities
            while (choice4 != 5)
            {
                cout << "----------------------------\n";
                cout << "|1.View Menu               |\n";
                cout << "|2.Place Order             |\n";
                cout << "|3.View Order History      |\n";
                cout << "|4.Rate Item               |\n";
                // cout << "|5.Display Ratings         |\n";
                cout << "|5.Logout                  |\n";
                cout << "---------------------------\n";
                cout << "Enter your choice (1-5): ";
                cin >> choice4;
                // if customer wants to view menu
                if (choice4 == 1)
                {
                    customers[customer_index].setadmin(admin);
                    string customer_type;
                    // asking customer to tell if he is student,faculty,non-faculty member
                    cout << "Enter your type (Student/Faculty/Non-Faculty): ";
                    cin.ignore();
                    getline(cin, customer_type);
                    // if customer is a student
                    if (customer_type == "Student")
                    {
                        customers[customer_index].ViewMenu(1);
                    }
                    // if customer is a faculty member
                    else if (customer_type == "Faculty")
                    {
                        customers[customer_index].ViewMenu(2);
                    }
                    // if customer is a non-faculty member
                    else if (customer_type == "Non-Faculty")
                    {
                        customers[customer_index].ViewMenu(3);
                    }
                    else
                    {
                        cout << "Invalid choice!\n";
                    }
                }
                // if customer wants to place order
                else if (choice4 == 2)
                {
                    string customer_type;
                    // asking customer to tell if he is student,faculty,non-faculty member
                    cout << "Enter your type (Student/Faculty/Non-Faculty): ";
                    cin.ignore();
                    getline(cin, customer_type);
                    // if customer is a student
                    if (customer_type == "Student")
                    {
                        customers[customer_index].PlaceOrder(1);
                    }
                    // if customer is a faculty member
                    else if (customer_type == "Faculty")
                    {
                        customers[customer_index].PlaceOrder(2);
                    }
                    // if customer is a non-faculty member
                    else if (customer_type == "Non-Faculty")
                    {
                        customers[customer_index].PlaceOrder(3);
                    }
                    else
                    {
                        cout << "Invalid choice!\n";
                    }
                }
                // if customer wants to view order history
                else if (choice4 == 3)
                {
                    customers[customer_index].ViewOrderHistory();
                }
                // if customer wants to rate item
                else if (choice4 == 4)
                {
                    customers[customer_index].RateItem();
                }
                // if customer wants to logout
                else if (choice4 == 5)
                {
                    customers[customer_index].Logout();
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
            }
        }
        // if user wants to exit
        else if (choice1 == 4)
        {
            cout << "Thank you for using our system!\n";
            cout << "Have a nice day!\n\n\n";
        }

        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}