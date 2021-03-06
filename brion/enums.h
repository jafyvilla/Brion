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

/** @file enums.h Enumerations used in Brion. */

#ifndef BRION_ENUMS
#define BRION_ENUMS

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace brion
{
/** @namespace enums Enumeration definitions */
namespace enums
{

/** The supported sections in a BlueConfig file. */
enum BlueConfigSection
{
    CONFIGSECTION_RUN = 0,
    CONFIGSECTION_CONNECTION,
    CONFIGSECTION_STIMULUS,
    CONFIGSECTION_STIMULUSINJECT,
    CONFIGSECTION_REPORT,
    CONFIGSECTION_UNKNOWN,
    CONFIGSECTION_ALL //!< @internal must be last
};

/**
 * The supported formats for compartment reports.
 * @deprecated since version 1.4, kept until removed from BBPSDK and replaced by
 * a string.
 */
enum CompartmentReportFormat
{
    REPORTFORMAT_BINARY,
    REPORTFORMAT_HDF5,
    REPORTFORMAT_STREAM,
    REPORTFORMAT_LEVELDB, //!< @version 1.4
    REPORTFORMAT_SKV,  //!< @version 1.4
    REPORTFORMAT_NULL,  //!< @version 1.4
    REPORTFORMAT_INVALID
};

/** The supported structural mesh types. */
enum MeshStructure
{
    MESH_SPINES = 0,    //!< spines
    MESH_BOUTONS,       //!< boutons
    MESH_PSD,           //!< post-synaptic densities
    MESH_AZ,            //!< active zones
    MESH_ENDO,          //!< endoplasmic reticulum
    MESH_ALL            //!< @internal must be last
};

/** The supported formats for mesh files. */
enum MeshFormat
{
    MESHFORMAT_BINARY,
    MESHFORMAT_HDF5
};

/** The supported versions for mesh files. */
enum MeshVersion
{
    MESH_VERSION_1 = 1,
    MESH_VERSION_2 = 2
};

/** The supported repair stages for morphologies. */
enum MorphologyRepairStage
{
    MORPHOLOGY_RAW,
    MORPHOLOGY_UNRAVELED,
    MORPHOLOGY_REPAIRED,
    MORPHOLOGY_UNDEFINED
};

/** The supported versions for morphology files. */
enum MorphologyVersion
{
    MORPHOLOGY_VERSION_1 = 1, //!< @deprecated use MORPHOLOGY_VERSION_H5_1
    MORPHOLOGY_VERSION_2 = 2, //!< @deprecated use MORPHOLOGY_VERSION_H5_2
    MORPHOLOGY_VERSION_H5_1 = 1,
    MORPHOLOGY_VERSION_H5_2 = 2,
    MORPHOLOGY_VERSION_SWC_1 = 101,
    MORPHOLOGY_VERSION_UNDEFINED
};

/** Output stream formatter for MorphologyVersion */
inline std::ostream& operator << ( std::ostream& os, const MorphologyVersion v )
{
    switch( v )
    {
    case MORPHOLOGY_VERSION_H5_1:
        return os << "h5v1";
    case MORPHOLOGY_VERSION_H5_2:
        return os << "h5v2";
    case MORPHOLOGY_VERSION_SWC_1:
        return os << "swcv1";
    default:
    case MORPHOLOGY_VERSION_UNDEFINED:
        return os << "UNDEFINED";
    }
}

/** The supported attributes of a neuron. */
enum NeuronAttributes
{
    NEURON_MORPHOLOGY_NAME = 1 << 0,
    NEURON_MORPHOLOGY_ORIGIN = 1 << 1,
    NEURON_COLUMN_GID = 1 << 2,
    NEURON_MINICOLUMN_GID = 1 << 3,
    NEURON_LAYER = 1 << 4,
    NEURON_MTYPE = 1 << 5,
    NEURON_ETYPE = 1 << 6,
    NEURON_POSITION_X = 1 << 7,
    NEURON_POSITION_Y = 1 << 8,
    NEURON_POSITION_Z = 1 << 9,
    NEURON_ROTATION = 1 << 10,
    NEURON_METYPE = 1 << 11,
    NEURON_ALL = 12,

    NEURON_ALL_ATTRIBUTES = (1 << NEURON_ALL) - 1
};

/** The supported classifications for a neuron. */
enum NeuronClass
{
    NEURONCLASS_MTYPE = 0,              //!< L2PC, L5CSPC, ...
    NEURONCLASS_MORPHOLOGY_CLASS = 1,   //!< PYR, INT
    NEURONCLASS_FUNCTION_CLASS = 2,     //!< EXC, INH
    NEURONCLASS_ETYPE,                  //!< cAD, dAL, ...
    NEURONCLASS_INVALID
};

/** The supported target types. */
enum TargetType
{
    TARGET_CELL = 0,
    TARGET_COMPARTMENT,
    TARGET_ALL //!< @internal must be last
};

/** Classification of neuron substructures. */
enum SectionType
{
    SECTION_UNDEFINED = 0,
    SECTION_SOMA,               //!< neuron cell body
    SECTION_AXON,
    SECTION_DENDRITE,           //!< general or basal dendrite (near to soma)
    SECTION_APICAL_DENDRITE,    //!< apical dendrite (far from soma)
    SECTION_ALL //!< @internal must be last
};

/** The supported attributes of a synapse. */
enum SynapseAttributes
{
    SYNAPSE_CONNECTED_NEURON = 1 << 0,
    SYNAPSE_DELAY = 1 << 1,
    SYNAPSE_POSTSYNAPTIC_SECTION = 1 << 2,
    SYNAPSE_POSTSYNAPTIC_SEGMENT = 1 << 3,
    SYNAPSE_POSTSYNAPTIC_SEGMENT_DISTANCE = 1 << 4,
    SYNAPSE_PRESYNAPTIC_SECTION = 1 << 5,
    SYNAPSE_PRESYNAPTIC_SEGMENT = 1 << 6,
    SYNAPSE_PRESYNAPTIC_SEGMENT_DISTANCE = 1 << 7,
    SYNAPSE_CONDUCTANCE = 1 << 8,
    SYNAPSE_UTILIZATION = 1 << 9,
    SYNAPSE_DEPRESSION = 1 << 10,
    SYNAPSE_FACILITATION = 1 << 11,
    SYNAPSE_DECAY = 1 << 12,
    SYNAPSE_TYPE = 1 << 13,
    SYNAPSE_PRESYNAPTIC_MTYPE = 1 << 14,
    SYNAPSE_DENDRITE_BRANCHORDER = 1 << 15,
    SYNAPSE_AXON_BRANCHORDER = 1 << 16,
    SYNAPSE_ABSOLUTE_SYNAPTIC_EFFICACY = 1 << 17,
    SYNAPSE_POSTSYNAPTIC_BRANCH_TYPE = 1 << 18,
    SYNAPSE_NO_ATTRIBUTES = 1 << 19,
    SYNAPSE_ALL = 19,

    SYNAPSE_DYNAMICS_CONSTANTS = SYNAPSE_CONDUCTANCE | SYNAPSE_UTILIZATION |
                                 SYNAPSE_DEPRESSION | SYNAPSE_FACILITATION |
                                 SYNAPSE_DELAY | SYNAPSE_DECAY |
                                 SYNAPSE_ABSOLUTE_SYNAPTIC_EFFICACY,

    SYNAPSE_PRESYNAPTIC_NEURON = SYNAPSE_PRESYNAPTIC_SECTION |
                                 SYNAPSE_PRESYNAPTIC_SEGMENT |
                                 SYNAPSE_PRESYNAPTIC_SEGMENT_DISTANCE,

    SYNAPSE_POSTSYNAPTIC_NEURON = SYNAPSE_POSTSYNAPTIC_SECTION |
                                  SYNAPSE_POSTSYNAPTIC_SEGMENT |
                                  SYNAPSE_POSTSYNAPTIC_SEGMENT_DISTANCE,

    SYNAPSE_ALL_ATTRIBUTES = SYNAPSE_CONNECTED_NEURON | SYNAPSE_TYPE |
                             SYNAPSE_PRESYNAPTIC_MTYPE |
                             SYNAPSE_DENDRITE_BRANCHORDER |
                             SYNAPSE_AXON_BRANCHORDER |
                             SYNAPSE_POSTSYNAPTIC_BRANCH_TYPE |
                             SYNAPSE_DYNAMICS_CONSTANTS |
                             SYNAPSE_PRESYNAPTIC_NEURON |
                             SYNAPSE_POSTSYNAPTIC_NEURON
};

/** The positions of a synapse. */
enum SynapsePositions
{
    SYNAPSE_PRESYNAPTIC_SURFACE_X = 1 << 1,
    SYNAPSE_PRESYNAPTIC_SURFACE_Y = 1 << 2,
    SYNAPSE_PRESYNAPTIC_SURFACE_Z = 1 << 3,
    SYNAPSE_POSTSYNAPTIC_SURFACE_X = 1 << 4,
    SYNAPSE_POSTSYNAPTIC_SURFACE_Y = 1 << 5,
    SYNAPSE_POSTSYNAPTIC_SURFACE_Z = 1 << 6,
    SYNAPSE_PRESYNAPTIC_CENTER_X = 1 << 7,
    SYNAPSE_PRESYNAPTIC_CENTER_Y = 1 << 8,
    SYNAPSE_PRESYNAPTIC_CENTER_Z = 1 << 9,
    SYNAPSE_POSTSYNAPTIC_CENTER_X = 1 << 10,
    SYNAPSE_POSTSYNAPTIC_CENTER_Y = 1 << 11,
    SYNAPSE_POSTSYNAPTIC_CENTER_Z = 1 << 12,
    SYNAPSE_POSITION_NO_ATTRIBUTES = 1 << 13,
    SYNAPSE_POSITION_ALL = 13,

    SYNAPSE_PRESYNAPTIC_POSITION = SYNAPSE_PRESYNAPTIC_SURFACE_X |
                                   SYNAPSE_PRESYNAPTIC_SURFACE_Y |
                                   SYNAPSE_PRESYNAPTIC_SURFACE_Z |
                                   SYNAPSE_PRESYNAPTIC_CENTER_X |
                                   SYNAPSE_PRESYNAPTIC_CENTER_Y |
                                   SYNAPSE_PRESYNAPTIC_CENTER_Z,

    SYNAPSE_POSTSYNAPTIC_POSITION = SYNAPSE_POSTSYNAPTIC_SURFACE_X |
                                    SYNAPSE_POSTSYNAPTIC_SURFACE_Y |
                                    SYNAPSE_POSTSYNAPTIC_SURFACE_Z |
                                    SYNAPSE_POSTSYNAPTIC_CENTER_X |
                                    SYNAPSE_POSTSYNAPTIC_CENTER_Y |
                                    SYNAPSE_POSTSYNAPTIC_CENTER_Z,

    SYNAPSE_POSITION = SYNAPSE_CONNECTED_NEURON |
                       SYNAPSE_PRESYNAPTIC_POSITION |
                       SYNAPSE_POSTSYNAPTIC_POSITION
};

/**
 * Specify the access mode of data.
 * @version 1.4
 */
enum AccessMode
{
    MODE_READ = 0x00000001,
    MODE_WRITE = 0x00000002,
    MODE_OVERWRITE = 0x00000004 | MODE_WRITE,
    MODE_READWRITE = MODE_READ | MODE_WRITE,
    MODE_READOVERWRITE = MODE_READ | MODE_OVERWRITE
};

}
}

namespace boost
{

// CompartmentReportFormat <-> std::string converters (used for type
// field in BlueConfig)

/** @internal */
template<> inline
std::string lexical_cast( const brion::enums::CompartmentReportFormat& f )
{
    switch( f )
    {
    case brion::enums::REPORTFORMAT_BINARY: return "bin";
    case brion::enums::REPORTFORMAT_HDF5: return "hdf5";
    case brion::enums::REPORTFORMAT_STREAM: return "stream";
    case brion::enums::REPORTFORMAT_LEVELDB: return "leveldb";
    case brion::enums::REPORTFORMAT_SKV: return "skv";
    case brion::enums::REPORTFORMAT_NULL: return "null";
    case brion::enums::REPORTFORMAT_INVALID: return "invalid";
    default: return lexical_cast< std::string >( int( f ));
    }
}

/** @internal */
template<> inline
brion::enums::CompartmentReportFormat lexical_cast( const std::string& string )
{
    std::string type = string;
    algorithm::to_lower( type );

    if( type == "binary" || type == "bin" )
        return brion::enums::REPORTFORMAT_BINARY;
    if( type.empty() || boost::filesystem::is_directory( type ) ||
        type == "hdf5" )
    {
        return brion::enums::REPORTFORMAT_HDF5;
    }
    if( type == "stream" )
        return brion::enums::REPORTFORMAT_STREAM;
    if( type == "leveldb" )
        return brion::enums::REPORTFORMAT_LEVELDB;
    if( type == "skv" )
        return brion::enums::REPORTFORMAT_SKV;
    if( type == "null" )
        return brion::enums::REPORTFORMAT_NULL;
    return brion::enums::REPORTFORMAT_INVALID;
}
}


#endif
