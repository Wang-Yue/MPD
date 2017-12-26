/*
 * Copyright 2003-2017 The Music Player Daemon Project
 * http://www.musicpd.org
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_ICY_INPUT_STREAM_HXX
#define MPD_ICY_INPUT_STREAM_HXX

#include "ProxyInputStream.hxx"
#include "Compiler.h"

#include <memory>

struct Tag;
class IcyMetaDataParser;

/**
 * An #InputStream filter that parses Icy metadata.
 */
class IcyInputStream final : public ProxyInputStream {
	std::shared_ptr<IcyMetaDataParser> parser;

	/**
	 * The #Tag object ready to be requested via ReadTag().
	 */
	std::unique_ptr<Tag> input_tag;

	/**
	 * The #Tag object ready to be requested via ReadTag().
	 */
	std::unique_ptr<Tag> icy_tag;

	offset_type override_offset = 0;

public:
	/**
	 * @param _parser a IcyMetaDataParser instance which is shared
	 * with our input; it needs to be shared because our input
	 * needs to feed parameters (e.g. from the "icy-metaint"
	 * header) into it
	 */
	IcyInputStream(InputStream *_input,
		       std::shared_ptr<IcyMetaDataParser> _parser) noexcept;
	virtual ~IcyInputStream() noexcept;

	IcyInputStream(const IcyInputStream &) = delete;
	IcyInputStream &operator=(const IcyInputStream &) = delete;

	gcc_pure
	bool IsEnabled() const noexcept;

	/* virtual methods from InputStream */
	void Update() noexcept override;
	std::unique_ptr<Tag> ReadTag() override;
	size_t Read(void *ptr, size_t size) override;
};

#endif
