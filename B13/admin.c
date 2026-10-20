#include "vending.h"
/*
- Nguoi thuc hien: Ngoc Mai
- File phu trach: admin.c
- Ham 6: dangNhapAdmin
- Mo ta: Yeu cau nhap mat khau quan tri (vi du: 123456).
- Dau vao: Khong co
- Dau: 1 neu mat khau dung, 0 neu nhap sai
*/
int dangNhapAdmin() {
    char matKhau[50];
    
    printf("\n=== CHE DO QUAN TRI (ADMIN) ===\n");
    printf("Nhap mat khau quan tri: ");
    if (scanf("%49s", matKhau) != 1) {
        return 0;
    }
    
    if (strcmp(matKhau, "123456") == 0) {
        printf("-> Dang nhap thanh cong!\n");
        return 1;
    } else {
        printf("-> Sai mat khau quan tri!\n");
        return 0;
    }
}

/*
- Ham 7: nhapThemHang
- Mo ta: Cho phep Admin chon mot san pham va cong them so luong nhap kho.
- Dau vao: ds[]: Mang san pham, n: So luong loai san pham
- Dau ra: Khong co (void)
*/
void nhapThemHang(SanPham ds[], int n) {
    int luaChon;
    int soLuongThem;

    printf("\n===== NHAP THEM HANG VAO KHO =====\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d. %s - Gia: %d VND - So luong hien tai: %d\n", 
               i + 1, ds[i].ten, ds[i].gia, ds[i].soLuong);
    }

    printf("Chon san pham can nhap them (1-%d): ", n);
    if (scanf("%d", &luaChon) != 1 || luaChon < 1 || luaChon > n) {
        printf("-> Lua chon san pham khong hop le!\n");
        return;
    }

    printf("Nhap so luong muon them cho '%s': ", ds[luaChon - 1].ten);
    if (scanf("%d", &soLuongThem) != 1 || soLuongThem <= 0) {
        printf("-> So luong nhap them phai la so nguyen duong (> 0)!\n");
        return;
    }

    ds[luaChon - 1].soLuong += soLuongThem;
    printf("-> Nhap hang thanh cong!\n");
    printf("   San pham: %s | So luong moi trong kho: %d\n", 
           ds[luaChon - 1].ten, ds[luaChon - 1].soLuong);
}

/*
- Ham 8: xemDoanhThu
- Mo ta: In ra tong doanh thu thu duoc tu cac giao dich mua ban thanh cong.
- Dau vao: doanhThu: Bien tich luy tong tien
- Dau ra: Khong co (void)
*/
void xemDoanhThu(int doanhThu) {
    printf("\n================ BAO CAO DOANH THU ================\n");
    printf("Tong doanh thu hien tai cua may: %d VND\n", doanhThu);
    printf("===================================================\n");
}