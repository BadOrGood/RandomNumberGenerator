#include <stdio.h>
#include <windows.h>

static ULONG64 qwSeed;

static ULONG Random(VOID) {
  ULONG32 dwOutput = 0;

  while (!dwOutput || dwOutput == -1) {
    for (ULONG_PTR i = 0; i < 32; i += 4) {
      ULONG dwValue = 0;

      for (ULONG_PTR y = 0; y != 32; y += 8) {
        qwSeed += qwSeed % 31;

        dwValue |= (qwSeed % 256) << y;
      }

      dwOutput |= (dwValue % 31) << i;
    }
  }

  return dwOutput;
}

int main() {
  qwSeed = GetTickCount64();

  for (ULONG_PTR i = 0; i != 32; i++) {
    ULONG dwValue = Random();

    printf("%08lX %lu\n", dwValue, dwValue & 0x1);
  }

  return 0;
}
