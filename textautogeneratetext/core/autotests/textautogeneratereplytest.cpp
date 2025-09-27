/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratereplytest.h"
#include "core/textautogeneratereply.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateReplyTest)

class CustomTextAutoGenerateReply : public TextAutoGenerateText::TextAutoGenerateReply
{
    Q_OBJECT
public:
    using TextAutoGenerateReply::TextAutoGenerateReply;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply::Response readResponse() const override;
};

TextAutoGenerateText::TextAutoGenerateReply::Response CustomTextAutoGenerateReply::readResponse() const
{
    return {};
}

TextAutoGenerateReplyTest::TextAutoGenerateReplyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateReplyTest::shouldHaveDefaultValues()
{
    CustomTextAutoGenerateReply w(nullptr, {});
    // TODO
}

#include "textautogeneratereplytest.moc"
