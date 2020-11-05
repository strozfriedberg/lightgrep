#include "filerecord.h"

#include "tskconversion.h"

#include <tsk/libtsk.h>

FileRecord::FileRecord(TSK_FS_FILE* file) {
  TskConverter converter;

  if (file->meta) {
    Doc["meta"] = converter.convertMeta(*file);
  }

  if (file->name) {
    Doc["name"] = converter.convertName(*file->name);
  }
}
