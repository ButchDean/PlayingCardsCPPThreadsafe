//
// Created by Dean Butcher on 2021-10-24.
//

#include <cstdio>

typedef unsigned int uint;

const uint TOTAL_BAR_LENGTH = 30;

void UpdateProgress(int pct) {
  const uint barcount = pct * TOTAL_BAR_LENGTH / 100;

  std::printf("\r[");

  for(uint i = 0; i < TOTAL_BAR_LENGTH; i++) {
    std::printf("#");
  }

  const uint BLANK_COUNT = TOTAL_BAR_LENGTH - barcount;

  for(uint j = 0; j < BLANK_COUNT; j++) {
    std::printf(" ");
  }

  std::printf("] %d%% Shuffled", pct);

  std::fflush(stdout);
}