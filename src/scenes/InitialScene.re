let initialNarrationElement =
  <>
    <FadeInElement fadeInTime=3000>
      {React.string(
         {|Three friends are seated around a campfire.

It is nearly nighttime. There's not much to do but go to bed, and yet... none of the three feel eager to sleep.

What will they do now?

|},
       )}
    </FadeInElement>
    <FadeInElement fadeInTime=6000 startFadeInAtPercent=50>
      <span> {React.string("[Type ")} </span>
      <CommandClickText command=Command.Defaults.help text="help" />
      <span>
        {React.string(
           ", or simply click the word, to see a list of available commands.]",
         )}
      </span>
    </FadeInElement>
  </>;

let reducer: (Command.t, GlobalState.t) => GlobalState.t =
  (command, state) =>
    switch (command.character, command.action, command.arguments) {
    | (Some(character), "kick", arguments) =>
      GlobalState.pushNarrationString(
        state,
        Character.toString(character)
        ++ " kicks "
        ++ String.concat(" ", arguments)
        ++ ".",
      )
    | _ => DefaultCommandReducer.reducer(command, state)
    };