# Football Management System (FMS)

A console-based C application for managing football teams and player
statistics. It loads team/player data from a text file, lets you add players
and update stats interactively through a menu, and computes summary
statistics (top scorer, best defense, most minutes played) on save.

## Files

| File                        | Purpose                                              |
|-----------------------------|-------------------------------------------------------|
| `Assingment codes/0112320015.1.c` | Main source: `Team`/`Player` structs and the menu-driven program |
| `Assingment codes/football_database.txt` | Team/player data store, loaded on startup and rewritten on save |
| `Assingment codes/stats.txt`      | Generated summary statistics, written when data is saved |

## Build

```bash
cd "Assingment codes"
gcc 0112320015.1.c -o fms
```

## Run

```bash
./fms
```

## Menu options

1. **Add a player** — add a player to a team (creates the team if it's new)
2. **Display Team information** — show all players and stats for a team
3. **Update team information** — apply a player's stats to their team's totals
4. **Show Statistics** — print top scorer, best defense, and most minutes played across all teams
5. **Save Team** — write teams back to `football_database.txt` and regenerate `stats.txt`
6. **Exit**

## Data format

`football_database.txt` stores one team per block: a line with `<teamName> <numPlayers>`,
followed by one line per player: `<name> <number> <position> <goalsScored> <goalsConceded> <minutesPlayed>`.
