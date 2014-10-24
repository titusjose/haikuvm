################################################################################
# Is a copy of haiku.makefile from directory haikuVM. Edit with care.
################################################################################

-include ../../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
O_SRCS :=
C_SRCS :=
S_UPPER_SRCS :=
S_SRCS :=
OBJ_SRCS :=
ASM_SRCS :=
OBJS :=
C_DEPS :=
ASM_DEPS :=
EEPROM_IMAGE :=
FLASH_IMAGE :=
ELFS :=
LSS :=
S_DEPS :=
SIZEDUMMY :=
S_UPPER_DEPS :=

# Every subdirectory with source files must be described here
SUBDIRS :=



-include subdir.mk


USER_OBJS :=
LIBS := -lc 

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LSS += \
$(HAIKU_APP_NAME).lss \

FLASH_IMAGE += \
$(HAIKU_OUTPUT) \

EEPROM_IMAGE += \
$(HAIKU_APP_NAME).eep \

SIZEDUMMY += \
sizedummy \


# All Target
ifeq ($(strip $(HAIKU_LINKER)),NONE)
all: none
else
ifeq ($(strip $(HAIKU_EXTENSION)),.hex)
all: $(HAIKU_APP_NAME).elf $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)
else
all: $(HAIKU_APP_NAME)
endif
endif

none:
	@echo
	
info:
	@echo '#'
	@echo '#'
	@echo '#'
	@echo '#############################################################'
	@echo '# cross compiling'
	@echo '#############################################################'
	@echo '#'
	@echo '#'
	@echo '#'
		
# Tool invocations
$(HAIKU_APP_NAME).elf: info $(OBJS) $(USER_OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: C Linker'
	touch "$@"
	$(HAIKU_LINKER) $(HAIKU_LDFLAGS) 
	@echo 'Finished building target: $@'
	@echo ' '

$(HAIKU_OUTPUT): info $(OBJS) $(USER_OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: C Linker'
	touch "$@"
	$(HAIKU_LINKER) $(HAIKU_LDFLAGS) 
	@echo 'Finished building target: $@'
	@echo ' '

$(HAIKU_APP_NAME).lss: $(HAIKU_APP_NAME).elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S "$<"  >"$@"
	@echo 'Finished building: $@'
	@echo ' '

$(HAIKU_APP_NAME).hex: $(HAIKU_APP_NAME).elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex "$<" "$@"
	@echo 'Finished building: $@'
	@echo ' '

$(HAIKU_APP_NAME).eep: $(HAIKU_APP_NAME).elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex "$<"  "$@"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: $(HAIKU_APP_NAME).elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=$(HAIKU_TARGET) "$<"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets

# Clean Target
ifeq ($(strip $(HAIKU_LINKER)),NONE)
clean: none
else
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) $(HAIKU_APP_NAME).elf
	-@echo ' '
endif

upload:
	$(HAIKU_UPLOAD)

.PHONY: all clean dependents upload
.SECONDARY:

-include ../../makefile.targets
