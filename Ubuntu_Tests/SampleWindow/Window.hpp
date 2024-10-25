#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

#include <MenuBar.hpp>

#include <QWidget>

class QPushButton;

class Window : public QWidget
{
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = 0);
    private slots:
        void slotButtonClicked(bool checked);        
    private:
        QPushButton* m_Button;
        MenuBar*     m_menuBar;
};

#endif // WINDOW_H