
all:
	docker run --rm --name dev-build \
		--mount type=bind,source="`pwd`",target=/build \
		-w="/build" \
		dev make kernel

kernel: kernel_stub.o kernel.o
	ld -m elf_i386 -T link.ld -o $@ kernel_stub.o kernel.o

kernel_stub.o: kernel.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
	gcc -m32 -o $@ -c $<

.PHONY: clean
clean:
	rm -fr kernel *.o

.PHONY: docker_image
docker_image:
	docker build -t dev -f Dockerfile.build .
