#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
using namespace std;

// forward declaration of admin class
class Admin;

// user class(pure abstract class)
class User
{
    // using encapsulation here by using protected
protected:
    string userId;
    string userName;
    string Password;
    string userType;
    bool isLoggedIn;

    // public member functions of user class
public:
    // constructor
    User();
    // parametrized constructor
    User(string id, string name, string pass, string type);
    // below are getter and setters
    bool IsLoggedIn();
    void setUserId(string id);
    void setUserName(string name);
    void setPassword(string pass);
    void setUserType(string type);
    string getUserId() const;
    string getUserName() const;
    string getPassword() const;
    string getUserType() const;

    // pure virtual functions (applying polymorphism)
    virtual void Register() = 0;

    virtual void Login() = 0;
};

// payment class
class Payment
{
    // using encapsulation here by using protected
protected:
    string paymentId;
    string orderId;
    double amountPaid;
    string paymentStatus;

    // public member functions of payment class
public:
    // constructor
    Payment();
    // parametrized constructor
    Payment(string id, string oId, double amount, string status);
    // below are getter and setters
    void setPaymentId(string id);
    void setOrderId(string oId);
    void setAmountPaid(double amount);
    void setPaymentStatus(string status);
    string getPaymentId();
    string getOrderId();
    double getAmountPaid();
    string getPaymentStatus();
    // method which will allow admin and staff to process payment
    void ProcessPayment(double price, string orderid);
};

// order class
class Order
{
    // using encapsulation here by using protected
protected:
    // using composition(payment can'not exist independently without order)
    Payment payment_instance;
    string orderId;
    string customerId;
    int itemsOrdered[10]; // Specify the size of the array
    int quantities[100];
    int numItems = 0;
    double totalPrice;
    string orderStatus;

public:
    // constructor
    Order();
    // parametrized constructor
    Order(string id, string custId, int items[], double price, string status);
    // below are getter and setters
    void setOrderId(string id);
    void setCustomerId(string custId);
    // void setItemsOrdered(int items[]);
    void setTotalPrice(double price);
    void setOrderStatus(string status);
    string getOrderId();
    string getCustomerId();
    // int *getItemsOrdered();
    double getTotalPrice();
    string getOrderStatus();
    // method which will allow customer to add item to order
    void AddItem(string itemname, int quantity);
    // method which will allow customer to review order
    void revieworder();
    // method which will allow customer to remove item from order
    void RemoveItem();
    // method which will allow customer to calculate total price
    void CalculateTotalPrice();
    // method which will allow customer to confirm order
    void ConfirmOrder();
    // method which will allow customer to cancel order
    void CancelOrder();
};

// Rating class
class Rating
{
    // using encapsulation here by using protected members
protected:
    Rating *R[10];
    int ratings_count = 0;
    string ratingId;
    string menuItemId;
    string customerId;
    int score;
    string comment;

public:
    // constructor
    Rating();
    // parametrized constructor
    Rating(string id, string itemId, string custId, int s, string c);
    // below are getter and setters
    void setRatingId(string id);
    void setMenuItemId(string itemId);
    void setCustomerId(string custId);
    void setScore(int s);
    void setComment(string c);
    string getRatingId();
    string getMenuItemId();
    string getCustomerId();
    int getScore();
    string getComment();

    // method which will allow customer to rate item
    void Rate(string name, string id, string c_id);
    // void ViewAllRatings();
};

// Using inheritance here (Between Staff and USer class)
class Staff : public User
{
public:
    // using aggregation here(admin can exist without staff )
    Admin *admin_instance;
    // using composition here(order can not exist without staff)
    Order order_instance;
    static int staffcount;
    // constructor for staff
    Staff();
    // using polymorphism setting admin in staff class
    void setadmin(Admin *admin);
    // parametrized constructor for staff
    Staff(string id, string name, string pass, string type);
    // function overriding from user class(achieveing polymorphism)
    void Register();
    void Login();

    // method if staff wants to view menu
    void ViewMenu();
    // method if staff wants to process order
    void ProcessOrder();
    // method if staff wants to add item to menu
    void AddMenuItem();
    // method if staff wants to remove item from menu
    void RemoveMenuItem();
    // method if staff wants to logout
    void Logout();
    // operator overloading here
    void *operator new[](size_t s);
    ~Staff();
};

// Using inheritance here (Between Customer and USer class)
class Customer : public User
{

public:
    static int customercount;
    // using association (staff can exits wiithout customer)
    Staff staff_instance;
    // using association
    Rating rating_instance;
    // using composition here(can not have a customer without order id, if customer is destroyed order is also destroyed)
    Order order_instance;
    // using aggregation (admin part of customer but admin can exist independently)
    Admin *admin_instance;
    double total_price;
    int selected_items_student[100];
    int selected_items_faculty[100];
    int selected_items_nonfaculty[100];

    // constructor
    Customer();
    // using polymorphism setting admin in customer class
    void setadmin(Admin *admin);
    // parametrized constructor
    Customer(string id, string name, string pass, string type);
    // function overriding from user class(achieveing polymorphism)
    void Register();
    void Login();
    // method if user wants to see menu
    void ViewMenu(int menu_choice);
    // method if user wants to add item to order
    void PlaceOrder(int menu_choice);
    // method if user wants to review order
    void ViewOrderHistory();
    // method if user wants to rate item
    void RateItem();
    // method if user wants to logout
    void Logout();
    // operator overloading here
    void *operator new[](size_t s);
    ~Customer();
};

// menu class
class Menu
{
    // using encapsulation
protected:
    string itemId;
    string itemName;
    string itemDescription;
    double Price;
    int quantityInStock;

public:
    // constructor
    Menu();
    // parametrized constructor
    Menu(string id, string name, string desc, double price, int quantity);
    // below are getter and setters
    void setItemId(string id);
    void setItemName(string name);
    void setItemDescription(string desc);
    void setPrice(double price);
    void setQuantityInStock(int quantity);
    string getItemId();
    string getItemName();
    string getItemDescription();
    double getPrice();
    int getQuantityInStock();

    // method which will allow admin and staff to update stock
    void updateStock();
};

// file manager class
class FileManager
{
public:
    // variable for name of file
    string FileName;
    // using association here
    Menu menuItem;
    Order order;
    Rating rating;
    Payment payment;
    // method which will save users to file
    void SaveUserToFile();
    // method which will save menu items to file
    void SaveMenuItemsToFile(Menu Item, int menu_choice);
    // method which will save orders to file
    void SaveOrderToFile(Order order);
    // method which will save ratings to file
    void SaveRatingToFile(Rating rating);
    // method which will save payments to file
    void SavePaymentToFile(Payment payment);
};

// admin class(inherited from user class)
class Admin : public User
{

public:
    // using association here ( establishing weak relationships)
    Order order_instance;
    Customer customer_instance;
    FileManager filemanager_instance;

    // array stores all notifications for staff
    string notification_staff[10];
    // array stores all notifications for customer
    string notification_customer[10];
    bool isNotified_staff = false;
    bool isNotified_customer = false;
    int notificationcount_staff = 0;
    int notificationcount_customer = 0;
    // Menu for students
    Menu Stu_menu[10];
    // Menu for faculty
    Menu Fac_menu[10];
    // Menu for non faculty
    Menu NF_menu[10];
    int Stu_itemcount = 0;
    int Fac_itemcount = 0;
    int NF_itemcount = 0;

    // constructor
    Admin();
    // parametrized constructor
    Admin(string id, string name, string pass, string type);
    // function overriding from user class(achieveing polymorphism)
    void Register();
    void Login();

    // method if admin wants to view menu
    void ViewMenu(int choice);
    // method if admin wants to add item to menu
    void AddMenuItem(const Menu &Item, int menu_choice);
    // method if admin wants to remove item from menu
    void RemoveMenuItem(string id, string name, int menu_choice);
    // method if admin wants to update stock
    void ManageInventory();
    // method if admin wants to manage discount promotion
    void ManageDiscountPromotion();
    // method if admin wants to view orders
    void ViewOrderHistory();
    // method if admin wants to add notifications
    void AddNotification();
    // method if admin wants to remove notifications
    void RemoveNotification();
    // method if admin wants rate menu items
    void RateMenuItem();
    // method if admin wants to display users from file
    void DisplayFromFile();
    void ViewUsersFromFile();
    // method if admin wants to display menu items from file
    void ViewMenuItemsFromFile(int menu_choice);
    // method if admin wants to view orders from file
    void ViewOrdersFromFile();
    // method if admin wants to view ratings from file
    void ViewRatingsFromFile();
    // method if admin wants to view payments from file
    void ViewPaymentsFromFile();
    void CalculateMonthlyEarnings();
    // method if admin wants to logout
    void Logout();
    // operator overloading here
    void *operator new[](size_t s);
};
