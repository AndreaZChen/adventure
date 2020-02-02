open Scene;

let value = {
  getNextSceneFromAction: input =>
    switch (input) {
    | "hello" => InvalidAction("Thanks for the greeting!")
    | _ => InvalidAction("Dunno what that means!")
    },
};