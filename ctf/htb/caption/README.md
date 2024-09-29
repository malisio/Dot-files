## Enumeration
- Nmap scan 
3 open Ports 
80,8080,22:
Both of port 80 && 8080 are running a web server 
- Directory fuzzing

```sh
        /'___\  /'___\           /'___\       
       /\ \__/ /\ \__/  __  __  /\ \__/       
       \ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\      
        \ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/      
         \ \_\   \ \_\  \ \____/  \ \_\       
          \/_/    \/_/   \/___/    \/_/       

       v2.1.0-dev
________________________________________________

 :: Method           : GET
 :: URL              : http://caption.htb/FUZZ
 :: Wordlist         : FUZZ: /home/malisio/git/ffuf/list.txt
 :: Follow redirects : false
 :: Calibration      : false
 :: Timeout          : 10
 :: Threads          : 40
 :: Matcher          : Response status: 200-299,301,302,307,401,403,405,500
________________________________________________

                        [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 146ms]
#                       [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 238ms]
download                [Status: 403, Size: 94, Words: 6, Lines: 5, Duration: 331ms]
# Copyright 2007 James Fisher [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 372ms]
# on at least 2 different hosts [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 460ms]
#                       [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 520ms]
# Priority ordered case-sensitive list, where entries were found [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 587ms]
# directory-list-2.3-medium.txt [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 693ms]
# Attribution-Share Alike 3.0 License. To view a copy of this [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 700ms]
# license, visit http://creativecommons.org/licenses/by-sa/3.0/ [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 919ms]
# or send a letter to Creative Commons, 171 Second Street, [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 919ms]
home                    [Status: 302, Size: 189, Words: 18, Lines: 6, Duration: 1213ms]
# This work is licensed under the Creative Commons [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 1365ms]
# Suite 300, San Francisco, California, 94105, USA. [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 1409ms]
#                       [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 1435ms]
#                       [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 1504ms]
Download                [Status: 403, Size: 94, Words: 6, Lines: 5, Duration: 96ms]
logout                  [Status: 302, Size: 189, Words: 18, Lines: 6, Duration: 212ms]
firewalls               [Status: 302, Size: 189, Words: 18, Lines: 6, Duration: 103ms]
logs                    [Status: 403, Size: 94, Words: 6, Lines: 5, Duration: 98ms]
DOWNLOAD                [Status: 403, Size: 94, Words: 6, Lines: 5, Duration: 152ms]
firewalls-faq           [Status: 302, Size: 189, Words: 18, Lines: 6, Duration: 183ms]
                        [Status: 200, Size: 4412, Words: 503, Lines: 208, Duration: 543ms]
```

## Attack vectors
Port 80 have a login that needs to be bypassed
  Ideas for this bypass:
- SQL injection somehow 
- Miss with the returned parameter `http://caption.htb/?err=login_err`
  Nothing of the above worked let take a look at port 8080

Port 8080 have an exposed git repository, with default creds root:root
navigating to http://caption.htb:8080/admin/dbviewer we get access to a H2 databases we can gain rce 
