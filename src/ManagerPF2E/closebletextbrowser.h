#ifndef CLOSEBLETEXTBROWSER_H
#define CLOSEBLETEXTBROWSER_H

#include <QObject>
#include <QTextBrowser>

class ClosebleTextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    ClosebleTextBrowser();

signals:
    void closed(QCloseEvent *event = nullptr);

protected slots:
    void closeEvent(QCloseEvent *event = nullptr) override {
        emit closed(event);
    }
};

#endif // CLOSEBLETEXTBROWSER_H
