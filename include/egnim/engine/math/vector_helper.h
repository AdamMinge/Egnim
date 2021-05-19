#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <cmath>
/* -------------------------------------------------------------------------- */

namespace egnim::math
{

  class VectorHelper
  {
  public:
    template<typename TYPE>
    static TYPE distance(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second);

    template<typename TYPE>
    static TYPE dot(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second);

    template<typename TYPE>
    static TYPE cross(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second);

  private:
    explicit VectorHelper() = default;
    ~VectorHelper() = default;
  };

  template<typename TYPE>
  TYPE VectorHelper::distance(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second)
  {
    auto vec = second - first;
    return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
  }

  template<typename TYPE>
  TYPE VectorHelper::dot(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second)
  {
    return first.x * second.x + first.y * second.y;
  }

  template<typename TYPE>
  TYPE VectorHelper::cross(const sf::Vector2<TYPE>& first, const sf::Vector2<TYPE>& second)
  {
    return first.x * second.y + first.y * second.x;
  }

}

#endif //VECTOR_HELPER_H
