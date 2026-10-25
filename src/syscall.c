#include "define.h"
#include "log.h"
#include "syscall.h"
#include "puh_metadata.h"

void puhlog_syscall(uint32_t* registers) {
    uint32_t syscall = registers[REG_EBX];

    switch (syscall) {
        case PUHLOG_PRINT: {
            char* message = (char*)(registers[REG_ECX]);
            uint8_t color = (uint8_t)(registers[REG_EDX]);
            puhlog_printc(message, color);
            break;
        }
        case PUHLOG_CLEAR: {
            puhlog_clear();
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
        case PUHLOG: {
            return puhlog_syscall(registers);
        }
        case PUHINFO: {
            return puhinfo_syscall(registers);
        }
    }
}