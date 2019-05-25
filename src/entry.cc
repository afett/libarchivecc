/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <archivecc/entry.h>

#include <archive_entry.h>
#include <cassert>

namespace archivecc {

class EntryImpl : public Entry {
public:
	EntryImpl();

	void clear() noexcept override;
private:
	class Deleter {
	public:
		void operator()(archive_entry *ar) const noexcept
		{
			archive_entry_free(ar);
		}
	};

	inline archive_entry *raw() const
	{
		return entry_.get();
	}

	std::unique_ptr<archive_entry, Deleter> entry_;
};

EntryImpl::EntryImpl()
:
	entry_(archive_entry_new())
{
	if (entry_ == nullptr) {
		throw std::bad_alloc();
	}
}

void EntryImpl::clear() noexcept
{
	archive_entry_clear(raw());
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
