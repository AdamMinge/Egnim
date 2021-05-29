/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/game_document.h>

#include <utility>
/* -------------------------------------------------------------------------- */

GameDocument::GameDocument(QString file_name, QObject* parent) :
  Document(Type::Game, std::move(file_name), parent)
{

}

GameDocument::~GameDocument() = default;
