/*
code based on source from Gwenview
SPDX-FileCopyrightText: 2007 Aurélien Gâteau <agateau@kde.org>

SPDX-License-Identifier: LGPL-2.0-or-later

*/
// Qt
#include <QApplication>
using namespace Qt::Literals::StringLiterals;

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <TextAddonsWidgets/SlideContainer>

using namespace TextAddonsWidgets;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto container = new SlideContainer(this);

        auto inButton = new QPushButton(this);
        inButton->setText(u"Slide &In"_s);
        connect(inButton, &QPushButton::clicked, container, &SlideContainer::slideIn);

        auto outButton = new QPushButton(this);
        outButton->setText(u"Slide &Out"_s);
        connect(outButton, &QPushButton::clicked, container, &SlideContainer::slideOut);

        auto layout = new QVBoxLayout(this);
        layout->addWidget(inButton);
        layout->addWidget(outButton);
        layout->addWidget(container);

        auto content = new QLineEdit(container);
        content->setText(u"Some long text. Some long text. Some long text. Some long text."_s);
        container->setContent(content);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.show();
    return app.exec();
}

#include "slidecontainer_gui.moc"
