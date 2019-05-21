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

private:
	class Deleter {
	public:
		void operator()(archive *ar) const noexcept
		{
			archive_read_free(ar);
		}
	};

	inline archive *raw() const
	{
		return ar_.get();
	}

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
