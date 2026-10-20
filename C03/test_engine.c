#include "quiz.h"
/*
- Ham 4: chonCauHoiNgauNhien
- Nguoi thuc hien: Thanh Hau
- File phu trach: test_engine.c
- Mo ta: Chon ngau nhien n cau hoi tu ngan hang cau hoi sao cho khong cau nao trung nhau (dung thuat toan xao tron Fisher-Yates va rand()).
- Dau vao: dsGoc[]: Mang cau hoi goc, nGoc: Tong so cau goc, dsChon[]: Mang luu cau da chon, nChon: So cau can chon
- Dau ra: Khong (void)
*/
void chonCauHoiNgauNhien(CauHoi dsGoc[], int nGoc, CauHoi dsChon[], int nChon) {
    if (nChon > nGoc) {
        nChon = nGoc;
    }

    int *p = (int*)malloc(nGoc * sizeof(int));
    if (p == NULL) return;

    for (int i = 0; i < nGoc; i++) {
        p[i] = i;
    }

    // Thuat toan xao tron Fisher-Yates
    for (int i = nGoc - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }

    for (int i = 0; i < nChon; i++) {
        dsChon[i] = dsGoc[p[i]];
    }

    free(p);
}

/*
- Ham 5: daoThuTuPhuongAn
- Nguoi thuc hien: Thanh Hau
- File phu trach: test_engine.c
- Mo ta: (Mo rong) dao ngau nhien vi tri 4 phuong an A, B, C, D cua tung cau hoi va cap nhat lai dap an dung tuong ung.
- Dau vao: *ch: Con tro tro toi cau hoi can dao
- Dau ra: Khong (void)
*/
void daoThuTuPhuongAn(CauHoi *ch) {
    // Luu vi tri chi so dap an dung hien tai (0: 'A', 1: 'B', 2: 'C', 3: 'D')
    int viTriDung = ch->dapanDung - 'A';

    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            // Hoan doi noi dung 2 phuong an i va j
            char temp[100];
            strcpy(temp, ch->phuongAn[i]);
            strcpy(ch->phuongAn[i], ch->phuongAn[j]);
            strcpy(ch->phuongAn[j], temp);

            // Cap nhat lai vi tri dap an dung neu bi thay doi
            if (viTriDung == i) {
                viTriDung = j;
            } else if (viTriDung == j) {
                viTriDung = i;
            }
        }
    }

    // Gán lại ký tự đáp án đúng mới sau khi đảo ('A', 'B', 'C', hoặc 'D')
    ch->dapanDung = (char)('A' + viTriDung);
}

/*
- Ham 6: lamBaiThiCoThoiGian
- Nguoi thuc hien: Anh Vy
- File phu trach: test_engine.c
- Mo ta: Hien thi tung cau, nhan dap an A/B/C/D hoac bo qua (nhap 'N'). Tinh diem thang 10, in cau sai kem dap an dung. Gioi han thoi gian lam bai (Mo rong).
- Dau vao: ds[]: Mang cau hoi duoc chon, n: So luong cau thi, hoTen: Ten thi sinh
- Dau ra: Diem so dat duoc (float)
*/
float lamBaiThiCoThoiGian(CauHoi ds[], int n, const char *hoTen) {
    if (n <= 0) return 0.0f;

    int soCauDung = 0;
    char traLoi[n];
    int thoiGianGioiHan = n * 60; // Mo rong: Quy dinh 60 giay cho moi cau hoi
    time_t batDau = time(NULL);

    printf("\n================ BAT DAU BAI THI ================\n");
    printf("Thi sinh: %s\n", hoTen);
    printf("So cau hoi: %d cau | Thoi gian lam bai: %d giay\n", n, thoiGianGioiHan);
    printf("(Nhap A/B/C/D de chon, hoac 'N' de bo qua cau hoi)\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        // Kiem tra het gio làm bai
        time_t hienTai = time(NULL);
        if (difftime(hienTai, batDau) > thoiGianGioiHan) {
            printf("\n>> HET THOI GIAN LAM BAI! He thong tu dong nop bai.\n");
            for (int k = i; k < n; k++) {
                traLoi[k] = 'N'; // Cac cau chua lam coi nhu bo qua
            }
            break;
        }

        printf("\nCau %d/%d: %s\n", i + 1, n, ds[i].noiDung);
        printf("  A. %s\n", ds[i].phuongAn[0]);
        printf("  B. %s\n", ds[i].phuongAn[1]);
        printf("  C. %s\n", ds[i].phuongAn[2]);
        printf("  D. %s\n", ds[i].phuongAn[3]);

                char chon = 'N';
        char buf[50];
        while (1) {
            printf("Dap an cua ban: ");
            if (fgets(buf, sizeof(buf), stdin) == NULL) {   // het du lieu nhap -> coi nhu bo qua
                chon = 'N';
                break;
            }
            buf[strcspn(buf, "\r\n")] = 0;
            if (strlen(buf) == 1) {                          // chi chap nhan dung 1 ky tu
                chon = buf[0];
                if (chon >= 'a' && chon <= 'z') chon -= 32;
                if ((chon >= 'A' && chon <= 'D') || chon == 'N') break;
            }
            printf("Khong hop le! Vui long chi chon A, B, C, D hoac N.\n");
        }

        traLoi[i] = chon;
        if (traLoi[i] == ds[i].dapanDung) {
            soCauDung++;
        }
    }

    // Tinh diem tren thang diem 10
    float diem = ((float)soCauDung / n) * 10.0f;

    printf("\n================ KET QUA BAI THI ================\n");
    printf("Thi sinh: %s\n", hoTen);
    printf("So cau tra loi dung: %d/%d\n", soCauDung, n);
    printf("Diem so: %.1f / 10.0\n", diem);

    // Hien thi danh sach cac cau lam sai kem dap an dung
    if (soCauDung < n) {
        printf("\n--- CHI TIET CAC CAU LAM SAI / BO QUA ---\n");
        for (int i = 0; i < n; i++) {
            if (traLoi[i] != ds[i].dapanDung) {
                printf("Cau %d: %s\n", i + 1, ds[i].noiDung);
                printf("   -> Ban chon: %c | Dap an dung: %c\n", 
                       (traLoi[i] == 'N') ? '-' : traLoi[i], ds[i].dapanDung);
            }
        }
    }

    return diem;
}