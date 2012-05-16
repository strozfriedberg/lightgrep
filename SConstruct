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
  vars = ['env', 'isWindows', 'isLinux']
  return env.SConscript(p.join(src, 'SConscript'), exports=vars, variant_dir=p.join('bin', src), duplicate=0)

arch = platform.platform()
print("System is %s, %s" % (arch, platform.machine()))
if (platform.machine().find('64') > -1):
  bits = '64'

isWindows = arch.find('Windows') > -1
isLinux = arch.find('Linux') > -1

defines = [] # a list of defined symbols, as strings, for the preprocessor


vars = Variables('build_variables.py')
vars.AddVariables(
  BoolVariable('isShared', 'whether to build with shared libraries', False),
  ('customer', 'Customer name to be compiled into build products', ''),
  ('debug', 'Default false. Can be true|profile|coverage|perf|trace', 'false'),
  ('boostType', 'Suffix to add to Boost libraries to enable finding them', ''),
  ('CC', 'set the name of the C compiler to use (scons finds default)', ''),
  ('CXX', 'set the name of the C++ compiler to use (scons finds default)', '')
)

# we inherit the OS environment to get PATH, so ccache works
if (isWindows):
  env = Environment(ENV=os.environ, tools=['mingw'], variables = vars) # we don't want scons to use Visual Studio just yet

  # This define results in BOOST_USE_WINDOWS_H being defined, but only in the right place,
  # so as to limit exposure to name conflicts caused by our friend, windows.h
  defines.append('POLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H')

  if (platform.release() == 'XP'):
    defines.append('_WIN32_WINNT=0x0501')

  if (not env['isShared']):
    defines.append('BOOST_THREAD_USE_LIB')
else:
  env = Environment(ENV=os.environ, variables = vars)

vars.Save('build_variables.py', env)

debug = env['debug']
if (debug == 'true'):
  flags = '-g'
  ldflags = ''
  if (not isWindows):
    flags += ' -fstack-protector-all'
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

ldflags += ' -static-libstdc++'
ccflags = '-pedantic -Wall -Wextra -pipe %s' % (flags)
cxxflags = '-std=c++0x -Wnon-virtual-dtor'

if (isWindows):
  cxxflags += ' -mthreads'

# add vendors/scope and vendors/boost as system include paths, if they exist
ccflags += ''.join(' -isystem ' + d for d in filter(p.exists, ['vendors/scope', 'vendors/boost', 'vendors/icu']))

env['DEBUG_MODE'] = debug
env.Replace(CCFLAGS=ccflags)
env.Replace(CXXFLAGS=cxxflags)
env.Replace(CPPDEFINES=defines)
env.Append(CPPPATH=['#/include'])
env.Append(LIBPATH=['#/lib'])
env.Append(LINKFLAGS=ldflags)

print("CC = " + env['CC'])
print("CXX = " + env['CXX'])

Help(vars.GenerateHelpText(env))

conf = Configure(env)
boostType = env['boostType']
if (not (conf.CheckCXXHeader('boost/program_options.hpp')
   and conf.CheckLib('boost_system' + boostType)
   and conf.CheckLib('boost_thread' + boostType)
   and conf.CheckLib('boost_filesystem' + boostType)
   and conf.CheckLib('boost_program_options' + boostType))):
   print('Boost sanity check failed.')
   Exit(1)

if (not isWindows and 'DYLD_LIBRARY_PATH' not in os.environ and 'LD_LIBRARY_PATH' not in os.environ):
  print("** You probably need to set LD_LIBRARY_PATH or DYLD_LIBRARY_PATH **")

enc = sub('src/enc')

liblg = sub('src/lib')

libDir = env.Install('lib', liblg)

c_example = sub('c_example')

test = sub('test')

cmd = sub('src/cmd')

env.Command('unittests', test, '$SOURCE --test')
env.InstallAs('#/lightgrep.exe', cmd)
