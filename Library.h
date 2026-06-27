#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include "Person.h"
#include "LibraryItem.h"
#include "Loan.h"
using namespace std;

class Library
{
private:
    vector<LibraryItem *> danhSachTaiLieu;
    vector<SinhVien *> danhSachSinhVien;
    vector<Librarian *> danhSachThuThu;
    vector<Loan *> danhSachPhieuMuon;
    int ngayHienTai;
    int demSoPhieu;

public:
    Library()
    {
        ngayHienTai = 0;
        demSoPhieu = 1;
    }

    void themSach(string id, string ten, string tacGia)
    {
        danhSachTaiLieu.push_back(new Book(id, ten, tacGia, 1));
    }

    void themTapChi(string id, string ten, int soPH)
    {
        danhSachTaiLieu.push_back(new Magazine(id, ten, soPH, 1));
    }

    void themDVD(string id, string ten, int phut)
    {
        danhSachTaiLieu.push_back(new DVD(id, ten, phut, 1));
    }

    void themSach(string id, string ten, string tacGia, int copies)
    {
        danhSachTaiLieu.push_back(new Book(id, ten, tacGia, copies));
    }

    void themTapChi(string id, string ten, int soPH, int copies)
    {
        danhSachTaiLieu.push_back(new Magazine(id, ten, soPH, copies));
    }

    void themDVD(string id, string ten, int phut, int copies)
    {
        danhSachTaiLieu.push_back(new DVD(id, ten, phut, copies));
    }

    void themSinhVien(string id, string ten, string mssv)
    {
        danhSachSinhVien.push_back(new SinhVien(id, ten, mssv));
    }

    void themThuThu(string id, string ten, string mssv, string maNV)
    {
        Librarian *l = new Librarian(id, ten, mssv, maNV);
        // password mặc định = maNV
        l->setPassword(maNV);
        danhSachThuThu.push_back(l);
    }

    // tự động tạo id mới theo dạng SVxx
    string dangKySinhVien(string ten, string password)
    {
        int maxNum = 0;
        for (auto s : danhSachSinhVien)
        {
            string sid = s->getId();
            if (sid.size() > 2 && sid.substr(0, 2) == "SV")
            {
                try
                {
                    int v = stoi(sid.substr(2));
                    if (v > maxNum)
                        maxNum = v;
                }
                catch (...)
                {
                }
            }
        }
        int newNum = maxNum + 1;
        char buf[10];
        if (newNum < 10)
            sprintf(buf, "SV0%d", newNum);
        else
            sprintf(buf, "SV%d", newNum);
        string newId = string(buf);
        SinhVien *sv = new SinhVien(newId, ten, "");
        sv->setPassword(password);
        danhSachSinhVien.push_back(sv);
        return newId;
    }

    int dangNhap(string id, string password, bool &isLibrarian)
    {
        for (auto s : danhSachSinhVien)
        {
            if (s->getId() == id && s->getPassword() == password)
            {
                isLibrarian = false;
                return 1;
            }
        }
        for (auto l : danhSachThuThu)
        {
            if (l->getId() == id && l->getPassword() == password)
            {
                isLibrarian = true;
                return 2;
            }
        }
        return 0;
    }

    // 2 hàm tìm kiếm theo id và tên
    void timKiemTheoId(const string &id)
    {
        LibraryItem *it = timTaiLieu(id);
        if (!it)
        {
            cout << "Khong tim thay tai lieu voi ID: " << id << endl;
            return;
        }
        cout << "\n\tKET QUA TIM KIEM THEO ID: " << id << endl;
        cout << left << setw(12) << "Loai" << "| " << setw(8) << "ID" << "| " << setw(30) << "Ten" << "| " << setw(25) << "Thong tin" << "| " << setw(8) << "So luong" << "| " << setw(6) << "Con lai" << endl;
        cout << string(105, '-') << endl;
        it->show();
        cout << string(105, '-') << endl;
    }

    void timKiemTheoTen(const string &ten)
    {
        cout << "\n\tKET QUA TIM KIEM THEO TEN: " << ten << endl;
        cout << left << setw(12) << "Loai" << "| " << setw(8) << "ID" << "| " << setw(30) << "Ten" << "| " << setw(25) << "Thong tin" << "| " << setw(8) << "So luong" << "| " << setw(6) << "Con lai" << endl;
        cout << string(105, '-') << endl;
        bool found = false;
        for (auto it : danhSachTaiLieu)
        {
            if (it->getTen().find(ten) != string::npos)
            {
                it->show();
                found = true;
            }
        }
        if (!found)
            cout << "Khong tim thay tai lieu voi ten chua: " << ten << endl;
        cout << string(105, '-') << endl;
    }

    bool xoaTaiLieu(string id)
    {
        for (auto it = danhSachTaiLieu.begin(); it != danhSachTaiLieu.end(); ++it)
        {
            if ((*it)->getId() == id)
            {
                delete *it;
                danhSachTaiLieu.erase(it);
                return true;
            }
        }
        return false;
    }

    bool suaTenVaSoLuong(string id, string newTen, int newTotalCopies)
    {
        LibraryItem *item = timTaiLieu(id);
        if (!item)
            return false;
        for (size_t i = 0; i < danhSachTaiLieu.size(); ++i)
        {
            if (danhSachTaiLieu[i]->getId() == id)
            {
                Book *b = dynamic_cast<Book *>(danhSachTaiLieu[i]);
                if (b)
                {
                    string tacgia = b->tacGia;
                    delete danhSachTaiLieu[i];
                    danhSachTaiLieu[i] = new Book(id, newTen, tacgia, newTotalCopies);
                    return true;
                }
                Magazine *m = dynamic_cast<Magazine *>(danhSachTaiLieu[i]);
                if (m)
                {
                    int soPH = m->soPhatHanh;
                    delete danhSachTaiLieu[i];
                    danhSachTaiLieu[i] = new Magazine(id, newTen, soPH, newTotalCopies);
                    return true;
                }
                DVD *d = dynamic_cast<DVD *>(danhSachTaiLieu[i]);
                if (d)
                {
                    int phut = d->thoiLuong;
                    delete danhSachTaiLieu[i];
                    danhSachTaiLieu[i] = new DVD(id, newTen, phut, newTotalCopies);
                    return true;
                }
            }
        }
        return false;
    }

    void hienThiTaiLieu()
    {
        cout << "\n\tDANH SACH TAI LIEU" << endl;
        cout << left << setw(12) << "Loai" << "| " << setw(8) << "ID" << "| " << setw(30) << "Ten" << "| " << setw(25) << "Thong tin" << "| " << setw(10) << "So luong" << "| " << setw(6) << "Con lai" << endl;
        cout << string(105, '-') << endl;

        // sách
        bool found = false;
        for (auto i = danhSachTaiLieu.begin(); i != danhSachTaiLieu.end(); ++i)
        {
            Book *b = dynamic_cast<Book *>(*i);
            if (b)
            {
                found = true;
                b->show();
            }
        }
        if (found)
            cout << string(105, '-') << endl;

        // tạp chí
        found = false;
        for (auto i = danhSachTaiLieu.begin(); i != danhSachTaiLieu.end(); ++i)
        {
            Magazine *m = dynamic_cast<Magazine *>(*i);
            if (m)
            {
                found = true;
                m->show();
            }
        }
        if (found)
            cout << string(105, '-') << endl;

        // dvd
        found = false;
        for (auto i = danhSachTaiLieu.begin(); i != danhSachTaiLieu.end(); ++i)
        {
            DVD *d = dynamic_cast<DVD *>(*i);
            if (d)
            {
                found = true;
                d->show();
            }
        }
        if (found)
            cout << string(105, '-') << endl;
    }

    void hienThiSinhVien()
    {
        cout << "\n\tDANH SACH SINH VIEN" << endl;
        cout << left << setw(8) << "ID" << "| " << setw(25) << "Ten" << "| " << setw(15) << "MSSV" << "| " << setw(10) << "Dang muon" << endl;
        cout << string(70, '-') << endl;
        for (auto i = danhSachSinhVien.begin(); i != danhSachSinhVien.end(); ++i)
        {
            (*i)->show();
        }
        cout << string(70, '-') << endl;
    }

    // tìm tài liệu theo id
    LibraryItem *timTaiLieu(string id)
    {
        for (vector<LibraryItem *>::iterator i = danhSachTaiLieu.begin(); i != danhSachTaiLieu.end(); i++)
        {
            if ((*i)->getId() == id)
            {
                return *i;
            }
        }
        return NULL;
    }

    // tìm sinh viên theo id
    SinhVien *timSinhVien(string id)
    {
        for (vector<SinhVien *>::iterator i = danhSachSinhVien.begin(); i != danhSachSinhVien.end(); i++)
        {
            if ((*i)->getId() == id)
            {
                return *i;
            }
        }
        return NULL;
    }

    void muonTaiLieu(string maSV, string maTL)
    {
        SinhVien *sv = timSinhVien(maSV);
        LibraryItem *tl = timTaiLieu(maTL);

        if (sv == NULL)
        {
            cout << "Khong tim thay sinh vien!" << endl;
            return;
        }
        if (tl == NULL)
        {
            cout << "Khong tim thay tai lieu!" << endl;
            return;
        }
        if (tl->getAvailableCopies() <= 0)
        {
            cout << "Khong con ban sao de muon!" << endl;
            return;
        }
        if (sv->soSachDangMuon >= 3)
        {
            cout << "Sinh vien da muon toi da 3 sach, khong the muon them!" << endl;
            return;
        }

        // nếu pass được hết điều kiện từ hàm muonTaiLieu thì bắt đầu thực hiện mượn
        tl->borrowCopy();
        sv->soSachDangMuon++;

        string maPhieu = "LN" + to_string(demSoPhieu);
        demSoPhieu++;
        Loan *phieu = new Loan(maPhieu, maSV, maTL, ngayHienTai);
        danhSachPhieuMuon.push_back(phieu);

        cout << "\nMuon thanh cong! " << sv->getName() << " da muon \"" << tl->getTen() << "\" (Ma phieu: " << maPhieu << ")" << endl;
        cout << "Gioi han muon la 7 ngay, qua 7 ngay se bi tinh tien phat 5000d/ngay." << endl;
    }

    void traTaiLieu(string maSV, string maTL)
    {
        SinhVien *sv = timSinhVien(maSV);
        LibraryItem *tl = timTaiLieu(maTL);

        if (sv == NULL || tl == NULL)
        {
            cout << "Thong tin khong hop le!" << endl;
            return;
        }

        Loan *phieuCanTra = NULL;
        for (vector<Loan *>::iterator i = danhSachPhieuMuon.begin(); i != danhSachPhieuMuon.end(); i++)
        {
            Loan *p = *i;
            if (p->maSinhVien == maSV && p->maTaiLieu == maTL && p->daTra == false)
            {
                phieuCanTra = p;
                break;
            }
        }

        if (phieuCanTra == NULL)
        {
            cout << "Khong tim thay phieu muon phu hop!" << endl;
            return;
        }

        int soNgayMuon = ngayHienTai - phieuCanTra->ngayMuon;

        tl->returnCopy();
        sv->soSachDangMuon--;
        phieuCanTra->daTra = true;
        phieuCanTra->ngayTra = ngayHienTai;

        cout << sv->getName() << " da tra \"" << tl->getTen() << "\"." << endl;

        // tính tiền phạt: muộn quá 7 ngày thì tính 5000d/ngày
        if (soNgayMuon > 7)
        {
            int soNgayTre = soNgayMuon - 7;
            int tienPhat = soNgayTre * 5000;
            cout << sv->getName() << " da tra sach tre " << soNgayTre << " ngay (gioi han: 7 ngay) -> Tien phat: " << tienPhat << " VND" << endl;
        }
        else
        {
            cout << "Tra dung han, khong bi phat." << endl;
        }
    }

    void choNgayTroiQua(int soNgay)
    {
        ngayHienTai += soNgay;
        cout << "Da troi qua " << soNgay << " ngay. Hom nay la ngay thu " << ngayHienTai << "." << endl;
    }

    void hienThiPhieuMuon(string maSV = "")
    {
        cout << "\n\tLICH SU MUON SACH" << endl;
        cout << left << setw(8) << "Phieu" << "| " << setw(8) << "ID" << "| " << setw(12) << "Ma Tai Lieu" << "| " << setw(22) << "Ngay da muon" << "| " << setw(10) << "Trang thai" << endl;
        cout << string(95, '-') << endl;
        for (auto i = danhSachPhieuMuon.begin(); i != danhSachPhieuMuon.end(); ++i)
        {
            if (maSV.empty() || (*i)->maSinhVien == maSV)
            {
                (*i)->show(ngayHienTai);
            }
        }
        cout << string(95, '-') << endl;
    }
};

#endif
