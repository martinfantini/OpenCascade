#include "Window.hpp"

#include "MenuBar.hpp"

#include <QApplication>
#include <QPushButton>
#include <QLayout>
#include <QVBoxLayout>


Window::Window(QWidget *parent):
    QWidget(parent),
    m_Button(new QPushButton("Hello World", this)),
    m_menuBar(new MenuBar())
{
    // Set size of the window
    setFixedSize(300, 200);

    // Create a layout, to show in the infomation
    QVBoxLayout* boxVLayout = new QVBoxLayout(this);
    QHBoxLayout* boxHLayout = new QHBoxLayout();

    boxVLayout->addLayout(boxHLayout);

    // Create and position the button
    m_Button->setGeometry(10, 10, 80, 30);
    m_Button->setCheckable(true);

    boxHLayout->addWidget(m_Button);
    
    QPushButton* m_Button2 = new QPushButton("Hello World2", this);
    boxHLayout->addWidget(m_Button2);

    // this->layout()->addWidget(m_Button);
    // Create Menu Bar
    this->layout()->setMenuBar(m_menuBar->getMenuBar());

    connect(m_Button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
}

void Window::slotButtonClicked(bool checked)
{
    if (checked) {
        m_Button->setText("Checked");
    } else {
        m_Button->setText("Hello World");
    }
}
