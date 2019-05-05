AS = nasm

all: build

build:
	$(AS) boot.s -o boot.bin
	dd if=boot.bin of=floppy.img bs=512 count=1

clean:
	rm -rf *.bin *.img