//
// Created by Dean Butcher on 2021-10-24.
//

#include <cstdio>

typedef unsigned int uint;

const uint TOTAL_BAR_LENGTH = 30;

void UpdateProgress(const uint pct, const uint size) {
  const uint BARCOUNT = (pct + 1) * TOTAL_BAR_LENGTH / 100;

  std::printf("\rShuffling Deck: [");

  for(uint i = 0; i < BARCOUNT; i++) {
    std::printf("=");
  }

  const uint BLANK_COUNT = TOTAL_BAR_LENGTH - BARCOUNT;

  for(uint j = 0; j < BLANK_COUNT; j++) {
    std::printf(" ");
  }

  std::printf("] %d%% for %d cards", (pct == 0 ? 0 : pct + 1), size);

  std::fflush(stdout);
}