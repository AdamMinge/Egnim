/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/game_document.h>

#include <utility>
/* -------------------------------------------------------------------------- */

GameDocument::GameDocument(QString file_name, QString display_name, QObject* parent) :
  Document(Type::Game, std::move(file_name), std::move(display_name), parent)
{

}

GameDocument::~GameDocument() = default;
