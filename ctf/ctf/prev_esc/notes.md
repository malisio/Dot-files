## Things to look at 
- Env variable `env`
- Open ports  `ss -tulpn`
- Getting passwords or creds

```bash
grep --color=auto -rnw '/' -ie "PASSWORD=" --color=always 2>/dev/null
#Play around with the greped keyword
```
