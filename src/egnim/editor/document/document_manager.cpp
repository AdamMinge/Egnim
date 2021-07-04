/* ------------------------------------ Qt ---------------------------------- */
#include <QMessageBox>
#include <QCoreApplication>
/* ----------------------------------- Local -------------------------------- */
#include "document/document_manager.h"
#include "document/no_document_widget.h"
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
  m_tab_bar(new QTabBar(m_widget.data())),
  m_editor_stack(new QStackedLayout()),
  m_no_document_widget(new NoDocumentWidget()),
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

  m_editor_stack->addWidget(m_no_document_widget.data());

  connect(m_tab_bar, &QTabBar::currentChanged, this, &DocumentManager::currentIndexChanged);
  connect(m_tab_bar, &QTabBar::tabMoved, this, &DocumentManager::documentTabMoved);
  connect(m_tab_bar, &QTabBar::tabCloseRequested, this, &DocumentManager::documentCloseRequested);
}

DocumentManager::~DocumentManager()
{
  removeAllDocuments();
  removeAllEditors();
}

QWidget* DocumentManager::getWidget() const
{
  return m_widget.data();
}

void DocumentManager::addEditor(Document::Type document_type, std::unique_ptr<DocumentEditor> editor)
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

DocumentEditor* DocumentManager::getEditor(Document::Type document_type) const
{
  if(m_editor_for_document_type.contains(document_type))
    return m_editor_for_document_type.at(document_type).get();

  return nullptr;
}

DocumentEditor* DocumentManager::getCurrentEditor() const
{
  auto current_document = getCurrentDocument();
  return current_document ? getEditor(current_document->getType()) : nullptr;
}

void DocumentManager::addDocument(std::unique_ptr<Document> document)
{
  Q_ASSERT(document);

  auto document_ptr = document.get();
  m_documents.emplace_back(std::move(document));
  m_undo_group->addStack(document_ptr->getUndoStack());

  auto editor = getEditor(document_ptr->getType());
  Q_ASSERT(editor);
  editor->addDocument(document_ptr);

  auto document_index = m_tab_bar->addTab(document_ptr->getDisplayName());
  m_tab_bar->setTabToolTip(document_index, document_ptr->getFileName());

  switchToDocument(document_index);
}

bool DocumentManager::loadDocument(const QString& file_name)
{
  if(switchToDocument(file_name))
    return true;

  auto document = Document::load(file_name);
  if(!document)
  {
    QMessageBox::critical(m_widget.get(),
                          tr("Error Opening File"),
                          tr("Error opening '%1'").arg(file_name));
    return false;
  }

  addDocument(std::move(document));
  return true;
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

int DocumentManager::findDocument(Document *document) const
{
  auto found = std::find_if(m_documents.begin(), m_documents.end(), [document](auto& current_document){
    return current_document.get() == document;
  });

  if(found == m_documents.end())
    return -1;

  return static_cast<int>(std::distance(m_documents.begin(), found));
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

bool DocumentManager::switchToDocument(const QString& file_name)
{
  auto found_iter = std::find_if(m_documents.begin(), m_documents.end(), [&file_name](auto&& current_document){
    return current_document->getFileName() == file_name;
  });

  if(found_iter == m_documents.end())
    return false;

  auto index = std::distance(m_documents.begin(), found_iter);
  switchToDocument(static_cast<int>(index));
  return true;
}

QUndoGroup* DocumentManager::getUndoGroup() const
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

bool DocumentManager::saveDocument(Document* document)
{
  Q_ASSERT(document);

  if(!document->save(document->getFileName()))
  {
    switchToDocument(document);
    QMessageBox::critical(
      m_widget->window(),
      tr("Error Saving File"), "Something went wrong");
    return false;
  }

  return true;
}

bool DocumentManager::saveDocumentAs(Document* document)
{
  Q_ASSERT(document);
}

const std::vector<std::unique_ptr<Document>>& DocumentManager::getDocuments() const
{
  return m_documents;
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
    m_editor_stack->setCurrentWidget(m_no_document_widget.data());
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


