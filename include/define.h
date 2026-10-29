#ifndef DEFINE_H
#define DEFINE_H

// this header contains defines needed, including kernel MD

// i can probably import stdint.h without it blowing up but eh
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned int uintptr_t; // FRAGILE! this will DIE on 32bit. assuming ill ever go 32bit lol
typedef unsigned long long uint64_t;

// i am not memorizing this so im just gonna
#define REG_EDI 0
#define REG_ESI 1
#define REG_EBP 2
#define REG_ESP 3
#define REG_EBX 4
#define REG_EDX 5
#define REG_ECX 6
#define REG_EAX 7




#endif