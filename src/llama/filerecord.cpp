#include "filerecord.h"

#include "tskconversion.h"

FileRecord::FileRecord(TSK_FS_META* meta, TSK_FS_TYPE_ENUM fsType) {
  TskConverter converter;
  jsoncons::json metaRec;
  converter.convertMeta(*meta, fsType, metaRec);
  Doc["meta"] = metaRec;
}
