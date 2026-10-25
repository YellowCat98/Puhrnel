#include "define.h"
#include "log.h"
#include "syscall.h"

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
        case PUHINFO_VERSION: {
            return;
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