.PHONY: c03 b13 clean

# Biên dịch riêng C03
c03:
	$(MAKE) -C C03

# Biên dịch riêng B13
b13:
	$(MAKE) -C B13

# Dọn dẹp file rác
clean:
	$(MAKE) -C C03 clean
	$(MAKE) -C B13 clean