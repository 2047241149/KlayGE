/**
 * @file Extract7z.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef _KFL_EXTRACT7Z_HPP
#define _KFL_EXTRACT7Z_HPP

#pragma once

#include <KFL/PreDeclare.hpp>

#include <string>

namespace KlayGE
{
	uint32_t Find7z(ResIdentifierPtr const & archive_is,
		std::string const & password,
		std::string const & extract_file_path);
	void Extract7z(ResIdentifierPtr const & archive_is,
		std::string const & password,
		std::string const & extract_file_path,
		boost::shared_ptr<std::ostream> const & os);
}

#endif		// _KFL_EXTRACT7Z_HPP
