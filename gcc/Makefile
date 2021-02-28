
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ifdef SystemRoot
	SHELL = cmd.exe
	MK_DIR = mkdir
else
	ifeq ($(shell uname), Linux)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), CYGWIN)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW32)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW64)
		MK_DIR = mkdir -p
	endif
endif

# List the subdirectories for creating object files
SUB_DIRS +=  \
 \
stdio_redirect/gcc \
hpl/tc \
samd21a/gcc/gcc \
hpl/dmac \
stdio_redirect \
hpl/pac \
hal/src \
samd21a/gcc \
hpl/pm \
hpl/core \
hpl/sysctrl \
hal/utils/src \
hpl/sercom \
examples \
hpl/gclk \
hpl/rtc \
hpl/dsu \
xdense \
xdense_utils \
drivers

# List the object files
OBJS +=  \
hal/src/hal_io.o \
stdio_redirect/stdio_io.o \
samd21a/gcc/gcc/startup_samd21.o \
stdio_redirect/gcc/write.o \
hal/utils/src/utils_syscalls.o \
hal/src/hal_timer.o \
hal/src/hal_pwm.o \
hal/src/hal_i2c_m_sync.o \
hal/src/hal_delay.o \
hpl/sysctrl/hpl_sysctrl.o \
hpl/core/hpl_init.o \
hal/utils/src/utils_list.o \
hpl/core/hpl_core_m0plus_base.o \
hal/utils/src/utils_assert.o \
hal/utils/src/utils_ringbuffer.o \
hpl/pac/hpl_pac.o \
hpl/pm/hpl_pm.o \
hal/src/hal_usart_sync.o \
stdio_redirect/gcc/read.o \
hpl/gclk/hpl_gclk.o \
stdio_start.o \
hal/src/hal_init.o \
hal/src/hal_crc_sync.o \
main.o \
samd21a/gcc/system_samd21.o \
hpl/rtc/hpl_rtc.o \
examples/driver_examples.o \
driver_init.o \
hpl/sercom/hpl_sercom.o \
hal/src/hal_gpio.o \
hal/utils/src/utils_event.o \
hal/src/hal_sleep.o \
hpl/dmac/hpl_dmac.o \
atmel_start.o \
hpl/tc/hpl_tc.o \
hal/src/hal_atomic.o \
hpl/dsu/hpl_dsu.o \
xdense/router.o \
xdense/packet.o \
xdense/application.o \
xdense/flasher.o \
xdense/terminal.o \
xdense/sensors.o \
xdense_utils/ringback_packet_xdense.o \
drivers/i2c_xdense_driver.o \
drivers/apds9960.o


OBJS_AS_ARGS +=  \
"hal/src/hal_io.o" \
"stdio_redirect/stdio_io.o" \
"samd21a/gcc/gcc/startup_samd21.o" \
"stdio_redirect/gcc/write.o" \
"hal/utils/src/utils_syscalls.o" \
"hal/src/hal_timer.o" \
"hal/src/hal_pwm.o" \
"hal/src/hal_i2c_m_sync.o" \
"hal/src/hal_delay.o" \
"hpl/sysctrl/hpl_sysctrl.o" \
"hpl/core/hpl_init.o" \
"hal/utils/src/utils_list.o" \
"hpl/core/hpl_core_m0plus_base.o" \
"hal/utils/src/utils_assert.o" \
"hal/utils/src/utils_ringbuffer.o" \
"hpl/pac/hpl_pac.o" \
"hpl/pm/hpl_pm.o" \
"hal/src/hal_usart_sync.o" \
"stdio_redirect/gcc/read.o" \
"hpl/gclk/hpl_gclk.o" \
"stdio_start.o" \
"hal/src/hal_init.o" \
"hal/src/hal_crc_sync.o" \
"main.o" \
"samd21a/gcc/system_samd21.o" \
"hpl/rtc/hpl_rtc.o" \
"examples/driver_examples.o" \
"driver_init.o" \
"hpl/sercom/hpl_sercom.o" \
"hal/src/hal_gpio.o" \
"hal/utils/src/utils_event.o" \
"hal/src/hal_sleep.o" \
"hpl/dmac/hpl_dmac.o" \
"atmel_start.o" \
"hpl/tc/hpl_tc.o" \
"hal/src/hal_atomic.o" \
"hpl/dsu/hpl_dsu.o" \
"xdense/router.o" \
"xdense/packet.o" \
"xdense/application.o" \
"xdense/flasher.o" \
"xdense/terminal.o" \
"xdense/sensors.o" \
"xdense_utils/ringback_packet_xdense.o" \
"drivers/i2c_xdense_driver.o" \
"drivers/apds9960.o"

# List the dependency files
DEPS := $(OBJS:%.o=%.d)

DEPS_AS_ARGS +=  \
"samd21a/gcc/gcc/startup_samd21.d" \
"stdio_redirect/stdio_io.d" \
"hal/utils/src/utils_event.d" \
"hal/src/hal_io.d" \
"hal/utils/src/utils_syscalls.d" \
"stdio_redirect/gcc/write.d" \
"hal/src/hal_i2c_m_sync.d" \
"hal/src/hal_pwm.d" \
"hal/src/hal_timer.d" \
"hpl/core/hpl_core_m0plus_base.d" \
"hal/utils/src/utils_list.d" \
"hpl/pac/hpl_pac.d" \
"hal/utils/src/utils_assert.d" \
"hal/utils/src/utils_ringbuffer.d" \
"hal/src/hal_delay.d" \
"hpl/core/hpl_init.d" \
"hpl/sysctrl/hpl_sysctrl.d" \
"stdio_start.d" \
"hpl/gclk/hpl_gclk.d" \
"hal/src/hal_crc_sync.d" \
"hal/src/hal_init.d" \
"hal/src/hal_usart_sync.d" \
"stdio_redirect/gcc/read.d" \
"hpl/dmac/hpl_dmac.d" \
"driver_init.d" \
"samd21a/gcc/system_samd21.d" \
"main.d" \
"examples/driver_examples.d" \
"hpl/rtc/hpl_rtc.d" \
"hal/src/hal_sleep.d" \
"hpl/sercom/hpl_sercom.d" \
"hal/src/hal_gpio.d" \
"hal/src/hal_atomic.d" \
"hpl/tc/hpl_tc.d" \
"hpl/pm/hpl_pm.d" \
"hpl/dsu/hpl_dsu.d" \
"atmel_start.d" \
"xdense/router.d" \
"xdense/packet.d" \
"xdense/application.d" \
"xdense/flasher.d" \
"xdense/terminal.d" \
"xdense/sensors.d" \
"xdense_utils/ringback_packet_xdense.d" \
"drivers/i2c_xdense_driver.d" \
"drivers/apds9960.d"

PROGRAMMING_PORT :=/dev/ttyUSB0
OUTPUT_FILE_NAME :=xdense
QUOTE := "
OUTPUT_FILE_PATH +=$(OUTPUT_FILE_NAME).elf
OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_FILE_NAME).elf

vpath %.c ../
vpath %.s ../
vpath %.S ../

# All Target
all: $(SUB_DIRS) $(OUTPUT_FILE_PATH)

# Linker target

#For SAM-BA with both USB and UART interfaces enabled, the firmware size exceeds 4kB. So flash region 0x0000 – 0x2000 (8kB) will be allocated for SAM-BA
#For SAM-BA with only one interface enabled (either USB or UART), it is stored in flash memory from 0x0000 – 0x1000
#Added this command to the end: -Wl,--section-start=.text=0x2000

$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -o $(OUTPUT_FILE_NAME).elf $(OBJS_AS_ARGS) -Wl,--start-group -lm -Wl,--end-group -mthumb \
-Wl,-Map="$(OUTPUT_FILE_NAME).map" --specs=nano.specs -Wl,--gc-sections -mcpu=cortex-m0plus \
 \
 \
-T"../samd21a/gcc/gcc/samd21g18a_flash.ld" \
-L"../samd21a/gcc/gcc" \
-Wl,--section-start=.text=0x2000

	@echo Finished building target: $@

	"arm-none-eabi-objcopy" -O binary "$(OUTPUT_FILE_NAME).elf" "$(OUTPUT_FILE_NAME).bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  \
        "$(OUTPUT_FILE_NAME).elf" "$(OUTPUT_FILE_NAME).hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
        .eeprom=0 --no-change-warnings -O binary "$(OUTPUT_FILE_NAME).elf" \
        "$(OUTPUT_FILE_NAME).eep" || exit 0
	"arm-none-eabi-objdump" -h -S "$(OUTPUT_FILE_NAME).elf" > "$(OUTPUT_FILE_NAME).lss"
	"arm-none-eabi-size" "$(OUTPUT_FILE_NAME).elf"

# Compiler targets


%.o: %.c
	@echo Building file: $<
	@echo ARM/GNU C Compiler
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAMD21G18A__ -mcpu=cortex-m0plus  \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

%.o: %.s
	@echo Building file: $<
	@echo ARM/GNU Assembler
	$(QUOTE)arm-none-eabi-as$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAMD21G18A__ -mcpu=cortex-m0plus  \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

%.o: %.S
	@echo Building file: $<
	@echo ARM/GNU Preprocessing Assembler
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAMD21G18A__ -mcpu=cortex-m0plus  \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(SUB_DIRS):
	$(MK_DIR) "$@"
	
program:
	stty -F $(PROGRAMMING_PORT) 115200
	/bin/echo -e "R" >$(PROGRAMMING_PORT)
	sleep 1
	../../bossac-1.7.0/bin/bossac -p $(PROGRAMMING_PORT) -w $(OUTPUT_FILE_NAME).bin -e -R

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -f $(OUTPUT_FILE_NAME).a $(OUTPUT_FILE_NAME).hex $(OUTPUT_FILE_NAME).bin \
        $(OUTPUT_FILE_NAME).lss $(OUTPUT_FILE_NAME).eep $(OUTPUT_FILE_NAME).map \
        $(OUTPUT_FILE_NAME).srec
