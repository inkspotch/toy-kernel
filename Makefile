
all:
	docker run --rm --name dev-build \
		--mount type=bind,source="`pwd`",target=/build \
		-w="/build" \
		dev make kernel

kernel: boot.o kernel.o link.ld
	ld -m elf_i386 -T link.ld -o $@ boot.o kernel.o

boot.o: boot.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
	gcc -m32 -o $@ -c $<

.PHONY: clean
clean:
	rm -fr kernel *.o

.PHONY: docker_image
docker_image:
	docker build -t dev -f Dockerfile.build .
