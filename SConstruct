import os
import os.path as p

def sub(src):
  return env.SConscript(p.join(src, 'SConscript'), exports='env', variant_dir=p.join('bin', src), duplicate=0)

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
env.Replace(CCFLAGS='-Wall -Wextra %s -I%s -I%s' % (flags, scopeDir, boostDir))
env.Append(LIBPATH=['#/lib'])

liblg = sub('src')
libDir = env.Install('lib', liblg)
test = sub('test')

env.Command('unittests', test, './$SOURCE test')
