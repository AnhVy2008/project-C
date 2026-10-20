#include <stdio.h>
#include "vending.h"

/**
 * Nguoi thuc hien: Thanh Hau
 * File phu trach: products.c
 * Ham 1: hienThiSanPham
 * 
 * Mo ta:  Hien thi danh sach tat ca cac san pham con hang trong may ban hang.
 * Dau vao: ds[] (Mang san pham), n (So luong loai san pham)
 * Dau ra: Khong (void)
 */
void hienThiSanPham(SanPham ds[], int n) {
    int i, k = 0;
    printf("\n=== DANH SACH SAN PHAM CON HANG ===\n");
    for (i = 0; i < n; i++) {
        if (ds[i].soLuong > 0) {
            printf("%d\n Ten san pham: %s\n Gia: %d\n So luong san pham: %d\n-------------------\n", i+1, ds[i].ten, ds[i].gia, ds[i].soLuong);
            k = 1;
        }
    }
    if (k == 0) {
        printf("Het hang.\n");
    }
}

/**
 * Ham 2: capNhatKho
 * 
 * Mo ta: Tru so luong ton kho sau khi giao dich thanh cong. 
 *        Neu kho ve 0, in thong bao san pham vua het hang.
 * Dau vao: *sp (Con tro tro toi san pham mua), soLuongMua (So luong mua)
 * Dau ra: Khong (void)
 */
void capNhatKho(SanPham *sp, int soLuongMua) {
    if (sp->soLuong >= soLuongMua) {
        sp->soLuong -= soLuongMua;
        printf("Giao dich thanh cong!\nSan pham con lai: %d\n", sp->soLuong);
        if (sp->soLuong == 0) {
            printf("San pham %s vua het hang!\n", sp->ten);
        }
    } else {
        printf("So luong san pham %s con lai: %d\nGiao dich khong thanh cong!\n", sp->ten, sp->soLuong);
    }
}