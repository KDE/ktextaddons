/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QList>
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser
 * \brief Parse a "text/event-stream" (Server-Sent Events) stream
 * Data can be split anywhere between two feed() calls.
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSseParser
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Event {
        QByteArray event = QByteArrayLiteral("message");
        QByteArray data;
        QByteArray id;
        [[nodiscard]] bool operator==(const Event &other) const = default;
    };

    /*!
     * Append \a chunk to the internal buffer and return the complete events.
     */
    [[nodiscard]] QList<Event> feed(const QByteArray &chunk);
    /*!
     * Reset the parser state (buffer, pending event and last event id).
     */
    void clear();
    /*!
     * Drop buffered data and pending event (connection lost) but keep
     * last event id and retry delay, needed to resume stream.
     */
    void resetConnection();

    [[nodiscard]] QByteArray lastEventId() const;
    /*!
     * Reconnection delay in ms sent by server ("retry" field), -1 if not defined.
     */
    [[nodiscard]] int retry() const;

private:
    void parseLine(QByteArrayView line, QList<Event> &events);
    QByteArray mBuffer;
    QByteArray mEventType;
    QByteArray mData;
    QByteArray mLastEventId;
    int mRetry = -1;
};
}
