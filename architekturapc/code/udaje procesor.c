#include <stdio.h>
#include <string.h>

int main() {
    unsigned int cpuInfo[3];
    char vendorString[13];


    asm("cpuid"
            : "=a"(cpuInfo[0]), "=b"(cpuInfo[1]), "=c"(cpuInfo[2])
            : "a"(0)
            : );

    //copy the vendor string into a character array
    memcpy(vendorString, &cpuInfo[1], 4);
    memcpy(&vendorString[4], &cpuInfo[3], 4);
    memcpy(&vendorString[8], &cpuInfo[2], 4);
    vendorString[12] = '\0';

    printf("CPU vendor: %s\n", vendorString);

    int k;
    scanf("%d", &k);

    return 0;
}
