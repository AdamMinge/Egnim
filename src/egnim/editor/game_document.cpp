/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/game_document.h>
/* -------------------------------------------------------------------------- */

GameDocument::GameDocument(QStringView file_name, QStringView display_name, QObject* parent) :
  Document(Type::Game, file_name, display_name, parent)
{

}

GameDocument::~GameDocument() = default;
