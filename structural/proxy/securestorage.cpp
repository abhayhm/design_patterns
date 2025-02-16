#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Storage
{
public:
    virtual const string getContents() = 0;
    virtual ~Storage() = default;
};

class SecureStorage : public Storage
{
public:
    explicit SecureStorage(const string &data) : m_Contents(data) {}

    const string getContents()
    {
        return m_Contents;
    }

private:
    const string m_Contents;
};

class SecureStorageProxy: public Storage{
private:
    const int code;
    unique_ptr<SecureStorage> secureStorage;

    bool auth(const int &code){
        return code == 1431;
    }
public:
    SecureStorageProxy(const string &s, const int c): secureStorage(make_unique<SecureStorage>(s)), code(c) {}
    virtual const string getContents() override{
        if(auth(code)) return secureStorage->getContents();
        else cout<<"Access denied"<<endl;
        return "";
    }
};

int main()
{
    SecureStorageProxy secureStorage("Top Secret Information", 1431);

    // Limit access to sensitive data
    cout << "Sensitive Data: " << secureStorage.getContents() << endl;

    return 0;
}