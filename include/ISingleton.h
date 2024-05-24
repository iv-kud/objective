#ifndef SINGLETON_H
#define SINGLETON_H


template <typename T>
class ISingleton
{
    public:
        virtual T *getInstance() = 0;
};

#endif
