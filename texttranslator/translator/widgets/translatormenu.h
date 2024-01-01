/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "texttranslator_export.h"
#include <QObject>
#include <QPersistentModelIndex>
class QMenu;

namespace TextTranslator
{
class TEXTTRANSLATOR_EXPORT TranslatorMenu : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorMenu(QObject *parent = nullptr);
    ~TranslatorMenu() override;

    [[nodiscard]] QMenu *menu() const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] const QPersistentModelIndex &modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

    void updateMenu();

Q_SIGNALS:
    void translate(const QString &from, const QString &to, const QPersistentModelIndex &modelIndex);

private:
    QPersistentModelIndex mModelIndex;
    QMenu *const mMenu;
};
}
