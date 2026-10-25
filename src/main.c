#include "log.h"
#include "puh_metadata.h"

extern void big_boobs();

void kmain(void) {
    puhlog_print("Running Puhrnel ");
    puhlog_print(PUHPRETTYFULLNAME);
    puhlog_print("\n");

    big_boobs();

    while (1) {
        asm volatile(
            "cli\n\t"
            "1:\n\t"
            "hlt\n\t"
            "jmp 1b"
            : : : "memory"
        );
    }
}