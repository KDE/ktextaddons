/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateelicitationwidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSpinBox>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestFormParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <limits>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
QStringList checkedValues(const QListWidget *listWidget)
{
    QStringList values;
    for (int i = 0; i < listWidget->count(); ++i) {
        if (const QListWidgetItem *item = listWidget->item(i); item->checkState() == Qt::Checked) {
            values.append(item->data(Qt::UserRole).toString());
        }
    }
    return values;
}

QComboBox *createComboBox(const QStringList &texts, const QStringList &values, const std::optional<QString> &defaultValue, QWidget *parent)
{
    auto comboBox = new QComboBox(parent);
    for (qsizetype i = 0; i < values.count(); ++i) {
        comboBox->addItem(texts.value(i, values.at(i)), values.at(i));
    }
    if (defaultValue.has_value()) {
        comboBox->setCurrentIndex(comboBox->findData(*defaultValue));
    }
    return comboBox;
}

QListWidget *createListWidget(const QStringList &texts, const QStringList &values, const std::optional<QStringList> &defaultValue, QWidget *parent)
{
    auto listWidget = new QListWidget(parent);
    for (qsizetype i = 0; i < values.count(); ++i) {
        auto item = new QListWidgetItem(texts.value(i, values.at(i)), listWidget);
        item->setData(Qt::UserRole, values.at(i));
        item->setCheckState(defaultValue.value_or(QStringList()).contains(values.at(i)) ? Qt::Checked : Qt::Unchecked);
    }
    return listWidget;
}

QWidget *createStringEditor(const McpProtocolStringSchema &schema, QWidget *parent)
{
    const QString defaultValue = schema.defaultValue().value_or(QString());
    switch (schema.format().value_or(McpProtocolStringSchema::Format::Unknown)) {
    case McpProtocolStringSchema::Format::Date: {
        auto dateEdit = new QDateEdit(parent);
        dateEdit->setCalendarPopup(true);
        const QDate date = QDate::fromString(defaultValue, Qt::ISODate);
        dateEdit->setDate(date.isValid() ? date : QDate::currentDate());
        return dateEdit;
    }
    case McpProtocolStringSchema::Format::DateTime: {
        auto dateTimeEdit = new QDateTimeEdit(parent);
        dateTimeEdit->setCalendarPopup(true);
        const QDateTime dateTime = QDateTime::fromString(defaultValue, Qt::ISODate);
        dateTimeEdit->setDateTime(dateTime.isValid() ? dateTime : QDateTime::currentDateTime());
        return dateTimeEdit;
    }
    case McpProtocolStringSchema::Format::Email:
    case McpProtocolStringSchema::Format::Uri:
    case McpProtocolStringSchema::Format::Unknown:
        break;
    }
    auto lineEdit = new QLineEdit(defaultValue, parent);
    lineEdit->setClearButtonEnabled(true);
    if (const auto maxLength = schema.maxLength(); maxLength.has_value()) {
        lineEdit->setMaxLength(*maxLength);
    }
    return lineEdit;
}

QWidget *createNumberEditor(const McpProtocolNumberSchema &schema, QWidget *parent)
{
    if (schema.type() == McpProtocolNumberSchema::Type::Integer) {
        auto spinBox = new QSpinBox(parent);
        spinBox->setRange(static_cast<int>(schema.minimum().value_or(std::numeric_limits<int>::min())),
                          static_cast<int>(schema.maximum().value_or(std::numeric_limits<int>::max())));
        if (const auto defaultValue = schema.defaultValue(); defaultValue.has_value()) {
            spinBox->setValue(static_cast<int>(*defaultValue));
        }
        return spinBox;
    }
    auto doubleSpinBox = new QDoubleSpinBox(parent);
    doubleSpinBox->setDecimals(6);
    doubleSpinBox->setRange(schema.minimum().value_or(std::numeric_limits<double>::lowest()), schema.maximum().value_or(std::numeric_limits<double>::max()));
    if (const auto defaultValue = schema.defaultValue(); defaultValue.has_value()) {
        doubleSpinBox->setValue(*defaultValue);
    }
    return doubleSpinBox;
}

// Editor of property, its title, its description and its constraints
struct Editor {
    QWidget *widget = nullptr;
    std::optional<QString> title;
    std::optional<QString> description;
    std::optional<int> minLength;
    std::optional<int> minItems;
    std::optional<int> maxItems;
};

Editor createEditor(const McpProtocolUtils::PrimitiveSchemaDefinition &definition, QWidget *parent)
{
    return std::visit(
        [parent](const auto &schema) -> Editor {
            using T = std::decay_t<decltype(schema)>;
            Editor editor;
            editor.title = schema.title();
            editor.description = schema.description();
            QWidget *widget = nullptr;
            if constexpr (std::is_same_v<T, McpProtocolStringSchema>) {
                widget = createStringEditor(schema, parent);
                editor.minLength = schema.minLength();
            } else if constexpr (std::is_same_v<T, McpProtocolNumberSchema>) {
                widget = createNumberEditor(schema, parent);
            } else if constexpr (std::is_same_v<T, McpProtocolBooleanSchema>) {
                auto checkBox = new QCheckBox(parent);
                checkBox->setChecked(schema.defaultValue().value_or(false));
                widget = checkBox;
            } else if constexpr (std::is_same_v<T, McpProtocolUntitledSingleSelectEnumSchema>) {
                widget = createComboBox(schema.enums(), schema.enums(), schema.defaultValue(), parent);
            } else if constexpr (std::is_same_v<T, McpProtocolTitledSingleSelectEnumSchema>) {
                QStringList texts;
                QStringList values;
                const auto oneOf = schema.oneOf();
                for (const auto &item : oneOf) {
                    texts.append(item.title());
                    values.append(item.constValue());
                }
                widget = createComboBox(texts, values, schema.defaultValue(), parent);
            } else if constexpr (std::is_same_v<T, McpProtocolLegacyTitledEnumSchema>) {
                widget = createComboBox(schema.enumNames().value_or(QStringList()), schema.enums(), schema.defaultValue(), parent);
            } else if constexpr (std::is_same_v<T, McpProtocolUntitledMultiSelectEnumSchema>) {
                const QStringList values = schema.items().enumValue();
                widget = createListWidget(values, values, schema.defaultValue(), parent);
                editor.minItems = schema.minItems();
                editor.maxItems = schema.maxItems();
            } else if constexpr (std::is_same_v<T, McpProtocolTitledMultiSelectEnumSchema>) {
                QStringList texts;
                QStringList values;
                const auto anyOf = schema.items().anyOf();
                for (const auto &item : anyOf) {
                    texts.append(item.title());
                    values.append(item.constValue());
                }
                widget = createListWidget(texts, values, schema.defaultValue(), parent);
                editor.minItems = schema.minItems();
                editor.maxItems = schema.maxItems();
            }
            editor.widget = widget;
            return editor;
        },
        definition);
}
}

TextAutoGenerateElicitationWidget::TextAutoGenerateElicitationWidget(QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new QVBoxLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);
    mMainLayout->setContentsMargins({});
}

TextAutoGenerateElicitationWidget::~TextAutoGenerateElicitationWidget() = default;

void TextAutoGenerateElicitationWidget::setRequest(const McpProtocolElicitRequest &request)
{
    delete mFormWidget;
    mFields.clear();
    mFormMode = false;
    mFormWidget = new QWidget(this);
    mFormWidget->setObjectName(u"mFormWidget"_s);
    mMainLayout->addWidget(mFormWidget);
    auto formLayout = new QFormLayout(mFormWidget);
    formLayout->setObjectName(u"formLayout"_s);
    formLayout->setContentsMargins({});

    auto messageLabel = new QLabel(mFormWidget);
    messageLabel->setObjectName(u"messageLabel"_s);
    messageLabel->setWordWrap(true);
    messageLabel->setTextFormat(Qt::PlainText);
    formLayout->addRow(messageLabel);

    const McpProtocolUtils::ElicitRequestParams params = request.params();
    if (const auto urlParams = std::get_if<McpProtocolElicitRequestURLParams>(&params)) {
        messageLabel->setText(urlParams->message());
        // Server asks to open an URL: user must see it before accepting
        auto urlLabel = new QLabel(mFormWidget);
        urlLabel->setObjectName(u"urlLabel"_s);
        urlLabel->setTextFormat(Qt::PlainText);
        urlLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        urlLabel->setText(urlParams->url());
        formLayout->addRow(i18n("URL:"), urlLabel);
        Q_EMIT contentChanged();
        return;
    }
    mFormMode = true;
    const auto &formParams = std::get<McpProtocolElicitRequestFormParams>(params);
    messageLabel->setText(formParams.message());
    const McpProtocolElicitRequestFormParams::RequestedSchema schema = formParams.requestedSchema();
    const QStringList required = schema.required().value_or(QStringList());
    const QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> properties = schema.properties();
    for (auto it = properties.cbegin(); it != properties.cend(); ++it) {
        const Editor editor = createEditor(it.value(), mFormWidget);
        if (!editor.widget) {
            continue;
        }
        editor.widget->setObjectName(it.key());
        if (editor.description.has_value()) {
            editor.widget->setToolTip(*editor.description);
        }
        const bool isRequired = required.contains(it.key());
        mFields.append({.name = it.key(),
                        .editor = editor.widget,
                        .required = isRequired,
                        .minLength = editor.minLength,
                        .minItems = editor.minItems,
                        .maxItems = editor.maxItems});
        connectEditor(editor.widget);
        QString label = editor.title.value_or(it.key());
        if (isRequired) {
            label = i18nc("Label of required field", "%1 (required):", label);
        } else {
            label = i18nc("Label of field", "%1:", label);
        }
        formLayout->addRow(label, editor.widget);
    }
    Q_EMIT contentChanged();
}

void TextAutoGenerateElicitationWidget::connectEditor(QWidget *editor)
{
    // QDateEdit is a QDateTimeEdit
    if (auto lineEdit = qobject_cast<QLineEdit *>(editor)) {
        connect(lineEdit, &QLineEdit::textChanged, this, &TextAutoGenerateElicitationWidget::contentChanged);
    } else if (auto listWidget = qobject_cast<QListWidget *>(editor)) {
        connect(listWidget, &QListWidget::itemChanged, this, &TextAutoGenerateElicitationWidget::contentChanged);
    }
    // Other editors always have a valid value
}

std::optional<McpProtocolUtils::ElicitResultContent> TextAutoGenerateElicitationWidget::content() const
{
    if (!mFormMode) {
        return std::nullopt;
    }
    McpProtocolUtils::ElicitResultContent result;
    for (const Field &field : mFields) {
        if (auto lineEdit = qobject_cast<QLineEdit *>(field.editor)) {
            if (const QString text = lineEdit->text(); !text.isEmpty()) {
                result.insert(field.name, text);
            }
        } else if (auto dateEdit = qobject_cast<QDateEdit *>(field.editor)) {
            result.insert(field.name, dateEdit->date().toString(Qt::ISODate));
        } else if (auto dateTimeEdit = qobject_cast<QDateTimeEdit *>(field.editor)) {
            result.insert(field.name, dateTimeEdit->dateTime().toString(Qt::ISODate));
        } else if (auto spinBox = qobject_cast<QSpinBox *>(field.editor)) {
            result.insert(field.name, spinBox->value());
        } else if (auto doubleSpinBox = qobject_cast<QDoubleSpinBox *>(field.editor)) {
            result.insert(field.name, doubleSpinBox->value());
        } else if (auto checkBox = qobject_cast<QCheckBox *>(field.editor)) {
            result.insert(field.name, checkBox->isChecked());
        } else if (auto comboBox = qobject_cast<QComboBox *>(field.editor)) {
            if (comboBox->currentIndex() != -1) {
                result.insert(field.name, comboBox->currentData().toString());
            }
        } else if (auto listWidget = qobject_cast<QListWidget *>(field.editor)) {
            result.insert(field.name, checkedValues(listWidget));
        }
    }
    return result;
}

bool TextAutoGenerateElicitationWidget::isValid() const
{
    for (const Field &field : mFields) {
        if (auto lineEdit = qobject_cast<QLineEdit *>(field.editor)) {
            const qsizetype length = lineEdit->text().length();
            if (length == 0) {
                if (field.required) {
                    return false;
                }
            } else if (field.minLength.has_value() && length < *field.minLength) {
                return false;
            }
        } else if (auto comboBox = qobject_cast<QComboBox *>(field.editor)) {
            if (field.required && comboBox->currentIndex() == -1) {
                return false;
            }
        } else if (auto listWidget = qobject_cast<QListWidget *>(field.editor)) {
            const qsizetype count = checkedValues(listWidget).count();
            if ((field.minItems.has_value() && count < *field.minItems) || (field.maxItems.has_value() && count > *field.maxItems)) {
                return false;
            }
        }
    }
    return true;
}

#include "moc_textautogenerateelicitationwidget.cpp"
