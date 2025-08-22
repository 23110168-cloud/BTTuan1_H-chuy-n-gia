import numpy as np

def custom8_to_value(binary_str):
    # Đảm bảo chuỗi có đủ 8 ký tự
    b = binary_str.zfill(8)
    sign_bit = int(b[0])
    exponent = int(b[1:4], 2)
    mantissa = 1.0
    for i, bit in enumerate(b[4:]):
        mantissa += int(bit) * (2 ** -(i+1))
    return ((-1) ** sign_bit) * mantissa * (2 ** (exponent - 3))

def value_to_half_precision_hex(value):
    f16 = np.float16(value)
    # Lấy bit pattern từ np.float16
    half_bits = np.frombuffer(f16.tobytes(), dtype=np.uint16)[0]
    return "0x" + format(half_bits, "04X")

# Chuyển đổi từ input "82" (hex) sang 8-bit binary
hex_input = "8F"
binary_input = bin(int(hex_input, 16))[2:].zfill(8)  # "10000010"

val = custom8_to_value(binary_input)
half_hex = value_to_half_precision_hex(val)

print("8-bit input (hex):", "0x" + hex_input.upper())
print("8-bit binary:", binary_input)
print("Giá trị thực:", val)
print("IEEE 754 16-bit (hex):", half_hex)
