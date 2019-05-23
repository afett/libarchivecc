/*
   Copyright (c) 2019 Andreas Fett
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ARCHIVECC_READER_H
#define ARCHIVECC_READER_H

#include <memory>

#include <archivecc/error.h>

namespace archivecc {

class Reader {
public:
	using ptr = std::shared_ptr<Reader>;

	virtual Error support_filter_all() = 0;
	virtual Error support_filter_bzip2() = 0;
	virtual Error support_filter_compress() = 0;
	virtual Error support_filter_gzip() = 0;
	virtual Error support_filter_grzip() = 0;
	virtual Error support_filter_lrzip() = 0;
	virtual Error support_filter_lz4() = 0;
	virtual Error support_filter_lzip() = 0;
	virtual Error support_filter_lzma() = 0;
	virtual Error support_filter_lzop() = 0;
	virtual Error support_filter_program(const char *) = 0;
	virtual Error support_filter_program_signature(const char *, const void *, size_t) = 0;
	virtual Error support_filter_rpm() = 0;
	virtual Error support_filter_uu() = 0;
	virtual Error support_filter_xz() = 0;

	virtual Error support_format_7zip() = 0;
	virtual Error support_format_all() = 0;
	virtual Error support_format_ar() = 0;
	virtual Error support_format_cab() = 0;
	virtual Error support_format_cpio() = 0;
	virtual Error support_format_empty() = 0;
	virtual Error support_format_gnutar() = 0;
	virtual Error support_format_iso9660() = 0;
	virtual Error support_format_lha() = 0;
	virtual Error support_format_mtree() = 0;
	virtual Error support_format_rar() = 0;
	virtual Error support_format_raw() = 0;
	virtual Error support_format_tar() = 0;
	virtual Error support_format_warc() = 0;
	virtual Error support_format_xar() = 0;
	virtual Error support_format_zip() = 0;
	virtual Error support_format_zip_streamable() = 0;
	virtual Error support_format_zip_seekable() = 0;

	enum class Seek {
		SET,
		CUR,
		END,
	};

	using read_callback = std::function<ssize_t(const void **)>;
	using skip_callback = std::function<int64_t(int64_t)>;
	using seek_callback = std::function<int64_t(int64_t, Seek)>;
	using write_callback = std::function<ssize_t(const void *, size_t)>;
	using open_callback = std::function<int(void)>;
	using close_callback = std::function<int(void)>;

	virtual Error set_open_callback(open_callback const&) = 0;
	virtual Error set_read_callback(read_callback const&) = 0;
	virtual Error set_seek_callback(seek_callback const&) = 0;
	virtual Error set_skip_callback(skip_callback const&) = 0;
	virtual Error set_close_callback(close_callback const&) = 0;

	virtual Error open() = 0;
	virtual Error open_filename(const char *, size_t) = 0;
	virtual Error open_filename(std::string const&, size_t) = 0;
	virtual Error open_memory(const void *, size_t) = 0;
	virtual Error open_fd(int, size_t) = 0;

	static ptr create();
	virtual ~Reader();
};

class ReaderFactory {
public:
	using ptr = std::shared_ptr<ReaderFactory>;

	virtual Reader::ptr create_reader() const = 0;

	static ptr create();
	virtual ~ReaderFactory();
};

}

#endif
