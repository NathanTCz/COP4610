xv6 and QEMU Installation
=========================

xv6 installation was a smooth easy process on Arch Linux. the `qemu-system` package had to be installed but that was just a simple `pacman -S qemu-system`. Once the source for xv6 was download and untar'd, I just needed to change the path for the qemu binary in the Makefile to match my system. After that, a simple `make qemu` built and ran the qemu virtual machine software and the xv6 image file without problems as you can see here.

![Image](http://stuphapp.com/xv6.png)




The close() System Call
=======================

In xv6, the `close()` system call begins in when called from whatever arbitrary user program uses it. From the user space it enters the kernel space.

user.h
------

The original declaration of the `close()` system call is in this file. The function prototype here, defines the return type and the paramters of the `close()` system call.

`int close(int);`


syscall.c
---------

The decalrations for all of the system calls is located in this file. The close system call is defined as such:

`extern int sys_close(void);`

This is followed by a declaration of function pointers:

```
static int (*syscalls[])(void) = {
... [SYS_close]  sys_close,
};
```

The function `syscall(void)` runs the following code:

`num = proc->tf->eax;`<br>
`if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {`<br>
`  proc->tf->eax = syscalls[num]();`<br>
`} else {`<br>
`  cprintf("%d %s: unknown sys call %d\n",`<br>
`          proc->pid, proc->name, num);`<br>
`  proc->tf->eax = -1;`<br>
`}`<br>

In this function `num` is set to `proc->tf->eax` which is trapframe (or corresponding system call pointer/number) of that process. The function then pushes the registers onto the stack (ie. the arguments of the system call).

sysfile.c
---------

sysfile.c contains the actual definition of `sys_close()`, the function pointer assigned to the `close()` system call. The function looks like:

`int fd;`<br>
`struct file *f;`<br>
<br>
`if(argfd(0, &fd, &f) < 0)`<br>
`  return -1;`<br>
`proc->ofile[fd] = 0;`<br>
`fileclose(f);`<br>
`return 0;`<br>

In this function the arguments sent with the system call are retrieved from the stack
```
if(argfd(0, &fd, &f) < 0)
  return -1
```
setting the file descriptor `fd` and the file `f`.

`proc->ofile[fd] = 0;`

sets the open files of that process. Then the function `fileclose()` closes the file associated with that file descriptor.