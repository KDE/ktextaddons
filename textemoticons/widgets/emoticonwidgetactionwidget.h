/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_export.h"
#include <QWidget>
#include <TextEmoticonsWidgets/EmoticonWidgetAction>

class QHBoxLayout;
namespace TextEmoticonsWidgets
{
/**
 * @brief The TextEmoticonsWidgets::EmoticonWidgetActionWidget class
 *
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonWidgetActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonWidgetActionWidget(const QList<EmoticonWidgetAction::EmoticonInfo> &emojis, QWidget *parent = nullptr);
    ~EmoticonWidgetActionWidget() override;

Q_SIGNALS:
    void insertEmoji(const QString &str);
    void insertEmojiIdentifier(const QString &identifier);
    void selectEmoji();

private:
    [[nodiscard]] TEXTEMOTICONSWIDGETS_NO_EXPORT QList<EmoticonWidgetAction::EmoticonInfo> loadRecentsEmoticons() const;
    [[nodiscard]] TEXTEMOTICONSWIDGETS_NO_EXPORT QList<EmoticonWidgetAction::EmoticonInfo> defaultEmoticons() const;
    [[nodiscard]] TEXTEMOTICONSWIDGETS_NO_EXPORT EmoticonWidgetAction::EmoticonInfo generateEmoticonInfo(const QString &identifier) const;
    TEXTEMOTICONSWIDGETS_NO_EXPORT void addDefaultEmoticons(const QList<EmoticonWidgetAction::EmoticonInfo> &emojis);
    QHBoxLayout *const mMainLayout;
};
}
