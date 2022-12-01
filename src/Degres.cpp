#include <Degres.hpp>
Degres::Degres(int angle, int minutes, int seconds) {
  m_angle = angle;
  m_minutes = minutes;
  m_seconds = seconds;
}
Degres Degres::operator+(Degres b) {
  int a, m, s;
  int tot = this->m_angle * 3600 + this->m_minutes * 60 + this->m_seconds;
  tot += b.m_angle * 3600 + b.m_minutes * 60 + b.m_seconds;
  s = tot % 60;
  m = tot / 60;
  tot = m;
  m %= 60;
  a = tot / 60;
  return Degres(a, m, s);
}
Degres::Degres() {
  m_angle = 0;
  m_minutes = 0;
  m_seconds = 0;
}
