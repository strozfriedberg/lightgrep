#include "filerecord.h"

#include "tskconversion.h"

#include <tsk/libtsk.h>

FileRecord::FileRecord(TSK_FS_FILE* file) {
  // ridiculous bullshit to force attrs to be populated
  tsk_fs_file_attr_get_idx(file, 0);

  TskConverter converter;

  if (file->meta) {
    Doc["meta"] = converter.convertMeta(*file->meta, file->fs_info->ftype);
  }

  if (file->name) {
    Doc["name"] = converter.convertName(*file->name);
  }
}
