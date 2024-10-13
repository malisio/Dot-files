def hex_xor(hex1, hex2):
    min_length = min(len(hex1), len(hex2))
    bytes1 = bytes.fromhex(hex1[:min_length])
    bytes2 = bytes.fromhex(hex2[:min_length])
    xor_result = ''.join(f"{b1 ^ b2:02x}" for b1, b2 in zip(bytes1, bytes2))
    return xor_result


known_plaintext = b"Our counter agencies have intercepted your messages and a lot of your agent's identities have been exposed. In a matter of days all of them will be captured"
known_hex = known_plaintext.hex()


encrypted_message = "7aa34395a258f5893e3db1822139b8c1f04cfab9d757b9b9cca57e1df33d093f07c7f06e06bb6293676f9060a838ea138b6bc9f20b08afeb73120506e2ce7b9b9dcd9e4a421584cfaba2481132dfbdf4216e98e3facec9ba199ca3a97641e9ca9782868d0222a1d7c0d3119b867edaf2e72e2a6f7d344df39a14edc39cb6f960944ddac2aaef324827c36cba67dcb76b22119b43881a3f1262752990"
encrypted_message_part = encrypted_message[:len(known_hex)]


keystream = hex_xor(known_hex, encrypted_message_part)
print("Keystream:", keystream)


encrypted_flag = "7d8273ceb459e4d4386df4e32e1aecc1aa7aaafda50cb982f6c62623cf6b29693d86b15457aa76ac7e2eef6cf814ae3a8d39c7"
decrypted_flag_hex = hex_xor(keystream, encrypted_flag)

try:
    
    decrypted_flag = bytes.fromhex(decrypted_flag_hex).decode('utf-8')
    print("Decrypted Flag:", decrypted_flag)
except Exception as e:
    print("Error decoding the flag:", str(e))
    print("Decrypted Flag Hex:", decrypted_flag_hex)
