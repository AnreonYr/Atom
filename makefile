BUILD += ./build
SRC += $(shell find -name "*.[cS]")
OBJ += $(wildcard ./build/*.o)

CFLAG := -m32
CFLAG += -Qn 
CFLAG += -fno-builtin
CFLAG += -fno-pic
CFLAG += -fno-pie
CFLAG += -fno-stack-protector
CFLAG += -fomit-frame-pointer
CFLAG += -mpreferred-stack-boundary=2
CFLAG += -fno-asynchronous-unwind-tables

p:
	@echo $(SRC)
	@echo $(OBJ)

bootloader.bin: ./arch/boot.S ./arch/loader.S
	gcc -m32 -c ./arch/*.S
	ld -T ./config/linker.ld boot.o loader.o -o bootloader.bin
	objcopy -j .boot -j .loader -O binary bootloader.bin
	rm *.o
	mv *.bin $(BUILD)

kernel.bin: $(OBJ)
	ld -T ./config/linker.ld $^ -o kernel.bin

O: $(SRC)
	gcc $(CFLAG) -I ./includes -c $^
	mv *.o $(BUILD)
