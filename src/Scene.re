type t = {getNextSceneFromCommand: Command.t => actionResult}
and actionResult =
  | NextScene(string, t)
  | SameScene(string);