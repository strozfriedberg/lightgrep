#include <scope/test.h>

#include <stdexcept>

#include "tskimgassembler.h"

SCOPE_TEST(testTskImgAssemblerAddImgVolumeSystemVolumeFS) {
  TskImgAssembler ass;

  ass.addImage(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" }
    }
  ));

  ass.addVolumeSystem(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "b", "I'm a Volume System" },
      { "volumes", jsoncons::json(jsoncons::json_array_arg) }
    }
  ));

  ass.addVolume(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "c", "I'm Volume 1" }
    }
  ));

  ass.addFileSystem(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "d", "I'm a File System" }
    }
  ));

  ass.addVolume(jsoncons::json(
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

  SCOPE_ASSERT_EQUAL(exp, ass.dump());
}

SCOPE_TEST(testTskImgCollectorAddImgFS) {
  TskImgAssembler ass;

  ass.addImage(jsoncons::json(
    jsoncons::json_object_arg,
    {
      { "a", "I'm an Image" }
    }
  ));

  ass.addFileSystem(jsoncons::json(
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

  SCOPE_ASSERT_EQUAL(exp, ass.dump());
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToVol) {
  // INIT -> VOL
  TskImgAssembler ass;
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToVS) {
  // INIT -> VS
  TskImgAssembler ass;
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionInitToFS) {
  // INIT -> { IMG_FS, VOL_FS }
  TskImgAssembler ass;
  SCOPE_EXPECT(ass.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgToImg) {
  // IMG -> IMG
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  SCOPE_EXPECT(ass.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgToVol) {
  // IMG -> VOL
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  SCOPE_EXPECT(ass.addVolume(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToVS) {
  // VS -> VS
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToImg) {
  // VS -> IMG
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addImage(jsoncons::json()), std::runtime_error);
}


SCOPE_TEST(testTskImgCollectorIllegalTransitionVSToFS) {
  // VS -> { IMG_FS, VOL_FS }
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolToImg) {
  // VOL -> IMG
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  ass.addVolume(jsoncons::json());
  SCOPE_EXPECT(ass.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolToVS) {
  // VOL -> VS
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  ass.addVolume(jsoncons::json());
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToImgFS) {
  // IMG_FS -> { VOL_FS, IMG_FS }
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToImg) {
  // IMG_FS -> IMG
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToVS) {
  // IMG_FS -> VS
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionImgFSToVol) {
  // IMG_FS -> VOL
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addVolume(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToVolFS) {
  // VOL_FS -> { VOL_FS, IMG_FS }
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  ass.addVolume(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addFileSystem(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToImg) {
  // VOL_FS -> IMG
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  ass.addVolume(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addImage(jsoncons::json()), std::runtime_error);
}

SCOPE_TEST(testTskImgCollectorIllegalTransitionVolFSToVS) {
  // VOL_FS -> VS
  TskImgAssembler ass;
  ass.addImage(jsoncons::json());
  ass.addVolumeSystem(
    jsoncons::json(
      jsoncons::json_object_arg,
      {
        { "volumes", jsoncons::json(jsoncons::json_array_arg) }
      }
    )
  );
  ass.addVolume(jsoncons::json());
  ass.addFileSystem(jsoncons::json());
  SCOPE_EXPECT(ass.addVolumeSystem(jsoncons::json()), std::runtime_error);
}
