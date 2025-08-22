import struct

def float_to_ieee754_hex(value):
    # Pack float (32-bit) theo Big-endian (‘>f’)
    packed = struct.pack('>f', value)
    # Chuyển bytes sang dạng hex, rồi viết hoa
    return "0x" + packed.hex().upper()

# Thử với 3892.5625
val = 39887.5625
hex_result = float_to_ieee754_hex(val)
print("Số:", val)
print("=> IEEE 754 32-bit dạng hex:", hex_result)
