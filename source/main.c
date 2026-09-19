#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static inline bool IsPrime16(uint32_t candidate)
{
  if (candidate < 2)
  {
    return false;
  }
  if (candidate == 2 || candidate == 3)
  {
    return true;
  }
  if (candidate % 2 == 0 || candidate % 3 == 0)
  {
    return false;
  }
  for (uint32_t factor = 5; factor * factor <= candidate; factor += 6)
  {
    if (candidate % factor == 0 || candidate % (factor + 2) == 0)
    {
      return false;
    }
  }
  return true;
}

static inline uint64_t PowMod64(uint64_t base, uint64_t exponent, uint64_t modulus)
{
  uint64_t result = 1;
  base %= modulus;
  while (exponent > 0)
  {
    if (exponent & 1)
    {
      result = (result * base) % modulus;
    }
    base = (base * base) % modulus;
    exponent >>= 1;
  }
  return result;
}

int main(void)
{
  const uint32_t maxPrime = UINT16_MAX;
  uint32_t foundCount = 0;

  printf("Initializing Wieferich Hunter...\n");

  for (uint32_t prime = 3; prime <= maxPrime; prime += 2)
  {
    if (IsPrime16(prime))
    {
      uint64_t prime64 = prime;
      uint64_t primeSq = prime64 * prime64;
      uint64_t primeMinus1 = prime64 - 1;

      uint64_t result = PowMod64(2, primeMinus1, primeSq);

      if (result == 1)
      {
        printf(">>> WIEFERICH PRIME FOUND: %" PRIu32 " <<<\n", prime);
        foundCount++;
      }
    }
  }

  printf("\n--- SEARCH COMPLETE ---\n");
  printf("Total Wieferich Primes found under %" PRIu16 ": %" PRIu32 "\n", UINT16_MAX, foundCount);

  return 0;
}
