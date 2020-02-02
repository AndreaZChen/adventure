let value: Scene.t = {
  getNextSceneFromCommand: (command: Command.t) =>
    switch (command.action) {
    | "hello" => SameScene("Thanks for the greeting!")
    | _ => SameScene("Dunno what that means!")
    },
};