/*
 * Copyright (C) 2004-2006 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ZLOPENFILEDIALOG_H__
#define __ZLOPENFILEDIALOG_H__

#include <vector>
#include <string>

#include <shared_ptr.h>

class ZLTreeNode;
typedef shared_ptr<ZLTreeNode> ZLTreeNodePtr;

class ZLTreeHandler {

protected:
	ZLTreeHandler();
	virtual ~ZLTreeHandler();
	
public:
	virtual const std::string accept(const std::string &name) const = 0;

	virtual const std::string stateDisplayName() const = 0;
	virtual void changeFolder(const std::string &nodeId) = 0;
	virtual const std::vector<ZLTreeNodePtr> &subnodes() const = 0;
	virtual std::string relativeId(const std::string &nodeId) const = 0;
};

class ZLTreeNode {

public:
	ZLTreeNode(const std::string &id, const std::string &displayName, const std::string &pixmapName, bool isFolder);

	const std::string &id() const;
	const std::string &displayName() const;
	const std::string &pixmapName() const;
	bool isFolder() const;

private:
	std::string myId;
	std::string myDisplayName;
	std::string myPixmapName;
	bool myIsFolder;
};

class ZLOpenFileDialog {

protected:
	ZLOpenFileDialog(ZLTreeHandler &handler);
	virtual ~ZLOpenFileDialog();

public:
	virtual void run() = 0;

protected:
	void runNode(const ZLTreeNodePtr node);
	virtual void exitDialog() = 0;
	virtual void update(const std::string &selectedNodeId) = 0;
	const ZLTreeHandler &handler() const;

private:
	ZLTreeHandler &myHandler;
};

inline const std::string &ZLTreeNode::id() const { return myId; }
inline const std::string &ZLTreeNode::displayName() const { return myDisplayName; }
inline const std::string &ZLTreeNode::pixmapName() const { return myPixmapName; }

inline const ZLTreeHandler &ZLOpenFileDialog::handler() const { return myHandler; }

#endif /* __ZLOPENFILEDIALOG_H__ */
