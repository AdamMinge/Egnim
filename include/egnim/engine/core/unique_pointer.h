#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{

  template<typename TO, typename FROM>
  std::unique_ptr<TO> static_unique_pointer_cast(std::unique_ptr<FROM>&& old)
  {
    return std::unique_ptr<TO>(static_cast<TO*>(old.release()));
  }

} // namespace egnim::core

#endif //UNIQUE_POINTER_H
