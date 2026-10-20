#include "quiz.h"

/**
 * Ham 1: docNganHangCauHoi
 * Nguoi thuc hien: Quynh Tram
 * Mo ta: Doc du lieu tu file van ban chua ngan hang cau hoi vao mang struct CauHoi.
 * Dau vao: tenFile (Ten file nguon), ds[] (Mang luu cau hoi)
 * Dau ra: So luong cau hoi doc duoc (int) hoac -1 neu loi mo file.
 */
int docNganHangCauHoi(const char *tenFile, CauHoi ds[]) {
    FILE *f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Loi: Khong the mo file %s hoac file khong ton tai!\n", tenFile);
        return -1;
    }
    
        int soLuong = 0;
    // MAX_CAU dinh nghia trong quiz.h, tranh tran mang
    while (soLuong < 100 &&
           fgets(ds[soLuong].noiDung, sizeof(ds[soLuong].noiDung), f) != NULL) {
        ds[soLuong].noiDung[strcspn(ds[soLuong].noiDung, "\r\n")] = 0;
        if (ds[soLuong].noiDung[0] == 0) continue;   // bo qua dong trong giua cac cau

        // Doc 4 phuong an A, B, C, D
        for (int i = 0; i < 4; i++) {
            if (fgets(ds[soLuong].phuongAn[i], sizeof(ds[soLuong].phuongAn[i]), f) == NULL) {
                printf("Loi dinh dang: cau %d thieu phuong an!\n", soLuong + 1);
                fclose(f);
                return -1;
            }
            ds[soLuong].phuongAn[i][strcspn(ds[soLuong].phuongAn[i], "\r\n")] = 0;
        }

        // Doc dap an dung, phai la A/B/C/D
        char buff[10];
        if (fgets(buff, sizeof(buff), f) == NULL) {
            printf("Loi dinh dang: cau %d thieu dap an dung!\n", soLuong + 1);
            fclose(f);
            return -1;
        }
        if (buff[0] >= 'a' && buff[0] <= 'd') buff[0] -= 32;
        if (buff[0] < 'A' || buff[0] > 'D' || (buff[1] != '\n' && buff[1] != '\r' && buff[1] != 0)) {
            printf("Loi dinh dang: dap an cau %d phai la A, B, C hoac D!\n", soLuong + 1);
            fclose(f);
            return -1;
        }
        ds[soLuong].dapanDung = buff[0];

        soLuong++;
    }

    fclose(f);
    return soLuong;
}

/**
 * Ham 2: luuLichSuKetQua
 * Nguoi thuc hien: Quynh Tram
 * Mo ta: Luu ket qua thi cua thi sinh (Ho ten, diem so, thoi diem) vao file lich su van ban.
 * Dau vao: hoTen (Ten thi sinh), diem (Diem so), thoiDiem (Thoi gian lam bai)
 * Dau ra: Khong (void)
 */
void luuLichSuKetQua(const char *hoTen, float diem, const char *thoiDiem) {
    // Mo file "lich_su.txt" o che do "a" (append) de ghi tiep du lieu moi vao cuoi file
    FILE *f = fopen("lich_su.txt", "a");
    if (f == NULL) {
        printf("Loi: Khong the mo file de ghi lich su ket qua!\n");
        return;
    }

    // Ghi du lieu thi sinh vao file theo dinh dang chuan
    fprintf(f, "%s|%.2f|%s\n", hoTen, diem, thoiDiem);

    fclose(f);
    printf("Da luu ket qua thi cua thi sinh %s thanh cong.\n", hoTen);
}
/*
- Ham 3: xemBangDiemLichSu
- Nguoi thuc hien: Huu Manh
- File phu trach: file_utils.c
- Mo ta: Doc va hien thi danh sach lich su thi cung bang diem cua tat ca thi sinh tu file lich su (lich_su.txt).
- Dau vao: Khong co
- Dau ra: Khong (void)
*/
void xemBangDiemLichSu() {
    FILE *f = fopen("lich_su.txt", "r");
    if (f == NULL) {
        printf("\nChua co lich su thi.\n");
        return;
    }

    char dong[200];
    LichSuThi kq; // Da doi sang struct LichSuThi trong quiz.h
    int stt = 0;

    printf("\n===== BANG DIEM LICH SU THI =====\n");
    printf("%-4s %-25s %-6s %s\n", "STT", "Ho ten", "Diem", "Thoi gian");

    while (fgets(dong, sizeof(dong), f) != NULL) {
        // Doc du lieu tuong ung voi struct LichSuThi (kq.hoTen, kq.diem, kq.thoiDiem)
        if (sscanf(dong, "%49[^|]| %f | %29[^\r\n]", kq.hoTen, &kq.diem, kq.thoiDiem) == 3) {
            // Xoa khoang trang thua o cuoi ho ten
            int len = strlen(kq.hoTen);
            while (len > 0 && kq.hoTen[len - 1] == ' ') {
                kq.hoTen[--len] = 0;
            }
            stt++;
            printf("%-4d %-25s %-6.2f %s\n", stt, kq.hoTen, kq.diem, kq.thoiDiem);
        }
    }
    fclose(f);

    if (stt == 0) printf("(Chua co ket qua nao)\n");
}