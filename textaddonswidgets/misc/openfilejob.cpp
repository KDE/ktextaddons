/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "openfilejob.h"
#include "savefileutils.h"
#include "textaddonswidgets_debug.h"
#include <KApplicationTrader>
#include <KLocalizedString>
#include <KService>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QPushButton>
#include <QTemporaryDir>
#include <QUrl>
using namespace Qt::Literals::StringLiterals;
using namespace TextAddonsWidgets;
OpenFileJob::OpenFileJob(QObject *parent)
    : QObject{parent}
{
}

OpenFileJob::~OpenFileJob() = default;

QWidget *OpenFileJob::parentWidget() const
{
    return mParentWidget;
}

void OpenFileJob::setParentWidget(QWidget *newParentWidget)
{
    mParentWidget = newParentWidget;
}

QString OpenFileJob::link() const
{
    return mLink;
}

void OpenFileJob::setLink(const QString &newLink)
{
    mLink = newLink;
}

bool OpenFileJob::canStart() const
{
    return !mLink.isEmpty();
}

enum class UserChoice : uint8_t {
    Save,
    Open,
    OpenWith,
    Cancel,
};
Q_DECLARE_METATYPE(UserChoice)

static UserChoice askUser(const QString &path, const KService::Ptr &offer, QWidget *widget)
{
    const QString title = i18nc("@title:window", "Open Attachment?");
    const QString text = xi18nc("@info", "Open attachment <filename>%1</filename>?<nl/>", QFileInfo(path).fileName());
    QMessageBox msgBox(QMessageBox::Question, title, text, QMessageBox::NoButton, widget);
    const char *prop = "_enumValue";
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    msgBox.addButton(i18nc("@action:button", "Open"), QMessageBox::YesRole)->setProperty(prop, QVariant::fromValue(UserChoice::Open));
#else
    if (offer) {
        auto *b = msgBox.addButton(i18nc("@action:button", "&Open With '%1'", offer->name()), QMessageBox::YesRole);
        b->setProperty(prop, QVariant::fromValue(UserChoice::Open));
    }
    msgBox.addButton(i18nc("@action:button", "Open &With…"), QMessageBox::YesRole)->setProperty(prop, QVariant::fromValue(UserChoice::OpenWith));
#endif
    msgBox.addButton(i18nc("@action:button", "Save &As…"), QMessageBox::ActionRole)->setProperty(prop, QVariant::fromValue(UserChoice::Save));
    msgBox.addButton(QMessageBox::Cancel)->setProperty(prop, QVariant::fromValue(UserChoice::Cancel));
    msgBox.exec();
    QAbstractButton *clickedButton = msgBox.clickedButton();
    if (!clickedButton) {
        return UserChoice::Cancel; // Default to cancel if dialog closed
    }
    return clickedButton->property(prop).value<UserChoice>();
}

void OpenFileJob::start()
{
    if (!canStart()) {
        qCWarning(TEXTADDONSWIDGETS_LOG) << "OpenFileJob::start: Link is empty";
        deleteLater();
        return;
    }
    const QString path = QUrl::fromPercentEncoding(mLink.toLatin1());
    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForFile(path);
    const bool valid = mimeType.isValid() && !mimeType.isDefault();
    const KService::Ptr offer = valid ? KApplicationTrader::preferredService(mimeType.name()) : KService::Ptr{};
    const UserChoice choice = askUser(path, offer, mParentWidget);

    switch (choice) {
    case UserChoice::Save: {
        const QString file = SaveFileUtils::querySaveFileName(mParentWidget, i18nc("@title:window", "Save File"), QUrl::fromLocalFile(path));
        if (!file.isEmpty()) {
            const QUrl fileUrl = QUrl::fromLocalFile(file);
            downloadFile(fileUrl);
        }
        break;
    }
    case UserChoice::Open:
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
        openUrl();
#else
        runApplication(offer);
#endif
        break;
    case UserChoice::OpenWith:
        runApplication({});
        break;
    case UserChoice::Cancel:
        deleteLater();
        break;
    }
}

#include "moc_openfilejob.cpp"
