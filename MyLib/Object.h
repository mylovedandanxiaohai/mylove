#ifndef OBJECT_H
#define OBJECT_H

namespace MyLib
{
    class Object
    {
          public:
            void* operator new(unsigned int size)throw();
            void operator delete(void* p);
            void* operator new[](unsigned int size)throw();
            void operator delete[](void* p);

            ~Object();
    };
}

#endif // OBJECT_H
