/*
  SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_export.h"
#include <QWidget>
class QLineEdit;
namespace TextEmoticonsCore
{
class EmoticonUnicodeProxyModel;
}
namespace TextEmoticonsWidgets
{
class EmoticonCategoryButtons;
class EmoticonListView;
/**
 * @brief The EmoticonTextEditSelector class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonTextEditSelector : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonTextEditSelector(QWidget *parent = nullptr);
    ~EmoticonTextEditSelector() override;

    void forceLineEditFocus();

public Q_SLOTS:
    void loadEmoticons();

Q_SIGNALS:
    void insertEmoji(const QString &);
    void insertEmojiIdentifier(const QString &);

private:
    class EmoticonTextEditSelectorPrivate;
    std::unique_ptr<EmoticonTextEditSelectorPrivate> const d;

    TEXTEMOTICONSWIDGETS_NO_EXPORT void slotItemSelected(const QString &str, const QString &identifier);
};
}
