/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_export.h"
#include <QWidgetAction>

class QHBoxLayout;
namespace TextEmoticonsWidgets
{
class EmoticonWidgetActionWidget;
/**
 * @brief The TextEmoticonsWidgets::EmoticonWidgetAction class
 *
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonWidgetAction : public QWidgetAction
{
    Q_OBJECT
public:
    struct TEXTEMOTICONSWIDGETS_EXPORT EmoticonInfo {
        QString emojiStr;
        QString emojiIdentifier;
    };

    explicit EmoticonWidgetAction(const QList<EmoticonWidgetAction::EmoticonInfo> &emojis, QObject *parent = nullptr);
    ~EmoticonWidgetAction() override;

Q_SIGNALS:
    void insertEmoji(const QString &str);
    void insertEmojiIdentifier(const QString &identifier);
    void selectEmoji();

private:
    EmoticonWidgetActionWidget *const mEmoticonWidgetActionWidget;
};
}

Q_DECLARE_TYPEINFO(TextEmoticonsWidgets::EmoticonWidgetAction::EmoticonInfo, Q_RELOCATABLE_TYPE);
