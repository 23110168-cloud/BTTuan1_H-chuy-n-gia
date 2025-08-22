def hex_to_binary_8bit(hex_str):
    return bin(int(hex_str, 16))[2:].zfill(8)

def decode_8bit_fp(hex_str):
    binary = hex_to_binary_8bit(hex_str)
    sign_bit = int(binary[0])
    exponent_bits = binary[1:4]
    mantissa_bits = binary[4:]

    exponent = int(exponent_bits, 2)
    bias = 3
    exponent_value = exponent - bias

    # Normalized mantissa: 1.xxx
    mantissa = 1.0
    for i, bit in enumerate(mantissa_bits):
        mantissa += int(bit) * (2 ** -(i + 1))

    # Final value:
    value = ((-1) ** sign_bit) * mantissa * (2 ** exponent_value)
    
    return {
        "binary": binary,
        "sign": sign_bit,
        "exponent_bits": exponent_bits,
        "exponent_value": exponent_value,
        "mantissa_bits": mantissa_bits,
        "mantissa_value": mantissa,
        "final_value": value
    }

# Ví dụ: nhập hex 57
hex_input = "67"
result = decode_8bit_fp(hex_input)

print("Hex:", hex_input)
print("Binary:", result["binary"])
print("Sign:", result["sign"])
print("Exponent (bits):", result["exponent_bits"], "->", result["exponent_value"])
print("Mantissa (bits):", result["mantissa_bits"], "->", result["mantissa_value"])
print("=> Decimal value:", result["final_value"])
