#include<iostream>
#include<vector>
#include<string>
using namespace std;
//1. Target interface expected by client
class IReports{
public:
    virtual string getJSONData(const string& data)=0;
    virtual ~IReports(){
        cout << "Ireports destructor" << endl;
    }
};

//2. Adaptee that provides XML data from a raw input
class XmlDataProvider {
public:
    //data is in the format of "name:id" (e.g "Akshay:22")
    string getXmlData(const string& data){
        size_t sep=data.find(':');
        string name=data.substr(0,sep);
        string id=data.substr(sep+1);

        //build and XML representation
        return "<user>"
                "<name>" + name + "</name>"
                "<id>" + id + "</id>"
                "</user>";
    }
};


//3. Adapter: implements IReports by converting XML -> JSON
class XmlDataProviderAdapter : public IReports{
private:
    XmlDataProvider* xmlProvider;
public:
    XmlDataProviderAdapter(XmlDataProvider* provider){
        this->xmlProvider=provider;
    }

    string getJSONData(const string& data) override{
        // 1. Get XML from the adaptee
        string xml = xmlProvider->getXmlData(data);

        // 2. Naïvely parse out <name> and <id> values
        size_t startName = xml.find("<name>") + 6;
        size_t endName   = xml.find("</name>");
        string name      = xml.substr(startName, endName - startName);

        size_t startId = xml.find("<id>") + 4;
        size_t endId   = xml.find("</id>");
        string id      = xml.substr(startId, endId - startId);

        // 3. Build and return JSON
        return "{\"name\":\"" + name + "\", \"id\":" + id + "}";
    }
};

// 4. Client code works only with IReports
class Client {
public:
    void getReport(IReports* report, string rawData) {
        cout << "Processed JSON: "
        << report->getJSONData(rawData)
        << endl;
    }
};
int main(){
    // 1. Create the adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider();

    // 2. Make our adapter
    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    // 3. Give it some raw data
    string rawData = "Alice:42";

    // 4. Client prints the JSON
    Client* client = new Client();
    client->getReport(adapter, rawData);
    // → Processed JSON: {"name":"Alice", "id":42}

    // 5. Cleanup
    delete adapter;
    delete xmlProv;
return 0;
}