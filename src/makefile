BUILD += ./build
EMU += ./emulator
INCLUDE += ./includes

SRC += $(shell find -name "*.[Sc]")
OBJ += $(wildcard ./build/*.o)

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
		 -ffreestanding\
		 -Wno-pointer-to-int-cast\
		 -Wno-address-of-packed-member\
		 -Wno-incompatible-pointer-types\
		 -I $(INCLUDE)

.PHONY: clean

dir:
	@mkdir $(BUILD)
	@mkdir $(EMU)

echo:
	@echo $(SRC)
	@echo $(OBJ)

clean:
	@rm $(BUILD)/*.o

obj: $(SRC)
	gcc $(CFLAG) -c $^
	@mv *.o $(BUILD)

os.bin: obj
	ld -T ./config/linker.ld $(OBJ) -o $@
	@cp $@ $(BUILD)/os.elf
	objcopy -R .note.gnu.property -O binary $@
	@mv *.bin $(BUILD)

os.debug: os.bin
	objcopy --only-keep-debug $^ $(BUILD)/$@

os.img: os.bin
	dd if=$(BUILD)/$^ of=$(EMU)/$@ bs=512 conv=notrunc

qemu-gdb: os.img os.debug
	qemu-system-i386 -m 128M -S -s ./emulator/os.img &
	cgdb -s $(BUILD)/os.debug -ex 'target remote :1234' -ex 'set architecture i386'
