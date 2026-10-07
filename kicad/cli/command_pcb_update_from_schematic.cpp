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

#include "command_pcb_update_from_schematic.h"
#include "jobs/job_pcb_update_from_schematic.h"
#include "cli/exit_codes.h"
#include <wx/crt.h>

#define ARG_DRY_RUN "--dry-run"
#define ARG_RELINK "--relink-footprints"
#define ARG_REPLACE "--replace-footprints"
#define ARG_DELETE_UNUSED "--delete-unused-footprints"
#define ARG_OVERRIDE_LOCKS "--override-locks"
#define ARG_UPDATE_FIELDS "--update-fields"
#define ARG_REMOVE_EXTRA_FIELDS "--remove-extra-fields"
#define ARG_TRANSFER_GROUPS "--transfer-groups"

CLI::PCB_UPDATE_FROM_SCHEMATIC_COMMAND::PCB_UPDATE_FROM_SCHEMATIC_COMMAND() :
        COMMAND( "update-from-schematic" )
{
    addCommonArgs( true, true, IO_TYPE::FILE, IO_TYPE::FILE );
    m_argParser.add_description( UTF8STDSTR(
            _( "Update the PCB from its schematic (the editor's Update PCB from Schematic), "
               "without opening any editor. Writes the board in place unless --output is given" ) ) );

    m_argParser.add_argument( ARG_DRY_RUN )
            .help( UTF8STDSTR( _( "Report the changes without writing anything" ) ) )
            .flag();
    m_argParser.add_argument( ARG_RELINK )
            .help( UTF8STDSTR( _( "Re-link footprints to schematic symbols by reference" ) ) )
            .flag();
    m_argParser.add_argument( ARG_REPLACE )
            .help( UTF8STDSTR( _( "Replace footprints whose library ID changed" ) ) )
            .flag();
    m_argParser.add_argument( ARG_DELETE_UNUSED )
            .help( UTF8STDSTR( _( "Delete footprints with no schematic symbol" ) ) )
            .flag();
    m_argParser.add_argument( ARG_OVERRIDE_LOCKS )
            .help( UTF8STDSTR( _( "Allow changes to locked footprints" ) ) )
            .flag();
    m_argParser.add_argument( ARG_UPDATE_FIELDS )
            .help( UTF8STDSTR( _( "Copy symbol fields to footprints" ) ) )
            .flag();
    m_argParser.add_argument( ARG_REMOVE_EXTRA_FIELDS )
            .help( UTF8STDSTR( _( "Remove footprint fields not in the symbol" ) ) )
            .flag();
    m_argParser.add_argument( ARG_TRANSFER_GROUPS )
            .help( UTF8STDSTR( _( "Copy schematic group membership to the PCB" ) ) )
            .flag();
}


int CLI::PCB_UPDATE_FROM_SCHEMATIC_COMMAND::doPerform( KIWAY& aKiway )
{
    std::unique_ptr<JOB_PCB_UPDATE_FROM_SCHEMATIC> job =
            std::make_unique<JOB_PCB_UPDATE_FROM_SCHEMATIC>();

    job->m_filename = m_argInput;
    job->SetConfiguredOutputPath( m_argOutput );
    job->m_dryRun = m_argParser.get<bool>( ARG_DRY_RUN );
    job->m_relinkFootprints = m_argParser.get<bool>( ARG_RELINK );
    job->m_replaceFootprints = m_argParser.get<bool>( ARG_REPLACE );
    job->m_deleteUnusedFootprints = m_argParser.get<bool>( ARG_DELETE_UNUSED );
    job->m_overrideLocks = m_argParser.get<bool>( ARG_OVERRIDE_LOCKS );
    job->m_updateFields = m_argParser.get<bool>( ARG_UPDATE_FIELDS );
    job->m_removeExtraFields = m_argParser.get<bool>( ARG_REMOVE_EXTRA_FIELDS );
    job->m_transferGroups = m_argParser.get<bool>( ARG_TRANSFER_GROUPS );

    if( !wxFile::Exists( job->m_filename ) )
    {
        wxFprintf( stderr, _( "Board file does not exist or is not accessible\n" ) );
        return EXIT_CODES::ERR_INVALID_INPUT_FILE;
    }

    return aKiway.ProcessJob( KIWAY::FACE_PCB, job.get() );
}
