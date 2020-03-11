#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h";
#include "port.h";
#include "gdt.h";

    class InterruptManager 
    {
        protected: 
            struct GateDescriptor{
                uint16_t hanlderAddressLowBits;
                uint16_t gdt_codeSegmentSelector;
                uint8_t reserved;
                uint8_t access;
                uint8_t hanlderAddressHighBits;
            }; __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];
            struct interruptDescriptorTablePointer{
                uint16_t size;
                uint32_t base;

            } __attribute__((packed));

            
            static void SetInterruptDescriptorTableEntry(
                uint8_t interruptNumber,
                uint8_t codeSegmentSelectorOffset,
                void (*hanlder)(),
                uint8_t DescriptorPrivilegeLevel,
                uint8_t DescriptorType
            );

            Port8BitSlow picMasterCommand;
            Port8BitSlow picMasterData;
            Port8BitSlow picSlaveCommand;
            Port8BitSlow picSlaveData;
            

        public: 

            InterruptManager(GlobalDescriptorTable* gdt);
            ~InterruptManager();
            
            static uint32_t handleInterrupt
            (uint8_t interruptNumber,
             uint32_t esp);

            void Activate();

            static void InterruptIgnore();
            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleExeception0x00();
            static void HandleExeception0x01();
    };

#endif 