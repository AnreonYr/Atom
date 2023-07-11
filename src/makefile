BUILD += ./build
EMU += ./emulator
INCLUDE += ./includes

ASRC += $(shell find -name "*.S")
CSRC += $(shell find -name "*.c")
OBJ += $(wildcard ../build/*.o)

CFLAG += -m32\
		 -g\
		 -O0\
		 -Qn\
		 -fno-builtin\
		 -fno-pic\
		 -fno-pie\
		 -fno-stack-protector\
		 -fno-asynchronous-unwind-tables\
		 -fomit-frame-pointer\
		 -mpreferred-stack-boundary=2\
		 -I $(INCLUDE)

.PHONY: bootloader.o kernel.o

dir:
	@mkdir $(BUILD)
	@mkdir $(EMU)

echo:
	@echo $(CSRC)
	@echo $(ASRC)
	@echo $(OBJ)

bootloader.o: $(ASRC)
	gcc $(CFLAG) -c $^

kernel.o: $(CSRC)
	gcc $(CFLAG) -c $^

os.bin: bootloader.o kernel.o 
	ld -T ./config/linker.ld *.o -o $@
	objcopy --only-keep-debug $@ $(BUILD)/os.debug
	objcopy -R .note.gnu.property -O binary $@
	@mv $@ $(BUILD)
	dd if=$(BUILD)/$@ of=$(EMU)/os.img bs=512 conv=notrunc
	@rm *.o

qemu-gdb:
	qemu-system-i386 -m 128M -S -s ./emulator/os.img &
	cgdb -s $(BUILD)/os.debug -ex 'target remote :1234' -ex 'set architecture i386'
