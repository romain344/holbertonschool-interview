#!/usr/bin/python3
"""Minimum operations module"""


def minOperations(n):
    """Return fewest operations to reach exactly n H characters."""
    if n < 2:
        return 0
    ops = 0
    divisor = 2
    while n > 1:
        while n % divisor == 0:
            ops += divisor
            n //= divisor
        divisor += 1
    return ops
