

## **Challenge Description**
Malicious actors have infiltrated our systems and we believe they've implanted a custom rootkit. Can you disarm the rootkit and find the hidden data?

First let decompile the rootkit source code using a decompiler.
But before that let take a look at the functions names, and the file name seems a bit interesting it a well known lkm (loadable kernel module) rootkit, name [diamorphine](https://github.com/m0nad/Diamorphine/)

![[func_names.png]]
Interesting those names are very similar to the ones in the diamorphine rootkit.
The main bread and butter is the `hacked_kill` function it controls the work flow for the rootkit   Let decompile it 
![[hacked_kill.png]]
Sending a 46 signal to the kernel will unhide  the module let try it out.
![[remove_lkm.png]]
and like that we made the module appear again we can remove it however we will need to have privileges and the rootkit grants that for us  by sending a `64` signal to the kernel 

![[get_root.png]]
and let get our flag!
![[flag.png]]

[[rootkit]]
[[Reversing]]
[[linux]]
