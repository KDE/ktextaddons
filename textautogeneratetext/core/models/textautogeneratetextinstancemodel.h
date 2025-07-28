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
        PluginIdentifier,
        Uuid,
        Plugin,
        Enabled,
        IsDefault,
        TranslatedPluginName,
    };
    explicit TextAutoGenerateTextInstanceModel(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QList<TextAutoGenerateTextInstance *> textInstances() const;
    void setTextInstances(const QList<TextAutoGenerateTextInstance *> &newTextInstances);

    void addInstance(TextAutoGenerateTextInstance *instance);

    [[nodiscard]] TextAutoGenerateTextPlugin *removeInstance(const QByteArray &uuid);

    [[nodiscard]] TextAutoGenerateTextPlugin *editInstance(const QByteArray &uuid);

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] QByteArray currentInstance() const;
    void setCurrentInstance(const QByteArray &newCurrentinstance);

    [[nodiscard]] TextAutoGenerateTextPlugin *currentPlugin() const;

private:
    QList<TextAutoGenerateTextInstance *> mTextInstances;
    QByteArray mCurrentinstance;
};
}
