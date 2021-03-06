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

#ifndef BRION_PLUGIN_COMPARTMENTREPORTHDF5
#define BRION_PLUGIN_COMPARTMENTREPORTHDF5

#include "compartmentReportCommon.h"

#include <boost/filesystem/path.hpp>
#include <lunchbox/stdExt.h>
#include <H5Cpp.h>

namespace brion
{
namespace plugin
{

class CompartmentReportHDF5 : public CompartmentReportCommon
{
public:
    explicit CompartmentReportHDF5( const CompartmentReportInitData& initData );
    virtual ~CompartmentReportHDF5();

    static bool handles( const CompartmentReportInitData& initData );

    float getStartTime() const final { return _startTime; }

    float getEndTime() const final { return _endTime; }

    float getTimestep() const final { return _timestep; }

    const std::string& getDataUnit() const final { return _dunit; }

    const std::string& getTimeUnit() const final { return _tunit; }

    const GIDSet& getGIDs() const final;
    const SectionOffsets& getOffsets() const final;
    const CompartmentCounts& getCompartmentCounts() const final;
    size_t getFrameSize() const final;

    floatsPtr loadFrame( const float timestamp ) const final;
    void updateMapping( const GIDSet& gids ) final;

    void writeHeader( const float startTime, const float endTime,
                      const float timestep, const std::string& dunit,
                      const std::string& tunit ) final;
    bool writeCompartments( const uint32_t gid, const uint16_ts& counts ) final;
    bool writeFrame( const uint32_t gid, const floats& voltages,
                     const float timestamp ) final;
    bool flush() final;

private:
    void _openFile( const uint32_t cellID );
    H5::DataSet _openDataset( const H5::H5File& file, const uint32_t cellID );

    H5::DataSet _createDataset( const uint32_t gid, const size_t compCount );
    H5::DataSet& _getDataset( const uint32_t gid );
    void _createMappingAttributes( H5::DataSet& dataset );
    void _createDataAttributes( H5::DataSet& dataset );

    typedef stde::hash_map< uint32_t, H5::H5File > Files;
    typedef stde::hash_map< uint32_t, H5::DataSet > Datasets;
    typedef stde::hash_map< uint32_t, H5::DataSpace > Dataspaces;

    double _startTime;
    double _endTime;
    double _timestep;
    std::string _dunit;
    std::string _tunit;

    GIDSet _gids;
    SectionOffsets _offsets;
    CompartmentCounts _counts;
    size_t _comps;
    boost::filesystem::path _path;
    std::string _reportName;
    Files _files;
    H5::H5File _file;
    Datasets _datas;
    Dataspaces _fspaces;
    Dataspaces _mspaces;
};

}
}

#endif
