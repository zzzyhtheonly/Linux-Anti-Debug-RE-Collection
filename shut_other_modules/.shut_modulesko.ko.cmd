cmd_/root/anti_RE/shut_other_modules/shut_modulesko.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T /usr/src/linux-headers-5.6.0-kali2-common/scripts/module-common.lds -o /root/anti_RE/shut_other_modules/shut_modulesko.ko /root/anti_RE/shut_other_modules/shut_modulesko.o /root/anti_RE/shut_other_modules/shut_modulesko.mod.o;  true
