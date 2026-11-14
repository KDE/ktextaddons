/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "cmark-rc/buffer.h"
#include "cmark-rc/chunk.h"
#include "cmark-rc/cmark-rc.h"
#include "cmark-rc/cmark_ctype.h"
#include "cmark-rc/houdini.h"
#include "cmark-rc/inlines.h"
#include "cmark-rc/iterator.h"
#include "cmark-rc/node.h"
#include "cmark-rc/parser.h"
#include "cmark-rc/references.h"
#include "cmark-rc/render.h"
#include "cmark-rc/scanners.h"
#include "cmark-rc/utf8.h"
#include "cmark/textutilsblockcmarksupport.h"
#include "colors/textutilscolorsandmessageviewstyle.h"
#include "converttext/converttext.h"
#include "syntaxhighlighting/textutilsblockcodemanager.h"
#include "syntaxhighlighting/textutilscopyblockiconcache.h"
#include "syntaxhighlighting/textutilsiconnamecache.h"
#include "syntaxhighlighting/textutilssyntaxhighlighter.h"
#include "syntaxhighlighting/textutilssyntaxhighlightingmanager.h"
#include "texttohtml/textutilsemoticonsparser_p.h"
#include "texttohtml/textutilstexttohtml.h"
#include "texttohtml/textutilstexttohtml_p.h"
#include "textutils_private_export.h"
