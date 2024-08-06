#ifndef DragNDropQWidgetCommands_H
#define DragNDropQWidgetCommands_H

//+++++++++++QT+++++++++++
#include <QApplication>
#include <QDrag>
#include <QHBoxLayout>
#include <QMimeData>
#include <QMouseEvent>
#include <QWidget>
//+++++++++++STL+++++++++++
#include <vector>
//+++++++++++CUSTOM+++++++++++
#include "../CommandDialog/commanddialog.h"
#include "../CommandIcon/commandicon.h"

class DragNDropQWidgetCommands : public QWidget {
 public:
  DragNDropQWidgetCommands(pf2e_manager::Controller* controller,
                           QWidget* parent = nullptr);

  CommandIcon* getCurrentIcon() { return _current_icon; }
  void updateContent();

  void addCommand(pf2e_manager::CommandBase* command);

 public slots:
  void mousePressEvent(QMouseEvent* event) override;
  // void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  //    void dragEnterEvent(QDragEnterEvent* event);
  //    void dragLeaveEvent(QDragLeaveEvent* event);
  // void dropEvent(QDropEvent* event);

 private:
  pf2e_manager::Controller* _controller;
  std::vector<pf2e_manager::CommandBase*>* _commands_list;

  QList<CommandIcon*> _widgets_collection;
  QHBoxLayout* _commands_layout;

  QPoint _mouseStartPosition = QPoint();

  CommandIcon* _current_icon = nullptr;
};

#endif  // DragNDropQWidgetCommands_H
