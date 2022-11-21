#ifndef DEGRES_HPP
#define DEGRES_HPP
class Degres {
public:
  Degres();
  Degres(int angle, int minutes, int seconds);
  Degres operator+(const Degres b);
  int m_angle;
  int m_minutes;
  int m_seconds;
};

#endif  // DEGRES_HPP
