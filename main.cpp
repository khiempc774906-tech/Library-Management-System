#include <iostream>
#include "Library.h"
using namespace std;

// dữ liệu mẫu để test chương trình
void nhapDuLieuMau(Library &lib)
{
    lib.themSach("B001", "Lap Trinh C++ Co Ban", "Nguyen Van A");
    lib.themSach("B002", "Lap Trinh Python Co Ban", "Tran Thi B");
    lib.themSach("B003", "Toan Roi Rac", "Le Van C");

    lib.themTapChi("M001", "Tap Chi Cong Nghe", 45);
    lib.themTapChi("M002", "Tap Chi Khoa Hoc", 12);
    lib.themTapChi("M003", "Tap Chi Kinh Te", 25);

    lib.themDVD("D001", "Phim Khoa Hoc Vu Tru", 120);
    lib.themDVD("D002", "Phim Am Nhac", 90);
    lib.themDVD("D003", "Phim Hoat Hinh", 60);

    lib.themSinhVien("SV01", "Pham Huy", "123456789012");
    lib.themSinhVien("SV02", "Tuyet Nhu", "234567890123");

    lib.themThuThu("LIB01", "Hoang Van Thu Thu", "0900000000", "TT001"); // password = TT001
}

void inMenu(bool showSinhVien = true)
{
    cout << "\n\tHE THONG QUAN LY THU VIEN" << endl;
    cout << "1. Xem danh sach tai lieu" << endl;
    if (showSinhVien)
        cout << "2. Xem danh sach sinh vien" << endl;
    cout << "3. Muon tai lieu" << endl;
    cout << "4. Tra tai lieu" << endl;
    cout << "5. Xem lich su muon sach" << endl;
    cout << "6. Cho thoi gian troi qua (de test tinh tien phat)" << endl;
}

int main()
{
    Library lib;
    nhapDuLieuMau(lib);
    string currentUser = "";
    bool isLibrarian = false;
    bool loggedIn = false;

    while (true)
    {
        if (!loggedIn)
        {
            cout << "\n\tHE THONG QUAN LY THU VIEN" << endl;
            cout << "1. Dang ky (Sinh vien)" << endl;
            cout << "2. Dang nhap" << endl;
            cout << "0. Thoat" << endl;
            cout << "Lua chon: ";
            int c;
            cin >> c;
            if (c == 1)
            {
                string name, pw;
                cout << "Nhap ten: ";
                cin.ignore();
                getline(cin, name);
                cout << "Dat mat khau: ";
                cin >> pw;
                string newId = lib.dangKySinhVien(name, pw);
                if (!newId.empty())
                {
                    cout << "\nDang ky thanh cong. id cua ban la " << newId << endl;
                    cout << "Vui long dang nhap de tiep tuc." << endl;
                }
                else
                {
                    cout << "Dang ky that bai." << endl;
                }
            }
            else if (c == 2)
            {
                string id, pw;
                cout << "Nhap ID: ";
                cin >> id;
                cout << "Nhap mat khau: ";
                cin >> pw;
                bool tmpIsLib = false;
                int res = lib.dangNhap(id, pw, tmpIsLib);
                if (res == 0)
                    cout << "Dang nhap that bai" << endl;
                else
                {
                    loggedIn = true;
                    currentUser = id;
                    isLibrarian = tmpIsLib;
                    cout << "Dang nhap thanh cong. Vai tro: " << (isLibrarian ? "Thu thu" : "Sinh vien") << endl;
                }
            }
            else if (c == 0)
            {
                cout << "Thoat." << endl;
                return 0;
            }
        }
        else
        {
            // hiển thị menu dựa trên vai trò của người dùng
            int chon;
            inMenu(isLibrarian);
            cout << "7. Tra cuu tai lieu" << endl;
            if (isLibrarian)
            {
                cout << "8. Them tai lieu" << endl;
                cout << "9. Sua tai lieu" << endl;
                cout << "10. Xoa tai lieu" << endl;
                cout << "11. Dang xuat" << endl;
            }
            else
            {
                cout << "8. Dang xuat" << endl;
            }
            cout << "0. Thoat" << endl;
            cout << "Chon: ";
            cin >> chon;

            if (chon == 1)
            {
                lib.hienThiTaiLieu();
            }
            else if (chon == 2)
            {
                lib.hienThiSinhVien();
            }
            else if (chon == 3)
            {
                string maTL;
                if (!loggedIn)
                {
                    cout << "Ban phai dang nhap de muon." << endl;
                    continue;
                }
                if (isLibrarian)
                {
                    string maSV;
                    cout << "Nhap ma sinh vien (vd: SV01): ";
                    cin >> maSV;
                    cout << "Nhap ma tai lieu (vd: B001): ";
                    cin >> maTL;
                    lib.muonTaiLieu(maSV, maTL);
                }
                else
                {
                    cout << "Nhap ma tai lieu (vd: B001): ";
                    cin >> maTL;
                    lib.muonTaiLieu(currentUser, maTL);
                }
            }
            else if (chon == 4)
            {
                string maTL;
                if (!loggedIn)
                {
                    cout << "Ban phai dang nhap de tra." << endl;
                    continue;
                }
                if (isLibrarian)
                {
                    string maSV;
                    cout << "Nhap ma sinh vien (vd: SV01): ";
                    cin >> maSV;
                    cout << "Nhap ma tai lieu (vd: B001): ";
                    cin >> maTL;
                    lib.traTaiLieu(maSV, maTL);
                }
                else
                {
                    cout << "Nhap ma tai lieu (vd: B001): ";
                    cin >> maTL;
                    lib.traTaiLieu(currentUser, maTL);
                }
            }
            else if (chon == 5)
            {
                if (loggedIn && !isLibrarian)
                {
                    lib.hienThiPhieuMuon(currentUser);
                }
                else
                {
                    lib.hienThiPhieuMuon();
                }
            }
            else if (chon == 6)
            {
                int soNgay;
                cout << "Nhap so ngay cho troi qua: ";
                cin >> soNgay;
                lib.choNgayTroiQua(soNgay);
            }
            else if (chon == 7)
            {
                cout << "Chon kieu tim kiem: 1 = Theo ID, 2 = Theo Ten: ";
                int s;
                cin >> s;
                if (s == 1)
                {
                    string id;
                    cout << "Nhap ID: ";
                    cin >> id;
                    lib.timKiemTheoId(id);
                }
                else if (s == 2)
                {
                    string ten;
                    cout << "Nhap Ten hoac chuoi: ";
                    cin.ignore();
                    getline(cin, ten);
                    lib.timKiemTheoTen(ten);
                }
                else
                    cout << "Lua chon khong hop le." << endl;
            }
            else if (chon == 8 && isLibrarian)
            {
                int type;
                cout << "Chon kieu tai lieu: 1 = Sach, 2 = Tap chi, 3 = DVD: ";
                cin >> type;
                string id, ten;
                int tempInt;
                string tempStr;
                int copies;
                cout << "Nhap ID: ";
                cin >> id;
                cin.ignore();
                cout << "Nhap Ten: ";
                getline(cin, ten);
                if (type == 1)
                {
                    cout << "Nhap tac gia: ";
                    getline(cin, tempStr);
                    cout << "Nhap so ban sao: ";
                    cin >> copies;
                    lib.themSach(id, ten, tempStr, copies);
                }
                else if (type == 2)
                {
                    cout << "Nhap so phat hanh: ";
                    cin >> tempInt;
                    cout << "Nhap so ban sao: ";
                    cin >> copies;
                    lib.themTapChi(id, ten, tempInt, copies);
                }
                else if (type == 3)
                {
                    cout << "Nhap thoi luong (phut): ";
                    cin >> tempInt;
                    cout << "Nhap so ban sao: ";
                    cin >> copies;
                    lib.themDVD(id, ten, tempInt, copies);
                }
                cout << "Da them tai lieu." << endl;
            }
            else if (chon == 9 && isLibrarian)
            {
                string id, ten;
                int copies;
                cout << "Nhap ID can sua: ";
                cin >> id;
                cin.ignore();
                cout << "Nhap ten moi: ";
                getline(cin, ten);
                cout << "Nhap tong ban sao moi: ";
                cin >> copies;
                if (lib.suaTenVaSoLuong(id, ten, copies))
                    cout << "Da cap nhat." << endl;
                else
                    cout << "Khong tim thay." << endl;
            }
            else if (chon == 10 && isLibrarian)
            {
                string id;
                cout << "Nhap ID can xoa: ";
                cin >> id;
                if (lib.xoaTaiLieu(id))
                    cout << "Da xoa." << endl;
                else
                    cout << "Khong tim thay." << endl;
            }
            else if ((chon == 11 && isLibrarian) || (chon == 8 && !isLibrarian))
            {
                loggedIn = false;
                currentUser = "";
                isLibrarian = false;
                cout << "Da dang xuat." << endl;
            }
            else if (chon == 0)
            {
                cout << "Thoat." << endl;
                break;
            }
            else
            {
                cout << "Lua chon khong hop le!" << endl;
            }
        }
    }

    return 0;
}
