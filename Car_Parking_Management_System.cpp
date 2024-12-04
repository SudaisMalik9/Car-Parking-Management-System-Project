#include<iostream>
#include<queue>
#include<string>
#include<chrono>
#include<ctime>
using namespace std;
using namespace chrono;

struct Vehicle
{
    string licensePlate;
    int slot;
    Vehicle* next;
    system_clock::time_point parkTime;
    Vehicle(string lp,int s)
    {
        licensePlate=lp;
        slot=s;
        next=NULL;
        parkTime=system_clock::now();
    }
};

class ParkingLot
{
public:
    Vehicle* head;
    queue<string> waitingQueue;
    int totalSlots;            
    int currentSlot;        
    double ratePerMinute;   
    ParkingLot(int slots,double rate)
    {
        head=NULL;
        totalSlots=slots;
        currentSlot=0;
        ratePerMinute=rate;
    }
    // Park Vehicles
    void parkVehicle(string licensePlate)
    {
        if(currentSlot>=totalSlots)
        {
            cout<<"Parking is full!! Adding vehicle to the waiting!!"<<endl;
            waitingQueue.push(licensePlate);
            return;
        }
        currentSlot++;
        Vehicle* newVehicle=new Vehicle(licensePlate,currentSlot);
        newVehicle->next=head;
        head=newVehicle;
        cout<<"Vehicle "<<licensePlate<<" parked at slot "<<currentSlot<<"!!"<<endl;
    }
    // Remove Vehicles
    void removeVehicle(string licensePlate)
    {
        if(head==NULL)
        {
            cout<<"Parking lot is empty!!"<<endl;
            return;
        }

        Vehicle* prev=NULL;
        Vehicle* curr=head;
        while(curr && curr->licensePlate!=licensePlate)
        {
            prev=curr;
            curr=curr->next;
        }
        if(curr==NULL)
        {
            cout<<"Vehicle not found!!"<<endl;
            return;
        }
        auto now=system_clock::now();
        auto duration=duration_cast<minutes>(now-curr->parkTime);
        double billAmount=duration.count()*ratePerMinute;
        if(prev)
        {
            prev->next=curr->next;
        }
        else
        {
            head=curr->next;
        }
        cout<<"Vehicle "<<licensePlate<<" has left the parking lot from slot " << curr->slot << "!!"<<endl;
        cout<<"Total parking time: "<<duration.count()<<" minutes!!"<<endl;
        cout<<"Total bill: Rs. "<<billAmount<<endl;
        delete curr;
        currentSlot--;
        if(!waitingQueue.empty())
        {
            string nextVehicle=waitingQueue.front();
            waitingQueue.pop();
            parkVehicle(nextVehicle);
        }
    }
    // Search Vehicles
    void searchVehicle(string licensePlate)
    {
        Vehicle* temp=head;
        while(temp)
        {
            if(temp->licensePlate==licensePlate)
            {
                auto now=system_clock::now();
                auto duration=duration_cast<minutes>(now-temp->parkTime);
                cout<<"Vehicle "<<licensePlate<<" is parked at slot "<<temp->slot<<"!! Parked for "<<duration.count()<<" minutes!!"<<endl;
                return;
            }
            temp=temp->next;
        }
        cout<<"Vehicle "<<licensePlate<<" not found in the parking lot!!"<<endl;
    }
    // Display Vehicles
    void displayStatus()
    {
        cout<<"\nParking Lot Status:"<<endl;
        if(head==NULL)
        {
            cout<<"Parking lot is empty!!"<<endl;
            return;
        }
        Vehicle* temp=head;
        while(temp)
        {
            auto now=system_clock::now();
            auto duration=duration_cast<minutes>(now-temp->parkTime);
            cout<<"License Plate: "<<temp->licensePlate<<" | Slot: "<<temp->slot<<" | Parked for: "<<duration.count()<<" minutes!!"<<endl;
            temp=temp->next;
        }
        cout<<"Waiting Queue: "<<waitingQueue.size()<<" vehicle(s)!!"<<endl;
        cout<<"Available Slots: "<<totalSlots-currentSlot<<"/"<<totalSlots<<endl;
    }
};

// Main Function
int main()
{
    int totalSlots;
    double rate;
    cout<<"Enter total number of parking slots: ";
    cin>>totalSlots;
    cout<<"Enter rate per minute: Rs. ";
    cin>>rate;
    ParkingLot parkingLot(totalSlots,rate);
    int choice;
    string licensePlate;
    while(true)
    {
        cout<<"\nParking Lot Management System"<<endl;
        cout<<"1. Park Vehicle"<<endl;
        cout<<"2. Remove Vehicle"<<endl;
        cout<<"3. Display Status"<<endl;
        cout<<"4. Search for a Vehicle"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                cout<<"Enter license plate: ";
                cin>>licensePlate;
                parkingLot.parkVehicle(licensePlate);
                break;
            }
            case 2:
            {
                cout<<"Enter license plate: ";
                cin>>licensePlate;
                parkingLot.removeVehicle(licensePlate);
                break;
            }
            case 3:
            {
                parkingLot.displayStatus();
                break;
            }
            case 4:
            {
                cout<<"Enter license plate: ";
                cin>>licensePlate;
                parkingLot.searchVehicle(licensePlate);
                break;
            }
            case 5:
            {
                cout<<"Exiting the program...";
                return 0;
            }
            default:
            {
                cout<<"Invalid Choice!! Please Try Again!!"<<endl;
            }
        }
    }
    return 0;
}
