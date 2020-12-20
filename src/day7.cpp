#include <iostream>
#include <algorithm>
#include "../inc/catch_amalgamated.hpp"
#include "util.h"

using namespace std;

namespace day7 {
   unordered_map<string, vector<pair<uint, string>>> loadRules() {
      auto rulesInput = util::loadInputFile("day7-input.txt");

      unordered_map<string, vector<pair<uint, string>>> rules;
      transform(rulesInput.begin(), rulesInput.end(), inserter(rules, rules.end()),
         [](const auto& ruleLine) {
            auto elements = util::split(ruleLine, ' ');
            auto key = elements.at(0) + "-" + elements.at(1);

            static const string containKeyword = " contain ";
            auto contains = ruleLine.substr(ruleLine.find(containKeyword) + containKeyword.size());
            auto splitted = util::split(contains, ',');

            vector<pair<uint, string>> luagages;
            transform(splitted.begin(), splitted.end(), inserter(luagages, luagages.end()),
               [](const auto& value){
                  auto splitted = util::split(value, ' ');

                  return make_pair(
                     splitted.at(0) == "no" ? 0 : stoi(splitted.at(0)),
                     splitted.at(splitted.size() - 3) + "-" + splitted.at(splitted.size() - 2));
               });

            return make_pair(key, luagages);
      });
      
      return rules;
   }

   bool containsShinyGoldBag(const unordered_map<string, vector<pair<uint, string>>>* rules, const string bag) {
      auto it = rules->find(bag);
      if (it == rules->end())
         return false;

      for (const auto& luagage : it->second)
         if (luagage.second == "shiny-gold")
            return true;
         else
            if (containsShinyGoldBag(rules, luagage.second))
               return true;

      return false;
   }

   uint day7Part1() {
      cout << "Day 7 - Part 1 from https://adventofcode.com/2020/day/7" << endl;

      auto rules = loadRules();

      return count_if(rules.begin(), rules.end(),
         [rules](const auto& rule) {
            return containsShinyGoldBag(&rules, rule.first);
         });
   }

   TEST_CASE("Day 7 - Part 1") {
      REQUIRE(day7Part1() == 268);
   }

   uint countBags(const unordered_map<string, vector<pair<uint, string>>>* rules, const string bag) {
      auto it = rules->find(bag);
      if (it == rules->end())
         return 0;
     
      return accumulate(it->second.begin(), it->second.end(), 0U,
         [rules](const auto sum, auto& luagage) {
            return sum + luagage.first + (luagage.first * countBags(rules, luagage.second));
         });
   }

   uint day7Part2() {
      cout << "Day 7 - Part 2 from https://adventofcode.com/2020/day/7#part2" << endl;

      auto rules = loadRules();

      return countBags(&rules, "shiny-gold");
   }

   TEST_CASE("Day 7 - Part 2") {
      REQUIRE(day7Part2() == 7867);
   }
}
