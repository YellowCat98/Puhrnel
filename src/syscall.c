#include "define.h"
#include "vgalog.h"
#include "syscall.h"
#include "puh_metadata.h"

void puhvgalog_syscall(uint32_t* registers) {
    uint32_t syscall = registers[REG_EBX];

    switch (syscall) {
        case PUHVGALOG_PRINT: {
            char* message = (char*)(registers[REG_ECX]);
            uint8_t color = (uint8_t)(registers[REG_EDX]);
            puhvgalog_printc(message, color);
            break;
        }
        case PUHVGALOG_CLEAR: {
            puhvgalog_clear();
            break;
        }
    }
}

void puhinfo_syscall(uint32_t* registers) {
    uint32_t syscall = registers[REG_EBX];

    switch (syscall) {
        case PUHINFO_CODENAME: {
            registers[REG_EAX] = (uint32_t)PUHCODENAME;
            break;
        }
        case PUHINFO_VERSION: {
            registers[REG_EAX] = (uint32_t)PUHVERSION;
            break;
        }
        case PUHINFO_FULLNAME: {
            registers[REG_EAX] = (uint32_t)PUHFULLNAME;
            break;
        }
        case PUHINFO_PRETTYCODENAME: {
            registers[REG_EAX] = (uint32_t)PUHPRETTYCODENAME;
            break;
        }
        case PUHINFO_PRETTYFULLNAME: {
            registers[REG_EAX] = (uint32_t)PUHPRETTYFULLNAME;
            break;
        }
    }
}

void syscall_dispatch(uint32_t* registers) {
    uint32_t syscall_kind = registers[REG_EAX];

    switch (syscall_kind) {
        case PUHVGALOG: {
            return puhvgalog_syscall(registers);
        }
        case PUHINFO: {
            return puhinfo_syscall(registers);
        }
    }
}