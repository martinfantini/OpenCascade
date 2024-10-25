#include "MenuBar.hpp"

#include <QMenu>

MenuBar::MenuBar(): m_menuBar(new QMenuBar())
{
    QMenu *file = new QMenu("&File");
    file->addMenu("Open");
    file->addMenu("new");

    QMenu *Build = new QMenu("&Build");
    Build->addAction("Rebuild this file");
    Build->addAction("Rebuild All");

    m_menuBar->addMenu(file);
    m_menuBar->addMenu(Build);
}

QMenuBar* MenuBar::getMenuBar()
{
    return m_menuBar;
}