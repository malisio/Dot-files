#  sys-admin

- Data bases
- Protocols (http,ftp,smb,e-mail...)
- RDP
- Firewalls 
- Use the target OS  as your daily driver, with CLI && GUI


## languages
- [x]  Learn c 
- [ ] learn cpp
- [ ] Assembly
- [ ] Haskell
## IT skills 

- [ ] Networking stuff
- [ ] Active Directory 
- [ ] Blue teaming side



## Road for AD

- Learn windows basics (command line,file system,etc...) 15 days 
- Windows exploitation (priv esc,etc...) 10 days 
- Active dir fundemateles 1month 
- Exploiting active directory 3 months 
- Practice (Tryhackme networks) 15 days 
- Pro hacker Rank on hack the box  4-5 months 
- VulnLab 1 month practice 
- CPTS path 2 months 
- CPTS Exam (if I'm not broke)

## Idea for box

- 3 services running on port (ssh,apache2,mysql_db)
- Discover that web have a local file inclusion (with a specific payload (hex injection)) to then access  backup directory to find back up files, which contains db password.
- Log-in to data base 1 of those creds are valid. (seadris:S34Dr1stgoat_1)
- Priv esc to Guts,by a missconfiguration like in athena. 
- Reverse a binary that runs as sudo (Using anti-debugging techniques), and exploit a function that gives root

## configuring the box
- [x] Create all the users and passwords
- [x] Learn how to manage Databases
- [ ] Play athena again
- [ ] Learn PHP
- [x] Learn how to manage files for perms 
- [ ] Work on the main page (blog) html css etc...
- [ ] Learn how to bypass the anti reversing technique.

## Progress
```sql
CREATE TABLE information(ID int NOT NULL, username varchar(16), password varchar(8),PRIMARY KEY(ID));
```

```sql

```