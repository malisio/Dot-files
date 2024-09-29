
## What is RSA?
- RSA (**Rivest–Shamir–Adleman**) is a public-key cryptosystem  and one of the most oldest and widely used for secure data transmission.First published at 1977 by  Ron Rivest  Adi Shamir and Leonard Adleman.
- Public key cryptography, also known as asymmetric cryptography, uses two different keys, one public and one private. The private key can be shared with anyone, but the private needs to be kept a secret. 
- In RSA, both of the keys can encrypt a message. The opposite key from the one used to encrypt a message is used to decrypt it. This the only reason why RSA has become widely used. It checks all the list for the **CIA** triad  (confidentiality, integrity, authenticity).
## Generating Keys

- Before diving into the math I well assume you have basic understanding of the following things: Factors,Prime Numbers,Semi-Prime number, Modulo, If you lack in any of those topic trying googling and understanding it and then come back and follow with us.
To get started we need to chose Two prime numbers let name them P && Q, For the sake of simplicity we'll use small numbers.
- Let take P = 7 && Q = 19
- N is their product (P* Q) = 133 
- This is kinda tricky since you well need to understand what is a Totient but as I said before for the sake of simplicity I wont dive too deep feel free to google stuff.  You can read more about it [here](https://en.wikipedia.org/wiki/Euler%27s_totient_function) 
- To get the Totient of  a semi prime number is the following formula `(P-1) * (Q-1)`  = 108 
- The public key needs to math the following 3 conditions:
1) Must be a prime number
2) Must be less than Totient 
3) Must not be a factor of the Totient  
- Let take 5 as our public key E=5
- Selecting a private key needs to fufill one condition let name it D 
1) The product  of D and E modulo   T must result in in a reminder of 1
Let put this in a formula to understand it more 
`D * E % T ==1 `
- In our case we well take D = 41
## Encryption &&  Decryption

The encryption and Decryption follow a simple formula.
Encryption: 
`Message ^ E % N = Cipher text`
Decryption: 
`Cipher Text ^ D % N = Message`
- Example Let take the numbers from the above section as an example
Let take A as our cipher text converting it to ASCII well give us the value of 65, following the above formula it well result in: 
`Cipher text = 60 ^ 5 % 133 = 86`
`Message = 86 ^ 41 % 5 = 60 `
We can switch keys encrypt with private key and with decrypt it with public keys
`Cipher text = 60 ^ 41 % 133 = 72`
`Message = 72 ^ 29 % 5 = 60 `

