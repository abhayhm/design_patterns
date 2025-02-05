#include <iostream>
#include <string>
#include <memory>
#include <ctime>

using namespace std;

class CloudStorage
{
public:
    virtual bool uploadContents(const string &content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;

        return true;
    }

    int getFreeSpace() override
    {
        // Implement the logic for getting the free space on CloudDrive here.
        const int size = rand() % 20;
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        const int size = rand() % 10;
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }
    int usedSpace()
    {
        return rand() % 10;
    }
    const int totalSpace = 15;
};

class VirtualDriveAdapter: public CloudDrive{
private:
    unique_ptr<VirtualDrive> vDrive;
public:
    VirtualDriveAdapter(): vDrive(make_unique<VirtualDrive>()) {}

    bool uploadContents(const string &content){
        cout << "Uploading " << content.length() << " bytes to VirtualDrive: " << endl;
        return vDrive->uploadData(content, rand() % 999);
    }
    int getFreeSpace(){
        int freeSpace = vDrive->totalSpace - vDrive->usedSpace();
        cout << "Available VirtualDrive storage: " << freeSpace << "GB" << endl;
        return freeSpace;
    }
};

int main()
{
    // Create an array of pointers to CloudStorage objects.
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<VirtualDriveAdapter>()
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object.
    const string content = "Beam me up, Scotty!";
    for (const auto &service : cloudServices)
    {        
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}