/* ----------------------------------- Local -------------------------------- */
#include "physics_scenes/example_game.h"
/* -------------------------------------------------------------------------- */

int main(int argc, char** argv)
{
  ExampleGame example_game(800, 600, "physics_scenes");
  return example_game.run();
}
