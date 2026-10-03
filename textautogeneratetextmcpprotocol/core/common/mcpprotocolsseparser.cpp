/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsseparser.h"

using namespace TextAutoGenerateTextMcpProtocolCore;

QList<McpProtocolSseParser::Event> McpProtocolSseParser::feed(const QByteArray &chunk)
{
    mBuffer.append(chunk);
    QList<Event> events;
    qsizetype start = 0;
    while (start < mBuffer.size()) {
        qsizetype end = start;
        while (end < mBuffer.size() && mBuffer.at(end) != '\n' && mBuffer.at(end) != '\r') {
            ++end;
        }
        if (end == mBuffer.size()) {
            // Incomplete line, wait for more data
            break;
        }
        qsizetype next = end + 1;
        if (mBuffer.at(end) == '\r') {
            if (next == mBuffer.size()) {
                // Can be the first part of "\r\n", wait for more data
                break;
            }
            if (mBuffer.at(next) == '\n') {
                ++next;
            }
        }
        parseLine(QByteArrayView(mBuffer).sliced(start, end - start), events);
        start = next;
    }
    mBuffer.remove(0, start);
    return events;
}

void McpProtocolSseParser::parseLine(QByteArrayView line, QList<Event> &events)
{
    if (line.isEmpty()) {
        // Empty line => dispatch event
        if (!mData.isEmpty()) {
            mData.chop(1); // Remove last '\n'
            Event event;
            if (!mEventType.isEmpty()) {
                event.event = mEventType;
            }
            event.data = mData;
            event.id = mLastEventId;
            events.append(std::move(event));
        }
        mData.clear();
        mEventType.clear();
        return;
    }
    if (line.startsWith(':')) {
        // Comment (keep-alive)
        return;
    }
    QByteArrayView field = line;
    QByteArrayView value;
    if (const qsizetype index = line.indexOf(':'); index != -1) {
        field = line.first(index);
        value = line.sliced(index + 1);
        if (value.startsWith(' ')) {
            value = value.sliced(1);
        }
    }
    if (field == "data") {
        mData.append(value);
        mData.append('\n');
    } else if (field == "event") {
        mEventType = value.toByteArray();
    } else if (field == "id") {
        if (!value.contains('\0')) {
            mLastEventId = value.toByteArray();
        }
    }
    // "retry" and unknown fields are ignored
}

void McpProtocolSseParser::clear()
{
    mBuffer.clear();
    mEventType.clear();
    mData.clear();
    mLastEventId.clear();
}

QByteArray McpProtocolSseParser::lastEventId() const
{
    return mLastEventId;
}
