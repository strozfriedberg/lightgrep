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
  /*
    This is the graph of our state machine:

    digraph {
      INIT -> IMG;
      IMG -> VS;
      VS -> VOL;
      VOL -> VOL;
      VOL -> VOL_FS;
      VOL_FS -> VOL;
      IMG -> IMG_FS;
      INIT -> END;
      IMG -> END;
      VS -> END;
      VOL -> END;
      IMG_FS -> END;
      VOL_FS -> END;
    }
  */
  enum { INIT, IMG, IMG_FS, VS, VOL, VOL_FS, END } State = INIT;

  jsoncons::json Doc;
};
