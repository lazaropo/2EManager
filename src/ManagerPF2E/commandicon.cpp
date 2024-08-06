#include "commandicon.h"

CommandIcon::CommandIcon(pf2e_manager::CommandBase* command, QWidget* parent)
    : QWidget{parent}, _command(command) {
  setWindowIcon(QIcon(":/path/images/images/sword.jpg"));
}
