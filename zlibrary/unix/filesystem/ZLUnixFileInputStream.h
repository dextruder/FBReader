/*
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

#ifndef __ZLUNIXFILEINPUTSTREAM_H__
#define __ZLUNIXFILEINPUTSTREAM_H__

#include <stdio.h>

#include <abstract/ZLInputStream.h>

class ZLUnixFileInputStream : public ZLInputStream {

public:
	ZLUnixFileInputStream(const std::string &name);
	~ZLUnixFileInputStream();
	bool open();
	int read(char *buffer, int maxSize);
	int read(unsigned short *p);
	int read(unsigned long *p);
	void close();

	void seek(int offset) { fseek(myFile, offset, SEEK_CUR); }
	int offset() const { return ftell(myFile); }

private:
	std::string myName;
	FILE *myFile;
};

#endif /* __ZLUNIXFILEINPUTSTREAM_H__ */
