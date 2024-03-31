#include "../arch/SecondaryInit.h"
#include "../drivers/acpi/Acpi.h"
#include <StringOperations.h>

void empty() {};

void main()
{
    SecondaryInitialization init;

    init.devicesInitialize();
    init.processorInitialize();

    out::display << "Hello, World!\n";
    Rsdp *rsdp = (Rsdp *)StringOperations::findInMemory(Rsdp::signatureString, 
                                                MemArea(
                                                        Rsdp::romAreaStart,
                                                        Rsdp::romAreaEnd));
    const Rsdt *rsdt = rsdp->getRsdt();
    const Entry *entry = rsdt->getEntry(1);
    const Madt *madt = (Madt *)entry;
    const Ics *icsEntry[10] = {madt->getIcs(0),
                               madt->getIcs(1),
                               madt->getIcs(2),
                               madt->getIcs(3),
                               madt->getIcs(4),
                               madt->getIcs(5),
                               madt->getIcs(6),
                               madt->getIcs(7),
                               madt->getIcs(8)};
    const IoapicStruct *ioapicStruct = (IoapicStruct *)icsEntry[1];
    empty();
};
