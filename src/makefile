BUILD += ../build
EMU += ../emulator
SRC += $(shell find -name "*.[cS]")
OBJ += $(wildcard ../build/*.o)

CFLAG := -m32
CFLAG += -Qn
CFLAG += -fno-builtin
CFLAG += -fno-pic
CFLAG += -fno-pie
CFLAG += -fno-stack-protector
CFLAG += -fomit-frame-pointer
CFLAG += -mpreferred-stack-boundary=2
CFLAG += -fno-asynchronous-unwind-tables

dir:
	mkdir ../build
	mkdir ../emulator

echo:
	@echo $(SRC)
	@echo $(OBJ)

.PHONY: bootloader.bin

bootloader.bin: ./arch/boot.S ./arch/loader.S
	gcc -m32 -c $^
	ld -T ./config/linker.ld boot.o loader.o -o bootloader.bin
	objcopy -R .note.gnu.property -O binary bootloader.bin
	dd if=../build/bootloader.bin of=../emulator/os.img bs=512 conv=notrunc
	rm *.o
	mv *.bin $(BUILD)

qemu-gdb:
	qemu-system-i386 -m 128M -S -s ../emulator/os.img
	cgdb -ex 'target remote :1234' -ex 'set architecture i386'
