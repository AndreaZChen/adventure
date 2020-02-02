let helpText = {|INSTRUCTIONS:

In this story, you play as three characters simultaneously: Anethir, Jaziel, and Stieletta.

To perform actions and advance the story, type commands into the input field below, or simply click any highlighted words in the narration.

For example, type "help" to bring up this help text again, or "look [something]" to get a description of something in the scene.

Some actions will require you to specify which character you want to perform the action. Write the character's name, or their first initial, followed by the action you want to perform.

For example, "stieletta sleep" will prompt Stieletta to sleep, and "a speak j" will prompt Anethir to talk to Jaziel.

This game does not have a particularly exhaustive list of available commands, and many are only valid in particular situations. If you find yourself struggling to find one that will work, the highlighted words in the narration will help you progress.
However, there may be some actions that can't be discovered without experimenting a little...

Common actions include:
|};

let helpTextElement =
  <>
    {React.string(helpText)}
    <ul>
      <li> {React.string("look")} </li>
      <li> {React.string("look [something]")} </li>
      <li> {React.string("[character] speak [character]")} </li>
      <li> {React.string("[character] take [something]")} </li>
      <li> {React.string("go [place]")} </li>
    </ul>
  </>;

let reducer: (Command.t, GlobalState.t) => GlobalState.t =
  (command, state) =>
    switch (command.character, command.action, command.arguments) {
    | (_, "help", _) =>
      GlobalState.pushNarrationElement(state, helpTextElement)
    | (Some(character), "kick", arguments) =>
      GlobalState.pushNarrationString(
        state,
        Character.toString(character)
        ++ " kicks "
        ++ String.concat(" ", arguments)
        ++ ".",
      )
    | _ =>
      GlobalState.pushNarrationString(
        state,
        "Invalid command. Type 'help' to learn what commands are available.",
      )
    };