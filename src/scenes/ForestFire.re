module Scene: Interfaces.Scene = {
  let id = "forestFire";

  let title = {js|🔥🌲🔥 A Forest Fire 🔥🌲🔥|js};

  let backgroundColorHex = "E25822";

  type state = {
    charactersReactedSequence: list(Character.t),
    anethirBurned: option(bool),
    stielettaGoesFirst: bool,
  };

  let initialState = {
    charactersReactedSequence: [],
    anethirBurned: None,
    stielettaGoesFirst: false,
  };

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
               <FadeInDiv key="anethirReaction" fadeInTime=2000>
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
             <FadeInDiv key="stielettaReaction1" fadeInTime=1000>
               <Text>
                 {js|The ominous voice grows even louder, its gleeful laughter reverberating throughout the clearing amidst the chaos and the fire.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               key="stielettaReaction2" fadeInTime=2000 startFadeInAt=1000>
               <br />
               <Text>
                 {js|Suddenly, a grim expression dawns on Stieletta's face. Her knuckles whiten as she tightens her fists.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               key="stielettaReaction3" fadeInTime=4000 startFadeInAt=2000>
               <br />
               <Text> {js|"I know that voice," she says coldly.|js} </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=4500
               startFadeInAt=4000>
               <button onClick={_ => localDispatch(ReactStieletta)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         | [Stieletta, Stieletta]
         | [Stieletta, Stieletta, Anethir] =>
           <>
             <FadeInDiv key="initial1" fadeInTime=2000>
               <Text>
                 {js|The circle of flame that ensnares the three adventurers begins to close in on them, as more and more of the clearing is swallowed by smoke and fire.

"Terribly sorry," the mysterious voice gloats, "but this is the end for—"

"Oh, enough!" Stieletta shouts. "I know it's you, |js}
               </Text>
               <Text npc=Euporie> "Euporie" </Text>
               <Text> {js|!"|js} </Text>
             </FadeInDiv>
             <FadeInDiv key="initial2" fadeInTime=2500 startFadeInAt=2000>
               <br />
               <Text> {js|For a moment, nothing happens.|js} </Text>
             </FadeInDiv>
             <FadeInDiv key="initial3" fadeInTime=3000 startFadeInAt=2500>
               <br />
               <Text>
                 {js|And then, in an instant, all of the raging fires disappear into puffs of ash, snuffed out like candles.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial4" fadeInTime=3500 startFadeInAt=3000>
               <br />
               <Text>
                 {{js|From the lingering smoke, a figure emerges.

She is a tiefling woman, with wine-red skin, bright amber eyes, and smooth curved horns. She approaches them with long, regal strides in her leather boots; an ornate cape, dyed a deep navy color, flows behind her. |js}
                  ++ {js|Everything about her, from her smartly tailored vest to the poise and elegance of her gait, exudes wealth and power.

"Well, well!" she says, grinning. "If it isn't Goldilocks Stabbytoes, in all her glory!"|js}}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial5" fadeInTime=4000 startFadeInAt=3500>
               <br />
               <Text> {js|Stieletta grits her teeth.|js} </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=4000
               startFadeInAt=3500>
               <button onClick={_ => localDispatch(NextScene)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         | [Jaziel]
         | [Jaziel, Anethir] =>
           <>
             <FadeInDiv key="jazielReaction1" fadeInTime=1000>
               <Text>
                 {js|"Beg your pardon," Jaziel shouts into the trees, somehow managing to sound reservedly polite. "Might we inquire as to your identity, o mysterious arsonist?"

The voice falls silent, and a hush falls over the clearing; even the roaring flames quieten a little.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               key="jazielReaction2" fadeInTime=4000 startFadeInAt=3000>
               <br />
               <Text>
                 {js|Then, a small gap appears in the circle of fire. The flames part slightly, like curtains pulled aside on a theater stage...|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               key="jazielReaction3" fadeInTime=7000 startFadeInAt=6000>
               <br />
               <Text>
                 {js|... and they reveal the silhouette of a woman, leaning casually against a burning tree.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               key="jazielReaction4" fadeInTime=10000 startFadeInAt=9000>
               <br />
               <Text> {js|"I thought you'd never ask," she says.|js} </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=15000
               startFadeInAt=9500>
               <button onClick={_ => localDispatch(ReactJaziel)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         | [Jaziel, Jaziel]
         | [Jaziel, Jaziel, Anethir] =>
           <>
             <FadeInDiv key="initial1" fadeInTime=2000>
               <Text>
                 {{js|The wall of fire parts, the smoke clears, and there she is.

Leaning against the base of a burning oak is a figure—a tiefling woman, judging by the wine-red skin and smooth curved horns. She rests one foot on the tree, her knee upraised,|js}
                  ++ {js| while she twirls a charred twig absent-mindedly between her fingers. With the deep navy cape draped underneath her, and her relaxed |js}
                  ++ {js|demeanour, the tiefling gives off a distinct air of comfort and ownership. The fire doesn't seem to affect her at all; her clothes and skin are completely untouched.

Amber, almond-shaped eyes watch the trail of soot the twig makes as she spins it around—she's either bored and lost in thought, or pretending to be. She does not acknowledge the three adventurers with her gaze.

"My name," she says, "is |js}}
               </Text>
               <Text npc=Euporie> "Euporie" </Text>
               <Text>
                 {js|."

She finally looks up at them, a devilish smirk on her face. "And you, my unfortunate friends, are—wait a minute."|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial2" fadeInTime=2500 startFadeInAt=2000>
               <br />
               <Text>
                 {js|She coughs, and suddenly her composure is completely lost. In an instant, the raging fires surrounding the clearing vanish into puffs of smoke, snuffed out like a candle.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial3" fadeInTime=3000 startFadeInAt=2500>
               <br />
               <Text>
                 {js|"Stieletta!? Knifeshoes Fancyfoot!?" she says.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv key="initial4" fadeInTime=3500 startFadeInAt=3000>
               <br />
               <Text>
                 {js|A bright grin spreads across her lips.

Stieletta, too, seems shocked. Her jaw drops slightly, and her eyes fill with seething rage.|js}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=4000
               startFadeInAt=3500>
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