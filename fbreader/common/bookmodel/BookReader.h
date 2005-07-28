/*
 * FBReader -- electronic book reader
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __BOOKREADER_H__
#define __BOOKREADER_H__

#include <vector>
#include <string>

#include <abstract/ZLString.h>

#include "../model/TextKind.h"
#include "../model/Paragraph.h"

class BookModel;
class PlainTextModel;
class ZLInputStream;

class BookReader {

public:
	BookReader(BookModel &model) MODEL_SECTION;
	virtual ~BookReader() MODEL_SECTION;

	void setMainTextModel() MODEL_SECTION;
	void setFootnoteTextModel(const std::string &id) MODEL_SECTION;
	void unsetTextModel() MODEL_SECTION;
	bool currentTextModelIsNull() const MODEL_SECTION;

	void insertEndOfSectionParagraph() MODEL_SECTION;
	void pushKind(TextKind kind) MODEL_SECTION;
	void popKind() MODEL_SECTION;
	void beginParagraph(Paragraph::Kind kind = Paragraph::TEXT_PARAGRAPH) MODEL_SECTION;
	void endParagraph() MODEL_SECTION;
	void addControl(TextKind kind, bool start) MODEL_SECTION;
	void addHyperlinkControl(TextKind kind, const std::string &label) MODEL_SECTION;
	void addHyperlinkLabel(const std::string &label) MODEL_SECTION;

	void addImageReference(const std::string &id) MODEL_SECTION;
	void addImage(const std::string &id, ZLImage *image) MODEL_SECTION;

	void beginContentsParagraph() MODEL_SECTION;
	void endContentsParagraph() MODEL_SECTION;

	void addDataToBuffer(const char *data, int len) MODEL_SECTION;
	virtual void flushTextBufferToParagraph() MODEL_SECTION;

	void beginImageData() MODEL_SECTION;
	void endImageData() MODEL_SECTION;

	void enterTitle() { myInsideTitle = true; }
	void exitTitle() { myInsideTitle = false; }

private:
	BookModel &myModel;
	PlainTextModel *myCurrentTextModel;

	std::vector<TextKind> myKindStack;

	Paragraph *myCurrentParagraph;
	ParagraphWithReference *myCurrentContentsParagraph;
	bool myProcessData;

	bool mySectionContainsRegularContents;
	bool myInsideTitle;

public:
	ZLStringBuffer myBuffer;
};

#endif /* __BOOKREADER_H__ */
