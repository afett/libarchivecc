/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include "entry-impl.h"

#include <archive_entry.h>
#include <cassert>

namespace archivecc {

EntryImpl::EntryImpl()
:
	entry_(archive_entry_new(), &archive_entry_free)
{
	if (entry_ == nullptr) {
		throw std::bad_alloc();
	}
}

EntryImpl::EntryImpl(archive_entry* entry_)
:
	entry_(entry_, &archive_entry_free)
{
	if (entry_ == nullptr) {
		throw std::bad_alloc();
	}
}

void EntryImpl::clear() noexcept
{
	archive_entry_clear(raw());
}

Entry::ptr EntryImpl::clone() const
{
	return std::make_shared<EntryImpl>(archive_entry_clone(raw()));
}

Entry::ptr Entry::create()
{
	return std::make_shared<EntryImpl>();
}

Entry::~Entry() = default;

class EntryFactoryImpl : public EntryFactory {
public:
	Entry::ptr create_entry() const override;
};

Entry::ptr EntryFactory::create_entry() const
{
	return Entry::create();
}

EntryFactory::ptr EntryFactory::create()
{
	return std::make_shared<EntryFactoryImpl>();
}

EntryFactory::~EntryFactory() = default;

}
