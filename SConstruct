import glob
import os
import platform
import os.path as p
import re

isWindows = False
isLinux = False
bits = '32'

def shellCall(cmd):
  print(cmd)
  os.system(cmd)

def sub(src):
  return env.SConscript(p.join(src, 'SConscript'), exports=['env', 'isWindows', 'isLinux'], variant_dir=p.join('bin', src), duplicate=0)

def buildBoost(target, source, env):
  shouldBuild = False
  for t in target:
#	print("Looking for %s" % t)
    if (len(env.Glob(str(t))) == 1):
#	  print("Couldn't find %s... need to build" % str(t))
      shouldBuild = True
      break
  if (shouldBuild):
    print("building")
    curDir = os.getcwd()
    os.chdir(str(source[0]))
    libsToBuild = '--with-program_options --with-system --with-thread'
    if (isWindows == True):
      shellCall('.\\bootstrap.bat')
      shellCall('.\\bjam --stagedir=%s %s '
        'link=static variant=release threading=multi runtime-link=static toolset=gcc '
        'address-model=%s define=BOOST_USE_WINDOWS_H '
        '-s BOOST_NO_RVALUE_REFERENCES stage' % (curDir, libsToBuild, bits))
    else:
      shellCall('./bootstrap.sh')
      shellCall('./bjam --stagedir=%s %s link=shared variant=release threading=multi stage' % (curDir, libsToBuild))
    os.chdir(curDir)
    if (isWindows):
      libs = [str(x) for x in Glob('#/lib/libboost*')]
      if len(libs) == 0:
        print("GLOB DID NOT SUCCEED")
      for lib in libs:
        try:
          newName = re.sub(r'-.*\.(a|dll)', r'.\g<1>', lib) # Boost tacks on version/MT options, which this gets rid of
          print("renaming %s to %s" % (lib, newName))
          os.rename(lib, newName)
        except:
          print('had an error with the rename')


arch = platform.platform()
print("System is %s, %s" % (arch, platform.machine()))
if (platform.machine().find('64') > -1):
  bits = '64'

isWindows = arch.find('Windows') > -1
isLinux = arch.find('Linux') > -1

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

debug = ARGUMENTS.get('debug', 'false')
if (debug == 'true'):
  flags = '-g -fstack-protector-all -D LBT_TRACE_ENABLED'
  ldflags = ''
elif (debug == 'profile'):
  flags = '-g -pg -O'
  ldflags = '-pg'
elif (debug == 'coverage'):
  flags = '-g -O0 -fprofile-arcs -ftest-coverage -fbranch-probabilities'
  ldflags = '--coverage'
elif (debug == 'trace'):
  flags = '-O3 -D LBT_TRACE_ENABLED'
  ldflags = ''
else:
  flags = '-O3'
  ldflags = ''

ccflags = '-Wall -Wextra %s -isystem %s -isystem %s' % (flags, scopeDir, boostDir)
if (isWindows):
  env = Environment(ENV=os.environ, tools=['mingw']) # this builds in a dependency on the PATH, which is useful for ccache
else:
  env = Environment(ENV=os.environ)

env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS=ccflags)
env.Append(LIBPATH=['#/lib'])
env.Append(LINKFLAGS=ldflags)

if ('DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

libBoost = env.Command(['#/lib/*boost_system*', '#/lib/*boost_thread*', '#/lib/*boost_program_options'], boostDir, buildBoost)
liblg = sub('src')
c_example = sub('c_example')
libDir = env.Install('lib', liblg)
test = sub('test')
env.Depends(test, libBoost)
env.Depends(test, libDir)
env.Command('unittests', test, '$SOURCE --test')
env.InstallAs('#/lightgrep.exe', test)
