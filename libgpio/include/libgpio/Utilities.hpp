#ifndef LIBGPIO_UTILITIES
#define LIBGPIO_UTILITIES

#include <string>

#if !defined(LIBGPIO_VERSION)
#error "LIBGPIO_VERSION is not defined"
#endif

#if !defined(LIBGPIO_LIBRARY)
#error "LIBGPIO_LIBRARY is not defined"
#endif

namespace libgpio
{

std::string version()
{
    return LIBGPIO_VERSION;
}

std::string gpioLibrary()
{
    return LIBGPIO_LIBRARY;
}

}

#endif // LIBGPIO_UTILITIES