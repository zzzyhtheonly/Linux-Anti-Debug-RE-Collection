# Linux Anti-debug tech collection
Still working on it, any idea helps

## About
This is a collection of anti-debug techniques samples for Linux. It offers unversal-known user-mode CRC check and ptrace check from /proc. And it also has kernel-mode ptrace check, hardware breakpoint check, hiding process from /proc and preventing other modules from insmod. Quite similar to Rootkit techniques.

## Note
Code works well on Linux 5.6 x86_64, probably not working on kernel version lower than this, further tests are welcome.

## References & Resources & Readings
https://github.com/NoviceLive/research-rootkit
https://github.com/ivyl/rootkit
https://stackoverflow.com/questions/3596781/how-to-detect-if-the-current-process-is-being-run-by-gdb
https://stackoverflow.com/questions/23928530/how-does-ptrace-work-in-linux
https://www.kernel.org/
https://www.apriorit.com/dev-blog/367-anti-reverse-engineering-protection-techniques-to-use-before-releasing-software
