# Setting FS Register Test Codes

### What for?

For windows, the Address of TEB is stored in FS register.
The Address is not the exact value, because the FS register's value has special format.
If you not follow this, segfault occurs.
For further information, search LDT.

This codes are setting FS register value to meaning less value.
In Linux, typically FS register is not used, so this code do not affect to any other works. (except windows compatible things, like Wine projects.)


### How to use

Just compile it with pthread.
```(ex) g++ pthread_fs.cc -lpthread```

Also, static builded binary for 32bit x86 arch is on the repo.


### Bugs on Linux Hyper-V Instance.

Refer my linux [bugzilla report](https://bugzilla.kernel.org/show_bug.cgi?id=203937)
