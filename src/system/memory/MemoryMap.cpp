#pragma once

#include "../../Kernel.h"
#include "../../driver/VGA_Screen.cpp"

struct MemoryMapEntry {
    uint_64 BaseAddress;
    uint_64 RegionLength;
    uint_32 RegionType;
    uint_32 ExtendedAttributes;
};

extern uint_8 MemoryRegionCount;

uint_8 UsableMemoryRegionsCount;

uint_32 TotalMemoryLength;

MemoryMapEntry* UsableMemoryMaps[10];

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint_16 position = CursorPosition){
    SetCursorPosition(position);
    PrintString("Memory Base: "); PrintString(IntegerToString(memoryMap->BaseAddress)); PrintString("\n");
    PrintString("Region Length: "); PrintString(IntegerToString(memoryMap->RegionLength)); PrintString("\n");
    PrintString("Memory Type: "); PrintString(IntegerToString(memoryMap->RegionType)); PrintString("\n");
    PrintString("Memory Attributes: "); PrintString(IntegerToString(memoryMap->ExtendedAttributes)); PrintString("\n");
}

bool MemoryRegionsGot = false;

MemoryMapEntry** GetUsableMemoryRegions(){
    if(MemoryRegionsGot) return UsableMemoryMaps;
    uint_8 UsableRegionIndex;
    for(uint_8 i = 0; i < MemoryRegionCount; i++){
        MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
        memMap += i;
        if(memMap->RegionType == 1){
            UsableMemoryMaps[UsableRegionIndex] = memMap;
            UsableRegionIndex++;
            TotalMemoryLength += memMap->RegionLength;
        }
    }
    UsableMemoryRegionsCount = UsableRegionIndex;
    MemoryRegionsGot = true;
    return UsableMemoryMaps;
}