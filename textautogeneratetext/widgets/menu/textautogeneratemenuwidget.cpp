/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenuwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratemenuconfiguredialog.h"
#include "textautogeneratemenutextmanager.h"
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGenerateQuickAskDialog>

#include <KLocalizedString>
#include <QMenu>
using namespace TextAutoGenerateText;
TextAutoGenerateMenuWidget::TextAutoGenerateMenuWidget(QObject *parent)
    : TextAutoGenerateMenuWidget(new TextAutoGenerateMenuTextManager(parent), parent)
{
}

TextAutoGenerateMenuWidget::TextAutoGenerateMenuWidget(TextAutoGenerateMenuTextManager *manager, QObject *parent)
    : QObject{parent}
    , mTextMenu(new QMenu)
    , mMenuTextManager(manager)
{
    initialize();
}

void TextAutoGenerateMenuWidget::initialize()
{
    mMenuTextManager->load();
    mTextMenu->setTitle(i18n("Ask AI…"));
    // mMenu->setIcon(QIcon::fromTheme(u"document-share"_s));
    mTextMenu->setObjectName(u"mMenu"_s);
    initializeMenu();
    connect(mMenuTextManager, &TextAutoGenerateMenuTextManager::textInfoChanged, this, &TextAutoGenerateMenuWidget::updateMenu);
    connect(this, &TextAutoGenerateMenuWidget::refreshMenu, this, &TextAutoGenerateMenuWidget::updateMenu);
}

TextAutoGenerateMenuWidget::~TextAutoGenerateMenuWidget()
{
    delete mTextMenu;
}

void TextAutoGenerateMenuWidget::initializeMenu()
{
    const auto infos = mMenuTextManager->textInfos();
    for (const TextAutoGenerateMenuTextInfo &info : infos) {
        if (info.enabled()) {
            const QString requestText = info.requestText();
            auto action = new QAction(requestText, mTextMenu);
            connect(action, &QAction::triggered, this, [requestText, this]() {
                auto dlg = new TextAutoGenerateText::TextAutoGenerateQuickAskDialog(mManager, mParentWidget);
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->show();
                dlg->ask(u"%1 %2"_s.arg(requestText, mSelectedText));
            });
            mTextMenu->addAction(action);
        }
    }
    auto configureAction = new QAction(QIcon::fromTheme(u"configure"_s), i18nc("@action", "Configure…"), mTextMenu);
    connect(configureAction, &QAction::triggered, this, &TextAutoGenerateMenuWidget::slotConfigure);
    if (!mTextMenu->isEmpty()) {
        mTextMenu->addSeparator();
    }
    mTextMenu->addAction(configureAction);
}

QMenu *TextAutoGenerateMenuWidget::menu() const
{
    return mTextMenu;
}

QString TextAutoGenerateMenuWidget::selectedText() const
{
    return mSelectedText;
}

void TextAutoGenerateMenuWidget::setSelectedText(const QString &newSelectedText)
{
    mSelectedText = newSelectedText;
}

void TextAutoGenerateMenuWidget::updateMenu()
{
    mTextMenu->clear();
    initializeMenu();
}

QWidget *TextAutoGenerateMenuWidget::parentWidget() const
{
    return mParentWidget;
}

void TextAutoGenerateMenuWidget::setParentWidget(QWidget *newParentWidget)
{
    mParentWidget = newParentWidget;
}

TextAutoGenerateManager *TextAutoGenerateMenuWidget::manager() const
{
    return mManager;
}

void TextAutoGenerateMenuWidget::setManager(TextAutoGenerateText::TextAutoGenerateManager *newManager)
{
    mManager = newManager;
}

void TextAutoGenerateMenuWidget::slotConfigure()
{
    auto dlg = new TextAutoGenerateMenuConfigureDialog(nullptr);
    dlg->setTextInfos(mMenuTextManager->textInfos());
    if (dlg->exec()) {
        mMenuTextManager->setTextInfos(dlg->textInfos());
        mMenuTextManager->save();
        updateMenu();
    }
    delete dlg;
}

#include "moc_textautogeneratemenuwidget.cpp"
