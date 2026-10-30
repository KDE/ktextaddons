/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextInstance>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstanceModel;
class TextAutoGenerateEngineLoader;
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextInstancesManager
 * \brief The TextAutoGenerateTextInstancesManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextInstancesManager
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief The InstanceFilter enum
     */
    enum class InstanceFilter : uint8_t {
        All = 0,
        LocalOnly,
    };

    /*!
     */
    explicit TextAutoGenerateTextInstancesManager(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextInstancesManager() override;

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateTextInstance *> instances() const;
    /*!
     */
    void setInstances(const QList<TextAutoGenerateTextInstance *> &newInstances);

    /*!
     */
    void deleteInstance(const QByteArray &uuid);
    /*!
     */
    void addInstance(TextAutoGenerateTextInstance *instance);

    /*!
     */
    void loadInstances();

    /*!
     */
    void saveInstances();

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextInstanceModel *textAutoGenerateTextInstanceModel() const;

    /*!
     */
    [[nodiscard]] bool isCurrentInstance(const QByteArray &instanceUuid) const;

    /*!
     */
    [[nodiscard]] QByteArray currentInstance() const;
    /*!
     */
    void setCurrentinstance(const QByteArray &newCurrentinstance);

    /*!
     */
    [[nodiscard]] TextAutoGenerateEngineLoader *textAutoGenerateEngineLoader() const;

    /*!
     */
    [[nodiscard]] bool isEmpty() const;

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextPlugin *textAutoGeneratePlugin() const;

    /*!
     */
    [[nodiscard]] QStringList instanceDisplayNames() const;

    /*!
     * \brief instanceFilter
     * \return
     */
    [[nodiscard]] InstanceFilter instanceFilter() const;
    /*!
     * \brief setInstanceFilter
     * \param newInstanceFilter
     */
    void setInstanceFilter(InstanceFilter newInstanceFilter);

Q_SIGNALS:
    /*!
     * \brief instanceFilterChanged
     */
    void instanceFilterChanged();

private:
    TextAutoGenerateTextInstanceModel *const mTextAutoGenerateTextInstanceModel;
    TextAutoGenerateEngineLoader *const mTextAutoGenerateEngineLoader;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    InstanceFilter mInstanceFilter = InstanceFilter::All;
};
}
