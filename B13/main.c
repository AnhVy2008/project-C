#include "vending.h"

int main() {
    SanPham ds[3] = {
        {"Coca Cola", 15000, 5},
        {"Sting", 12000, 2},
        {"Nuoc suoi", 8000, 10}
    };
    int n = 3;
    int tongDoanhThu = 0;

    // Khoi tao kho tien le san co trong may (Mo rong 1)
    QuanLyTienThoi khoTien[7] = {
        {100000, 2}, {50000, 5}, {20000, 10}, 
        {10000, 10}, {5000, 10}, {2000, 10}, {1000, 10}
    };

    int luaChon;
    do {
        printf("\n================ MAY BAN HANG TU DONG ================\n");
        printf("1. Xem danh sach san pham\n");
        printf("2. Mua hang, nap tien va Ma giam gia\n");
        printf("3. Che do quan tri (Nhap hang, Xem doanh thu)\n");
        printf("0. Thoat chuong trinh\n");
        printf("Moi ban nhan so de chon: ");
        if (scanf("%d", &luaChon) != 1) {
        while (getchar() != '\n');
        luaChon = -1;                  // roi vao default: "Lua chon khong hop le!"
        }

        switch (luaChon) {
            case 1:
                hienThiSanPham(ds, n);
                break;
            case 2: {
                hienThiSanPham(ds, n);
                int chonSP;
                printf("Chon san pham muon mua: ");
                if (scanf("%d", &chonSP) != 1) {
                while (getchar() != '\n');
                chonSP = 0;                    // chonSP-- thanh -1 -> "San pham khong ton tai..."
                }
                chonSP--;

                if (chonSP >= 0 && chonSP < n && ds[chonSP].soLuong > 0) {
                    int giaGoc = ds[chonSP].gia;
                    printf("Gia goc: %d VND\n", giaGoc);

                    // Ap dung ma giam gia (Mo rong 2)
                    int giaThucTe = apDungMaGiamGia(giaGoc);
                    printf("So tien can thanh toan sau khi giam: %d VND\n", giaThucTe);

                    int soToNap[7] = {0}; int tongTienNap = 0;
                    while (tongTienNap < giaThucTe) {
                        int tien;
                        printf("Nap tien (menh gia 1k-100k): ");
                        if (scanf("%d", &tien) != 1) {
                        while (getchar() != '\n');
                        tien = 0;                      // kiemTraMenhGia(0) = 0 -> "Menh gia khong hop le!" roi hoi lai
                        }
                        if (kiemTraMenhGia(tien)) {
                            tongTienNap += tien; for (int j = 0; j < 7; j++) { if (khoTien[j].menhGia == tien) { soToNap[j]++; break; }}
                            printf("Da nap: %d VND (Tong nap: %d VND)\n", tien, tongTienNap);
                        } else {
                            printf("Menh gia khong hop le!\n");
                        }
                    }

                    int tienThua = tongTienNap - giaThucTe;
                    if (tienThua > 0) {
                        // Kiem tra xem may co du tien thoi khong
                        if (!thoiTienCoGioiHan(tienThua, khoTien)) {
                            // Neu khong du tien thoi, huy giao dich va trả lai tien khach da nap
                            printf("Huy giao dich do khong du tien thoi. Tra lai ban: %d VND\n", tongTienNap);
                            break;
                        }
                    }
                    for (int j = 0; j < 7; j++) { khoTien[j].soLuongTo += soToNap[j];}
                    // Cap nhat kho va doanh thu
                    capNhatKho(&ds[chonSP], 1);
                    tongDoanhThu += giaThucTe;
                    printf("Giao dich thanh cong! Cam on ban.\n");
                } else {
                    printf("San pham khong ton tai hoac da het hang!\n");
                }
                break;
            }
            case 3:
                if (dangNhapAdmin()) {
                    int subOpt;
                    printf("1. Nhap them hang\n2. Xem doanh thu\nChon: ");
                    scanf("%d", &subOpt);
                    if (subOpt == 1) {
                        nhapThemHang(ds, n);
                    } else if (subOpt == 2) {
                        xemDoanhThu(tongDoanhThu);
                    }
                }
                break;
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);

    return 0;
}

