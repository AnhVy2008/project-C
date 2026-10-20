# C03 (★★) – Thi trắc nghiệm

Chương trình console viết bằng **C**, có menu. Ngân hàng câu hỏi lưu trong file văn bản; chương trình đọc file, chọn đề ngẫu nhiên, cho thí sinh làm bài, chấm điểm thang 10 và lưu lịch sử kết quả.

## 1. Chức năng

| STT | Chức năng | Mô tả |
|---|---|---|
| 1 | Đọc ngân hàng câu hỏi | Đọc `cauhoi.txt`; báo lỗi nếu file không tồn tại hoặc sai định dạng |
| 2 | Chọn đề ngẫu nhiên | Chọn n câu **không trùng nhau** (xáo trộn Fisher-Yates với `rand()`) |
| 3 | Làm bài | Hiển thị từng câu, nhập A/B/C/D, nhập `N` để bỏ qua |
| 4 | Chấm điểm | Điểm = (số câu đúng / số câu thi) × 10; in câu sai/bỏ qua kèm đáp án đúng |
| 5 | Lịch sử | Lưu (họ tên, điểm, thời điểm) vào `lich_su.txt`; xem bảng điểm bằng menu |
| ★ | Đảo thứ tự phương án | Mỗi lần thi, 4 phương án của từng câu được xáo trộn, đáp án đúng cập nhật theo |
| ★ | Giới hạn thời gian | 60 giây cho mỗi câu (tổng = số câu × 60 giây); hết giờ tự động nộp bài, câu chưa làm tính là bỏ qua |

`★: Chức năng mở rộng`
## 2. Cấu trúc thư mục

```
C03/
├── quiz.h          # struct CauHoi, LichSuThi, và nguyên mẫu hàm
├── main.c          # Menu chính, kết nối các chức năng
├── file_utils.c    # Đọc ngân hàng câu hỏi, lưu và xem lịch sử
├── test_engine.c   # Chọn đề, đảo phương án, làm bài và chấm điểm
├── cauhoi.txt      # Ngân hàng câu hỏi (30 câu)
├── lich_su.txt     # Lịch sử thi (tự tạo khi có người thi)
├── Makefile
└── README_C03.md
```

| File | Hàm | Vai trò |
|---|---|---|
| `file_utils.c` | `docNganHangCauHoi` | Đọc file vào mảng; trả về số câu, hoặc -1 nếu lỗi |
| | `luuLichSuKetQua` | Ghi 1 dòng kết quả vào `lich_su.txt` |
| | `xemBangDiemLichSu` | Đọc và in bảng điểm tất cả lượt thi |
| `test_engine.c` | `chonCauHoiNgauNhien` | Chọn n câu không trùng |
| | `daoThuTuPhuongAn` | (Mở rộng) Đảo vị trí A/B/C/D |
| | `lamBaiThiCoThoiGian` | Làm bài, chấm điểm, in câu sai; trả về điểm |
| `main.c` | `main` | Khởi tạo `srand`, đọc ngân hàng, hiển thị menu |

## 3. Định dạng file dữ liệu

**`cauhoi.txt`** – mỗi câu gồm 6 dòng liên tiếp (cho phép có dòng trống giữa các câu):

```
Noi dung cau hoi
Phuong an A
Phuong an B
Phuong an C
Phuong an D
C                <- dap an dung: A, B, C hoac D (chi 1 ky tu)
```

- Tối đa **100 câu**; nội dung câu hỏi tối đa 255 ký tự, mỗi phương án tối đa 99 ký tự.
- Thiếu dòng, đáp án khác A–D, file rỗng hoặc không tồn tại → báo lỗi và không cho bắt đầu thi.

**`lich_su.txt`** – mỗi dòng một lượt thi: `Ho ten|Diem|dd/mm/yyyy hh:mm:ss`

## 4. Biên dịch và chạy

```bash
gcc -Wall main.c file_utils.c test_engine.c -o quiz
./quiz            # Linux / macOS
quiz.exe          # Windows
```

Hoặc dùng `make` (tạo file `quiz_app`). Với **Code::Blocks / Dev-C++**: tạo Console Project (C), thêm 3 file `.c` và `quiz.h`, nhấn Build & Run.

> `cauhoi.txt` phải nằm cùng thư mục với chương trình khi chạy. Nên viết câu hỏi không dấu để console Windows không lỗi font.

## 5. Hướng dẫn sử dụng

```
1. Bat dau lam bai thi
2. Xem bang diem & lich su thi
0. Thoat
```

1. **Làm bài (1):** nhập họ tên → nhập số câu muốn thi (từ 1 đến tổng số câu trong ngân hàng) → trả lời từng câu (`A`/`B`/`C`/`D`, hoặc `N` để bỏ qua) → xem điểm và các câu sai → kết quả tự lưu vào lịch sử.
2. **Xem lịch sử (2):** hiển thị STT, họ tên, điểm, thời điểm của mọi lượt thi.
3. **Thoát (0).**

Ví dụ: làm 10 câu, đúng 7 → **7,0 điểm**; câu sai được in kèm đáp án đúng.

**Kiểm tra dữ liệu nhập:** nhập chữ thay số, số âm, số ngoài phạm vi (menu, số câu), đáp án ngoài A/B/C/D/N, họ tên để trống đều bị báo lỗi và yêu cầu nhập lại; chương trình không bị treo.

## 6. Kiểm thử

Gồm 15 test case (bình thường, biên, sai) – xem bảng test case trong báo cáo.

## 7. Thành viên

| Họ tên | MSSV | 
|---|---|
| Bùi Anh Vy | 26161176 |
| Nguyễn Khánh Linh | 26161116 |
| Trần Nguyễn Quỳnh Trâm | 26161160 |
| Võ Thị Ngọc Mai | 26161122 |
| Trần Thị Kim Anh | 26161056 |
| Đỗ Đặng Trường Hải | 26161079 |
| Võ Thanh Hậu | 26161084 |
| Đặng Hữu Mạnh | 26161123 |
