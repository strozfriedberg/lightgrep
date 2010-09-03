import glob
import os
import platform
import os.path as p
import re

isWindows = False

def shellCall(cmd):
  print(cmd)
  os.system(cmd)

def sub(src):
  return env.SConscript(p.join(src, 'SConscript'), exports=['env', 'isWindows'], variant_dir=p.join('bin', src), duplicate=0)

def buildBoost(target, source, env):
  shouldBuild = False
  for t in target:
    if (len(env.Glob(str(t))) == 1):
      shouldBuild = True
      break
  if (shouldBuild):
    curDir = os.getcwd()
    os.chdir(str(source[0]))
    if (isWindows == True):
      shellCall('.\\bootstrap.bat')
      shellCall('.\\bjam --stagedir=%s --with-thread --with-system '
        'link=static variant=release threading=multi runtime-link=static toolset=gcc '
        '-s BOOST_NO_RVALUE_REFERENCES stage' % curDir)
    else:
      shellCall('./bootstrap.sh')
      shellCall('./bjam --stagedir=%s --with-thread --with-system link=shared variant=release threading=multi stage' % curDir)
    os.chdir(curDir)
    if (isWindows):
      libs = [str(x) for x in Glob('#/lib/libboost*')]
      if len(libs) == 0:
        print("GLOB DID NOT SUCCEED")
      for lib in libs:
        try:
          newName = re.sub(r'-.*\.a', '.a', lib) #.replace('lib\\lib', 'lib\\', 1)
          print("renaming %s to %s" % (lib, newName))
          os.rename(lib, newName)
        except:
          print('had an error with the rename')


arch = platform.platform()
print("System is %s" % arch)
isWindows = arch.find('Windows') > -1

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

debug = ARGUMENTS.get('debug', 'false')
if (debug == 'true'):
  flags = '-g -fstack-protector-all -D LBT_TRACE_ENABLED'
elif (debug == 'profile'):
  flags = '-g -O1'
elif (debug == 'trace'):
  flags = '-O3 -D LBT_TRACE_ENABLED'
else:
  flags = '-O3'

ccflags = '-Wall -Wextra %s -isystem %s -isystem %s' % (flags, scopeDir, boostDir)
if (isWindows):
  env = Environment(ENV=os.environ, tools='mingw') # this builds in a dependency on the PATH, which is useful for ccache
else:
  env = Environment(ENV=os.environ)
env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS=ccflags)
env.Append(LIBPATH=['#/lib'])

if ('DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

libBoost = env.Command(['#/lib/*boost_thread*', '#/lib/*boost_system*'], boostDir, buildBoost)
liblg = sub('src')
libDir = env.Install('lib', liblg)
test = sub('test')
env.Depends(test, libBoost)
env.Depends(test, libDir)
env.Command('unittests', test, '$SOURCE --test')
