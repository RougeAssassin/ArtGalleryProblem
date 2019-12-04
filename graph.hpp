#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

using std::vector;
using std::cout;
using std::ostream;

enum Color { None, Red, Yellow, Blue };

struct Point // A tuple containing two ints
{
    int x, y;
    friend bool operator== (const Point &lhs, const Point &rhs);
};

struct Edge // A tuple containing two Points
{
  Point src, dest;
  float slope, intercept;
  friend bool operator== (const Edge &lhs, const Edge &rhs);
  friend ostream& operator<< (ostream &os, const Edge &e);
  void setSlope(float item){ slope = item;}
  void setIntercept(float item){intercept = item;}
};

struct Vertex // A Point which is connected to one or more other points
{
    Point src;
    vector<Point> dest;
    int color = Color(None);

    inline Vertex& operator= (const Vertex &rhs);
    friend ostream& operator<< (ostream &os, const Vertex &v);
};

double dot(Point a, Point b, Point c) {
    int segment1_x = a.x-b.x, segment1_y = a.y-b.y;
    int segment2_x = c.x-b.x, segment2_y = c.y-b.y;
    return (segment1_x*segment2_x + segment1_y*segment2_y);
}

class Graph // The actual graph structure
{
private:
    vector<Vertex> m_adjList;
    vector<Edge> m_edgeList;
protected:
    void linkVerticesUtil(const Edge &edge, bool toggleRecursion = true);
    double interiorAngle(Point a, Point b, Point c) const; // returns interior angle ABC
    bool midpointInGraph(Point a, Point b) const;
public:
    Graph(vector<Edge> &edge);
    Vertex * findVertex(const Point &point);
    void linkVertices(const Edge &edge);
    bool isClosed(); // A method to check whether a graph is closed
    void triangulate();
    friend ostream& operator<< (ostream &os, const Graph &obj);
    float getIntercept(Edge edge);
    float getSlope(Edge edge);
    bool hasIntercept(Edge edge1, Edge edge2);
};

/*
 *
 * Function Definitions
 *
 */

bool operator== (const Point &lhs, const Point &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator== ( const Edge &lhs, const Edge &rhs) {
    return (lhs.src == rhs.src && lhs.dest == rhs.dest);
}

Graph::Graph(vector<Edge> &edges)
{
  for (size_t i = 0; i < edges.size(); i++)
  {
      edges[i].setSlope(getSlope(edges[i]));
      edges[i].setIntercept(getIntercept(edges[i]));
      m_edgeList.push_back(edges[i]);
      linkVertices(edges[i]);
  }
}

Vertex * Graph::findVertex(const Point &point) {
    for (size_t i = 0; i < m_adjList.size(); i++) {
        if (m_adjList[i].src == point)
            return &m_adjList[i];
    }
    return nullptr;
}

void Graph::linkVertices(const Edge &edge) {
    linkVerticesUtil(edge);
}

bool Graph::midpointInGraph(Point a, Point b) const {
    int counter = 0;
    int i, N = m_adjList.size();
    double xinters;
    Point p1,p2;

    double mid_x = (a.x + b.x)/2, mid_y = (a.y + b.y)/2;

    p1 = m_adjList[0].src;
    for (i = 1; i <= N; i++) {
        p2 = m_adjList[i % N].src;
        if (mid_y > MIN(p1.y,p2.y)) {
            if (mid_y <= MAX(p1.y,p2.y)) {
                if (mid_y <= MAX(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (mid_y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || mid_y <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    return (counter % 2 == 0)? false : true;
}

double Graph::interiorAngle(Point a, Point b, Point c) const {
    int segment1_x = a.x-b.x, segment1_y = a.y-b.y;
    int segment2_x = c.x-b.x, segment2_y = c.y-b.y;
    double segment1 = sqrt(pow(segment1_x, 2) + pow(segment1_y, 2));
    double segment2 = sqrt(pow(segment2_x, 2) + pow(segment2_y, 2));

    double theta = acos(dot(a,b,c) / (segment1*segment2));
    return (midpointInGraph(a,c))? theta : (360-theta);
}

void Graph::linkVerticesUtil(const Edge &edge, bool toggleRecursion) {
    // Check for vertex in graph with src == edge.src
    if (findVertex(edge.src)) {
        for (size_t i = 0; i < m_adjList.size(); i++) {
            if (m_adjList[i].src == edge.src) {
                m_adjList[i].dest.push_back(edge.dest);
            }
        }
    } else {
        Vertex newVertex;
        newVertex.src = edge.src;
        newVertex.dest.push_back(edge.dest);
        m_adjList.push_back(newVertex);
    }

    if (toggleRecursion) {
        linkVerticesUtil(Edge { edge.dest , edge.src }, false);
    }
}

// WIP
// void Graph::triangulate() {

// }

ostream& operator<< (ostream &os, const Vertex &v) {
    os << "{ " << v.src.x << " , " << v.src.y << " } --> ";
    for (size_t i = 0; i < v.dest.size(); i++)
        os << "{ " << v.dest[i].x << " , " << v.dest[i].y << " } ";

    return os;
}

ostream& operator<< (ostream &os, const Graph &obj) {
    for(size_t i = 0; i < obj.m_adjList.size(); i++) {
        os << obj.m_adjList[i];
        os << obj.m_edgeList[i];
        os << '\n';
    }

    return os;
}
ostream& operator<< (ostream &os, const Edge &e) {
  os << "{ " << e.src.x << " , " << e.src.y << " } --> ";
  os << "{ " << e.dest.x << " , " << e.dest.y << " } ";
  os << "Slope: " << e.slope << ", Intercept: " << e.intercept;


  return os;
}
bool Graph::hasIntercept(Edge edge1, Edge edge2)
{
  float x, MIN1, MAX1, MIN2, MAX2;
  if((edge1.slope - edge2.slope) != 0)
    x = (edge2.intercept - edge1.intercept)/(edge1.slope - edge2.slope);
  else
    return false;
  float y = (edge1.slope*x + edge1.intercept);
  cout << "(" << x << ", " << y << ")\n";

  MIN1 = MIN(edge1.src.x, edge1.dest.x);
  MAX1 = MAX(edge1.src.x, edge1.dest.x);

  MIN2 = MIN(edge2.src.x, edge2.dest.x);
  MAX2 = MAX(edge2.src.x, edge2.dest.x);

  if(MIN1 > x || x > MAX1 || MIN2 > x || x > MAX2)
    return false;
  else
    return true;
}
float Graph::getSlope(Edge edge)
{
  if((edge.dest.x-edge.src.x) != 0)
    return ((edge.dest.y-edge.src.y)/(edge.dest.x-edge.src.x));
}
float Graph::getIntercept(Edge edge)
{
  return (edge.src.y-(edge.src.x*edge.slope));
}

#endif //GRAPH_HPP_
