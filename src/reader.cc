/*
   Copyright (c) 2019 Andreas Fett. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.
*/

#include <archivecc/reader.h>

#include <archive.h>
#include <archive_entry.h>
#include <cassert>

#include "entry-impl.h"

namespace archivecc {

class ReaderImpl : public Reader {
public:
	ReaderImpl();

	Error support_filter_all() override;
	Error support_filter_bzip2() override;
	Error support_filter_compress() override;
	Error support_filter_gzip() override;
	Error support_filter_grzip() override;
	Error support_filter_lrzip() override;
	Error support_filter_lz4() override;
	Error support_filter_lzip() override;
	Error support_filter_lzma() override;
	Error support_filter_lzop() override;
	Error support_filter_program(const char *command) override;
	Error support_filter_program_signature(const char * /* cmd */, const void * /* match */, size_t) override;
	Error support_filter_rpm() override;
	Error support_filter_uu() override;
	Error support_filter_xz() override;

	Error support_format_7zip() override;
	Error support_format_all() override;
	Error support_format_ar() override;
	Error support_format_cab() override;
	Error support_format_cpio() override;
	Error support_format_empty() override;
	Error support_format_gnutar() override;
	Error support_format_iso9660() override;
	Error support_format_lha() override;
	Error support_format_mtree() override;
	Error support_format_rar() override;
	Error support_format_raw() override;
	Error support_format_tar() override;
	Error support_format_warc() override;
	Error support_format_xar() override;
	Error support_format_zip() override;
	Error support_format_zip_streamable() override;
	Error support_format_zip_seekable() override;

	Error set_open_callback(open_callback const&) override;
	Error set_read_callback(read_callback const&) override;
	Error set_seek_callback(seek_callback const&) override;
	Error set_skip_callback(skip_callback const&) override;
	Error set_close_callback(close_callback const&) override;

	Error open() override;
	Error open_filename(const char *, size_t) override;
	Error open_filename(std::string const&, size_t) override;
	Error open_memory(const void *, size_t) override;
	Error open_fd(int, size_t) override;

	Error close() override;
	Entry::ptr create_entry() override;

	Error next_header(Entry::ptr const&) override;

private:
	inline archive *raw() const
	{
		return ar_.get();
	}

	static la_ssize_t read_callback_stub(archive *, void *, const void **);
	static la_int64_t skip_callback_stub(archive *, void *, la_int64_t);
	static la_int64_t seek_callback_stub(archive *, void *, la_int64_t, int);
	static la_ssize_t write_callback_stub(archive *, void *, const void *, size_t);
	static int open_callback_stub(archive *, void *);
	static int close_callback_stub(archive *, void *);

	std::unique_ptr<archive, decltype(&archive_read_free)> ar_;
	read_callback read_cb_;
	skip_callback skip_cb_;
	seek_callback seek_cb_;
	write_callback write_cb_;
	open_callback open_cb_;
	close_callback close_cb_;
};

ReaderImpl::ReaderImpl()
:
	ar_(archive_read_new(), &archive_read_free)
{
	if (ar_ == nullptr) {
		throw std::bad_alloc();
	}
}

Error ReaderImpl::support_filter_all()
{
	return Error(archive_read_support_filter_all(raw()));
}

Error ReaderImpl::support_filter_bzip2()
{
	return Error(archive_read_support_filter_bzip2(raw()));
}

Error ReaderImpl::support_filter_compress()
{
	return Error(archive_read_support_filter_compress(raw()));
}

Error ReaderImpl::support_filter_gzip()
{
	return Error(archive_read_support_filter_gzip(raw()));
}

Error ReaderImpl::support_filter_grzip()
{
	return Error(archive_read_support_filter_grzip(raw()));
}

Error ReaderImpl::support_filter_lrzip()
{
	return Error(archive_read_support_filter_lrzip(raw()));
}

Error ReaderImpl::support_filter_lz4()
{
	return Error(archive_read_support_filter_lz4(raw()));
}

Error ReaderImpl::support_filter_lzip()
{
	return Error(archive_read_support_filter_lzip(raw()));
}

Error ReaderImpl::support_filter_lzma()
{
	return Error(archive_read_support_filter_lzma(raw()));
}

Error ReaderImpl::support_filter_lzop()
{
	return Error(archive_read_support_filter_lzop(raw()));
}

Error ReaderImpl::support_filter_program(const char *command)
{
	return Error(archive_read_support_filter_program(raw(), command));
}

Error ReaderImpl::support_filter_program_signature(const char *cmd, const void *signature, size_t signature_length)
{
	return Error(archive_read_support_filter_program_signature(raw(), cmd, signature, signature_length));
}

Error ReaderImpl::support_filter_rpm()
{
	return Error(archive_read_support_filter_rpm(raw()));
}

Error ReaderImpl::support_filter_uu()
{
	return Error(archive_read_support_filter_uu(raw()));
}

Error ReaderImpl::support_filter_xz()
{
	return Error(archive_read_support_filter_xz(raw()));
}

Error ReaderImpl::support_format_7zip()
{
	return Error(archive_read_support_format_7zip(raw()));
}

Error ReaderImpl::support_format_all()
{
	return Error(archive_read_support_filter_all(raw()));
}

Error ReaderImpl::support_format_ar()
{
	return Error(archive_read_support_format_ar(raw()));
}

Error ReaderImpl::support_format_cab()
{
	return Error(archive_read_support_format_cab(raw()));
}

Error ReaderImpl::support_format_cpio()
{
	return Error(archive_read_support_format_cpio(raw()));
}

Error ReaderImpl::support_format_empty()
{
	return Error(archive_read_support_format_empty(raw()));
}

Error ReaderImpl::support_format_gnutar()
{
	return Error(archive_read_support_format_gnutar(raw()));
}

Error ReaderImpl::support_format_iso9660()
{
	return Error(archive_read_support_format_iso9660(raw()));
}

Error ReaderImpl::support_format_lha()
{
	return Error(archive_read_support_format_lha(raw()));
}

Error ReaderImpl::support_format_mtree()
{
	return Error(archive_read_support_format_mtree(raw()));
}

Error ReaderImpl::support_format_rar()
{
	return Error(archive_read_support_format_rar(raw()));
}

Error ReaderImpl::support_format_raw()
{
	return Error(archive_read_support_format_raw(raw()));
}

Error ReaderImpl::support_format_tar()
{
	return Error(archive_read_support_format_tar(raw()));
}

Error ReaderImpl::support_format_warc()
{
	return Error(archive_read_support_format_warc(raw()));
}

Error ReaderImpl::support_format_xar()
{
	return Error(archive_read_support_format_xar(raw()));
}

Error ReaderImpl::support_format_zip()
{
	return Error(archive_read_support_format_zip(raw()));
}

Error ReaderImpl::support_format_zip_streamable()
{
	return Error(archive_read_support_format_zip_streamable(raw()));
}

Error ReaderImpl::support_format_zip_seekable()
{
	return Error(archive_read_support_format_zip_seekable(raw()));
}

#define ASSERT_OR_FAIL(expr)                   \
	assert(expr);                          \
	if (!(expr)) { return ARCHIVE_FATAL; } \

ssize_t ReaderImpl::read_callback_stub(archive *ar, void *data, const void **buffer)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->read_cb_);
	return self->read_cb_(buffer);
}

int64_t ReaderImpl::skip_callback_stub(archive *ar, void *data, int64_t request)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->skip_cb_);
	return self->skip_cb_(request);
}

int64_t ReaderImpl::seek_callback_stub(archive *ar, void *data, int64_t offset, int whence)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->seek_cb_);
	Seek w;
	switch (whence) {
	case SEEK_SET: w = Seek::SET; break;
	case SEEK_CUR: w = Seek::CUR; break;
	case SEEK_END: w = Seek::END; break;
	default:
	       ASSERT_OR_FAIL(false && "bad seek whence value");
	}
	return self->seek_cb_(offset, w);
}

ssize_t ReaderImpl::write_callback_stub(archive *ar, void *data, const void *buffer, size_t length)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->write_cb_);
	return self->write_cb_(buffer, length);
}

int ReaderImpl::open_callback_stub(archive *ar, void *data)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->open_cb_);
	return self->open_cb_();
}

int ReaderImpl::close_callback_stub(archive *ar, void *data)
{
	auto self = static_cast<ReaderImpl*>(data);
	ASSERT_OR_FAIL(ar && self && self->raw() == ar && self->close_cb_);
	return self->close_cb_();
}

Error ReaderImpl::set_open_callback(open_callback const& cb)
{
	return Error(archive_read_set_open_callback(raw(),
		cb ? ReaderImpl::open_callback_stub : nullptr));
}

Error ReaderImpl::set_read_callback(read_callback const& cb)
{
	return Error(archive_read_set_read_callback(raw(),
		cb ? ReaderImpl::read_callback_stub : nullptr));
}

Error ReaderImpl::set_seek_callback(seek_callback const& cb)
{
	return Error(archive_read_set_seek_callback(raw(),
		cb ? ReaderImpl::seek_callback_stub : nullptr));
}

Error ReaderImpl::set_skip_callback(skip_callback const& cb)
{
	return Error(archive_read_set_skip_callback(raw(),
		cb ? ReaderImpl::skip_callback_stub : nullptr));
}

Error ReaderImpl::set_close_callback(close_callback const& cb)
{
	return Error(archive_read_set_close_callback(raw(),
		cb ? ReaderImpl::close_callback_stub : nullptr));
}

Error ReaderImpl::open()
{
	return Error(archive_read_open1(raw()));
}

Error ReaderImpl::open_filename(const char *filename, size_t block_size)
{
	return Error(archive_read_open_filename(raw(), filename, block_size));
}

Error ReaderImpl::open_filename(std::string const& filename, size_t block_size)
{
	return Error(archive_read_open_filename(raw(), filename.c_str(), block_size));
}

Error ReaderImpl::open_memory(const void *buff, size_t size)
{
	return Error(archive_read_open_memory(raw(), buff, size));
}

Error ReaderImpl::open_fd(int fd, size_t block_size)
{
	return Error(archive_read_open_fd(raw(), fd, block_size));
}

Error ReaderImpl::close()
{
	return Error(archive_read_close(raw()));
}

Entry::ptr ReaderImpl::create_entry()
{
	return std::make_shared<EntryImpl>(archive_entry_new2(raw()));
}

Error ReaderImpl::next_header(Entry::ptr const& entry)
{
	auto entry_impl = std::dynamic_pointer_cast<EntryImpl>(entry);
	assert(entry_impl);
	if (!entry_impl) {
		return Error(ARCHIVE_FATAL);
	}
	return Error(archive_read_next_header2(raw(), entry_impl->raw()));
}

Reader::ptr Reader::create()
{
	return std::make_shared<ReaderImpl>();
}

Reader::~Reader() = default;

class ReaderFactoryImpl : public ReaderFactory {
public:
	Reader::ptr create_reader() const override;
};

Reader::ptr ReaderFactory::create_reader() const
{
	return Reader::create();
}

ReaderFactory::ptr ReaderFactory::create()
{
	return std::make_shared<ReaderFactoryImpl>();
}

ReaderFactory::~ReaderFactory() = default;

}
