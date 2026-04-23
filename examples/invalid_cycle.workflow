# Invalid workflow with a dependency cycle

job a
  command: echo a
  depends: c

job b
  command: echo b
  depends: a

job c
  command: echo c
  depends: b