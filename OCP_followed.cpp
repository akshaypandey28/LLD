#include<iostream>
#include<vector>
using namespace std;

//product class
class Product{
public:
    string name;
    double price;
    Product(string name,double price){
        this->name=name;
        this->price=price;
    }
};

//shopping cart class
class ShoppingCart{
private:
    vector<Product*> products;

public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product*> getProducts(){
        return products;
    }

    //calculate the total price in cart
    double calculateTotal(){
        double total=0;
        for(auto p:products) total+=p->price;

        return total;
    }
};

//shopping cart invoice print class
class ShoppingCartPrinter {
private:
    ShoppingCart* cart;

public:
    ShoppingCartPrinter(ShoppingCart* cart){
        this->cart=cart;
    }

    void printInvoice(){
        cout<<"Shopping Cart Invoice : "<<endl;
        for(auto p:cart->getProducts()){
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }   
};

//abstract class
class Persistence {
private:
    ShoppingCart* cart;

public:
    virtual void save(ShoppingCart* cart)=0; //pure virtual function for abstraction
    
};

class SQLPersistence : public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving shopping cart to SQL DB..." << endl;
    }
};

class MongoPersistence : public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving shopping cart to MongoDB..." << endl;
    }
};

class FilePersistence : public Persistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving shopping cart to a file..." << endl;
    }
};
int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    Persistence* db = new SQLPersistence();
    Persistence* mongo = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(cart);   // Save to SQL database
    mongo->save(cart); // Save to MongoDB
    file->save(cart);  // Save to File
    
    return 0;
}