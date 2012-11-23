/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstring>
#include <new>

#include "c_api_util.h"

void fill_error(LG_Error** err, const char* msg) {
  if (err) {
    try {
     *err = new LG_Error;
     (*err)->Message = new char[std::strlen(msg)];
      std::strcpy((*err)->Message, msg);
    }
    catch (const std::bad_alloc&) {
      // Not enough memory to copy the error message. Everything is hosed.
    }
    catch (...) {
      // Should be impossible.
    }
  }
}
