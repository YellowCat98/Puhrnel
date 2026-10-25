PROJECT_CODENAME = undescended_testes
PROJECT_VERSION = 0.0.0
PROJECT_PRETTYCODENAME = Undescended Testes
PROJECT_MINICODENAME = utestes
PROJECT_FULLNAME = puhrnel_$(PROJECT_CODENAME)_v$(PROJECT_VERSION)
PROJECT_PRETTYFULLNAME = Puhrnel $(PROJECT_PRETTYCODENAME) v$(PROJECT_VERSION)
PROJECT_ISOLABEL = puh_$(PROJECT_MINICODENAME)_v$(PROJECT_VERSION)

NASM = nasm
NASMFLAGS = -f elf32
CC = gcc
CC_FLAGS = -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -fno-PIE -Wall -Wextra -fno-tree-loop-distribute-patterns -m32 -I$(INCLUDE) -I$(CODEGEN) -mpreferred-stack-boundary=2
# TODO: implement the basic functions that GCC expects and remove -fno-tree-loop-distribute-patterns

BUILD = build
OUT = out
INCLUDE = include
CODEGEN = $(BUILD)/codegen

PUHRNEL_ISO = $(PROJECT_FULLNAME).iso

ASM = $(wildcard src/*.asm)
C = $(wildcard src/*.c)
ASM_OBJ = $(patsubst src/%.asm,$(BUILD)/%.asm.o,$(ASM))
C_OBJ = $(patsubst src/%.c,$(BUILD)/%.c.o,$(C))
OBJ = $(ASM_OBJ) $(C_OBJ)

.PHONY: all clean run

all: $(CODEGEN)/puh_metadata.h $(OUT)/$(PUHRNEL_ISO)

$(BUILD) $(OUT) $(CODEGEN):
	mkdir -p $@

$(CODEGEN)/puh_metadata.h: | $(CODEGEN)
	@printf '#ifndef PUH_METADATA_H\n#define PUH_METADATA_H\n\n#define PUHCODENAME "%s"\n#define PUHVERSION "%s"\n#define PUHFULLNAME "%s"\n#define PUHPRETTYCODENAME "%s"\n#define PUHPRETTYFULLNAME "%s"\n\n#endif\n' \
		'$(PROJECT_CODENAME)' \
		'$(PROJECT_VERSION)' \
		'$(PROJECT_FULLNAME)' \
		'$(PROJECT_PRETTYCODENAME)' \
		'$(PROJECT_PRETTYFULLNAME)' > $@

$(BUILD)/%.asm.o: src/%.asm | $(BUILD)
	$(NASM) $(NASMFLAGS) $< -o $@

$(BUILD)/%.c.o: src/%.c | $(BUILD)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OUT)/puhImage: $(OBJ) linker.ld | $(OUT)
	ld -m elf_i386 -n -T linker.ld -o $@ $(OBJ)

$(OUT)/$(PUHRNEL_ISO): $(OUT)/puhImage
	mkdir -p $(BUILD)/iso_root/boot/grub
	cp $< $(BUILD)/iso_root/boot/puhImage
	echo 'menuentry "puhrnel" { multiboot2 /boot/puhImage; boot }' > $(BUILD)/iso_root/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BUILD)/iso_root -volid $(PROJECT_ISOLABEL)

run: $(OUT)/$(PUHRNEL_ISO)
	qemu-system-x86_64 -cdrom $(OUT)/$(PUHRNEL_ISO)

clean:
	rm -rf $(BUILD) $(OUT)