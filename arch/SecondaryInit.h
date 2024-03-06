#include "x86/PrimaryInit.h"

class SecondaryInitialization : protected PrimaryInitialization
{
    public:
        void processorInitialize() override final;
        void devicesInitialize() override final;
};

