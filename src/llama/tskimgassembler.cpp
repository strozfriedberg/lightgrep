#include "tskimgassembler.h"

void TskImgAssembler::addImage(jsoncons::json&& img) {
  Doc = std::move(img);
}

void TskImgAssembler::addVolumeSystem(jsoncons::json&& vs) {
  Doc["volumeSystem"] = std::move(vs);
}

void TskImgAssembler::addVolume(jsoncons::json&& vol) {
  Doc["volumeSystem"]["volumes"].push_back(std::move(vol));
}

void TskImgAssembler::addFileSystem(jsoncons::json&& fs) {
  // The fs goes in the last volume added, or directly into the image if
  // there is no volume system.
  auto i = Doc.find("volumeSystem");
  auto& fs_parent = i == Doc.object_range().end() ? Doc :
    *(i->value()["volumes"].array_range().rbegin());
  fs_parent["fileSystem"] = std::move(fs);
}

jsoncons::json TskImgAssembler::dump() {
  return std::move(Doc);
}
