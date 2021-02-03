#pragma once

#include "jsoncons_wrapper.h"

class TskImgAssembler {
public:
  void addImage(jsoncons::json&& img);
  void addVolumeSystem(jsoncons::json&& vs);
  void addVolume(jsoncons::json&& vol);
  void addFileSystem(jsoncons::json&& fs);

  jsoncons::json dump();

private:
  enum { INIT, IMG, VS, VOL, FS, END } State = INIT;
  jsoncons::json Doc;
};
