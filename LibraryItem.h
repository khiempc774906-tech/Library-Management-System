#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class LibraryItem
{
protected:
    string id;
    string ten;
    int totalCopies;
    int availableCopies;

public:
    LibraryItem(string id, string ten, int copies = 1)
    {
        this->id = id;
        this->ten = ten;
        totalCopies = copies > 0 ? copies : 1;
        availableCopies = totalCopies;
    }

    string getId() { return id; }
    string getTen() { return ten; }


    int getTotalCopies() { return totalCopies; }
    int getAvailableCopies() { return availableCopies; }
    void borrowCopy()
    {
        if (availableCopies > 0)
            availableCopies--;
    }
    void returnCopy()
    {
        if (availableCopies < totalCopies)
            availableCopies++;
    }
    void setTotalCopies(int copies)
    {
        if (copies < 0)
            copies = 0;
        totalCopies = copies;
        if (availableCopies > totalCopies)
            availableCopies = totalCopies;
    }

    virtual ~LibraryItem() {}
    virtual void show() = 0;
};

class Book : public LibraryItem
{
public:
    string tacGia;

    Book(string id, string ten, string tacGia, int copies = 1) : LibraryItem(id, ten, copies)
    {
        this->tacGia = tacGia;
    }

    void show()
    {
        cout << left << setw(12) << "Sach" << "| " << setw(8) << id << "| " << setw(30) << ten << "| " << setw(25) << (string("Tac gia: ") + tacGia) << "| " << setw(10) << totalCopies << "| " << setw(6) << availableCopies << endl;
    }
};

class Magazine : public LibraryItem
{
public:
    int soPhatHanh;

    Magazine(string id, string ten, int soPH, int copies = 1) : LibraryItem(id, ten, copies)
    {
        soPhatHanh = soPH;
    }

    void show()
    {
        cout << left << setw(12) << "Tap chi" << "| " << setw(8) << id << "| " << setw(30) << ten << "| " << setw(25) << (string("So: ") + to_string(soPhatHanh)) << "| " << setw(10) << totalCopies << "| " << setw(6) << availableCopies << endl;
    }
};

class DVD : public LibraryItem
{
public:
    int thoiLuong;

    DVD(string id, string ten, int phut, int copies = 1) : LibraryItem(id, ten, copies)
    {
        thoiLuong = phut;
    }

    void show()
    {
        cout << left << setw(12) << "DVD" << "| " << setw(8) << id << "| " << setw(30) << ten << "| " << setw(25) << (string("Thoi luong: ") + to_string(thoiLuong) + string(" phut")) << "| " << setw(10) << totalCopies << "| " << setw(6) << availableCopies << endl;
    }
};

#endif
