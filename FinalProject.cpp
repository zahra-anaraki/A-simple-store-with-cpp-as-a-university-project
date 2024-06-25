#include <iostream>
#include <string>
using namespace std;

class Product {
    public:
        int id;
        string name;
        float price;
        int quantity;

    Product(int product_id, string product_name, float product_price, int product_quantity) {
        id = product_id;
        name = product_name;
        price = product_price;
        quantity = product_quantity;
    }
};

class PerishableProduct : public Product {
    public:
        string Date;

    PerishableProduct(int product_id, string product_name, float product_price, int product_quantity, string product_Date)
        : Product(product_id, product_name, product_price, product_quantity) {
        Date = product_Date;
    }
};

class ImPerishableProduct : public Product {
    public:
        ImPerishableProduct(int product_id, string product_name, float product_price, int product_quantity)
            : Product(product_id, product_name, product_price, product_quantity) {}
};

class Order {
    public:
        string customerName;
        Product* products[20];
        int numProducts;

    Order(string name) {
     customerName=name;
     numProducts=0;
    }

    void addProduct(Product* product) {
        if (numProducts < 20) {
            products[numProducts] = product;
            numProducts++;
            }
            else {
            cout << "Can not add more products to order." << endl;
            }
    }

    void displayOrder() {
        cout << "Order for customer: " << customerName << endl;
        for (int i=0; i < numProducts ; i++) {
            cout << "ID: " << products[i]->id << ", Name: " << products[i]->name << ", Price: " << products[i]->price << endl;
        }
    }
};

class Store {
    public:
        const int MAX_PRODUCTS = 20;
        const int MAX_ORDERS = 20;

        Product* mojodi[20];
        int numProducts;
        Order* orders[20];
        int numOrders;

    Store() {
        numProducts=0;
        numOrders=0;
    } 

    void addProduct(Product* new_product) {
        if (numProducts < MAX_PRODUCTS) {
            mojodi[numProducts] = new_product;
            numProducts++;
        } 
        else {
            cout << "Cannot add new product." << endl;
        }
    }

    void displayProducts() {
        if (numProducts == 0) {
            cout << "No products available." << endl;
        }
        else {
            for (int i = 0; i < numProducts; i++) {
                cout << "ID: " << mojodi[i]->id << ", Name: " << mojodi[i]->name << ", Price: " << mojodi[i]->price << ", Quantity: " << mojodi[i]->quantity << endl;
            }
        }
    }

    Order createOrder() {
        string customerName;
        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, customerName);
        Order newOrder(customerName);

        int productId;
        while (true) {
            cout << "Enter product id to add to order (or 0 to finish): ";
            cin >> productId;
            if (productId == 0) {
                break;
            }
            if (productId <= numProducts && productId > 0) {
                newOrder.addProduct(mojodi[productId - 1]); 
                cout << "Product added to your order." << endl;
            } 
            else {
                cout << "Invalid product id." << endl;
            }
        }
        if (numOrders < MAX_ORDERS) {
            orders[numOrders] = new Order(newOrder);
            numOrders++;
        }
        else {
            cout << "Cannot place more orders." << endl;
        }
        return newOrder;
    }

    void displayOrders() {
        if (numOrders == 0) {
            cout << "No orders available." << endl;
            }
        else {
            for (int i = 0; i < numOrders; i++) {
                orders[i]->displayOrder();
            }
        }
    }
};

int main() {
    Store st;
    int choice;
    do {
        cout << ".........................................................................................." << endl;
        cout << ".........................................MENU............................................." << endl;
        cout << ".........................................................................................." << endl;
        cout << "                                  1. Add Product" << endl;
        cout << "                                  2. Display Products" << endl;
        cout << "                                  3. Create an Order" << endl;
        cout << "                                  4. Display Orders" << endl;
        cout << "                                  5. Exit " << endl;
        cout << "                                  Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, quantity;
                string name, expiry_date;
                float price;
                cout << "Enter the ID of the product: ";
                cin >> id;
                cin.ignore();
                cout << "Enter the name of the product: ";
                getline(cin, name);
                cout << "Enter the price: ";
                cin >> price;
                cout << "Enter the quantity: ";
                cin >> quantity;
                cout << "Is the product perishable? (y/n): ";
                char perishable_choice;
                cin >> perishable_choice;
                if (perishable_choice == 'y') {
                    cout << "Enter the expiry date: ";
                    cin >> expiry_date;
                    PerishableProduct* new_perishable_product = new PerishableProduct(id, name, price, quantity, expiry_date);
                    st.addProduct(new_perishable_product);
                } else {
                    ImPerishableProduct* new_Im_perishable_product = new ImPerishableProduct(id, name, price, quantity);
                    st.addProduct(new_Im_perishable_product);
                }
                } break;
            case 2: {
                st.displayProducts();
                } break;
            case 3: {
                st.createOrder();
                } break;
            case 4: {
                st.displayOrders();
                } break;
            case 5: {
                cout << "Exiting program." << endl;
                } break;
            default: {
                cout << "Invalid choice." << endl;
                } break;
            }
        } while (choice != 5);

    return 0;
}