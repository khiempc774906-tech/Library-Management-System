#ifndef PERSON_H 
#define PERSON_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Person
{
protected:
    string id;
    string name;
    string mssv;
    string password;

public:
    Person(string id, string name, string mssv)
    {
        this->id = id;
        this->name = name;
        this->mssv = mssv;
    }

    string getId() { return id; }
    string getName() { return name; }
    string getMssv() { return mssv; }
    void setPassword(const string &p) { password = p; }
    string getPassword() { return password; }

    virtual void show() = 0;
};


class SinhVien : public Person
{
public:
    int soSachDangMuon;

    SinhVien(string id, string name, string mssv) : Person(id, name, mssv)
    {
        soSachDangMuon = 0;
    }

    void show()
    {
        cout << left << setw(8) << id << "| " << setw(25) << name << "| " << setw(15) << mssv << "| " << setw(10) << (to_string(soSachDangMuon) + string(" tai lieu")) << endl;
    }
};

class Librarian : public Person
{
public:
    string maNhanVien;

    Librarian(string id, string name, string mssv, string maNV) : Person(id, name, mssv)
    {
        maNhanVien = maNV;
    }

    void show()
    {
        cout << left << setw(8) << id << "| " << setw(25) << name << "| " << setw(15) << mssv << "| " << setw(10) << maNhanVien << endl;
    }
};

#endif
