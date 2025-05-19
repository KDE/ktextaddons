/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textautogeneratemenutextinfo.h"

#include <KSharedConfig>
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateMenuTextManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMenuTextManager(QObject *parent = nullptr);
    ~TextAutoGenerateMenuTextManager() override;

    void load();
    void save();

    [[nodiscard]] QList<TextAutoGenerateMenuTextInfo> textInfos() const;
    void setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &newTextInfos);

private:
    [[nodiscard]] QStringList keyRecorderList(KSharedConfig::Ptr &config) const;
    QList<TextAutoGenerateMenuTextInfo> mTextInfos;
};
}
