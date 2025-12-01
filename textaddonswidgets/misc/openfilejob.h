/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <KService>
#include <QObject>
namespace TextAddonsWidgets
{
class TEXTADDONSWIDGETS_EXPORT OpenFileJob : public QObject
{
    Q_OBJECT
public:
    explicit OpenFileJob(QObject *parent = nullptr);
    ~OpenFileJob() override;

    [[nodiscard]] QWidget *parentWidget() const;
    void setParentWidget(QWidget *newParentWidget);

    [[nodiscard]] QString link() const;
    void setLink(const QString &newLink);

    [[nodiscard]] bool canStart() const;

    void start();

    virtual void downloadFile(const QUrl &fileUrl) = 0;
    virtual void runApplication(const KService::Ptr &offer) = 0;
    virtual void openUrl() = 0;

protected:
    QWidget *mParentWidget = nullptr;
    QString mLink;
};
}
