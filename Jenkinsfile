library "jenkins_shared_base" _
loadSharedLib()

def BUILDS = [
  'linux/64/shared',
  'windows/64/shared',
// 'windows/64/shared-fat',
  'windows/64/static',
  'windows/32/shared',
// 'windows/32/shared-fat',
  'windows/32/static'
]

def BASE_URL = 'ssh://git@stash.strozfriedberg.com/asdf'

pipeline {
  agent none
  stages {
    stage('Handle Upstream Trigger') {
      steps {
        script {
          common.HandleUpstreamTrigger(env, params, BASE_URL)
        }
      }
    }
    stage('Build') {
      steps {
        script {
          parallel common.makeConfigurations(scm, BUILDS, BASE_URL, common.UPSTREAM_REPOS)
        }
      }
    }
    stage('Trigger Downstream') {
      steps {
        script {
          common.TriggerDownstream(env, params)
        }
      }
    }
  }
}
