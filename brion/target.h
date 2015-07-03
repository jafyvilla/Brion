/* Copyright (c) 2013-2015, EPFL/Blue Brain Project
 *                          Daniel Nachbaur <daniel.nachbaur@epfl.ch>
 *
 * This file is part of Brion <https://github.com/BlueBrain/Brion>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BRION_TARGET
#define BRION_TARGET

#include <brion/types.h>
#include <boost/noncopyable.hpp>

namespace brion
{

namespace detail { class Target; }

/** Read access to a Target file.
 *
 * Following RAII, this class is ready to use after the creation and will ensure
 * release of resources upon destruction.
 */
class Target : public boost::noncopyable
{
public:
    /** Close target file. @version 1.0 */
    ~Target();

    /** @name Read API */
    //@{
    /** Open the given source to a target file for reading.
     *
     * @param source filepath to target file
     * @throw std::runtime_error if file is not a valid target file
     * @version 1.0
     */
    explicit Target( const std::string& source );

    /** Get list of targets for the desired type.
     *
     * @param type desired target type to look for
     * @return list of target names
     * @version 1.0
     */
    const Strings& getTargetNames( const TargetType type ) const;

    /** Get targets and/or GIDSet grouped by the given target
     *
     * @param name target name to get the values from
     * @return list of values in the target. Can be targets and/or GIDSet
     * @version 1.0
     */
    const Strings& get( const std::string& name ) const;
    //@}

private:
    friend std::ostream& operator << ( std::ostream&, const Target& );

    detail::Target* const _impl;
};

/** Stream out content of target file. */
std::ostream& operator << ( std::ostream&, const Target& );

}

#endif