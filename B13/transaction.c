#include "vending.h"

int kiemTraMenhGia(int tien) {
    int menhGiaHopLe[] = {1000, 2000, 5000, 10000, 20000, 50000, 100000};
    int soMenhGia = sizeof(menhGiaHopLe) / sizeof(menhGiaHopLe[0]);

    for (int i = 0; i < soMenhGia; i++) {
        if (tien == menhGiaHopLe[i]) {
            return 1; // Hop le
        }
    }
    return 0; // Khong dung menh gia cho phep
}

int thoiTienCoGioiHan(int tienThua, QuanLyTienThoi khoTien[]) {
    // Neu khong can thoi tien
    if (tienThua == 0) {
        return 1;
    }

    // Tao ban sao kiem tra gia lap kho tien le
    int banSaoSoLuong[7];
    for (int i = 0; i < 7; i++) {
        banSaoSoLuong[i] = khoTien[i].soLuongTo;
    }

    int tienConLai = tienThua;
    int soToThoi[7] = {0}; // Luu so loung tung loai to se thoi cho khach

    // Thuat toan tham lam: Duyet tu menh gia cao xuong menh gia thap
    for (int i = 0; i < 7; i++) {
        if (tienConLai >= khoTien[i].menhGia && banSaoSoLuong[i] > 0) {
            int soToCan = tienConLai / khoTien[i].menhGia;
            int soToLay = (soToCan < banSaoSoLuong[i]) ? soToCan : banSaoSoLuong[i];

            soToThoi[i] = soToLay;
            tienConLai -= soToLay * khoTien[i].menhGia;
            banSaoSoLuong[i] -= soToLay;
        }
    }

    // Neu sau khi duyet het menh gia ma van thieu tien le -> May khong du tien thoi
    if (tienConLai > 0) {
        printf("\nLOI: May khong du tien le de thoi lai cho ban!\n");
        return 0; // That bai
    }

    // Neu du tien thoi -> Tien hanh tru kho that va in danh sach to tien thoi
    printf("\nThoi lai cho quy khach: %d VND, bao gom:\n", tienThua);
    for (int i = 0; i < 7; i++) {
        if (soToThoi[i] > 0) {
            printf("- %d to %d VND\n", soToThoi[i], khoTien[i].menhGia);
            khoTien[i].soLuongTo -= soToThoi[i]; // Tru so loung to trong kho that
        }
    }

    return 1; // Thoi tien thanh cong
}


int apDungMaGiamGia(int giaGoc) {
    char ma[20];
    printf("Nhap ma giam gia (neu khong co nhap '0'): ");
    
    // Doc ma giam gia tu ban phim
    if (scanf("%19s", ma) != 1) {
        return giaGoc;
    }

    // Truong hop khong nhap ma
    if (strcmp(ma, "0") == 0) {
        return giaGoc;
    }

    // Xu ly cac ma giam gia
    if (strcmp(ma, "GIAM10K") == 0) {
        printf("-> Ap dung ma thanh cong! Giam 10.000 VND.\n");
        int giaMoi = giaGoc - 10000;
        return (giaMoi > 0) ? giaMoi : 0;
    } 
    else if (strcmp(ma, "GIAM20%") == 0) {
        printf("-> Ap dung ma thanh cong! Giam 20%%.\n");
        int giaMoi = giaGoc - (giaGoc * 20 / 100);
        int giaLamTron = (giaMoi + 999) / 1000 * 1000;   // lam tron len hang nghin
        if (giaLamTron != giaMoi) {
        printf("-> Gia sau giam %d VND, lam tron len %d VND.\n", giaMoi, giaLamTron);
    }
    return giaLamTron;
} 
    else {
        printf("-> Ma giam gia khong hop le hoac da het han!\n");
        return giaGoc; // Giu nguyen gia goc neu ma sai
    }
}