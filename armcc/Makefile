
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
stdio_redirect \
hpl/tc \
hpl/dmac \
samd21a/armcc/Device/SAMD21/Source/ARM \
hpl/pac \
hal/src \
hpl/pm \
hpl/core \
hpl/sysctrl \
hal/utils/src \
hpl/sercom \
examples \
hpl/gclk \
stdio_redirect/keil \
hpl/rtc \
samd21a/armcc/Device/SAMD21/Source \
hpl/dsu

# List the object files
OBJS +=  \
hal/src/hal_io.o \
stdio_redirect/stdio_io.o \
samd21a/armcc/Device/SAMD21/Source/ARM/startup_SAMD21.o \
hal/src/hal_timer.o \
hal/src/hal_pwm.o \
hal/src/hal_i2c_m_sync.o \
hal/src/hal_delay.o \
hpl/sysctrl/hpl_sysctrl.o \
hpl/core/hpl_init.o \
hal/utils/src/utils_list.o \
hpl/core/hpl_core_m0plus_base.o \
hal/utils/src/utils_assert.o \
hpl/pac/hpl_pac.o \
hpl/pm/hpl_pm.o \
hal/src/hal_usart_sync.o \
stdio_redirect/keil/Retarget.o \
hpl/gclk/hpl_gclk.o \
stdio_start.o \
hal/src/hal_init.o \
hal/src/hal_crc_sync.o \
main.o \
hpl/rtc/hpl_rtc.o \
examples/driver_examples.o \
driver_init.o \
samd21a/armcc/Device/SAMD21/Source/system_samd21.o \
hpl/sercom/hpl_sercom.o \
hal/src/hal_gpio.o \
hal/utils/src/utils_event.o \
hal/src/hal_sleep.o \
hpl/dmac/hpl_dmac.o \
atmel_start.o \
hpl/tc/hpl_tc.o \
hal/src/hal_atomic.o \
hpl/dsu/hpl_dsu.o

OBJS_AS_ARGS +=  \
"hal/src/hal_io.o" \
"stdio_redirect/stdio_io.o" \
"samd21a/armcc/Device/SAMD21/Source/ARM/startup_SAMD21.o" \
"hal/src/hal_timer.o" \
"hal/src/hal_pwm.o" \
"hal/src/hal_i2c_m_sync.o" \
"hal/src/hal_delay.o" \
"hpl/sysctrl/hpl_sysctrl.o" \
"hpl/core/hpl_init.o" \
"hal/utils/src/utils_list.o" \
"hpl/core/hpl_core_m0plus_base.o" \
"hal/utils/src/utils_assert.o" \
"hpl/pac/hpl_pac.o" \
"hpl/pm/hpl_pm.o" \
"hal/src/hal_usart_sync.o" \
"stdio_redirect/keil/Retarget.o" \
"hpl/gclk/hpl_gclk.o" \
"stdio_start.o" \
"hal/src/hal_init.o" \
"hal/src/hal_crc_sync.o" \
"main.o" \
"hpl/rtc/hpl_rtc.o" \
"examples/driver_examples.o" \
"driver_init.o" \
"samd21a/armcc/Device/SAMD21/Source/system_samd21.o" \
"hpl/sercom/hpl_sercom.o" \
"hal/src/hal_gpio.o" \
"hal/utils/src/utils_event.o" \
"hal/src/hal_sleep.o" \
"hpl/dmac/hpl_dmac.o" \
"atmel_start.o" \
"hpl/tc/hpl_tc.o" \
"hal/src/hal_atomic.o" \
"hpl/dsu/hpl_dsu.o"

# List the dependency files
DEPS := $(OBJS:%.o=%.d)

DEPS_AS_ARGS +=  \
"stdio_redirect/stdio_io.d" \
"hal/utils/src/utils_event.d" \
"hal/src/hal_io.d" \
"samd21a/armcc/Device/SAMD21/Source/ARM/startup_SAMD21.d" \
"hal/src/hal_i2c_m_sync.d" \
"samd21a/armcc/Device/SAMD21/Source/system_samd21.d" \
"hal/src/hal_pwm.d" \
"hal/src/hal_timer.d" \
"hpl/core/hpl_core_m0plus_base.d" \
"hal/utils/src/utils_list.d" \
"hpl/pac/hpl_pac.d" \
"hal/utils/src/utils_assert.d" \
"hal/src/hal_delay.d" \
"hpl/core/hpl_init.d" \
"hpl/sysctrl/hpl_sysctrl.d" \
"stdio_start.d" \
"hpl/gclk/hpl_gclk.d" \
"hal/src/hal_crc_sync.d" \
"hal/src/hal_init.d" \
"hal/src/hal_usart_sync.d" \
"stdio_redirect/keil/Retarget.d" \
"hpl/dmac/hpl_dmac.d" \
"driver_init.d" \
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
"atmel_start.d"

OUTPUT_FILE_NAME :=AtmelStart
QUOTE := "
OUTPUT_FILE_PATH +=$(OUTPUT_FILE_NAME).elf
OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_FILE_NAME).elf

vpath %.c ../
vpath %.s ../
vpath %.S ../

# All Target
all: $(SUB_DIRS) $(OUTPUT_FILE_PATH)

# Linker target

$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Building target: $@
	@echo Invoking: ARMCC Linker
	$(QUOTE)armlink$(QUOTE) --ro-base 0x00000000 --entry 0x00000000 --rw-base 0x20000000 --entry Reset_Handler --first __Vectors \
--strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols \
--info sizes --info totals --info unused --info veneers --list $(OUTPUT_FILE_NAME).map \
-o $(OUTPUT_FILE_NAME).elf --cpu Cortex-M0+ \
$(OBJS_AS_ARGS)

	@echo Finished building target: $@

# Compiler target(s)




%.o: %.c
	@echo Building file: $<
	@echo ARMCC Compiler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M0+ -D__SAMD21G18A__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

%.o: %.s
	@echo Building file: $<
	@echo ARMCC Assembler
	$(QUOTE)armasm$(QUOTE) -g --apcs=interwork --cpu Cortex-M0+ --pd "D__SAMD21G18A__ SETA 1" \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
--depend "$(@:%.o=%.d)" -o "$@" "$<"

	@echo Finished building: $<

%.o: %.S
	@echo Building file: $<
	@echo ARMCC Preprocessing Assembler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M0+ -D__SAMD21G18A__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/dsu" -I"../hpl/gclk" -I"../hpl/pac" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/rtc" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/tc" -I"../hri" -I"../" -I"../config" -I"../stdio_redirect" -I"../" -I"../CMSIS/Include" -I"../samd21a/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(SUB_DIRS):
	$(MK_DIR) "$@"

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -f $(OUTPUT_FILE_NAME).map $(OUTPUT_FILE_NAME).elf
