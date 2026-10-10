/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QVBoxLayout;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolElicitRequest;
}
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateElicitationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateElicitationWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateElicitationWidget() override;
    /*!
     * Create form of \a request: one editor by property of requested schema (object name: property name).
     */
    void setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request);

    /*!
     * Values of form (empty optional fields are not added). No content for URL request.
     */
    [[nodiscard]] std::optional<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitResultContent> content() const;

    /*!
     * Required fields are filled and constraints of schema (minLength, minItems, maxItems) are respected.
     */
    [[nodiscard]] bool isValid() const;

Q_SIGNALS:
    void contentChanged();

private:
    struct Field {
        QString name;
        QWidget *editor = nullptr;
        bool required = false;
        std::optional<int> minLength;
        std::optional<int> minItems;
        std::optional<int> maxItems;
    };
    TEXTAUTOGENERATETEXT_NO_EXPORT void connectEditor(QWidget *editor);
    QVBoxLayout *const mMainLayout;
    QWidget *mFormWidget = nullptr;
    QList<Field> mFields;
    bool mFormMode = false;
};
}
