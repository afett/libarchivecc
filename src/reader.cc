/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <archivecc/reader.h>

#include <archive.h>

namespace archivecc {

class ReaderImpl : public Reader {
public:
	ReaderImpl();

private:
	class Deleter {
	public:
		void operator()(archive *ar) const noexcept
		{
			archive_read_free(ar);
		}
	};

	std::unique_ptr<archive, Deleter> ar_;
};

ReaderImpl::ReaderImpl()
:
	ar_(archive_read_new())
{
	if (ar_ == nullptr) {
		throw std::bad_alloc();
	}
}

Reader::ptr Reader::create()
{
	return std::make_shared<ReaderImpl>();
}

Reader::~Reader() = default;

}
