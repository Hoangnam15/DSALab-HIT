#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

// ==========================================
// BÀI 1: TÍNH MIN, MAX, TỔNG, TRUNG BÌNH MẢNG 1 CHIỀU
// ==========================================
namespace Bai1 {
    void run() {
        int n;
        cout << "\n--- [BAI 1] QUAN LY MANG 1 CHIEU ---\n";
        cout << "Nhap so phan tu n: ";
        cin >> n;

        int* arr = new int[n];

        cout << "Nhap " << n << " phan tu:\n";
        for (int i = 0; i < n; i++) {
            cout << "  a[" << i << "] = ";
            cin >> arr[i];
        }

        int minVal = arr[0], maxVal = arr[0];
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
            sum += arr[i];
        }

        double avg = (double)sum / n;

        cout << "\n=== KET QUA BAI 1 ===\n";
        cout << "Min    : " << minVal << "\n";
        cout << "Max    : " << maxVal << "\n";
        cout << "Tong   : " << sum << "\n";
        cout << "TB     : " << avg << "\n";

        delete[] arr;
    }
}

// ==========================================
// BÀI 2: NHÂN MA TRẬN VÀ TÍNH ĐỊNH THỨC 3X3
// ==========================================
namespace Bai2 {
    const int MAXN = 10;

    void printMatrix(int mat[][MAXN], int n, const char* title) {
        cout << "\n--- " << title << " ---\n";
        for (int i = 0; i < n; i++) {
            cout << "| ";
            for (int j = 0; j < n; j++)
                cout << setw(5) << mat[i][j];
            cout << "  |\n";
        }
    }

    void multiplyMatrix(int A[][MAXN], int B[][MAXN], int C[][MAXN], int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
    }

    int determinant3x3(int m[][MAXN]) {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
            - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
            + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    void inputMatrix(int mat[][MAXN], int n, const char* name) {
        cout << "\nNhap ma tran " << name << " (" << n << "x" << n << "):\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cout << "  [" << i << "][" << j << "] = ";
                cin >> mat[i][j];
            }
    }

    void run() {
        int n;
        cout << "\n--- [BAI 2] THAO TAC TREN MA TRAN ---\n";
        cout << "Nhap n (toi da " << MAXN << "): ";
        cin >> n;

        if (n > MAXN || n <= 0) {
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
        inputMatrix(A, n, "A");
        inputMatrix(B, n, "B");
        multiplyMatrix(A, B, C, n);

        printMatrix(A, n, "Ma tran A");
        printMatrix(B, n, "Ma tran B");
        printMatrix(C, n, "A x B");

        if (n == 3) {
            cout << "\nDinh thuc A = " << determinant3x3(A) << "\n";
            cout << "Dinh thuc B = " << determinant3x3(B) << "\n";
        }
    }
}

// ==========================================
// BÀI 3: DEMO MẢNG ĐỘNG DYNAMIC ARRAY (INT)
// ==========================================
namespace Bai3 {
    class DynamicArray {
        int* data;
        int sz;
        int cap;

        void resize() {
            cap = (cap == 0) ? 1 : cap * 2;
            int* newData = new int[cap];
            for (int i = 0; i < sz; i++)
                newData[i] = data[i];
            delete[] data;
            data = newData;
        }

    public:
        DynamicArray() : data(nullptr), sz(0), cap(0) {}
        ~DynamicArray() { delete[] data; }

        void push_back(int val) {
            if (sz == cap) resize();
            data[sz++] = val;
        }

        void pop_back() {
            if (sz == 0) throw underflow_error("Mang rong!");
            sz--;
        }

        int& at(int i) {
            if (i < 0 || i >= sz)
                throw out_of_range("Chi so ngoai pham vi!");
            return data[i];
        }

        int size() const { return sz; }
        int capacity() const { return cap; }

        void print() const {
            cout << "[ ";
            for (int i = 0; i < sz; i++)
                cout << data[i] << (i + 1 < sz ? ", " : "");
            cout << " ]  size=" << sz << "  cap=" << cap << "\n";
        }
    };

    void run() {
        DynamicArray v;
        cout << "\n--- [BAI 3] DEMO DYNAMIC ARRAY (INT) ---\n";

        for (int i = 1; i <= 6; i++) {
            v.push_back(i * 10);
            cout << "push_back(" << i * 10 << ")  -> ";
            v.print();
        }

        cout << "\npop_back()         -> ";
        v.pop_back();
        v.print();

        cout << "\nat(2) = " << v.at(2) << "\n";

        v.at(2) = 999;
        cout << "at(2) = 999        -> ";
        v.print();

        try {
            v.at(100);
        }
        catch (const out_of_range& e) {
            cout << "\nNgoai le bat duoc: " << e.what() << "\n";
        }
    }
}

// ==========================================
// BÀI 4: QUẢN LÝ ĐIỂM SINH VIÊN (MẢNG ĐỘNG STRUCT)
// ==========================================
struct Student {
    string name;
    string mssv;
    float  score;
};

class StudentList {
    Student* data;
    int sz, cap;
    void grow() {
        cap = (cap == 0) ? 2 : cap * 2;
        Student* tmp = new Student[cap];
        for (int i = 0; i < sz; i++) tmp[i] = data[i];
        delete[] data; data = tmp;
    }
public:
    StudentList() : data(nullptr), sz(0), cap(0) {}
    ~StudentList() { delete[] data; }
    void push(const Student& s) { if (sz == cap) grow(); data[sz++] = s; }
    int  size() const { return sz; }
    Student& at(int i) { return data[i]; }
    void remove(int i) {
        for (int j = i; j < sz - 1; j++) data[j] = data[j + 1];
        sz--;
    }
};

void printHeader() {
    cout << left
        << setw(5) << "STT"
        << setw(15) << "MSSV"
        << setw(25) << "Ho Ten"
        << setw(8) << "Diem"
        << "Xep loai\n";
    cout << string(60, '-') << "\n";
}

string xepLoai(float s) {
    if (s >= 9.0) return "Xuat sac";
    if (s >= 8.0) return "Gioi";
    if (s >= 7.0) return "Kha";
    if (s >= 5.0) return "Trung binh";
    return "Yeu";
}

void printStudent(int stt, const Student& s) {
    cout << left
        << setw(5) << stt
        << setw(15) << s.mssv
        << setw(25) << s.name
        << setw(8) << fixed << setprecision(1) << s.score
        << xepLoai(s.score) << "\n";
}

void themSinhVien(StudentList& lst) {
    Student s;
    cout << "MSSV    : "; cin.ignore(); getline(cin, s.mssv);
    cout << "Ho ten  : "; getline(cin, s.name);
    do {
        cout << "Diem (0-10): "; cin >> s.score;
    } while (s.score < 0 || s.score > 10);
    lst.push(s);
    cout << "=> Da them " << s.name << "!\n";
}

void xoaSinhVien(StudentList& lst) {
    string ms;
    cout << "Nhap MSSV can xoa: "; cin.ignore(); getline(cin, ms);
    for (int i = 0; i < lst.size(); i++) {
        if (lst.at(i).mssv == ms) {
            cout << "=> Da xoa: " << lst.at(i).name << "\n";
            lst.remove(i); return;
        }
    }
    cout << "=> Khong tim thay MSSV!\n";
}

void suaSinhVien(StudentList& lst) {
    string ms;
    cout << "Nhap MSSV can sua: "; cin.ignore(); getline(cin, ms);
    for (int i = 0; i < lst.size(); i++) {
        if (lst.at(i).mssv == ms) {
            cout << "Ten moi (Enter giu nguyen): ";
            string tmp; getline(cin, tmp);
            if (!tmp.empty()) lst.at(i).name = tmp;
            float sc;
            cout << "Diem moi (nhap -1 giu nguyen): "; cin >> sc;
            if (sc >= 0) lst.at(i).score = sc;
            cout << "=> Da cap nhat!\n"; return;
        }
    }
    cout << "=> Khong tim thay MSSV!\n";
}

void timKiem(StudentList& lst) {
    string kw;
    cout << "Nhap ten hoac MSSV: "; cin.ignore(); getline(cin, kw);
    bool found = false;
    printHeader();
    for (int i = 0; i < lst.size(); i++) {
        Student& s = lst.at(i);
        if (s.name.find(kw) != string::npos || s.mssv.find(kw) != string::npos) {
            printStudent(i + 1, s); found = true;
        }
    }
    if (!found) cout << "Khong tim thay ket qua.\n";
}

void sapXep(StudentList& lst) {
    for (int i = 0; i < lst.size() - 1; i++)
        for (int j = 0; j < lst.size() - 1 - i; j++)
            if (lst.at(j).score < lst.at(j + 1).score)
                swap(lst.at(j), lst.at(j + 1));
    cout << "\n=== BANG XEP HANG LOP ===\n";
    printHeader();
    for (int i = 0; i < lst.size(); i++)
        printStudent(i + 1, lst.at(i));
}

void thongKe(StudentList& lst) {
    if (lst.size() == 0) { cout << "Danh sach trong!\n"; return; }
    float mn = lst.at(0).score, mx = lst.at(0).score, sum = 0;
    string mnName = lst.at(0).name, mxName = lst.at(0).name;
    for (int i = 0; i < lst.size(); i++) {
        float sc = lst.at(i).score;
        sum += sc;
        if (sc < mn) { mn = sc; mnName = lst.at(i).name; }
        if (sc > mx) { mx = sc; mxName = lst.at(i).name; }
    }
    cout << fixed << setprecision(2);
    cout << "\n=== THONG KE ===\n";
    cout << "Si so       : " << lst.size() << " sinh vien\n";
    cout << "Diem cao nhat: " << mx << " (" << mxName << ")\n";
    cout << "Diem thap nhat: " << mn << " (" << mnName << ")\n";
    cout << "Trung binh  : " << sum / lst.size() << "\n";
}

void xuatFile(StudentList& lst) {
    for (int i = 0; i < lst.size() - 1; i++)
        for (int j = 0; j < lst.size() - 1 - i; j++)
            if (lst.at(j).score < lst.at(j + 1).score)
                swap(lst.at(j), lst.at(j + 1));

    ofstream f("diem_sinhvien.txt");
    f << "=== BANG DIEM SINH VIEN ===\n\n";
    f << left << setw(5) << "STT" << setw(15) << "MSSV"
        << setw(25) << "Ho Ten" << setw(8) << "Diem" << "Xep loai\n";
    f << string(60, '-') << "\n";
    for (int i = 0; i < lst.size(); i++) {
        Student& s = lst.at(i);
        f << left << setw(5) << i + 1 << setw(15) << s.mssv
            << setw(25) << s.name << setw(8)
            << fixed << setprecision(1) << s.score
            << xepLoai(s.score) << "\n";
    }
    f << "\n" << string(60, '-') << "\n";
    f << "Tong so: " << lst.size() << " sinh vien\n";
    f.close();
    cout << "=> Da xuat ra file diem_sinhvien.txt!\n";
}

void hienThiTat(StudentList& lst) {
    if (lst.size() == 0) { cout << "Danh sach trong!\n"; return; }
    printHeader();
    for (int i = 0; i < lst.size(); i++)
        printStudent(i + 1, lst.at(i));
}

void chayBai4(StudentList& lst) {
    int choice;
    do {
        cout << "\n=== [BAI 4] MENU QUAN LY DIEM SINH VIEN ===\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Sua sinh vien\n";
        cout << "4. Hien thi danh sach\n";
        cout << "5. Tim kiem\n";
        cout << "6. Xep hang lop\n";
        cout << "7. Thong ke\n";
        cout << "8. Xuat bao cao ra file\n";
        cout << "0. Quay lai Menu Chinh\n";
        cout << "Chon chuc nang (0-8): ";
        cin >> choice;

        switch (choice) {
        case 1: themSinhVien(lst);  break;
        case 2: xoaSinhVien(lst);   break;
        case 3: suaSinhVien(lst);   break;
        case 4: hienThiTat(lst);    break;
        case 5: timKiem(lst);       break;
        case 6: sapXep(lst);        break;
        case 7: thongKe(lst);       break;
        case 8: xuatFile(lst);      break;
        case 0: cout << "Quay lai menu tong...\n"; break;
        default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

// ==========================================
// HÀM MAIN TỔNG (MENU ĐIỀU HƯỚNG CHÍNH)
// ==========================================
int main() {
    StudentList bai4List; // Khởi tạo danh sách sinh viên cho bài 4 (giữ data xuyên suốt chương trình)
    int mainChoice;

    do {
        cout << "\n============================================\n";
        cout << "        MENU CHUONG TRINH TONG HOP          \n";
        cout << "============================================\n";
        cout << "1. Chay Bai 1 (Min, Max, Tong, TB mang 1D)\n";
        cout << "2. Chay Bai 2 (Nhan ma tran & Tinh dinh thuc)\n";
        cout << "3. Chay Bai 3 (Demo DynamicArray - Vector tu che)\n";
        cout << "4. Chay Bai 4 (Quan ly diem Sinh Vien)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "--------------------------------------------\n";
        cout << "Nhap lua chon cua ban (0-4): ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            Bai1::run();
            break;
        case 2:
            Bai2::run();
            break;
        case 3:
            Bai3::run();
            break;
        case 4:
            chayBai4(bai4List);
            break;
        case 0:
            cout << "\nCam on ban da su dung chuong trinh. Tam biet!\n";
            break;
        default:
            cout << "\nLua chon khong hop le! Vui long nhap lai.\n";
        }
        
        // Tạo khoảng nghỉ nhỏ trước khi quay lại menu chính
        if (mainChoice != 0) {
            cout << "\nNhấn Enter để tiếp tục...";
            cin.ignore();
            cin.get();
        }

    } while (mainChoice != 0);

    return 0;
}