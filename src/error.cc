/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <archivecc/error.h>

#include <archive.h>
#include <stdexcept>

namespace {

archivecc::Error::Code error_code(int code)
{
	using namespace ::archivecc;

	switch (code) {
	case ARCHIVE_EOF: return Error::Code::AEOF;
	case ARCHIVE_OK: return Error::Code::OK;
	case ARCHIVE_RETRY: return Error::Code::RETRY;
	case ARCHIVE_WARN: return Error::Code::WARN;
	case ARCHIVE_FAILED: return Error::Code::FAILED;
	case ARCHIVE_FATAL: return Error::Code::FATAL;
	}

	throw std::logic_error(std::string("unknown error:") + std::to_string(code));
	return Error::Code::FATAL;
}

}

namespace archivecc {

Error::Error() = default;

Error::Error(int code)
:
	code_(error_code(code))
{ }

Error::operator bool() const noexcept
{
	return code_ != Code::OK;
}

Error::Code Error::code() const noexcept
{
	return code_;
}

}
