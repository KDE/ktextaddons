/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
#include <TextAutoGenerateText/TextAutoGenerateTextInstance>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTextInstanceModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstanceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum InstanceRoles : uint16_t {
        Name = Qt::UserRole + 1,
        PluginName,
        PluginIdentifer,
        Uuid,
    };
    explicit TextAutoGenerateTextInstanceModel(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QList<TextAutoGenerateTextInstance> textInstances() const;
    void setTextInstances(const QList<TextAutoGenerateTextInstance> &newTextInstances);

    void addTextInstances(const TextAutoGenerateTextInstance &instance);

    void removeInstance(const QByteArray &uuid);

private:
    QList<TextAutoGenerateTextInstance> mTextInstances;
};
}
