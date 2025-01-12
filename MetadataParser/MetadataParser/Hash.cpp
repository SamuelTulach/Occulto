#include "Global.h"

#define XXH_INLINE_ALL true
#include "xxhash.h"

void Hash::Run(char* buffer, const size_t size)
{
    constexpr auto seed = 0x59648347113887; // change each update
    const XXH64_hash_t hash = XXH64(buffer, size, seed);

    static const char* hexDigits = "0123456789abcdef";
    char hashString[17];
    for (int i = 0; i < 8; ++i)
    {
        hashString[i * 2] = hexDigits[(hash >> (56 - i * 8)) & 0xF];
        hashString[i * 2 + 1] = hexDigits[(hash >> (52 - i * 8)) & 0xF];
    }
    hashString[16] = '\0';

    for (size_t i = 0; i < size; ++i)
        buffer[i] = hashString[i % 16];

    if (size < 16)
        buffer[size] = '\0';
}
