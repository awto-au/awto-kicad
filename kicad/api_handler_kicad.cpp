/*
 * This program source code file is part of KiCad, a free EDA CAD application.
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

#ifdef KICAD_IPC_API

#include "api_handler_kicad.h"

#include <kicad_manager_frame.h>
#include <project.h>
#include <tool/tool_manager.h>
#include <tools/kicad_manager_actions.h>

using namespace kiapi::common;
using google::protobuf::Empty;


API_HANDLER_KICAD::API_HANDLER_KICAD( KICAD_MANAGER_FRAME* aFrame ) :
        API_HANDLER(),
        m_frame( aFrame )
{
    registerHandler<commands::OpenEditors, Empty>( &API_HANDLER_KICAD::handleOpenEditors );
}


HANDLER_RESULT<Empty> API_HANDLER_KICAD::handleOpenEditors(
        const HANDLER_CONTEXT<commands::OpenEditors>& aCtx )
{
    if( !m_frame || m_frame->Prj().IsNullProject() )
    {
        ApiResponseStatus e;
        e.set_status( ApiStatusCode::AS_BAD_REQUEST );
        e.set_error_message( "no project is loaded in the KiCad project manager" );
        return tl::unexpected( e );
    }

    // Same actions as the toolbar buttons; each returns once its editor has loaded the project.
    if( aCtx.Request.schematic() )
        m_frame->GetToolManager()->RunAction( KICAD_MANAGER_ACTIONS::editSchematic );

    if( aCtx.Request.pcb() )
        m_frame->GetToolManager()->RunAction( KICAD_MANAGER_ACTIONS::editPCB );

    return Empty();
}

#endif // KICAD_IPC_API
