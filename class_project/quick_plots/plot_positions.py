""" Just a quick helper script, to plot the positions of planets/particles,
for debugging the orbital mechanics class project.
"""
from sys import argv
import matplotlib.pyplot as plt


def main():
    file_path = argv[1]
    positions_3d = read_positions(file_path)
    x = [p[0] for p in positions_3d]
    y = [p[1] for p in positions_3d]
    plt.scatter(x, y)
    plt.show()


def read_positions(file_path):
    lines = open(file_path, 'r').read().strip().replace('(', '').replace(')', '').replace(' ', '').split('\n')[1:]
    return [[float(v.strip()) for v in line.split(',')] for line in lines]


if __name__ == '__main__':
    main()

