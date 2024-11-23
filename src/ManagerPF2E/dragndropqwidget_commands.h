#ifndef DragNDropQWidgetCommands_H
#define DragNDropQWidgetCommands_H

//+++++++++++QT+++++++++++
#include <QApplication>
#include <QBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QScrollArea>
#include <QTextBrowser>
#include <QWidget>
//+++++++++++STL+++++++++++
#include <vector>
//+++++++++++CUSTOM+++++++++++
#include "../CommandDialog/commanddialog.h"
#include "../CommandIcon/commandicon.h"
#include "closebletextbrowser.h"

class DragNDropQWidgetCommands : public QWidget {
 public:
  DragNDropQWidgetCommands(pf2e_manager::Controller* controller,
                           QWidget* parent = nullptr);

  CommandIcon* getCurrentIcon() { return _current_icon; }
  void updateContent();

  void addCommand(pf2e_manager::CommandBase* command);

  void setArea(QScrollArea* area) { _area = area; }

  // void updateContent();

 public slots:
  void mousePressEvent(QMouseEvent* event) override;
   //  void resizeEvent(QResizeEvent* event) override;


 private:
  QScrollArea* _area = nullptr;

  pf2e_manager::Controller* _controller;
  std::vector<pf2e_manager::CommandBase*>* _commands_list;

  QList<CommandIcon*> _widgets_collection;
  QBoxLayout* _commands_layout;

  QPoint _mouseStartPosition = QPoint();

  CommandIcon* _current_icon = nullptr;
  CommandIcon* _prev_icon = nullptr;
  ClosebleTextBrowser* _description = nullptr;
};

#endif  // DragNDropQWidgetCommands_H
