# Simple taskflowd workflow

job build
  command: make all

job test
  command: ctest
  depends: build

job package
  command: tar -czf artifact.tgz build/
  depends: build, test