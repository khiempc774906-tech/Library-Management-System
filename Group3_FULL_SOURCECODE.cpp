#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

//Nhóm 1: Thành phần bổ trợ và nghiệp vụ.
class Author  // Tác giả
{ private:
    string name;
  public:
    Author(string n = "Unknown") : name(n) {}  //Constructor
    string getName() const {return name; }
};

class Fine  //Phạt tiền nếu trả sách quá hạn
{ private:
    double amount;
    bool isPaid;
  public:
    Fine(double amt = 0.0) : amount(amt), isPaid(false) {} //Constructor
    void payFine()
      { isPaid = true;
        amount = 0;
      }
    double getAmount() const {return amount; }
};

class Transaction //Giao dịch mượn và trả
{ private:
    int transactionId;
    int itemId;
    int userId;
  public:
    Transaction(int tId, int iId, int uId) : transactionId(tId), itemId(iId), userId(uId) {}
    void printTransaction() const
      { cout<<"Giao dich ID: "<<transactionId
            <<" | User ID: "<<userId<<" | Item ID: "
            <<itemId<<'\n'; 
      }
};

//Nhóm 2: Quản lý tài liệu.
class LibraryItem  //Mục thư viện, Abstract base class
{ protected:  //Encapsulation
    int id;
    string title;
    bool isAvailable;
  public:
    LibraryItem(int i, string t) : id(i), title(t), isAvailable(true) {} //Constructor
    virtual ~LibraryItem() {}  //Destructor
    virtual void displayDetails() const = 0;  //Pure virtual function
    int getId() const {return id; }
    bool getAvailability() const {return isAvailable; }
    void setAvailability(bool status) {isAvailable = status; }
};

class Book:public LibraryItem  //Inheritance
{ private:
    Author author;
    string isbn; //Mã chuẩn quốc tế cho sách
  public:
    Book(int i, string t, Author a, string is) : LibraryItem(i, t), author(a), isbn(is) {}

    //Polymorphism
    void displayDetails() const override
      { cout<<"[Sach] ID: "<<id<<" | Tua de: "<<title
            <<" | Tac gia: "<<author.getName()<<" | ISBN: "<<isbn
            <<" | Trang thai: "<<(isAvailable ? "San sang!" : "Da cho muon!")<<'\n';
      }
};

class Magazine:public LibraryItem //Inheritance
{ private:
    int issueNumber; //Số ấn bản
  public:
    Magazine(int i, string t, int issue) : LibraryItem(i, t), issueNumber(issue) {}
    
    //Polomorphism
    void displayDetails() const override
      { cout<<"[Tap chi] ID: "<<id<<" | Tua de: "<<title
            <<" | So an ban: "<<issueNumber
            <<" | Trang thai: "<<(isAvailable ? "San sang!" : "Da cho muon!")<<'\n';
      }
};

//Nhóm 3: Quản lý người dùng
class User //Abstract base class
{ protected:
    int userId;
    string name;
  public:
    User(int id, string n) : userId(id), name(n) {} //Constructor
    virtual ~User() {} //Destructor
    virtual void showRole() const = 0; //Pure virtual function
    int getUserId() const {return userId; }
    string getName() const {return name; }
};

class Member:public User //Inheritance
{ private:
    Fine memberFine;
  public:
    Member(int id, string n) : User(id, n), memberFine(0.0) {}
    
    //Polymorphism
    void showRole() const override
      { cout<<"Vai tro: Doc gia (Member) - "<<name<<'\n'; }
};

class Librarian:public User //Thủ thư (Inheritance)
{ public:
    Librarian(int id, string n) : User(id, n) {}
    void showRole() const override
      { cout<<"Vai tro: Thu thu (Librarian) - "<<name<<'\n'; }
};

//Nhóm 4: Quản trị hệ thống và giao diện.
class Catalog  //Danh mục tìm kiếm
{ private:
    vector<LibraryItem*> items;
  public:
    void addItemToCatalog(LibraryItem* item) 
      { items.push_back(item); }
    void showAllItems() const
      { cout<<"\n--- DANH MUC TAI LIEU ---\n";
        for(const auto& item : items)
          { item->displayDetails(); } //Polymorphism
      }
};

class Library //Hệ thống điều phối trung tâm
{ private:
    Catalog catalog;
    vector<LibraryItem*> inventory;
    vector<User*> users;
    vector<Transaction> transactions;
    int transactionCounter = 1;
  public:
    ~Library()  //Destructor
       { for(auto item : inventory) delete item;
         for(auto user : users) delete user;
       }
    void seedData()
      { Author a1("J.K. Rowling");
        LibraryItem* b1 = new Book(101, "Harry Potter", a1, "123-456");
        LibraryItem* m1 = new Magazine(102, "National Geographic", 2023);
        inventory.push_back(b1); inventory.push_back(m1);
        catalog.addItemToCatalog(b1); catalog.addItemToCatalog(m1); 
        users.push_back(new Member(1, "Nguyen Van A"));
        users.push_back(new Librarian(99, "Tran Thi B"));
      }
    void displayCatalog() 
      { catalog.showAllItems(); }
    void borrowItem(int userId, int itemId)
      { for(auto item : inventory)
          { if(item->getId() == itemId && item->getAvailability())
              { item->setAvailability(false);
                transactions.push_back(Transaction(transactionCounter++, itemId, userId));
                cout<<"=> Muon thanh cong!\n";
                return;
              }
          }
        cout<<"=> Tai lieu khong ton tai hoac da co nguoi muon!\n";
      }
};

class ConsoleInterface  //Giao diện người dùng
{ private:
    Library lib;
  public:
    void start()
      { lib.seedData();
        int choice;
        do
          { cout<<"\n================ HE THONG QUAN LY THU VIEN ================\n";
            cout<<"1. Xem danh muc tai lieu\n";
            cout<<"2. Muon tai lieu\n";
            cout<<"0. Thoat\n";
            cout<<"Chon chuc nang: ";cin>>choice;

            switch(choice)
              { case 1: 
                  { lib.displayCatalog();
                    break; } 
                case 2:
                  { int uId, iId;
                    cout<<"Nhap ID Nguoi dung(VD: 1): ";cin>>uId;
                    cout<<"Nhap ID Tai lieu muon muon(VD: 101): ";cin>>iId;
                    lib.borrowItem(uId, iId);
                    break;
                  }
                case 0:
                  { cout<<"Da thoat chuong trinh.\n";
                    break; }
                default:
                  cout<<"Lua chon khong hop le!\n";
               }
           } while(choice != 0);
       }
};

int main()
{ ConsoleInterface ui;
  ui.start();
  return 0;
}
