import glob
import os
import platform
import os.path as p
import re

isWindows = False
isLinux = False
isShared = False
bits = '32'

def shellCall(cmd):
  print(cmd)
  os.system(cmd)

def sub(src):
  vars = ['env', 'isWindows', 'isLinux', 'isShared']
  return env.SConscript(p.join(src, 'SConscript'), exports=vars, variant_dir=p.join('bin', src), duplicate=0)

arch = platform.platform()
print("System is %s, %s" % (arch, platform.machine()))
if (platform.machine().find('64') > -1):
  bits = '64'

isWindows = arch.find('Windows') > -1
isLinux = arch.find('Linux') > -1

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

isShared = True if 'true' == ARGUMENTS.get('shared', 'false') else False

debug = ARGUMENTS.get('debug', 'false')
if (debug == 'true'):
  flags = '-g -fstack-protector-all'
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
elif (debug == 'hist'):
  flags = '-O3 -D LBT_HISTOGRAM_ENABLED'
  ldflags = ''
else:
  flags = '-O3'
  ldflags = ''

ccflags = '-Wall -Wno-trigraphs -Wextra %s -isystem %s -isystem %s' % (flags, scopeDir, boostDir)

# we inherit the OS environment to get PATH, so ccache works
if (isWindows):
  env = Environment(ENV=os.environ, tools=['mingw']) # we don't want scons to use Visual Studio just yet
else:
  env = Environment(ENV=os.environ)

env['DEBUG_MODE'] = debug
env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS=ccflags)
env.Append(LIBPATH=['#/lib'])
env.Append(LINKFLAGS=ldflags)

conf = Configure(env)
if (not (conf.CheckCXXHeader('boost/shared_ptr.hpp')
   and conf.CheckLib('boost_system')
   and conf.CheckLib('boost_thread')
   and conf.CheckLib('boost_program_options'))):
   print('Boost sanity check failed.')
   Exit(1)

if ('DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

#libBoost = env.Command(['#/lib/*boost_system*', '#/lib/*boost_thread*', '#/lib/*boost_program_options*'],
#                        boostDir, buildBoost)

liblg = sub('src/lib')
#env.Depends(liblg, libBoost)

libDir = env.Install('lib', liblg)

c_example = sub('c_example')
#env.Depends(c_example, libDir)

test = sub('test')
#env.Depends(test, libDir)

cmd = sub('src/cmd')
#env.Depends(cmd, libDir)

env.Command('unittests', test, '$SOURCE --test')
env.InstallAs('#/lightgrep.exe', cmd)
