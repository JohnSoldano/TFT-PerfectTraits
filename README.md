<u><b> Summary </b></u>

Team Fight Tactics (TFT) is an auto battler game developed and published by Riot Games. Players compete online against seven other opponents by building a team to be the last one standing.

A team is created from a pool of units.
Each unit has a set of traits, which provide bonuses for a team.
A trait bonus only applies to a team if a team has enough units of a specific trait.

An end-game team will typically consist of 8 units.



<u><b> Problem </b></u>
Assume a team consists of 8 units and there are 59 units to select from. Which combination of 8 units will result in a team without any partial traits?

This a problem of Combinatorics and Constraint Satisfaction.

There are 59 choose 8 (2,217,471,399) possible team combinations.

[2024/01/11] - The current process enumerates all possible combinations of units and creates a team. The team is only saved if all conditions have been satisfied. This is known as a Brute-Force search. The time taken to check all 2 billion combinations is expected to take approximately 4 days (my specs). In attempts to optimize this process, code will be added to compare (TBD) constraint satisfaction problem solving techniques, matching algorithms and backtracking algorithms.
