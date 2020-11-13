#include "schema.h"

const char TYPE_UNDEF[]    = "Undefined";
const char TYPE_FIFO[]     = "Named Pipe";
const char TYPE_CHR[]      = "Character Device";
const char TYPE_DIR[]      = "Folder";
const char TYPE_BLK[]      = "Block Device";
const char TYPE_REG[]      = "File";
const char TYPE_LNK[]      = "Symbolic Link";
const char TYPE_SOCK[]     = "Domain Socket";
const char TYPE_SHAD[]     = "Shadow Inode";
const char TYPE_WHT[]      = "Whiteout Inode";
const char TYPE_VIRT[]     = "Virtual";
const char TYPE_VIRT_DIR[] = "Virtual Folder";

const char NAME_FLAG_ALLOC[]   = "Allocated";
const char NAME_FLAG_UNALLOC[] = "Deleted";

const char META_FLAG_ALLOC[]   = "Allocated";
const char META_FLAG_UNALLOC[] = "Deleted";
const char META_FLAG_USED[]    = "Used";
const char META_FLAG_UNUSED[]  = "Unused";
const char META_FLAG_COMP[]    = "Compressed";
const char META_FLAG_ORPHAN[]  = "Orphan";

const char ATTR_FLAG_INUSE[]    = "In Use";
const char ATTR_FLAG_NONRES[]   = "Non-resident";
const char ATTR_FLAG_RES[]      = "Resident";
const char ATTR_FLAG_ENC[]      = "Encrypted";
const char ATTR_FLAG_COMP[]     = "Compressed";
const char ATTR_FLAG_SPARSE[]   = "Sparse";
const char ATTR_FLAG_RECOVERY[] = "Recovered";

const char ATTR_TYPE_NOT_FOUND[]     = "Unknown";
const char ATTR_TYPE_DEFAULT[]       = "Data";
const char ATTR_TYPE_NTFS_SI[]       = "Standard Information";
const char ATTR_TYPE_NTFS_ATTRLIST[] = "NTFS Attributes";
const char ATTR_TYPE_NTFS_FNAME[]    = "Filename";
const char ATTR_TYPE_NTFS_OBJID[]    = "ObjID";
const char ATTR_TYPE_NTFS_SEC[]      = "Sec";
const char ATTR_TYPE_NTFS_VNAME[]    = "VName";
const char ATTR_TYPE_NTFS_VINFO[]    = "VInfo";
const char ATTR_TYPE_NTFS_DATA[]     = "Data";
const char ATTR_TYPE_NTFS_IDXROOT[]  = "IdxRoot";
const char ATTR_TYPE_NTFS_IDXALLOC[] = "IdxAlloc";
const char ATTR_TYPE_NTFS_BITMAP[]   = "Bitmap";
const char ATTR_TYPE_NTFS_SYMLNK[]   = "Symlink";
const char ATTR_TYPE_NTFS_EAINFO[]   = "EAInfo";
const char ATTR_TYPE_NTFS_EA[]       = "EA";
const char ATTR_TYPE_NTFS_PROP[]     = "Prop";
const char ATTR_TYPE_NTFS_LOG[]      = "Log";
const char ATTR_TYPE_UNIX_INDIR[]    = "Indirect";
const char ATTR_TYPE_UNIX_EXTENT[]   = "Extents";
const char ATTR_TYPE_HFS_DATA[]      = "Data";
const char ATTR_TYPE_HFS_RSRC[]      = "Resource";
const char ATTR_TYPE_HFS_EXT_ATTR[]  = "EA";
const char ATTR_TYPE_HFS_COMP_REC[]  = "Compressed";
const char ATTR_TYPE_UNKNOWN[]       = "Unknown";

const char ATTR_RUN_FLAG_NONE[] = "";
const char ATTR_RUN_FLAG_FILLER[] = "Filler";
const char ATTR_RUN_FLAG_SPARSE[] = "Sparse";

const char VS_TYPE_UNKNOWN[] = "Unknown";
const char VS_TYPE_DOS[] = "MBR";
const char VS_TYPE_BSD[] = "BSD";
const char VS_TYPE_SUN[] = "Sun";
const char VS_TYPE_MAC[] = "Macintosh";
const char VS_TYPE_GPT[] = "GPT";

const char VS_PART_FLAG_ALLOC[]   = "Allocated";
const char VS_PART_FLAG_UNALLOC[] = "Unallocated";
const char VS_PART_FLAG_META[]    = "Volume System";

const char FS_INFO_FLAG_HAVE_SEQ[] = "Sequenced";
const char FS_INFO_FLAG_HAVE_NANOSEC[] = "Nanosecond precision";

