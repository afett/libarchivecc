/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <archivecc/entry.h>

struct archive;
struct archive_entry;

namespace archivecc {

class EntryImpl : public Entry {
public:
	EntryImpl();
	explicit EntryImpl(archive_entry*);
	explicit EntryImpl(archive*);

	void clear() noexcept override;
	ptr clone() const override;

	inline archive_entry *raw() const
	{
		return entry_.get();
	}

private:
	std::unique_ptr<archive_entry, void(*)(archive_entry*)> entry_;
};

}
