#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <memory>
#include <QMenuBar>

class QPushButton;

class MenuBar : public QWidget
{
    Q_OBJECT
    public:
        MenuBar();

        QMenuBar* getMenuBar();

    private:
        QMenuBar* m_menuBar;
};

#endif // MENU_BAR_H