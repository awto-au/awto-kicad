/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command_sch_import.h"
#include <cli/exit_codes.h>
#include <jobs/job_sch_import.h>
#include <kiface_base.h>
#include <string_utils.h>
#include <macros.h>
#include <map>
#include <wx/crt.h>


#define ARG_FORMAT "--format"


CLI::SCH_IMPORT_COMMAND::SCH_IMPORT_COMMAND() : COMMAND( "import" )
{
    addCommonArgs( true, true, IO_TYPE::FILE, IO_TYPE::FILE );

    m_argParser.add_description( UTF8STDSTR(
            _( "Import a non-KiCad schematic, or all schematics of an Altium project (.PrjPcb), "
               "to KiCad format. Writes the .kicad_sch hierarchy and a .kicad_pro next to "
               "--output (default: beside the input)" ) ) );

    m_argParser.add_argument( ARG_FORMAT )
            .default_value( std::string( "auto" ) )
            .help( UTF8STDSTR( _( "Input format hint: auto, altium, cadstar, eagle, easyeda, "
                                  "easyedapro, ltspice, pads, geda (default: auto)" ) ) )
            .metavar( "FORMAT" );
}


int CLI::SCH_IMPORT_COMMAND::doPerform( KIWAY& aKiway )
{
    static const std::map<wxString, JOB_SCH_IMPORT::FORMAT> formats = {
        { wxS( "auto" ), JOB_SCH_IMPORT::FORMAT::AUTO },
        { wxS( "altium" ), JOB_SCH_IMPORT::FORMAT::ALTIUM },
        { wxS( "cadstar" ), JOB_SCH_IMPORT::FORMAT::CADSTAR },
        { wxS( "eagle" ), JOB_SCH_IMPORT::FORMAT::EAGLE },
        { wxS( "easyeda" ), JOB_SCH_IMPORT::FORMAT::EASYEDA },
        { wxS( "easyedapro" ), JOB_SCH_IMPORT::FORMAT::EASYEDAPRO },
        { wxS( "ltspice" ), JOB_SCH_IMPORT::FORMAT::LTSPICE },
        { wxS( "pads" ), JOB_SCH_IMPORT::FORMAT::PADS },
        { wxS( "geda" ), JOB_SCH_IMPORT::FORMAT::GEDA }
    };

    std::unique_ptr<JOB_SCH_IMPORT> importJob = std::make_unique<JOB_SCH_IMPORT>();

    importJob->m_inputFile = m_argInput;
    importJob->SetConfiguredOutputPath( m_argOutput );

    wxString format = From_UTF8( m_argParser.get<std::string>( ARG_FORMAT ).c_str() );
    auto     it = formats.find( format );

    if( it == formats.end() )
    {
        wxFprintf( stderr, _( "Invalid format: %s\n" ), format );
        return EXIT_CODES::ERR_ARGS;
    }

    importJob->m_format = it->second;

    return aKiway.ProcessJob( KIWAY::FACE_SCH, importJob.get() );
}
