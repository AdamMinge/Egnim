#ifndef SCENE_VISITOR_H
#define SCENE_VISITOR_H

namespace egnim::scene
{

  class AnimatedSpriteNode;
  class LabelNode;
  class MusicNode;
  class SceneNode;
  class SoundNode;
  class SpriteNode;

  class SceneVisitor
  {
  public:
    SceneVisitor() = default;
    ~SceneVisitor() = default;

    SceneVisitor(const SceneVisitor&) = default;
    SceneVisitor(SceneVisitor&&) = default;

    SceneVisitor& operator=(const SceneVisitor&) = default;
    SceneVisitor& operator=(SceneVisitor&&) = default;

    virtual void visit(AnimatedSpriteNode& animated_sprite_node) = 0;
    virtual void visit(LabelNode& label_node) = 0;
    virtual void visit(MusicNode& music_node) = 0;
    virtual void visit(SceneNode& scene_node) = 0;
    virtual void visit(SoundNode& sound_node) = 0;
    virtual void visit(SpriteNode& sprite_node) = 0;
  };

} // namespace egnim::scene

#endif //SCENE_VISITOR_H
