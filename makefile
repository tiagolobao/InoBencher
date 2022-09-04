
# ---------------------------
# Config
AVRDUDE_PORT = COM3

# ---------------------------
# Board specific
MCU=atmega328p
F_CPU=16000000UL

# ---------------------------
CC=avr-gcc
AVRDUDE=avrdude

# ---------------------------
# Target file name
TARGET=InoBencher.hex

# ---------------------------
# Source files
FREERTOS_DIR=miniAVRfreeRTOS
CURSES_DIR=avrcurses
PGMEMSPACE_DIR=myPgmspace
APP_DIR=src
INC_DIR=inc

FREERTOS_SRC  :=                       \
	$(FREERTOS_DIR)/timers.c           \
	$(FREERTOS_DIR)/stream_buffer.c    \
	$(FREERTOS_DIR)/heap_3.c           \
	$(FREERTOS_DIR)/event_groups.c     \
	$(FREERTOS_DIR)/hooks.c            \
	$(FREERTOS_DIR)/port.c             \
	$(FREERTOS_DIR)/queue.c            \
	$(FREERTOS_DIR)/list.c             \
	$(FREERTOS_DIR)/tasks.c

CURSES_SRC :=                           \
	$(CURSES_DIR)/drivers/$(MCU)/uart.c \
	$(CURSES_DIR)/src/mcurses-config.c  \
	$(CURSES_DIR)/src/mcurses.c

PGMEMSPACE_SRC := \
	$(PGMEMSPACE_DIR)/myPgmspace.c

APP_SRC :=                        \
	$(APP_DIR)/serialUi.c        \
	$(APP_DIR)/channelInterface.c \
	app_main.c

SOURCES :=            \
	$(FREERTOS_SRC)   \
	$(CURSES_SRC)     \
	$(PGMEMSPACE_SRC) \
	$(APP_SRC)        \

INC_PATH=                 \
	-I$(FREERTOS_DIR)     \
	-I$(CURSES_DIR)       \
	-I$(PGMEMSPACE_DIR)   \
	-I$(APP_DIR)          \
	-I$(INC_DIR)

# ---------------------------
# Verbose config
VERBOSE_MAKEFILE = 0
AVRDUDE_VERBOSE = -v -v

# ---------------------------
# Makefile definitions
ifeq ($(VERBOSE_MAKEFILE), 0)
	Q = @
	P = > /dev/null
else
  Q =
  P = 
endif

AVRDUDE_PROGRAMMER = arduino
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET)
AVRDUDE_FLAGS = -p $(MCU) -b 115200
AVRDUDE_FLAGS += -P $(AVRDUDE_PORT)
AVRDUDE_FLAGS += -c $(AVRDUDE_PROGRAMMER)

CFLAGS  = -mmcu=$(MCU)
CFLAGS += -funsigned-char -funsigned-bitfields
CFLAGS += -DF_CPU=$(F_CPU) 
CFLAGS += $(INC_PATH)
CFLAGS += -O2 -ffunction-sections -fdata-sections -fshort-enums
CFLAGS += -mrelax -Wall -Wstrict-prototypes
CFLAGS += -std=gnu11 -Wundef
CFLAGS += -MMD -MP -MF .dep/$(@F).d

LFLAGS  = -mmcu=$(MCU)
LFLAGS += -Wl,-Map=$(MAPFILE),--cref,--gc-sections
LFLAGS += -lm

OBJECTS := $(addprefix  obj/,$(SOURCES:.c=.o))
LINKED := $(addprefix obj/, $(TARGET:.hex=.elf))
BINARY := $(addprefix obj/, $(TARGET:.hex=.bin))
MAPFILE := $(addprefix obj/, $(TARGET:.hex=.map))
SYMFILE := $(addprefix obj/, $(TARGET:.hex=.sym))
LSSFILE := $(addprefix obj/, $(TARGET:.hex=.lss))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LD]        $(TARGET)"
	$Qavr-gcc $(LFLAGS) -o $(LINKED) $^
	$Qavr-objcopy -O ihex -R .eeprom $(LINKED) $@
	$Qavr-objcopy -I ihex $(TARGET) -O binary $(BINARY)
	$Qavr-size --format=berkeley $(LINKED)
	$Qavr-nm -n $(LINKED) > $(SYMFILE)
	$Qavr-objdump -h -S $(LINKED) > $(LSSFILE)

obj/%.o: %.c
	@echo "[CC]        $(notdir $<)"
	$Qmkdir -p $(dir $@)
	$Q$(CC) $(CFLAGS) -c -o $@ $<

program:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

clean:
	@echo "Cleaning $(TARGET)"
	$Qrm -f $(TARGET)
	$Qrm -f $(BINARY)
	$Qrm -f $(MAPFILE)
	$Qrm -f $(SYMFILE)
	$Qrm -f $(LSSFILE)
	@echo "Cleaning Objects"
	$Qrm -f *.o
	$Qrm -fR obj
	$Qrm -fR .dep

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)