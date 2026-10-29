
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player
{
    char playerName[50];
    int playerNumber;
    char playerPosition[10];
    int goalsScored;
    int goalsConceded;
    int minutes_played;
};

struct Team
{
    char teamName[50];
    struct Player players[20];
    int numPlayers;
    int goalsScored;
    int goalsConceded;
};

void loadTeamsFromFile(struct Team *teams, int *numTeams)
{
    FILE *file = fopen("football_database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    *numTeams = 0;
    while (fscanf(file, "%s %d", teams[*numTeams].teamName, &teams[*numTeams].numPlayers) == 2)
    {
        int i = 0;
        while (i < teams[*numTeams].numPlayers)
        {
            fscanf(file, "%s %d %s %d %d %d ", teams[*numTeams].players[i].playerName,
                   &teams[*numTeams].players[i].playerNumber, teams[*numTeams].players[i].playerPosition,
                   &teams[*numTeams].players[i].goalsScored, &teams[*numTeams].players[i].goalsConceded,
                   &teams[*numTeams].players[i].minutes_played);
            teams[*numTeams].goalsScored += teams[*numTeams].players[i].goalsScored;
            teams[*numTeams].goalsConceded += teams[*numTeams].players[i].goalsConceded;
            i++;
        }

        (*numTeams)++;
    }

    fclose(file);
}

void saveTeamsToFile(struct Team *teams, int numTeams)
{
    FILE *file = fopen("football_database.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    int i = 0;
    while (i < numTeams)
    {
        fprintf(file, "%s %d\n", teams[i].teamName, teams[i].numPlayers);

        int j = 0;
        while (j < teams[i].numPlayers)
        {
            fprintf(file, "%s %d %s %d %d %d\n", teams[i].players[j].playerName, teams[i].players[j].playerNumber,
                    teams[i].players[j].playerPosition, teams[i].players[j].goalsScored, teams[i].players[j].goalsConceded,
                    teams[i].players[j].minutes_played);
            j++;
        }

        i++;
    }

    fclose(file);

    int mg = -1;
    int lgc = 9999;
    char mgTeam[50];
    char lgcTeam[50];
    char m[50];
    int maxplay = -100;
    char maxMinutesPlayerName[50];

    i = 0;
    while (i < numTeams)
    {
        if (teams[i].goalsScored > mg)
        {
            mg = teams[i].goalsScored;
            strcpy(mgTeam, teams[i].teamName);
        }

        if (teams[i].goalsConceded < lgc)
        {
            lgc = teams[i].goalsConceded;
            strcpy(lgcTeam, teams[i].teamName);
        }
        i++;
    }

    i = 0;
    while (i < numTeams)
    {
        int j = 0;
        while (j < teams[i].numPlayers)
        {
            if (teams[i].players[j].minutes_played > maxplay)
            {
                maxplay = teams[i].players[j].minutes_played;
                strcpy(maxMinutesPlayerName, teams[i].players[j].playerName);
                strcpy(m, teams[i].teamName);
            }
            j++;
        }
        i++;
    }

    FILE *statsFile = fopen("stats.txt", "w");
    if (statsFile == NULL)
    {
        printf("Error opening stats file for writing.\n");
        return;
    }

    fprintf(statsFile, "Most Goals Scored: %s (%d goals)\n", mgTeam, mg);
    fprintf(statsFile, "Least Goals Conceded: %s (%d goals)\n", lgcTeam, lgc);
    fprintf(statsFile, "Player with the Maximum Minutes Played: %s (%d minutes) from %s\n", maxMinutesPlayerName, maxplay, m);

    fclose(statsFile);
}

void addPlayerToTeam(struct Team *team, struct Player *player)
{
    if (team->numPlayers < 20)
    {
        team->players[team->numPlayers] = *player;
        team->goalsScored += player->goalsScored;
        team->goalsConceded += player->goalsConceded;
        team->numPlayers++;

        printf("Player added to the team successfully.\n");
    }
    else
    {
        printf("Cannot add more players to the team. Maximum limit reached.\n");
    }
}

void displayTeam(struct Team *team)
{
    printf("Team Name: %s\n", team->teamName);
    printf("Number of Players: %d\n", team->numPlayers);

    printf("Players:\n");
    int i = 0;
    while (i < team->numPlayers)
    {
        printf("Player %d:\n", i + 1);
        printf("Name: %s\n", team->players[i].playerName);
        printf("Number: %d\n", team->players[i].playerNumber);
        printf("Position: %s\n", team->players[i].playerPosition);
        printf("Goals Scored: %d\n", team->players[i].goalsScored);
        printf("Goals Conceded: %d\n", team->players[i].goalsConceded);
        printf("Minutes Played: %d\n", team->players[i].minutes_played);
        printf("\n");
        i++;
    }
}

void displayPlayer(struct Player *player)
{
    printf("Player Name: %s\n", player->playerName);
    printf("Number: %d\n", player->playerNumber);
    printf("Position: %s\n", player->playerPosition);
    printf("Goals Scored: %d\n", player->goalsScored);
    printf("Goals Conceded: %d\n", player->goalsConceded);
    printf("Minutes Played: %d\n", player->minutes_played);
}

void updateTeamInfo(struct Team *team, struct Player *player)
{
    if (strcmp(player->playerPosition, "MID") == 0 || strcmp(player->playerPosition, "FWD") == 0)
    {
        team->goalsScored += player->goalsScored;
    }
    else if (strcmp(player->playerPosition, "DEF") == 0)
    {
        team->goalsConceded += player->goalsConceded;
    }
}

void displayStatistics(struct Team *teams, int numTeams)
{
    int mg = -1;
    int lgc = 9999;
    char mgTeam[50];
    char lgcTeam[50];
    char m[50];
    int maxplay = -1;
    char maxMinutesPlayerName[50];

    int i = 0;
    while (i < numTeams)
    {
        if (teams[i].goalsScored > mg)
        {
            mg = teams[i].goalsScored;
            strcpy(mgTeam, teams[i].teamName);
        }

        if (teams[i].goalsConceded < lgc)
        {
            lgc = teams[i].goalsConceded;
            strcpy(lgcTeam, teams[i].teamName);
        }
        i++;
    }

    i = 0;
    while (i < numTeams)
    {
        int j = 0;
        while (j < teams[i].numPlayers)
        {
            if (teams[i].players[j].minutes_played > maxplay)
            {
                maxplay = teams[i].players[j].minutes_played;
                strcpy(maxMinutesPlayerName, teams[i].players[j].playerName);
                strcpy(m, teams[i].teamName);
            }
            j++;
        }
        i++;
    }

    printf("Most Goals Scored: %s (%d goals)\n", mgTeam, mg);
    printf("Least Goals Conceded: %s (%d goals)\n", lgcTeam, lgc);
    printf("Player with the Maximum Minutes Played: %s (%d minutes) from %s\n", maxMinutesPlayerName, maxplay, m);
}

int main()
{
    struct Team footballTeams[10];
    int numTeams = 0;
    loadTeamsFromFile(footballTeams, &numTeams);
    int count;

    int choice;
    while (1)
    {
        printf("----------------------------------------------------------------------\n");
        printf("----------Welcome to Football Management System (FMS)-----------------\n");
        printf("----------------------------------------------------------------------\n\n");
        printf("Menu:\n1.Add a player\n2.Display Team information\n3.Update team information\n4.Show Statistics\n5.Save Team\n6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            struct Player newPlayer;
            printf("Enter player details:\n");
            printf("Name: ");
            scanf("%s", newPlayer.playerName);
            printf("Number: ");
            scanf("%d", &newPlayer.playerNumber);
            printf("Position : ");
            scanf("%s", newPlayer.playerPosition);
            printf("Goals Scored: ");
            scanf("%d", &newPlayer.goalsScored);
            printf("Goals Conceded: ");
            scanf("%d", &newPlayer.goalsConceded);
            printf("Minutes Played: ");
            scanf("%d", &newPlayer.minutes_played);

            int teamIndex;
            printf("Enter team number  : ");
            scanf("%d", &teamIndex);
            printf("the name of the team :");
            scanf("%s", footballTeams[teamIndex - 1].teamName);

            if (teamIndex > numTeams)
            {
                numTeams++;
            }

            addPlayerToTeam(&footballTeams[teamIndex - 1], &newPlayer);
            break;
        }
        case 2:
        {
            int teamIndex;
            printf("Enter team number : ");
            scanf("%d", &teamIndex);

            displayTeam(&footballTeams[teamIndex - 1]);
            break;
        }
        case 3:
        {
            struct Player playerToUpdate;
            printf("Enter player details for updating team statistics:\n");
            printf("Name: ");
            scanf("%s", playerToUpdate.playerName);
            printf("Number: ");
            scanf("%d", &playerToUpdate.playerNumber);
            printf("Position (MID/FWD/DEF): ");
            scanf("%s", playerToUpdate.playerPosition);
            printf("Goals Scored: ");
            scanf("%d", &playerToUpdate.goalsScored);
            printf("Goals Conceded: ");
            scanf("%d", &playerToUpdate.goalsConceded);
            printf("Minutes Played: ");
            scanf("%d", &playerToUpdate.minutes_played);

            int teamIndex;
            printf("Enter team number : ");
            scanf("%d", &teamIndex);

            updateTeamInfo(&footballTeams[teamIndex - 1], &playerToUpdate);
            break;
        }
        case 4:
            displayStatistics(footballTeams, numTeams);
            break;
        case 5:
            saveTeamsToFile(footballTeams, numTeams);
            printf("Data saved to file successfully.\n");
            break;
        case 6:
            printf("Thanks for using our System!!!\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}
