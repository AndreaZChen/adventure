module Styles = {
  open Css;

  let fadeIn = startFadeInAtPercent =>
    keyframes([
      (0, [opacity(0.)]),
      (startFadeInAtPercent, [opacity(0.)]),
      (100, [opacity(1.)]),
    ]);

  let wrapper = (fadeInTime, startFadeInAtPercent) =>
    style([
      animationName(fadeIn(startFadeInAtPercent)),
      animationDuration(fadeInTime),
    ]);
};

[@react.component]
let make = (~children: React.element, ~fadeInTime=1000, ~startFadeInAtPercent=0) =>
  <div className={Styles.wrapper(fadeInTime, startFadeInAtPercent)}> children </div>;