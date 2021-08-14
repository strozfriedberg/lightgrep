#include "tskimgassembler.h"

#include "throw.h"

void TskImgAssembler::addImage(jsoncons::json&& img) {
  THROW_IF(State != INIT, "Attempted to add image in state " << State);
  Doc = std::move(img);
  State = IMG;
}

void TskImgAssembler::addVolumeSystem(jsoncons::json&& vs) {
  THROW_IF(State != IMG, "Attempted to add volume system in state " << State);
  Doc["volumeSystem"] = std::move(vs);
  State = VS;
}

void TskImgAssembler::addVolume(jsoncons::json&& vol) {
  switch (State) {
  case VS:
  case VOL:
  case VOL_FS:
    Doc["volumeSystem"]["volumes"].push_back(std::move(vol));
    State = VOL;
    break;
  default:
    THROW("Attempted to add volume in state " << State);
  }
}

void TskImgAssembler::addFileSystem(jsoncons::json&& fs) {
  // The fs goes in the last volume added, or directly into the image if
  // there is no volume system.
  if (State == IMG) {
    Doc["fileSystem"] = std::move(fs);
    State = IMG_FS;
  }
  else if (State == VOL) {
    auto i = Doc.find("volumeSystem");
    THROW_IF(i == Doc.object_range().end(), "Inconceivable!");
    auto& fs_parent = *(i->value()["volumes"].array_range().rbegin());
    fs_parent["fileSystem"] = std::move(fs);
    State = VOL_FS;
  }
  else {
    THROW("Inconceivable!");
  }
}

jsoncons::json TskImgAssembler::dump() {
  State = END;
  return std::move(Doc);
}
