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

#ifndef KICAD_API_HANDLER_KICAD_H
#define KICAD_API_HANDLER_KICAD_H

#include <google/protobuf/empty.pb.h>

#include <api/api_handler.h>
#include <api/common/commands/project_commands.pb.h>

class KICAD_MANAGER_FRAME;

/// API commands only the KiCad project manager can serve (e.g. opening editors).
class API_HANDLER_KICAD : public API_HANDLER
{
public:
    explicit API_HANDLER_KICAD( KICAD_MANAGER_FRAME* aFrame );

private:
    HANDLER_RESULT<google::protobuf::Empty> handleOpenEditors(
            const HANDLER_CONTEXT<kiapi::common::commands::OpenEditors>& aCtx );

    KICAD_MANAGER_FRAME* m_frame;
};

#endif
