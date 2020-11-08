#!/usr/bin/env bash

set -e

{
  echo "TRAVIS_REPO_SLUG=$TRAVIS_REPO_SLUG"
  echo "TRAVIS_PULL_REQUEST=$TRAVIS_PULL_REQUEST"
  echo "TRAVIS_BRANCH=$TRAVIS_BRANCH"
  echo "TRAVIS_COMMIT=$TRAVIS_COMMIT"
} > .env
