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

#include <jobs/job_pcb_update_from_schematic.h>

JOB_PCB_UPDATE_FROM_SCHEMATIC::JOB_PCB_UPDATE_FROM_SCHEMATIC() :
        JOB( "pcb_update_from_schematic", false ),
        m_filename(),
        m_dryRun( false ),
        m_relinkFootprints( false ),
        m_replaceFootprints( false ),
        m_deleteUnusedFootprints( false ),
        m_overrideLocks( false ),
        m_updateFields( false ),
        m_removeExtraFields( false ),
        m_transferGroups( false )
{
}
