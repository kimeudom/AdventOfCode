# flake8: noqa: F811
import pathlib
from typing import TypeAlias, Callable

Motion: TypeAlias = tuple[str, int]
Position: TypeAlias = tuple[int, int]
Rope: TypeAlias = list[Position]


def main():
    with open(pathlib.Path(__file__).parent.parent / "1/test.csv") as file:
        motions = []
        for line in file:
            direction, distance = line.split()
            motions.append((direction, int(distance)))

    model_rope(motions, [(0, 0) for _ in range(2)])
    model_rope(motions, [(0, 0) for _ in range(10)])


def model_rope(motions: list[Motion], rope: Rope):
    tail_positions = {rope[-1]}
    for motion in motions:
        direction, moves = motion

        match direction:
            case "U":

                def next_pos(head: Position) -> Position:
                    return (head[0] + 1, head[1])

            case "D":

                def next_pos(head: Position) -> Position:
                    return (head[0] - 1, head[1])

            case "R":

                def next_pos(head: Position) -> Position:
                    return (head[0], head[1] + 1)

            case "L":

                def next_pos(head: Position) -> Position:
                    return (head[0], head[1] - 1)

        move(rope, moves, next_pos, tail_positions)
    print(len(tail_positions))
    # print(tail_positions)


def move(
    rope: Rope,
    moves: int,
    next_pos: Callable[[Position], Position],
    tail_positions: set[Position],
):
    for _ in range(moves):
        rope[0] = next_pos(rope[0])
        for i in range(1, len(rope)):
            head, tail = rope[i - 1], rope[i]
            if distance(head, tail) > 1:
                # right
                if head[0] == tail[0] and head[1] > tail[1]:
                    tail = tail[0], tail[1] + 1
                # left
                elif head[0] == tail[0] and head[1] < tail[1]:
                    tail = tail[0], tail[1] - 1
                # up
                elif head[0] > tail[0] and head[1] == tail[1]:
                    tail = tail[0] + 1, tail[1]
                # down
                elif head[0] < tail[0] and head[1] == tail[1]:
                    tail = tail[0] - 1, tail[1]
                # up right
                elif head[0] > tail[0] and head[1] > tail[1]:
                    tail = tail[0] + 1, tail[1] + 1
                # up left
                elif head[0] > tail[0] and head[1] < tail[1]:
                    tail = tail[0] + 1, tail[1] - 1
                # down right
                elif head[0] < tail[0] and head[1] > tail[1]:
                    tail = tail[0] - 1, tail[1] + 1
                # down left
                elif head[0] < tail[0] and head[1] < tail[1]:
                    tail = tail[0] - 1, tail[1] - 1
                rope[i] = tail

        tail_positions.add(rope[-1])


def distance(head: Position, tail: Position) -> int:
    x1, y1 = head
    x2, y2 = tail
    return max(abs(x2 - x1), abs(y2 - y1))


if __name__ == "__main__":
    main()
