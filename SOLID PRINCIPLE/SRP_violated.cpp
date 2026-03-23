#include<iostream>
#include<vector>
using namespace std;

class Product{
public:
    string name;
    double price;

    Product(string name,double price){
        this->name=name;
        this->price=price;
    }
};

class ShoppingCart{
private:
    vector<Product*> products;

public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& getProduct(){
        return products;
    }

    // calculates the total price
    double calculateTotal(){
        double total=0;
        for(auto p:products) total+=p->price;
        return total;
    }

    // Violating SRP - Prints invoice (Should be in a separate class)
    void printInvoice(){
        cout<<"Shopping Cart Invoice : \n";
        for(auto p:products){
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << calculateTotal() << endl;
    }

    // Violating SRP - Saves to DB (Should be in a separate class)
    void saveToDatabase() {
        cout << "Saving shopping cart to database..." << endl;
    }
};
int main(){
    ShoppingCart* cart =new ShoppingCart();
    cart->addProduct(new Product("Laptop",50000));
    cart->addProduct(new Product("Mouse", 2000));

    cart->printInvoice();  
    cart->saveToDatabase();
return 0;
}