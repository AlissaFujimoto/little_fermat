#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_prime16(uint32_t n)
{
  if (n < 2)
  {
    return false;
  }
  if (n == 2 || n == 3)
  {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0)
  {
    return false;
  }
  for (uint32_t i = 5; i * i <= n; i += 6)
  {
    if (n % i == 0 || n % (i + 2) == 0)
    {
      return false;
    }
  }
  return true;
}

uint64_t pow_mod_64(uint64_t base, uint64_t exp, uint64_t m)
{
  uint64_t res = 1;
  base %= m;
  while (exp > 0)
  {
    if (exp & 1)
    {
      res = (res * base) % m;
    }
    base = (base * base) % m;
    exp >>= 1;
  }
  return res;
}

int main(void)
{
  uint32_t max_p = UINT16_MAX;
  uint32_t count = 0;

  printf("Initializing Wieferich Hunter...\n");

  for (uint32_t p = 3; p <= max_p; p += 2)
  {
    if (is_prime16(p))
    {
      uint64_t p64 = p;
      uint64_t p2 = p64 * p64;
      uint64_t p_minus_1 = p64 - 1;

      uint64_t res = pow_mod_64(2, p_minus_1, p2);

      if (res == 1)
      {
        printf(">>> WIEFERICH PRIME FOUND: %u <<<\n", p);
        count++;
      }
    }
  }

  printf("\n--- SEARCH COMPLETE ---\n");
  printf("Total Wieferich Primes found under %d: %u\n", UINT16_MAX, count);

  return 0;
}
