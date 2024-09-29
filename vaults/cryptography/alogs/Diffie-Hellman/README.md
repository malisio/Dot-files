## Why?
 Key exchanging is a critical thing when it comes to cryptography. We need to protect data including our key but how can we exchange keys without someone being in the middle and sniffing our traffic? There are plenty and different algorithms  we can use but for this one we well use the famous Diffie-Hellman algo.

 ## What is DH-Key exchange ?
 From Wikipedia DH(Diffie-Hellman) key exchange is a mathematical method of securely exchanging cryptography keys over a public channel.
## How?
- First thing both parties agrees publicly on two Numbers.
- Second thing Both parties chooses a secret key and it won't need to be exchanged.
- Each of the client and the server well do some calculations (look down for more information) to get a public  key that they both exchange  once more.
- This is where the magic happens after some calculations (look down for more information) You both get a similar key.
## The Math part (Eww)
- Let go once more into the  algorithm.
1) First thing Both of the parties agrees on two numbers a Base G and a prime P.
2) Each of those parties (client/server) well chose a secret key
3) Both of those parties they well create a public key that they well exchange following this format: `Public_key = G ^Private_number % P`
- To generate the Public key you are going to take the base number `G` and then raise it to the power of the Private number and take the reminder when divided by `P`
- Both side well go into the same Process resulting into those keys that they well both exchange.
4) After the exchange and receiving the public key you almost go into the same process as the 3rd step.
- The formula is something like this:
   `Shared_Key = (Client_Public_key)^ Private_number % P`
  `Shared_Key = (Server_Public_key)^ Private_number % P`
  5) And here the fucking magic happens both of those Shared_keys are the same xD.
  
 # Example
  1) Public information G=5 && P=23
  2) Private Number a = 5 && b = 6
  3) Create Public keys 
  - Server key = `5^5 % 23 = 20`  
  - Clients key = `5^14 %23 = 8`
  - x = 20 ; y = 8
  4) Generating Private key 
  - `8 ^ 5 % 23` = 16
  - `20 ^ 6 % 23` = 16 
  ```c
  #include <std io.h>

int main(){

  int val = 32768;
  int mod = val % 23;

  printf("%d\n",mod);

  val = 64000000;
  mod = val % 23;
  printf("%d\n",mod);

  return 0;
}

```