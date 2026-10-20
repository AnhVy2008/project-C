//nguoi thuc hien : Anh Vy
#include "quiz.h"
int main() {
    // Khoi tao hat giong ngau nhien
    srand((unsigned int)time(NULL));

    CauHoi nganHang[100];
    CauHoi deThi[100];
    int tongSoCauGoc = 0;
    int soCauThi = 0; // So luong cau hoi chon cho de thi
    int luaChon;
    char hoTen[50];

    // Doc du lieu tu file ngan hang cau hoi khi khoi dong
    tongSoCauGoc = docNganHangCauHoi("cauhoi.txt", nganHang);

    do {
        printf("\n================ CHUONG TRINH THI TRAC NGHIEM ================\n");
        printf("1. Bat dau lam bai thi\n");
        printf("2. Xem bang diem & lich su thi\n");
        printf("0. Thoat\n");
        printf("Moi ban chon chuc nang: ");
        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n'); // Xoa bo nho dem neu nhap chu
            printf("Loi: Vui long nhap so (0-2)!\n");
            luaChon = -1;
            continue;
        }
        while (getchar() != '\n'); // Doc bo ky tu du thua

        switch (luaChon) {
            case 1: {
                if (tongSoCauGoc <= 0) {
                    printf("Loi: Ngan hang cau hoi rong hoac khong doc duoc file 'cauhoi.txt'!\n");
                    break;
                }

                                do {
                    printf("\nNhap ho va ten thi sinh: ");
                    fgets(hoTen, sizeof(hoTen), stdin);
                    hoTen[strcspn(hoTen, "\r\n")] = 0; // Loai bỏ ky tu xuong dong
                    if (hoTen[0] == 0) printf("Loi: Ho ten khong duoc de trong!\n");
                } while (hoTen[0] == 0);
                for (int i = 0; hoTen[i] != 0; i++)       // doi '|' thanh khoang trang
                    if (hoTen[i] == '|') hoTen[i] = ' ';

                // 1. Chon ngau nhien n cau hoi khong trung
                 // Nhap so cau muon thi, co kiem tra
                do {
                    printf("Nhap so cau muon thi (1-%d): ", tongSoCauGoc);
                    int kq = scanf("%d", &soCauThi);
                    while (getchar() != '\n');          // xoa bo nho dem (ke ca khi nhap chu)
                    if (kq != 1 || soCauThi < 1 || soCauThi > tongSoCauGoc) {
                        printf("Loi: Vui long nhap so nguyen tu 1 den %d!\n", tongSoCauGoc);
                        soCauThi = 0;
                    }
                } while (soCauThi == 0);

                int nChon = soCauThi;
                chonCauHoiNgauNhien(nganHang, tongSoCauGoc, deThi, nChon);

                // 2. Mo rong: Dao thu tu cac phuong an tung cau
                for (int i = 0; i < nChon; i++) {
                    daoThuTuPhuongAn(&deThi[i]);
                }

                // 3. Cho lam bai thi, tinh diem va hien thi ket qua
                float diem = lamBaiThiCoThoiGian(deThi, nChon, hoTen);

                // 4. Lay thoi gian hien tai va ghi lich su vao file
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                char thoiDiem[30];
                sprintf(thoiDiem, "%02d/%02d/%04d %02d:%02d:%02d", 
                        tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
                        tm.tm_hour, tm.tm_min, tm.tm_sec);

                luuLichSuKetQua(hoTen, diem, thoiDiem);
                printf("\nDa luu ket qua thi vao file lich su thanh cong!\n");
                break;
            }
            case 2:
                xemBangDiemLichSu();
                break;
            case 0:
                printf("Cam on ban da su dung chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (luaChon != 0);

    return 0;
}

