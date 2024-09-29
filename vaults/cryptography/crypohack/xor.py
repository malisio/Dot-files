from pwn import *


ciphertext="label"
for i in ciphertext:
    print(chr(ord(i)^13),end="")
