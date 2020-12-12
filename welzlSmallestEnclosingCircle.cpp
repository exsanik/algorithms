#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

class Point {
 private:
  double xCoord, yCoord;

 public:
  Point() : xCoord(0), yCoord(0) {}
  Point(double xCoord, double yCoord) : xCoord(xCoord), yCoord(yCoord) {}

  double distance(const Point& point) const {
    return sqrt(pow(this->xCoord - point.xCoord, 2) +
                pow(this->yCoord - point.yCoord, 2));
  }

  double getX() { return this->xCoord; }
  double getY() { return this->yCoord; }

  friend class Circle;
};

Point calcCircleCenter(double ax, double ay, double bx, double by) {
  double powerA = ax * ax + ay * ay;
  double powerB = bx * bx + by * by;
  double aB = ax * by - ay * bx;
  return Point((by * powerA - ay * powerB) / (2 * aB),
               (ax * powerB - bx * powerA) / (2 * aB));
}

class Circle {
 private:
  Point center;
  double radius;

 public:
  Circle() : radius(0) {}

  Circle(const Point& center, double radius) : center(center), radius(radius) {}

  Circle(const Point& pointA, const Point& pointB) {
    Point center((pointA.xCoord + pointB.xCoord) / 2.0,
                 (pointA.yCoord + pointB.yCoord) / 2.0);

    this->center = center;
    this->radius = pointA.distance(pointB) / 2.0;
  }

  Circle(const Point& pointA, const Point& pointB, const Point& pointC) {
    Point center = calcCircleCenter(
        pointB.xCoord - pointA.xCoord, pointB.yCoord - pointA.yCoord,
        pointC.xCoord - pointA.xCoord, pointC.yCoord - pointA.yCoord);

    center.xCoord += pointA.xCoord;
    center.yCoord += pointA.yCoord;

    this->center = center;
    this->radius = center.distance(pointA);
  }

  Point getCenter() { return this->center; }

  double getRadius() { return this->radius; }

  bool contains(const Point& point) {
    return point.distance(this->center) <= this->radius;
  }

  bool isValid(const std::vector<Point>& points) {
    for (const Point& point : points) {
      if (!this->contains(point)) return false;
    }
    return true;
  }
};

Circle minCircleBrute(const std::vector<Point>& points) {
  if (points.empty()) {
    return Circle();
  } else if (points.size() == 1) {
    return Circle(points[0], 0);
  } else if (points.size() == 2) {
    return Circle(points[0], points[1]);
  }

  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 3; ++j) {
      Circle circle(points[i], points[j]);

      if (circle.isValid(points)) return circle;
    }
  }

  return Circle(points[0], points[1], points[2]);
}

Circle welzl_helper(std::vector<Point>* points,
                    std::vector<Point> pointsOnRadius, int size) {
  if (size == 0 || pointsOnRadius.size() == 3) {
    return minCircleBrute(pointsOnRadius);
  }

  int randomIndex = rand() % size;
  Point randomPoint = points->at(randomIndex);

  std::swap((*points)[randomIndex], (*points)[size - 1]);

  Circle possibleCircle = welzl_helper(points, pointsOnRadius, size - 1);

  if (possibleCircle.contains(randomPoint)) {
    return possibleCircle;
  }

  pointsOnRadius.push_back(randomPoint);

  return welzl_helper(points, pointsOnRadius, size - 1);
}

Circle welzl(std::vector<Point>* points) {
  std::random_shuffle(points->begin(), points->end());
  return welzl_helper(points, {}, points->size());
}

int main() {
  int pointsAmount;
  std::cin >> pointsAmount;

  std::vector<Point> points(pointsAmount);
  for (int i = 0; i < pointsAmount; ++i) {
    int xCoord, yCoord;
    std::cin >> xCoord >> yCoord;
    points[i] = Point(xCoord, yCoord);
  }

  Circle mec = welzl(&points);
  std::cout << mec.getCenter().getX() << " " << mec.getCenter().getY()
            << std::endl;
  std::cout << std::fixed << std::showpoint << std::setprecision(9)
            << mec.getRadius() << std::endl;

  return 0;
}