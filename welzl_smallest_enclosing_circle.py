import random
import sys

sys.setrecursionlimit(10**6)


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance(self, point):
        return ((self.x - point.x) ** 2 + (self.y - point.y) ** 2) ** 0.5


def calc_circle_center(ax, ay, bx, by):
    p_a = ax * ax + ay * ay
    p_b = bx * bx + by * by
    a_b = ax * by - ay * bx
    return Point((by * p_a - ay * p_b) / (2 * a_b),
                 (ax * p_b - bx * p_a) / (2 * a_b))


class Circle:
    def __init__(self, center, radius):
        self.center = center
        self.radius = radius

    def contains(self, point):
        return point.distance(self.center) <= self.radius

    @classmethod
    def from_3points(cls, point_a, point_b, point_c):
        center = calc_circle_center(
            point_b.x - point_a.x, point_b.y - point_a.y,
            point_c.x - point_a.x, point_c.y - point_a.y)

        center.x += point_a.x
        center.y += point_a.y
        return cls(center, center.distance(point_a))

    @classmethod
    def from_2points(cls, point_a, point_b):
        center = Point((point_a.x + point_b.x) / 2.0,
                       (point_a.y + point_b.y) / 2.0)

        return cls(center, point_a.distance(point_b) / 2.0)

    def is_valid(self, points):
        for point in points:
            if not self.contains(point):
                return False
        return True


def min_circle_brute(points):
    if not points:
        return Circle(Point(0, 0), 0)
    elif len(points) == 1:
        return Circle(points[0], 0)
    elif len(points) == 2:
        return Circle.from_2points(*points)

    for i in range(0, 3):
        for j in range(i + 1, 3):
            circle = Circle.from_2points(points[i], points[j])
            if circle.is_valid(points):
                return circle

    return Circle.from_3points(*points)


def welzl_main(points, points_on_radius, size):
    if size == 0 or len(points_on_radius) == 3:
        return min_circle_brute(points_on_radius)

    random_index = random.randint(0, size - 1)
    random_point = points[random_index]

    points[random_index], points[size - 1] = \
        points[size - 1], points[random_index]

    possible_circle = welzl_main(points, points_on_radius.copy(), size - 1)

    if possible_circle.contains(random_point):
        return possible_circle

    points_on_radius.append(random_point)

    return welzl_main(points, points_on_radius.copy(), size - 1)


def welzl(points):
    random.shuffle(points)
    return welzl_main(points, [], len(points))


def main():
    points_amount = int(input())

    points = []
    for _ in range(points_amount):
        points.append(Point(*[int(i) for i in input().split()]))
    circle = welzl(points)

    circle = welzl(points)

    print(f"{circle.center.x} {circle.center.y}")
    print(f"{circle.radius}")


if __name__ == "__main__":
    main()
