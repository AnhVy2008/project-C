#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==========================================
// 1. CAU TRUC DU LIEU CHUNG (STRUCT)
// ==========================================

// Cau truc luu thong tin cua mot cau hoi trac nghiem
typedef struct {
    char noiDung[256];     // Noi dung cau hoi
    char phuongAn[4][100]; // 4 phuong an A, B, C, D
    char dapanDung;        // Dap an dung ('A', 'B', 'C', hoặc 'D')
} CauHoi;

// Cau truc luu lich su lam bai cua thi sinh
typedef struct {
    char hoTen[50];        // Ho ten thi sinh
    float diem;            // Diem so thang 10
    char thoiDiem[30];     // Thoi diem hoan thanh bai thi
} LichSuThi;


// ==========================================
// 2. KHAI BAO NGUYEN MAU HAM (CAU TRUC NHOM)
// ==========================================

// 1. Doc ngan hang cau hoi tu file van ban
int docNganHangCauHoi(const char *tenFile, CauHoi ds[]);

// 2. Luu ket qua thi vao file lich su
void luuLichSuKetQua(const char *hoTen, float diem, const char *thoiDiem);

// 3. Doc va hien thi bang diem lich su thi
void xemBangDiemLichSu();


// 4. Chon ngau nhien n cau hoi khong trung nhau (rand)
void chonCauHoiNgauNhien(CauHoi dsGoc[], int nGoc, CauHoi dsChon[], int nChon);
// 5. Mo rong: dao ngau nhien thu tu 4 phoung an A, B, C, D
void daoThuTuPhuongAn(CauHoi *ch);

// 6. Mo rong: Cho lam bai thi, tinh diem thang 10, hien thi cau sai + gioi han thoi gian
float lamBaiThiCoThoiGian(CauHoi ds[], int n, const char *hoTen);

#endif // QUIZ_H

