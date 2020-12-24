#include "days_private.h"

using namespace std;

namespace day11 {
   string getAdjacentSeats(vector<string>* map, uint x, uint y) {
      string seats;
      if (x > 0 && y > 0)
         seats.push_back(map->at(y - 1).at(x - 1));
      if (y > 0)
         seats.push_back(map->at(y - 1).at(x));
      if (x < map->at(x).size() - 1 && y > 0)
         seats.push_back(map->at(y - 1).at(x + 1));

      if (x > 0)
         seats.push_back(map->at(y).at(x - 1));
      if (x < map->at(x).size() - 1)
         seats.push_back(map->at(y).at(x + 1));

      if (x > 0 && y < map->size() - 1)
         seats.push_back(map->at(y + 1).at(x - 1));
      if (y < map->size() - 1)
         seats.push_back(map->at(y + 1).at(x));
      if (x < map->at(x).size() -1 && y < map->size() - 1)
         seats.push_back(map->at(y + 1).at(x + 1));
      
      return seats;
   }

   bool needsSwap(vector<string>* map, uint x, uint y) {
      auto seat = map->at(y).at(x);
      if (seat == '.')
         return false;

      auto adjacentSeats = getAdjacentSeats(map, x, y);
      if (seat == 'L' && adjacentSeats.find('#') == string::npos)
         return true;

      auto occupiedSeats = count(adjacentSeats.begin(), adjacentSeats.end(), '#');
      if (seat == '#' && occupiedSeats >= 4)
         return true;

      return false;
   }

   void runRounds(vector<string>* map) {
      vector<pair<int, int>> swaps;
      for (auto y = 0U; y < map->size(); y++)
         for (auto x = 0U; x < map->at(y).size(); x++)
            if (needsSwap(map, x, y))
               swaps.push_back(make_pair(x, y));

      if (swaps.size() == 0)
         return;

      for (const auto& swap : swaps)
         map->at(swap.second).at(swap.first) = map->at(swap.second).at(swap.first) == '#' ? 'L' : '#';

      return runRounds(map);
   }

   TEST_CASE("Day 11 - Part 1 from https://adventofcode.com/2020/day/11") {
      auto mapData = util::loadInputFile("day11-input.txt");

      runRounds(&mapData);
      auto result = accumulate(mapData.begin(), mapData.end(), 0U,
         [](const auto sum, auto& line) {
            return sum + count(line.begin(), line.end(), '#');
         });
      
      REQUIRE(result == 2283);
   }
}
