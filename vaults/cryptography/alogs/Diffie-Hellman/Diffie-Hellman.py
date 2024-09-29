import math 
import random 

def luck(G,a,P):
    if a == 1:
        return G
    else:
        return pow(G,a)%P

def main():
    #Both Persons aggress upon two numbers

    P = 396
    G = 5
    #Private Numbers 
    a = random.randint(1000,1000000)
    b = random.randint(1000,1000000)
    x = luck(G,a,P)
    print("Value of Public Key 1:",x)
    y = luck(G,b,P)
    print("Value of Public Key 1:",y)
    
    P1 = luck(y,a,P)
    P2 = luck(x,b,P)

    print("Value of Private key 1:",P1)
    print("Value of Privte Key 2:",P2)


if __name__ == "__main__":
    main()
