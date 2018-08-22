@Library('asdf_common') _

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
def DOWNSTREAM_REPOS = []
def UPSTREAM_REPOS = [['liblightrep', 'jenkins-aws-test']]

pipeline {
  agent none
  stages {
    stage('Handle Upstream Trigger') {
      agent any
      steps {
        script {
          sshagent(['jenkins_buildmaster']) {
            common.PrintUpstreamTriggerParams(params)
            common.IdentifyUpstream(env, BASE_URL, UPSTREAM_REPOS)
            common.PrintUpstreamRepos(UPSTREAM_REPOS)
          }
        }
      }
    }
    stage('Build') {
      steps {
        script {
          parallel common.makeConfigurations(scm, BUILDS)
        }
      }
    }
    stage('Trigger Downstream') {
      agent any
      steps {
        script {
          sshagent(['jenkins_buildmaster']) {
            common.TriggerDownstream(env, BASE_URL, DOWNSTREAM_REPOS)
          }
        }
      }
    }
  }
}
