#!/usr/bin/python3
"""
Module to check if all boxes can be opened
"""


def canUnlockAll(boxes):
    """Determines if all boxes can be opened"""
    n = len(boxes)
    opened = set([0])
    keys = [0]

    while keys:
        current = keys.pop()

        for key in boxes[current]:
            if key < n and key not in opened:
                opened.add(key)
                keys.append(key)

    return len(opened) == n