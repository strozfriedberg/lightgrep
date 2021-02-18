#include <scope/test.h>

#include <stdexcept>

#include "tskimgassembler.h"

SCOPE_TEST(testTskImgAssemblerAddImgVolumeSystemVolumeFS) {
  TskImgAssembler a;

  a.addImage(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" }
    }
  ));

  a.addVolumeSystem(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "b", "I'm a Volume System" },
      { "volumes", jsoncons::json(jsoncons::json_array_arg) }
    }
  ));

  a.addVolume(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "c", "I'm Volume 1" }
    }
  ));

  a.addFileSystem(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "d", "I'm a File System" }
    }
  ));

  a.addVolume(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "e", "I'm Volume 2" }
    }
  ));

  const jsoncons::json exp(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" },
      {
        "volumeSystem", jsoncons::json(
          jsoncons::json_object_arg,
          {
            { "b", "I'm a Volume System" },
            {
              "volumes", jsoncons::json(
                jsoncons::json_array_arg,
                {
                  jsoncons::json(
                    jsoncons::json_object_arg,
                    {
                      { "c", "I'm Volume 1" },
                      {
                        "fileSystem", jsoncons::json(
                          jsoncons::json_object_arg,
                          {
                            { "d", "I'm a File System" }
                          }
                        )
                      }
                    }
                  ),
                  jsoncons::json(
                    jsoncons::json_object_arg,
                    {
                      { "e", "I'm Volume 2" }
                    }
                  )
                }
              )
            }
          }
        )
      }
    }
  );

  SCOPE_ASSERT_EQUAL(exp, a.dump());
}

SCOPE_TEST(testTskImgCollectorAddImgFS) {
  TskImgAssembler a;

  a.addImage(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" }
    }
  ));

  a.addFileSystem(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "b", "I'm a File System" }
    }
  ));

  const jsoncons::json exp(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" },
      {
        "fileSystem", jsoncons::json(
          jsoncons::json_object_arg,
          {
            { "b", "I'm a File System" }
          }
        )
      }
    }
  );

  SCOPE_ASSERT_EQUAL(exp, a.dump());
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToVol) {
  // INIT -> VOL
  TskImgAssembler a;
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToVS) {
  // INIT -> VS
  TskImgAssembler a;
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToFS) {
  // INIT -> { IMG_FS, VOL_FS }
  TskImgAssembler a;
  SCOPE_EXPECT(a.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgToImg) {
  // IMG -> IMG
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  SCOPE_EXPECT(a.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgToVol) {
  // IMG -> VOL
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  SCOPE_EXPECT(a.addVolume(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToVS) {
  // VS -> VS
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToImg) {
  // VS -> IMG
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(a.addImage(jsoncons::json()), std::runtime_error);
}


SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToFS) {
  // VS -> { IMG_FS, VOL_FS }
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(a.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolToImg) {
  // VOL -> IMG
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  a.addVolume(jsoncons::json());
  SCOPE_EXPECT(a.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolToVS) {
  // VOL -> VS
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  a.addVolume(jsoncons::json());
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToImgFS) {
  // IMG_FS -> { VOL_FS, IMG_FS }
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToImg) {
  // IMG_FS -> IMG
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToVS) {
  // IMG_FS -> VS
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToVol) {
  // IMG_FS -> VOL
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addVolume(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToVolFS) {
  // VOL_FS -> { VOL_FS, IMG_FS }
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  a.addVolume(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToImg) {
  // VOL_FS -> IMG
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  a.addVolume(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToVS) {
  // VOL_FS -> VS
  TskImgAssembler a;
  a.addImage(jsoncons::json());
  a.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  a.addVolume(jsoncons::json());
  a.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(a.addVolumeSystem(jsoncons::json()), std::runtime_error);
}
