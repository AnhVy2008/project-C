# B13 (★★) – Máy bán hàng tự động

Chương trình console viết bằng **C**, có menu. Máy bán nước có danh sách sản phẩm (tên, giá, số lượng); người dùng chọn hàng, nạp tiền bằng các mệnh giá cho phép (1.000, 2.000, 5.000, 10.000, 20.000, 50.000, 100.000 đ), máy thối tiền với số tờ ít nhất, cập nhật tồn kho và có chế độ quản trị bằng mật khẩu.

## 1. Chức năng

| STT | Chức năng | Mô tả |
|---|---|---|
| 1 | Hiển thị sản phẩm còn hàng | Chỉ in những sản phẩm có số lượng > 0; nếu hết sạch thì báo hết hàng |
| 2 | Chọn sản phẩm, nạp tiền | Nạp tiền nhiều lần cho đến khi đủ giá; chỉ nhận đúng các mệnh giá cho phép |
| 3 | Thối tiền | Thối với số tờ ít nhất (thuật toán tham lam) |
| 4 | Cập nhật tồn kho | Trừ kho sau mỗi giao dịch thành công; báo khi sản phẩm vừa hết hàng |
| 5 | Chế độ quản trị | Nhập mật khẩu; nhập thêm hàng, xem tổng doanh thu |
| ★ | Kho tiền lẻ giới hạn | Máy chỉ có số tờ tiền lẻ nhất định; không đủ tiền thối thì báo lỗi, hủy giao dịch và trả lại tiền đã nạp |
| ★ | Mã giảm giá | Mã `GIAM10K` (giảm 10.000 đ) và `GIAM20%` (giảm 20%, làm tròn **lên** hàng nghìn để không phát sinh tiền thối lẻ) |

`★: Chức năng mở rộng`

## 2. Cấu trúc thư mục

```
B13/
├── vending.h          # struct SanPham, QuanLyTienThoi và nguyên mẫu hàm
├── main.c             # Khởi tạo dữ liệu, menu chính, kết nối các chức năng
├── products.c         # Hiển thị sản phẩm, cập nhật tồn kho
├── transaction.c      # Kiểm tra mệnh giá, thối tiền, mã giảm giá
├── admin.c            # Đăng nhập admin, nhập thêm hàng, xem doanh thu
├── testcase_B13.docx  # Bảng 15 test case
├── Makefile
└── README_B13.md
```

| File | Hàm | Vai trò |
|---|---|---|
| `products.c` | `hienThiSanPham` | In các sản phẩm còn hàng (số lượng > 0); hết sạch thì báo "Het hang" |
| | `capNhatKho` | Trừ tồn kho sau giao dịch; nếu kho về 0 thì báo sản phẩm vừa hết hàng |
| `transaction.c` | `kiemTraMenhGia` | Trả về 1 nếu tiền nạp đúng mệnh giá cho phép, 0 nếu sai |
| | `thoiTienCoGioiHan` | (Mở rộng) Thối tiền tham lam từ tờ lớn xuống tờ nhỏ, có kiểm tra kho tiền lẻ; trả về 1 nếu thối được, 0 nếu máy không đủ tiền thối |
| | `apDungMaGiamGia` | (Mở rộng) Nhập mã giảm giá, trả về giá cần thanh toán sau khi giảm |
| `admin.c` | `dangNhapAdmin` | Yêu cầu mật khẩu quản trị; trả về 1 nếu đúng, 0 nếu sai |
| | `nhapThemHang` | Admin chọn một sản phẩm và cộng thêm số lượng vào kho |
| | `xemDoanhThu` | In tổng doanh thu từ các giao dịch thành công |
| `main.c` | `main` | Khởi tạo mảng sản phẩm, kho tiền lẻ; hiển thị menu (switch-case) và gọi các hàm trên |

## 3. Dữ liệu ban đầu và cấu hình

Dữ liệu được khởi tạo trực tiếp trong `main()`, không đọc từ file.

**Sản phẩm:**

| STT | Tên | Giá (đ) | Số lượng |
|---|---|---|---|
| 1 | Coca Cola | 15.000 | 5 |
| 2 | Sting | 12.000 | 2 |
| 3 | Nuoc suoi | 8.000 | 10 |

**Kho tiền lẻ của máy:**

| Mệnh giá (đ) | 100.000 | 50.000 | 20.000 | 10.000 | 5.000 | 2.000 | 1.000 |
|---|---|---|---|---|---|---|---|
| Số tờ | 2 | 5 | 10 | 10 | 10 | 10 | 10 |

- **Mệnh giá được nhận:** 1.000, 2.000, 5.000, 10.000, 20.000, 50.000, 100.000 đ. Mệnh giá khác (ví dụ 3.000), chữ, số âm hoặc số 0 đều bị từ chối.
- **Mã giảm giá:** `GIAM10K` (giảm 10.000 đ, giá không xuống dưới 0), `GIAM20%` (giảm 20%, làm tròn lên hàng nghìn). Nhập `0` nếu không dùng mã; mã không đúng thì giữ nguyên giá gốc.
- **Mật khẩu quản trị:** `123456`.
- Mỗi lần mua được **1 sản phẩm**.

## 4. Biên dịch và chạy

```bash
gcc -Wall main.c admin.c products.c transaction.c -o vending
./vending         # Linux / macOS
.\vending.exe     # Windows (PowerShell)
```

Hoặc dùng `make` (tạo file `vending_app`). Với **Code::Blocks / Dev-C++**: tạo Console Project (C), thêm 4 file `.c` và `vending.h`, nhấn Build & Run. Với **VS Code**: mở terminal tại thư mục `B13` và chạy lệnh `gcc` ở trên.

## 5. Hướng dẫn sử dụng

```
1. Xem danh sach san pham
2. Mua hang, nap tien va Ma giam gia
3. Che do quan tri (Nhap hang, Xem doanh thu)
0. Thoat chuong trinh
```

1. **Xem sản phẩm (1):** hiển thị số thứ tự, tên, giá, số lượng của các sản phẩm còn hàng.
2. **Mua hàng (2):** chọn số thứ tự sản phẩm → nhập mã giảm giá (hoặc `0`) → nạp tiền từng lần cho đến khi đủ → máy thối tiền (nếu có) → cập nhật tồn kho và doanh thu. Nếu máy không đủ tiền thối, giao dịch bị hủy, tiền đã nạp được trả lại, kho và doanh thu không đổi.
3. **Quản trị (3):** nhập mật khẩu → chọn `1` để nhập thêm hàng (chọn sản phẩm, nhập số lượng > 0) hoặc `2` để xem tổng doanh thu.
4. **Thoát (0).**

Ví dụ: giá 15.000, khách đưa 50.000 → thối 35.000 = 20.000 + 10.000 + 5.000 (3 tờ).

**Kiểm tra dữ liệu nhập:** nhập chữ thay số, số âm, số ngoài phạm vi (menu, số thứ tự sản phẩm, số lượng nhập hàng), mệnh giá không cho phép đều bị báo lỗi và chương trình không bị treo. Cụ thể: nhập sai ở menu thì báo lỗi và hiển thị lại menu; nhập sai mệnh giá thì báo lỗi và hỏi lại; chọn sản phẩm không tồn tại hoặc đã hết hàng thì báo lỗi và quay về menu; nhập sai mật khẩu thì báo lỗi và quay về menu.

## 6. Kiểm thử

Gồm 15 test case (bình thường, biên, sai) – xem file `testcase_B13.docx` và bảng test case trong báo cáo.

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
