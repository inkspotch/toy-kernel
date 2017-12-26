
CFLAGS := -m32 -ffreestanding -O2 -Wall -Wextra
INCLUDES := -I.
SOURCE := $(wildcard *.c)
OBJECTS := $(SOURCE:.c=.o)

docker_build:
	docker run --rm --name dev-build \
		--mount type=bind,source="`pwd`",target=/build \
		-w="/build" \
		dev make kernel

kernel: $(OBJECTS) boot.o
	ld -m elf_i386 -T link.ld -o $@ $(OBJECTS) boot.o

boot.o: boot.asm
	nasm -f elf32 $< -o $@

.PHONY: clean
clean:
	rm -fr kernel *.o

.PHONY: docker_image
docker_image:
	docker build -t dev -f Dockerfile.build .
