type t = {getNextSceneFromAction: string => actionResult}
and actionResult =
  | NextScene(string, t)
  | InvalidAction(string);