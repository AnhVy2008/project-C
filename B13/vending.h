#ifndef VENDING_H
#define VENDING_H

#include <stdio.h>
#include <string.h>

// Dinh nghia struct san pham
typedef struct {
    char ten[50];
    int gia;
    int soLuong;
} SanPham;

// Cau truc quan ly so luong to tien le co trong may (Mo rong)
typedef struct {
    int menhGia;
    int soLuongTo;
} QuanLyTienThoi;

// Khai bao cac nguyen mau ham
void hienThiSanPham(SanPham ds[], int n);
void capNhatKho(SanPham *sp, int soLuongMua);

int kiemTraMenhGia(int tien);

// Ham mo rong: Thoi tien co gioi han kho tien le va kiem tra ma giam gia
int thoiTienCoGioiHan(int tienThua, QuanLyTienThoi khoTien[]);
int apDungMaGiamGia(int giaGoc);

int dangNhapAdmin(void);
void nhapThemHang(SanPham ds[], int n);
void xemDoanhThu(int doanhThu); // Bo sung xem doanh thu

#endif

