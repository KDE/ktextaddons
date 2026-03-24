/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternal>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalInterface : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextToolInternalInterface(QObject *parent = nullptr);
    /*!
     */
    virtual ~TextAutoGenerateTextToolInternalInterface();

    /*!
     */
    virtual void execute() = 0;

    /*!
     */
    void loadInternalTools(const QString &filename);

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> tools() const;
    /*!
     */
    void setTools(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &newTools);

protected:
    QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> mTools;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotToolsLoaded(const QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> &list);
};
}
