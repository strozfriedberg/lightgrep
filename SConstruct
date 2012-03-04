import glob
import os
import platform
import os.path as p
import re

isWindows = False
isLinux = False
isShared = False
bits = '32'
boostType = ''
customer = ''

def shellCall(cmd):
  print(cmd)
  os.system(cmd)

def sub(src):
  vars = ['env', 'isWindows', 'isLinux', 'isShared', 'boostType', 'customer']
  return env.SConscript(p.join(src, 'SConscript'), exports=vars, variant_dir=p.join('bin', src), duplicate=0)

arch = platform.platform()
print("System is %s, %s" % (arch, platform.machine()))
if (platform.machine().find('64') > -1):
  bits = '64'

isWindows = arch.find('Windows') > -1
isLinux = arch.find('Linux') > -1

defines = [] # a list of defined symbols, as strings, for the preprocessor

isShared = True if 'true' == ARGUMENTS.get('shared', 'false') else False

customer = ARGUMENTS.get('customer', '')

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
elif (debug == 'perf'):
  flags = '-g -O3'
  ldflags = ''
elif (debug == 'trace'):
  flags = '-O3'
  defines.append('LBT_TRACE_ENABLED')
  ldflags = ''
else:
  flags = '-O3'
  ldflags = ''

ccflags = '-pedantic -Wall -Wextra -pipe %s' % (flags)
cppflags = '-std=c++0x'

# add vendors/scope and vendors/boost as system include paths, if they exist
ccflags += ''.join(' -isystem ' + d for d in filter(p.exists, ['vendors/scope', 'vendors/boost']))

boostType = ARGUMENTS.get('boostType', '')

# we inherit the OS environment to get PATH, so ccache works
if (isWindows):
  env = Environment(ENV=os.environ, tools=['mingw']) # we don't want scons to use Visual Studio just yet

  # This define results in BOOST_USE_WINDOWS_H being defined, but only in the right place,
  # so as to limit exposure to name conflicts caused by our friend, windows.h
  defines.append('POLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H')
  if (not isShared):
    defines.append('BOOST_THREAD_USE_LIB')
else:
  env = Environment(ENV=os.environ)

env['DEBUG_MODE'] = debug
env.Replace(CCFLAGS=ccflags)
env.Replace(CPPFLAGS=cppflags)
env.Replace(CPPDEFINES=defines)
env.Append(CPPPATH=['#/include'])
env.Append(LIBPATH=['#/lib'])
env.Append(LINKFLAGS=ldflags)

conf = Configure(env)
if (not (conf.CheckCXXHeader('boost/scoped_ptr.hpp')
   and conf.CheckLib('boost_system' + boostType)
   and conf.CheckLib('boost_thread' + boostType)
   and conf.CheckLib('boost_filesystem' + boostType)
   and conf.CheckLib('boost_program_options' + boostType))):
   print('Boost sanity check failed.')
   Exit(1)

if ('DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

liblg = sub('src/lib')

libDir = env.Install('lib', liblg)

c_example = sub('c_example')

test = sub('test')

cmd = sub('src/cmd')

env.Command('unittests', test, '$SOURCE --test')
env.InstallAs('#/lightgrep.exe', cmd)
