#include <iostream>
using namespace std;

float getSlope(int x1, int x2, int y1, int y2);
float getIntercept(int x, int y, float slope);
float getSlope(int x1, int x2, float y1, float y2);
float getIntercept(int x, float y, float slope);
bool hasIntercept(float slopea, float intercepta, float slopeb, float interceptb);
float min(float x, float y);

int x1a = 1, x2a = 2, x1b = 2, x2b =3, y1a = 1, y2a = 4;
float y1b = 4.0, y2b = 2.0;

int main(){


  float slopea, slopeb, intercepta, interceptb;
  slopea = getSlope(x1a, x2a, y1a, y2a);
  slopeb = getSlope(x1b, x2b, y1b, y2b);
  intercepta = getIntercept(x1a, y1a, slopea);
  interceptb = getIntercept(x1b, y1b, slopeb);
  cout << "y = " << slopea << "*x + " << intercepta << endl;
  cout << "y = " << slopeb << "*x + " << interceptb << endl;
  if(hasIntercept(slopea, intercepta, slopeb, interceptb))
    cout << "Has intercept" << endl;
  else
    cout << "Nope" << endl;


  return 0;
}
float min(float x, float y)
{
  return (x <= y) ? x : y;
}
float max(float x, float y)
{
  return (x >= y) ? x : y;
}
bool hasIntercept(float slopea, float intercepta, float slopeb, float interceptb)
{
  float x, min1, max1, min2, max2;
  if((slopea-slopeb) != 0)
    x = (interceptb-intercepta)/(slopea-slopeb);
  else
    return false;
  float y = (slopea*x + intercepta);
  cout << "(" << x << ", " << y << ")" << endl;

  min1 = min(x1a, x2a);
  max1 = max(x1a, x2a);

  min2 = min(x1b, x2b);
  max2 = max(x1b, x2b);

  if(min1 > x || x > max1 || min2 > x || x > max2)
    return false;
  else
    return true;
}
float getSlope(int x1, int x2, int y1, int y2)
{
  return ((y2-y1)/(x2-x1));
}
float getIntercept(int x, int y, float slope)
{
  return (y-(x*slope));
}
float getSlope(int x1, int x2, float y1, float y2)
{
  return ((y2-y1)/(x2-x1));
}
float getIntercept(int x, float y, float slope)
{
  return (y-(x*slope));
}
