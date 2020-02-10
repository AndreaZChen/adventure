module Scene: Interfaces.Scene = {
  let id = "forestFire";

  let title = {js|🔥🌲🔥 A Forest Fire 🔥🌲🔥|js};

  let backgroundColorHex = "E25822";

  type state = {
    charactersReactedSequence: list(Character.t),
    anethirBurned: option(bool),
  };

  let initialState = {charactersReactedSequence: [], anethirBurned: None};

  type action =
    | NextScene
    | ReactStieletta
    | ReactAnethir
    | ReactJaziel
    | AnethirTouchFire
    | AnethirReconsiderTouchingFire;

  let reducer =
      (
        ~globalDispatch: GlobalState.action => unit,
        ~scrollToTop: unit => unit,
        action: action,
        state: state,
      ) =>
    switch (action) {
    | ReactStieletta =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Stieletta),
        },
        _self => {
          globalDispatch(StielettaRecognizeEuporieFirst);
          scrollToTop();
          None;
        },
      )
    | ReactAnethir =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Anethir),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | ReactJaziel =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Jaziel),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | AnethirTouchFire =>
      ReactUpdate.UpdateWithSideEffects(
        {...state, anethirBurned: Some(true)},
        _self => {
          globalDispatch(AnethirAddDamage(1));
          scrollToTop();
          None;
        },
      )
    | AnethirReconsiderTouchingFire =>
      ReactUpdate.UpdateWithSideEffects(
        {...state, anethirBurned: Some(false)},
        _self => {
          scrollToTop();
          None;
        },
      )
    | NextScene =>
      ReactUpdate.SideEffects(
        _self => {
          globalDispatch(SceneTransitioned(EuporieFirstMeeting.Scene.id));
          scrollToTop();
          None;
        },
      )
    };

  module Component = {
    [@react.component]
    let make = (~globalDispatch: GlobalState.action => unit) => {
      let scrollToTop = ScrollToTopProvider.useScrollToTop();
      let reducer =
        React.useMemo2(
          () => reducer(~globalDispatch, ~scrollToTop),
          (globalDispatch, scrollToTop),
        );
      let (localState, localDispatch) =
        ReactUpdate.useReducer(initialState, reducer);

      <>
        {switch (localState.charactersReactedSequence) {
         | [] =>
           <>
             <FadeInDiv key="initial" fadeInTime=2000>
               <Text>
                 {js|The forest is a roaring inferno.

Stieletta, Anethir, and Jaziel are on their feet, standing back to back around the campfire in the center of the clearing.

Jaziel is clutching his lute, silently letting his fingers glide across the strings; he scans the treetops for signs of their attacker, but to no avail.

Stieletta is elegantly posed in a martial fighting stance, seemingly unperturbed. She swats a stray cinder out of the air before it can land on her immaculate dress.

Anethir seems fascinated, rather than scared, by the forest fire. They've stashed their notebook inside their cloak and are now staring into the flames with bright eyes.

A disembodied voice cackles somewhere among the trees.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=2500
               startFadeInAt=2000>
               <button onClick={_ => localDispatch(ReactAnethir)}>
                 {React.string("React: Anethir")}
               </button>
               <button onClick={_ => localDispatch(ReactJaziel)}>
                 {React.string("React: Jaziel")}
               </button>
               <button onClick={_ => localDispatch(ReactStieletta)}>
                 {React.string("React: Stieletta")}
               </button>
             </FadeInDiv>
           </>
         | [Anethir] =>
           switch (localState.anethirBurned) {
           | None =>
             <>
               <FadeInDiv key="anethirReact" fadeInTime=2000>
                 <Text>
                   {js|"Ten gold coins says it's fake," Anethir says nonchalantly.

"What!?" Jaze and Stieletta exclaim in unison.

"You heard me! Fake, illusory, |js}
                 </Text>
                 <Text italicize=true> {js|bedräglig|js} </Text>
                 <Text>
                   {js|, whatever you wanna call it. I'm gonna stick my hand in it."

Jaziel groans, clutching the lute even tighter in his hands. "An, you damned rascal, this isn't the time to—"

With a mad glint in their eye, Anethir runs towards the edge of the clearing, closer to the burning trees...|js}
                 </Text>
               </FadeInDiv>
               <br />
               <FadeInDiv
                 className=CommonStyles.buttonsArea
                 fadeInTime=2500
                 startFadeInAt=2000>
                 {localState.charactersReactedSequence->Belt.List.length < 3
                    ? <>
                        <button
                          onClick={_ => localDispatch(AnethirTouchFire)}>
                          {React.string("Anethir: Put hand in fire")}
                        </button>
                        <button
                          onClick={_ =>
                            localDispatch(AnethirReconsiderTouchingFire)
                          }>
                          {React.string("Anethir: Reconsider")}
                        </button>
                      </>
                    : <button onClick={_ => localDispatch(NextScene)}>
                        {React.string("Next")}
                      </button>}
               </FadeInDiv>
             </>
           | Some(gotBurned) =>
             <>
               <FadeInDiv key="initial" fadeInTime=2000>
                 {gotBurned
                    ? <>
                        <Text>
                          {js|Anethir reaches out, sticking their little gnome hand into the flames—

—and immediately retracts it, yelping in pain. "Ow!!"

"Hey, Anethir?" says Jaziel, without taking his eyes off the trees. "I don't mean to be rude, but why the ever-loving heck did you stick your entire hand into what is clearly |js}
                        </Text>
                        <Text italicize=true> {js|fire?|js} </Text>
                        <Text>
                          {js|"

"😵", says Anethir, and quietly backs away from the burning trees.|js}
                        </Text>
                      </>
                    : <>
                        <Text>
                          {js|As Anethir approaches the flames, the sweltering heat becomes even more oppressive, the hot air more difficult to breathe. The sharp odor of charred wood fills their nostrils and makes their eyes water.

"On second thought," they muse, "not worth risking my notes over..."

"Or your |js}
                        </Text>
                        <Text italicize=true> {js|body|js} </Text>
                        <Text>
                          {js|," Stieletta adds, frowning. "Which you need to |js}
                        </Text>
                        <Text italicize=true> {js|live|js} </Text>
                        <Text>
                          {js|."

"Meh," says Anethir with a shrug, and quietly backs away from the burning trees.|js}
                        </Text>
                      </>}
               </FadeInDiv>
               <FadeInDiv
                 className=CommonStyles.buttonsArea
                 fadeInTime=2500
                 startFadeInAt=2000>
                 <button onClick={_ => localDispatch(ReactJaziel)}>
                   {React.string("React: Jaziel")}
                 </button>
                 <button onClick={_ => localDispatch(ReactStieletta)}>
                   {React.string("React: Stieletta")}
                 </button>
               </FadeInDiv>
             </>
           }
         | [Stieletta]
         | [Stieletta, Anethir] =>
           <>
             <FadeInDiv key="initial" fadeInTime=1000>
               <Text>
                 {js|The ominous voice grows even louder, its gleeful laughter reverberating throughout the clearing amidst the chaos and the fire.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial" fadeInTime=2000 startFadeInAt=1000>
               <br />
               <Text>
                 {js|Suddenly, a grim expression dawns on Stieletta's face. Her knuckles whiten as she tightens her fists.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial" fadeInTime=4000 startFadeInAt=2000>
               <br />
               <Text> {js|"I know that voice," she says coldly.|js} </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=4500
               startFadeInAt=4000>
               <button onClick={_ => localDispatch(NextScene)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         | [Jaziel]
         | [Jaziel, Anethir] =>
           <>
             <FadeInDiv key="initial" fadeInTime=1000>
               <Text>
                 {js|"Beg your pardon," Jaziel shouts into the trees, somehow managing to sound reservedly polite. "Might we inquire as to your identity, o mysterious arsonist?"

The voice falls silent, and a hush falls over the clearing; even the roaring flames quieten a little.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial" fadeInTime=4000 startFadeInAt=3000>
               <br />
               <Text>
                 {js|Then, a small gap appears in the circle of fire. The flames part slightly, like curtains pulled aside on a theater stage...|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial" fadeInTime=7000 startFadeInAt=6000>
               <br />
               <Text>
                 {js|... and they reveal the silhouette of a woman, leaning casually against a burning tree.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial" fadeInTime=10000 startFadeInAt=9000>
               <br />
               <Text> {js|"I thought you'd never ask," she says.|js} </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=15000
               startFadeInAt=9500>
               <button onClick={_ => localDispatch(NextScene)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         | [_reaction1, _reaction2, ..._] =>
           <>
             <br />
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=2500
               startFadeInAt=2000>
               <button onClick={_ => localDispatch(NextScene)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         }}
      </>;
    };
  };

  let renderer = (~globalState as _, ~globalDispatch) =>
    <Component globalDispatch />;
};