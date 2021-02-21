/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Clock.hpp>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/main_loop.h>
#include <egnim/engine/core/state_stack.h>
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

MainLoop::MainLoop() :
  m_context(std::make_unique<Context>()),
  m_states(std::make_unique<StateStack>(*m_context)),
  m_time_per_frame(sf::seconds(1.f/60.f))
{

}

MainLoop::~MainLoop() = default;

void MainLoop::setTimePerFrame(const sf::Time& time_per_frame)
{
  m_time_per_frame = time_per_frame;
}

sf::Time MainLoop::getTimePerFrame() const
{
  return m_time_per_frame;
}

void MainLoop::run()
{
  sf::Clock clock;
  sf::Time time_since_last_update = sf::Time::Zero;
  auto& render_window = m_context->getRenderWindow();

  while(render_window.isOpen())
  {
    sf::Time dt = clock.restart();
    time_since_last_update += dt;

    while(time_since_last_update > m_time_per_frame)
    {
      time_since_last_update -= m_time_per_frame;

      processInput();
      update(m_time_per_frame);

      if(m_states->empty())
        render_window.close();
    }

    render();
  }
}

void MainLoop::processInput()
{
  sf::Event event{};
  auto& render_window = m_context->getRenderWindow();

  while(render_window.pollEvent(event))
  {
    m_states->handleEvent(event);

    if(event.type == sf::Event::Closed)
      render_window.close();
  }
}

void MainLoop::update(sf::Time dt)
{
  m_states->update(dt);
}

void MainLoop::render()
{
  auto& render_window = m_context->getRenderWindow();

  render_window.clear();
  m_states->draw();
  render_window.display();
}

} // namespace egnim::core
