## ASCII

ASCII is a 7-bit encoding standard which allows the representation of text using the integers 0-127.
### Challenge
Using the below integer array, convert the numbers to their corresponding ASCII characters to obtain a flag.  
```python
array=[99, 114, 121, 112, 116, 111, 123, 65, 83, 67, 73, 73, 95, 112, 114, 49, 110, 116, 52, 98, 108, 51, 125]
```
- We can use the chr() function to reverse an int value to an char according to the ASCII table,and ord() to do the opposite.
```python
array = [99, 114, 121, 112, 116, 111, 123, 65, 83, 67, 73, 73, 95, 112, 114, 49, 110, 116, 52, 98, 108, 51, 125]

for x in array:
    print(chr(x),end="")
```
## Hex

When we encrypt something the resulting cipher text commonly has bytes which are not printable ASCII characters. If we want to share our encrypted data, it's common to encode it into something more user-friendly and portable across different systems.  
  
Hexadecimal can be used in such a way to represent ASCII strings. First each letter is converted to an ordinal number according to the ASCII table (as in the previous challenge). Then the decimal numbers are converted to base-16 numbers, otherwise known as hexadecimal. The numbers can be combined together, into one long hex string.
### Challenge

Included below is a flag encoded as a hex string. Decode this back into bytes to get the flag.
```python
val=63727970746f7b596f755f77696c6c5f62655f776f726b696e675f776974685f6865785f737472696e67735f615f6c6f747d
```
- In Python, the `bytes.fromhex()` function can be used to convert hex to bytes. The `.hex()` instance method can be called on byte strings to get the hex representation.
- Also `bytes.fromhex()` takes a string as an argument.
```python
#!/usr/bin/python3

val ="63727970746f7b596f755f77696c6c5f62655f776f726b696e675f776974685f6865785f737472696e67735f615f6c6f747d"

print(bytes.fromhex(val))
```
## Base64

Another common encoding scheme is Base64, which allows us to represent binary data as an ASCII string using an alphabet of 64 characters. One character of a Base64 string encodes 6 binary digits (bits), and so 4 characters of Base64 encode three 8-bit bytes.
### Challenge
Take the below hex string, _decode_ it into bytes and then _encode_ it into Base64.  
  
```python
val = "72bca9b68fc16ac7beeb8f849dca1d8a783e8acf9679bf9269f7bf"
```
- We can use the library `base64` to encode/decode base64  `base64.b64encode()` to encode.

```python
#!/usr/bin/python3
import bas64

val= "72bca9b68fc16ac7beeb8f849dca1d8a783e8acf9679bf9269f7bf"
new_val = bytes.fromhex(val)
print(base64.b64encode(new_val))
```

## Bytes and long integers

The most common way is to take the ordinal bytes of the message, convert them into hexadecimal, and concatenate. This can be interpreted as a base-16/hexadecimal number, and also represented in base-10/decimal.
  
### Challenge
  
Convert the following integer back into a message:  
`11515195063862318899931685488813747395775516287289682636499965282714637259206269`
- Luckily for us there is an already written lib that does the work for us  `Crypto.Util.number`  and it have the following functions `bytes_to_long()` and `long_to_bytes()`

```python
#!/usr/bin/python3
from Crypto.Util.number import *

long=11515195063862318899931685488813747395775516287289682636499965282714637259206269 
print(long_to_bytes(long))

```
## XOR 

XOR is a bit wise operator that return 0 if the two bits are the same other wise it well return 1
- Example: 

| A   | B   | Output |
| --- | --- | ------ |
| 0   | 0   | 0      |
| 0   | 1   | 1      |
| 1   | 0   | 1      |
| 1   | 1   | 0      |
### Challenge
- Given the string `label`, XOR each character with the integer `13`. Convert these integers back to a string and submit the flag as `crypto{new_string}`.
```python
from pwn import *

ciphertext="label"
for i in ciphertext:
    print(chr(ord(i)^13),end="")
```
## Xor proprieties 
Note from the question: 

Commutative: A ⊕ B = B ⊕ A  
Associative: A ⊕ (B ⊕ C) = (A ⊕ B) ⊕ C  
Identity: A ⊕ 0 = A  
Self-Inverse: A ⊕ A = 0
- Commutative: This fucking means it doesn't matter which order we use the xor operations.
- Associative : This means that it doesn't matter how you place brackets as long as you have the input set up.
- Identity: Using xor operations on 0 well always result in the same number.
- Self-Inverse: Xoring the same number well result in 0. 
### Challenge
Let's put this into practice! Below is a series of outputs where three random keys have been XOR'd together and with the flag. Use the above properties to undo the encryption in the final line to obtain the flag.  
  ```python 
KEY1 = a6c8b6733c9b22de7bc0253266a3867df55acde8635e19c73313  
KEY2 ^ KEY1 = 37dcb292030faa90d07eec17e3b1c6d8daf94c35d4c9191a5e1e  
KEY2 ^ KEY3 = c1545756687e7573db23aa1c3452a098b71a7fbf0fddddde5fc1  
FLAG ^ KEY1 ^ KEY3 ^ KEY2 = 04ee9855208a2cd59091d04767ae47963170d1660df7f56f5faf
```
- Solve 
