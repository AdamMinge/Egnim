#ifndef OBJECT_H
#define OBJECT_H

namespace egnim::core
{

  class Object
  {
  public:
    virtual ~Object() = default;

    static std::string_view staticClassName()                         { return "Object"; }
    [[nodiscard]] virtual std::string_view className() const          { return "Object"; }

    static std::string_view staticParentClassName()                   { return ""; }
    [[nodiscard]] virtual std::string_view parentClassName() const    { return ""; }

    virtual bool isClass(std::string_view className)                  { return Object::className() == className; }

  protected:
    explicit Object() = default;

  };

#define IMPL_EGNIM_CLASS(CLASS, PARENT_CLASS, CLASS_NAME)                                                       \
public:                                                                                                         \
  static std::string_view staticClassName()                       { return CLASS_NAME; }                        \
  [[nodiscard]] std::string_view className() const override       { return CLASS_NAME; }                        \
                                                                                                                \
  static std::string_view staticParentClassName()                 { return PARENT_CLASS::staticClassName(); }   \
  [[nodiscard]] std::string_view parentClassName() const override { return PARENT_CLASS::className(); }         \
                                                                                                                \
  bool isClass(std::string_view className) override                                                             \
    { return CLASS::className() == className ? true : PARENT_CLASS::isClass(className); }                       \

#define EGNIM_CLASS(CLASS, PARENT_CLASS)                                                                        \
IMPL_EGNIM_CLASS(CLASS, PARENT_CLASS, #CLASS)

} // egnim::core


#endif //OBJECT_H
