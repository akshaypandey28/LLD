#include<iostream>
#include<vector>
#include<string>
using namespace std;

class FileSystemItem{
public:
    virtual void ls(int indent=0)=0;
    virtual void openAll(int indent=0)=0;
    virtual int getSize()=0;
    virtual string getName()=0;
    virtual bool isFolder()=0;
    virtual FileSystemItem* cd(const string& name)=0;
    virtual ~FileSystemItem(){
        //cout<<"Destructor of FileSystemItem"<<endl;
    }
};

class File : public FileSystemItem{
private:
    string name;
    int size;
public:
    File(string name,int size){
        this->name=name;
        this->size=size;
    }
    
    void ls(int indent=0) override{
        cout<<string(indent,' ')<<name<<endl;
    }
    
    void openAll(int indent=0) override{
        cout<<string(indent , ' ')<<name<<endl;
    }
    
    int getSize() override{
        return size;
    }
    
    string getName() override {
        return name;
    }
    
    bool isFolder() override{
        return false;
    }
    
    FileSystemItem* cd(const string& ) override{
        return nullptr;
    }
    
};

class Folder : public FileSystemItem{
private:
    string name;
    vector<FileSystemItem*> children;
public:
    Folder(const string& name){
        this->name=name;
    }
    
    void add(FileSystemItem* item){
        children.push_back(item);
    }
    
    void ls(int indent = 0) override {
        for (auto child : children) {
            if (child->isFolder()) {
                cout <<string(indent, ' ') << "+ " << child->getName() << endl;
            } else {
                cout <<string(indent, ' ') <<child->getName() << endl;
            }
        }
    }
    
    void openAll(int indent=0) override{
        cout<<string(indent,' ')<<"+ "<<name<<endl;
        for(auto child:children){
            child->openAll(indent+4);
        }
    }
    
    int getSize() override{
        int total=0;
        for(auto child : children){
            total+=child->getSize();
        }
        return total;
    }
    
    string getName() override{
        return name;
    }
    
    bool isFolder() override{
        return true;
    }
    
    FileSystemItem* cd(const string& target) override {
        for (auto child : children) {
            if (child->isFolder() && child->getName() == target) {
                return child;
            }
        }
        // not found or not a folder
        return nullptr;
    }
    
    ~Folder(){
        //cout<<"Deleting the subfolder or subfiles of current folder "<<endl;
        for(auto c:children) delete c;
        //cout<<"Deletion completed"<<endl;
    }
};
int main(){
    // Build file system
    Folder* root = new Folder("root");
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 1));

    Folder* docs = new Folder("docs");
    docs->add(new File("resume.pdf", 1));
    docs->add(new File("notes.txt", 1));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo.jpg", 1));
    root->add(images);

    root->ls();

    docs->ls();

    root->openAll();

    FileSystemItem* cwd = root->cd("docs");
    if (cwd != nullptr) {
        cwd->ls();
    } else {
        cout << "\n Could not cd into docs \n";
    }

    cout << root->getSize();
    cout<<endl;
    // Cleanup
    delete root;
    return 0;
}

