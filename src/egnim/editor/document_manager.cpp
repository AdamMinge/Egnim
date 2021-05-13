/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document_manager.h>
#include <egnim/editor/no_editor_widget.h>
/* -------------------------------------------------------------------------- */

QScopedPointer<DocumentManager> DocumentManager::m_instance = QScopedPointer<DocumentManager>(nullptr);

DocumentManager& DocumentManager::getInstance()
{
  if(m_instance.isNull())
    m_instance.reset(new DocumentManager);

  return *m_instance;
}

void DocumentManager::deleteInstance()
{
  m_instance.reset(nullptr);
}

DocumentManager::DocumentManager() :
  m_widget(new QWidget()),
  m_no_editor_widget(new NoEditorWidget(m_widget.data())),
  m_tab_bar(new QTabBar(m_widget.data())),
  m_editor_stack(new QStackedLayout()),
  m_undo_group(new QUndoGroup(this))
{
  m_tab_bar->setExpanding(false);
  m_tab_bar->setDocumentMode(true);
  m_tab_bar->setTabsClosable(true);
  m_tab_bar->setMovable(true);
  m_tab_bar->setContextMenuPolicy(Qt::CustomContextMenu);

  auto vertical_layout = new QVBoxLayout(m_widget.data());
  vertical_layout->addWidget(m_tab_bar);
  vertical_layout->setContentsMargins(0, 0, 0, 0);
  vertical_layout->setSpacing(0);
  vertical_layout->addLayout(m_editor_stack);

  m_editor_stack->addWidget(m_no_editor_widget);

  connect(m_tab_bar, &QTabBar::currentChanged, this, &DocumentManager::currentIndexChanged);
  connect(m_tab_bar, &QTabBar::tabMoved, this, &DocumentManager::documentTabMoved);
  connect(m_tab_bar, &QTabBar::tabCloseRequested, this, &DocumentManager::documentCloseRequested);
}

DocumentManager::~DocumentManager()
{
  removeAllEditors();
  removeAllDocuments();
}

QWidget* DocumentManager::getWidget() const
{
  return m_widget.data();
}

void DocumentManager::addEditor(Document::Type document_type, std::unique_ptr<Editor> editor)
{
  m_editor_stack->addWidget(editor->getEditorWidget());
  m_editor_for_document_type.insert(std::make_pair(document_type, std::move(editor)));
}

void DocumentManager::removeEditor(Document::Type document_type)
{
  Q_ASSERT(m_editor_for_document_type.contains(document_type));
  m_editor_for_document_type.erase(document_type);
}

void DocumentManager::removeAllEditors()
{
  while(!m_editor_for_document_type.empty())
    removeEditor(m_editor_for_document_type.begin()->first);
}

Editor* DocumentManager::getEditor(Document::Type document_type) const
{
  if(m_editor_for_document_type.contains(document_type))
    return m_editor_for_document_type.at(document_type).get();

  return nullptr;
}

Editor* DocumentManager::getCurrentEditor() const
{
  auto current_document = getCurrentDocument();
  return current_document ? getEditor(current_document->getType()) : nullptr;
}

void DocumentManager::addDocument(std::unique_ptr<Document> document)
{
  Q_ASSERT(document);

  auto& document_ref = *document;

  m_documents.emplace_back(std::move(document));
  m_undo_group->addStack(document_ref.getUndoStack());

  auto document_index = m_tab_bar->addTab(document_ref.getDisplayName().toString());
  m_tab_bar->setTabToolTip(document_index, document_ref.getFileName().toString());

  switchToDocument(document_index);
}

void DocumentManager::removeDocument(int index)
{
  auto document_to_remove = getDocument(index);
  Q_ASSERT(document_to_remove);

  auto& editor = m_editor_for_document_type[document_to_remove->getType()];
  Q_ASSERT(editor);

  if(getCurrentDocument() == document_to_remove)
    editor->setCurrentDocument(nullptr);

  auto removed_document_iter = std::remove_if(
    m_documents.begin(), m_documents.end(), [&document_to_remove](auto&& document){
    return document.get() == document_to_remove;
  });

  m_undo_group->removeStack(document_to_remove->getUndoStack());
  m_tab_bar->removeTab(index);

  m_documents.erase(removed_document_iter, m_documents.end());
}

void DocumentManager::removeAllDocuments()
{
  while(!m_documents.empty())
    removeDocument(m_tab_bar->currentIndex());
}

Document* DocumentManager::getDocument(int index) const
{
  if(index < m_documents.size() && index >= 0)
    return m_documents.at(index).get();

  return nullptr;
}

Document* DocumentManager::getCurrentDocument() const
{
  auto index = m_tab_bar->currentIndex();
  return getDocument(index);
}

void DocumentManager::switchToDocument(int index)
{
  m_tab_bar->setCurrentIndex(index);
}

void DocumentManager::switchToDocument(Document* document)
{
  auto found_iter = std::find_if(m_documents.begin(), m_documents.end(), [&document](auto&& current_document){
    return current_document.get() == document;
  });

  Q_ASSERT(found_iter != m_documents.end());
  auto index = std::distance(m_documents.begin(), found_iter);
  switchToDocument(static_cast<int>(index));
}

QUndoGroup* DocumentManager::undoGroup() const
{
  return m_undo_group;
}

void DocumentManager::saveState()
{
  for(auto& [document_type, editor] : m_editor_for_document_type)
    editor->saveState();
}

void DocumentManager::restoreState()
{
  for(auto& [document_type, editor] : m_editor_for_document_type)
    editor->restoreState();
}

void DocumentManager::currentIndexChanged()
{
  auto document = getCurrentDocument();
  auto editor = getCurrentEditor();

  if(document)
    m_undo_group->setActiveStack(document->getUndoStack());

  if(editor)
  {
    editor->setCurrentDocument(document);
    m_editor_stack->setCurrentWidget(editor->getEditorWidget());
  }
  else
  {
    m_editor_stack->setCurrentWidget(m_no_editor_widget);
  }

  Q_EMIT currentDocumentChanged(document);
}

void DocumentManager::documentTabMoved(int from, int to)
{
  if(from > to)
    std::rotate(m_documents.rend() - from - 1,
                m_documents.rend() - from,
                m_documents.rend() - to);
  else
    std::rotate(m_documents.begin() + from,
                m_documents.begin() + from + 1,
                m_documents.begin() + to + 1);
}
