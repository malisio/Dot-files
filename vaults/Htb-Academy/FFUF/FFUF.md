## What is fuzzing
Fuzzing is sending multiple different type of data to target and analyze it behavior For example:
- Fuzzing a binary with long strings to see where the buffer over flow occurs 
- Fuzzing a web application with a pre-defined word list then analyze the HTTP respond if it is 200 then it is found 404 not found xD.
## Directory fuzzing 
- Simple as it sound fuzzing for directories in web. 
Using ffuf 
```bash 
ffuf -w /path/to/wordlist:FUZZ -w http://example.com/FUZZ
```
## Extension Fuzzing
As it sounds we're going to fuzz for web extensions assuming we have found a page but need to identify it extension.
Example using ffuf
```bash 
ffuf -w /path/to/wordlist:FUZZ -w http://exmaple.come/pageFUZZ
```
Make sure that the word list contains a dot other wise specifie it.
## Page fuzzing 
Same as above we want to search for a page with a certain parameter we can also do it using ffuf 

```sh
ffuf -w /path/to/wordlist:FUZZ -w http://example.com/FUZZ.php
```
