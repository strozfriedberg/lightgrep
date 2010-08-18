import os
import platform
import os.path as p

def shellCall(cmd):
  print(cmd)
  os.system(cmd)

def sub(src):
  return env.SConscript(p.join(src, 'SConscript'), exports='env', variant_dir=p.join('bin', src), duplicate=0)

def buildBoost(target, source, env):
  shouldBuild = False
  for t in target:
    if (len(env.Glob(str(t))) == 1):
      shouldBuild = True
      break
  if (shouldBuild):
    curDir = os.getcwd()
    os.chdir(str(source[0]))
    shellCall('./bootstrap.sh')
    shellCall('./bjam --stagedir=%s --with-thread link=shared variant=release threading=multi stage' % curDir)
    os.chdir(curDir)

arch = platform.platform()
print("System is %s" % arch)

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

debug = ARGUMENTS.get('debug', 'false')
if (debug == 'true'):
  flags = '-g -fstack-protector-all'
elif (debug == 'profile'):
  flags = '-g -O1'
else:
  flags = '-O3'

env = Environment(ENV=os.environ) # this builds in a dependency on the PATH, which is useful for ccache
env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS='-Wall -Wextra %s -isystem %s -isystem %s' % (flags, scopeDir, boostDir))
env.Append(LIBPATH=['#/lib'])

if ('DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

libBoost = env.Command(['#/lib/*boost_thread*'], boostDir, buildBoost)
liblg = sub('src')
libDir = env.Install('lib', liblg)
test = sub('test')
env.Depends(test, libBoost)
env.Command('unittests', test, './$SOURCE --test')
