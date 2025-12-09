/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateshowimagedialog.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateshowimagewidget.h"
#include "textautogeneratetextwidget_debug.h"
#include <KApplicationTrader>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KStandardActions>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QMenu>
#include <QMimeDatabase>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAutoGenerateText/TextAutoGenerateManager>
namespace
{
const char myTextAutoGenerateShowImageDialogGroupName[] = "TextAutoGenerateShowImageDialog";
}
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowImageDialog::TextAutoGenerateShowImageDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog(parent)
    , mShowImageWidget(new TextAutoGenerateShowImageWidget(manager, this))
    , mClipboardMenu(new QMenu(this))
    , mOpenWithButton(new QToolButton(this))
    , mOpenWithMenu(new QMenu(this))
    , mManager(manager)
{
    setWindowTitle(i18nc("@title:window", "Display Image"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mShowImageWidget->setObjectName(u"mShowImageWidget"_s);
    mainLayout->addWidget(mShowImageWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Save, this);
    buttonBox->setObjectName(u"button"_s);

    mOpenWithButton->setObjectName(u"openWithButton"_s);
    mOpenWithButton->setPopupMode(QToolButton::MenuButtonPopup);
    mOpenWithButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    buttonBox->addButton(mOpenWithButton, QDialogButtonBox::ActionRole);
    mOpenWithMenu->setObjectName(u"mOpenWithMenu"_s);
    mOpenWithButton->setMenu(mOpenWithMenu);
    connect(mOpenWithMenu, &QMenu::triggered, this, &TextAutoGenerateShowImageDialog::slotOpenWith);

    mClipboardImageAction = KStandardActions::copy(mShowImageWidget, &TextAutoGenerateShowImageWidget::copyImage, this);
    mClipboardImageAction->setObjectName(u"clipboardLocationAction"_s);
    mClipboardImageAction->setText(i18n("Copy Image to Clipboard"));

    auto clipboardLocationAction = new QAction(QIcon::fromTheme(u"edit-copy"_s), i18n("Copy Location to Clipboard"), this);
    clipboardLocationAction->setObjectName(u"clipboardLocationAction"_s);
    connect(clipboardLocationAction, &QAction::triggered, mShowImageWidget, &TextAutoGenerateShowImageWidget::copyLocation);

    mClipboardMenu->setObjectName(u"mClipboardMenu"_s);
    mClipboardMenu->addAction(mClipboardImageAction);
    mClipboardMenu->addAction(clipboardLocationAction);

    auto clipboardButton = new QToolButton(this);
    clipboardButton->setObjectName(u"clipboardButton"_s);

    clipboardButton->setMenu(mClipboardMenu);
    clipboardButton->setPopupMode(QToolButton::MenuButtonPopup);
    clipboardButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    buttonBox->addButton(clipboardButton, QDialogButtonBox::ActionRole);
    clipboardButton->setDefaultAction(clipboardLocationAction);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &TextAutoGenerateShowImageDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, mShowImageWidget, &TextAutoGenerateShowImageWidget::saveAs);
    mainLayout->addWidget(buttonBox);

    // TODO connect(mShowImageWidget, &TextAutoGenerateShowImageWidget::updateMenu, this, &TextAutoGenerateShowImageDialog::slotUpdateMenu);

    readConfig();
}

TextAutoGenerateShowImageDialog::~TextAutoGenerateShowImageDialog()
{
    writeConfig();
}

void TextAutoGenerateShowImageDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(800, 600));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowImageDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateShowImageDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateShowImageDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void TextAutoGenerateShowImageDialog::updateServiceList()
{
#if 0
    mOpenWithMenu->clear();
    const QString path = mRocketChatAccount->attachmentUrlFromLocalCache(mShowImageWidget->imageInfo().bigImagePath).toLocalFile();
    if (path.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "path is empty for " << mShowImageWidget->imageInfo().bigImagePath;
        mOpenWithButton->setEnabled(false);
        return;
    }
    mOpenWithButton->setEnabled(true);
    QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForFile(path);

    const bool valid = mimeType.isValid() && !mimeType.isDefault();
    mServiceList = valid ? KApplicationTrader::queryByMimeType(mimeType.name()) : KService::List{};

    int idx = 0;
    for (const KService::Ptr &service : std::as_const(mServiceList)) {
        const QString text = service->name().replace(u'&', u"&&"_s);
        QAction *action = mOpenWithMenu->addAction(text);
        action->setIcon(QIcon::fromTheme(service->icon()));
        action->setData(idx);
        if (idx == 0) {
            mOpenWithButton->setDefaultAction(action);
        }
        ++idx;
    }
#endif
    mOpenWithMenu->addSeparator();
    QAction *action = mOpenWithMenu->addAction(QIcon::fromTheme(u"system-run"_s), i18n("Other Application..."));
    action->setData(-1);
}

void TextAutoGenerateShowImageDialog::slotOpenWith(QAction *action)
{
    bool ok;
    const int idx = action->data().toInt(&ok);
    if (!ok) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Index is not defined";
        return;
    }
    KService::Ptr service;
    if (idx != -1) {
        service = mServiceList.at(idx);
    }
    mShowImageWidget->openWith(service);
}

#include "moc_textautogenerateshowimagedialog.cpp"
