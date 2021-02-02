#include <scope/test.h>

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
