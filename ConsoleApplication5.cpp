#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
    using namespace std;

    class Guest {
    public:
        int IdG;
        int Age;
        float Phone;
        int RoomNumber;
        string Name;

        Guest(int IdG, string Name, int age, float Phone, int RoomNumber = 0) : IdG(IdG), Name(Name), Age(age), Phone(Phone), RoomNumber(RoomNumber) {}
    };  

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class Room {
    public:
        int IdR;
        string Guests;
        int  Number;
        string Type;
        string Title;
        int Beds;
        bool Status;
        float Price;

        Room(int IdR, string Type, string Title, int Beds, bool Status, float Price , int Number) : IdR(IdR) , Type(Type) , Title(Title) , Beds(Beds), Status(Status), Price(Price),Number(Number) {}

    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class StandartRoom : public Room {
    public:
        StandartRoom(int IdR, string Type, string Title, int Beds, bool Status, float Price) : Room(IdR, "standart room", Title, Beds, Status, Price, Number) {}
       
    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class VIPRoom: public Room {
    public:
        VIPRoom(int IdR, string Type, string Title, int Beds, bool Status, float Price) : Room(IdR, "VIP room", Title, Beds, Status, Price, Number) {}
    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PremiumRoom: public Room {
    public:
        PremiumRoom(int IdR, string Type, string Title, int Beds, bool Status, float Price) : Room(IdR, "Premium Room", Title, Beds, Status, Price, Number) {}
    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class LuxRoom: public Room {
    public:
        LuxRoom(int IdR, string Type, string Title, int Beds, bool Status, float Price) : Room(IdR, "Lux room", Title, Beds, Status, Price, Number) {}
    
    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class Bill {
    public:
        int IdB;
        int IdG;
        int IdR;
        float CheckInDate;
        float CheckOutDate;
        float Amount;

        Bill(int IdB, int IdG, int IdR, float CheckInDatel,float CheckoutDate,float Amount) : IdB(IdB) , IdG(IdG) , IdR(IdR) , CheckInDate(CheckInDate) , CheckOutDate (CheckOutDate) , Amount (Amount) {}
    };

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    class  HotelManagement {
    private:
        vector <Guest> Guests;
        vector <Room*> Rooms;
        vector <Bill> Bills;

        //----------------------------------------------------------------------------------------------------------------------------------------------------------------
    public:
        void DGuest() {
            int age;
            string name;
            float phone;
            int IdG;

            cout << "имя :";
            cin >> name;

            cout << "возраст :";
            cin >> age;

            cout << "номер телефона :";
            cin >> phone;

            IdG = Guests.size() + 1;

            Guest NewGuest(IdG, name, age, phone);
            Guests.push_back(NewGuest);

            cout << NewGuest.Name << NewGuest.IdG << endl;
        }
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------
        void DRoom() {
            string Type;
            string Title;
            int Beds;
            int Number;
            float Price;

            cout << "Комната :";
            cin >> Type;

            cout << "Номер комнаты :";
            cin >> Number;

            cout << "Описание комнаты :";
            cin >> Title;

            cout << "Количество кроватей :";
            cin >> Beds;

            cout << "Цена :";
            cin >> Price;


            Room* Room = nullptr;
            int IdR = Rooms.size() + 1;


            if (Type == "Standart") {
                Room = new StandartRoom(IdR, Type, Title, Beds, true, Price);
            }
            else if (Type == "VIP") {
                Room = new VIPRoom(IdR, Type, Title, Beds, true, Price);
            }
            else if (Type == "Premium") {
                Room = new PremiumRoom(IdR, Type, Title, Beds, true, Price);
            }
            else if (Type == "Lux") {
                Room = new LuxRoom(IdR, Type, Title, Beds, true, Price);
            }

            if (Room) {
                Rooms.push_back(Room);
                cout << Title;
            }
        }
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------
        void checkInGues() {
            int IdG;
            int IdR;
            std::cout << "ID гостя :";
            std::cin >> IdG;
            std::cout << " ID комнаты :";
            std::cin >> IdR;

            if (IdG > 0 && IdG <= Guests.size() && IdR > 0 && IdR <= Rooms.size()) {
                auto& Guest = Guests[IdG - 1];
                auto& Room = Rooms[IdR - 1];
                if (!Room->Status) {
                    cout << "Комната занята.\n";
                }
                else {
                    Room->Status = false;
                    Guest.RoomNumber = Room->Number;
                    cout << "Гость " << Guest.Name << " зарегистрирован в комнате " << Room->Title << ".\n";
                }



            }

        };

        void CheckOutGuest() {
            int IdG;
            cout << "Id гостя";
            cin >> IdG;

            if (IdG > 0 && IdG <= Guests.size()) {
                auto& Guest = Guests[IdG - 1];

                if (Guest.RoomNumber == 0) {
                    cout << "Гость " << Guest.Name << " нету\n";

                }
                for (auto& Room : Rooms) {
                    if (Room->Number == Guest.RoomNumber) {
                        Room->Status = true;
                        Guest.RoomNumber = 0;


                        float Amount = Room->Price;
                        Bills.push_back(Bill(Bills.size() + 1, Guest.IdG, Room->IdR, 0, 0, Amount));

                        cout << "Гость " << Guest.Name << " выселен из комнаты " << Room->Title << ".\n";
                        cout << "Сумма к оплате: " << Amount << ".\n";


                    }


                }


            }
        }

        void VRooms() {
            void viewRooms(); {
                for (const auto& Room : Rooms) {
                    cout << Room->IdR << Room->Number << Room->Type << (Room->Status ? "Свободна" : "Занята") << Room->Price << "\n";
                }
            }
        }

        void VGuests() {
            for (const auto& Guest : Guests) {
                cout << Guest.IdG << Guest.Name << Guest.Age << Guest.Phone << Guest.RoomNumber << "\n";
            }
        }

        void VBills() {
            for (const auto& Bill : Bills) {
                cout << "ID щитов" << Bill.IdB << ", ID гостя: " << Bill.IdG << ", ID комнаты: " << Bill.IdR << ", Сумма: " << Bill.Amount << "\n";

            };

        }
        void saveData() {
            ofstream OutFile("Hotelsave.txt");


            OutFile << "Guests\n";
            OutFile << "ID,Name,Age,Phone,RoomNumber\n";
            for (const auto& guest : Guests) {
                OutFile << guest.IdG << "," << guest.Name << "," << guest.Age << "," << guest.Phone << "," << guest.RoomNumber << "\n";
            }

            OutFile << "Rooms\n";
            OutFile << "ID,Number,Type,Title,Beds,Status,Price\n";
            for (const auto& Room : Rooms) {
                OutFile << Room->IdR << "|" << Room->Number << "|" << Room->Type << "|" << Room->Title << "|" << Room->Beds << "|" << Room->Status << "|" << Room->Price << "\n";
            }

            OutFile << "Bills\n";
            OutFile << "ID,IDGuest,IDRoom,CheckInDate,CheckOutDate,Amount\n";
            for (const auto& Bill : Bills) {
                OutFile << Bill.IdB << "|" << Bill.IdG << "|" << Bill.IdR << "|"
                    << Bill.CheckInDate << "|" << Bill.CheckOutDate << "|" << Bill.Amount << "\n";
            }
            OutFile.close();
        }





        //----------------------------------------------------------------------------------------------------------------------------------------------------------------

    };
        
    
    int main() {
            setlocale(LC_ALL, "Russian");
            HotelManagement hotel;

            while (true) {
                cout << "Меню:\n";
                cout << "1. Добавить нового гостя\n";
                cout << "2. Добавить новую комнату\n";
                cout << "3. Заселить гостя в комнату\n";
                cout << "4. Добавить гостя в комнату\n";
                cout << "5. Выселить гостя и составить счет\n";
                cout << "6. Просмотр списка комнат\n";
                cout << "7. Просмотр списка гостей\n";
                cout << "8. Просмотр списка счетов\n";
                cout << "9. Сохранить данные и выйти\n";
                cout << "Выберите опцию: ";

                int option;
                cin >> option;

                switch (option) {
                case 1:
                    hotel.DGuest();
                    break;
                case 2:
                    hotel.DRoom();
                    break;
                case 3:
                    hotel.DGuest();
                    break;
                case 4:
                    hotel.DRoom();
                    break;
                case 5:
                    hotel.CheckOutGuest();
                    break;
                case 6:
                    hotel.VRooms();
                    break;
                case 7:
                    hotel.VGuests();
                    break;
                case 8:
                    hotel.VBills();
                    break;
                case 9:
                    hotel.saveData();
                    return 0;
                }
            }

            return 0;
    }

    
    