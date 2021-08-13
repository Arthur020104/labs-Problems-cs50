import csv
import sys
import random

# Numero de simulacoes para rodar
N = 1000


def main():

    # Garante usagem correta
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(f"{sys.argv[1]}", "r") as file:
        reader = csv.reader(file)
        next(reader)
        for row in reader:
            team = {
            "Country" : row[0],
            "rating" : int(row[1])
            }
            teams.append(team)

    counts = {}
    for i in range(len(teams)):
        counts[teams[i]["Country"]] = 0
    for i in range(N):
        winner = (simulate_tournament(teams))
        counts[winner["Country"]] += 1

    # simula N torneios e guarda quantidade de vitoriasa

    # printa as chacnce de vitoria de cada time(de acordo com o codigo)
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")



def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simula jogos para todos os pares de times
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while True:
        teams = simulate_round(teams)
        if len(teams) == 2:
            if simulate_game(teams[0], teams[1]):
                return teams[0]
            else:
                return teams[1]


if __name__ == "__main__":
    main()