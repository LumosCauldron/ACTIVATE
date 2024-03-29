

#include <emmintrin.h>
#include <smmintrin.h> //4.1
#include <immintrin.h> //AVX
#include <stdint.h>

#define _rotl_KAZE(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#undef  _rotl
#define _rotl(x,r) ((x << r) | (x >> (64 - r)))
 
// FNV1A_Hash_YoshimitsuTRIAD HASH
uint32_t signature(const char *str, uint32_t wrdlen)
{
    const uint32_t PRIME = 709607;
    uint32_t hash32      = 2166136261;
    uint32_t hash32B     = 2166136261;
    uint32_t hash32C     = 2166136261;
    const char *p = str;
    
	for(; wrdlen >= 3 * 2 * sizeof(uint32_t); wrdlen -= 3 * 2 * sizeof(uint32_t), p += 3 * 2 * sizeof(uint32_t)) 
	{
		hash32  = (hash32  ^ (_rotl_KAZE(*(uint32_t *)(p+0),  5) ^ *(uint32_t *)(p+4))) * PRIME;       
		hash32B = (hash32B ^ (_rotl_KAZE(*(uint32_t *)(p+8),  5) ^ *(uint32_t *)(p+12))) * PRIME;       
		hash32C = (hash32C ^ (_rotl_KAZE(*(uint32_t *)(p+16), 5) ^ *(uint32_t *)(p+20))) * PRIME;            
	}

	if (p != str) 
	{
		hash32 = (hash32 ^ _rotl_KAZE(hash32C, 5) ) * PRIME;
	}

    // 1111=15; 10111=23
	if (wrdlen & 4 * sizeof(uint32_t)) 
	{         
		hash32  = (hash32  ^ (_rotl_KAZE(*(uint32_t *)(p+0), 5) ^ *(uint32_t *)(p+4)))  * PRIME;       
		hash32B = (hash32B ^ (_rotl_KAZE(*(uint32_t *)(p+8), 5) ^ *(uint32_t *)(p+12))) * PRIME;       
		p += 8 * sizeof(uint16_t);
	}

    // Cases: 0,1,2,3,4,5,6,7,...,15

	if (wrdlen & 2 * sizeof(uint32_t)) 
	{
		hash32  = (hash32  ^ *(uint32_t*)(p+0)) * PRIME;
		hash32B = (hash32B ^ *(uint32_t*)(p+4)) * PRIME;
		p += 4 * sizeof(uint16_t);
	}

    // Cases: 0,1,2,3,4,5,6,7

	if (wrdlen & sizeof(uint32_t)) 
	{
		hash32  = (hash32  ^ *(uint16_t*)(p+0)) * PRIME;
		hash32B = (hash32B ^ *(uint16_t*)(p+2)) * PRIME;
		p += 2 * sizeof(uint16_t);
	}

    if (wrdlen & sizeof(uint16_t)) 
    {
        hash32 = (hash32 ^ *(uint16_t*)p) * PRIME;
        p += sizeof(uint16_t);
    }

    if (wrdlen & 1)
        hash32 = (hash32 ^ *p) * PRIME;

    hash32 = (hash32 ^ _rotl_KAZE(hash32B, 5) ) * PRIME;

    return hash32 ^ (hash32 >> 16);
}
