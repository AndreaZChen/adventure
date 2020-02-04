open Css;

let defaultBackgroundHex = "f2f2f2";
let defaultBorderHex = "000000";
let defaultTextHex = "000000";
let defaultClickableTextHex = "B60024";
let defaultClickableHoveredTextHex = "DC143C";

let dialogZIndex = 1000;

let buttonsArea = style([
  width(`percent(100.)),
  display(`flex),
  justifyContent(`spaceAround),
  alignItems(`center),
  borderTop(`px(1), `solid, `hex(defaultBorderHex)),
  paddingTop(`px(10)),
  marginTop(`px(10)),
]);

global("button", [
  cursor(`pointer),
  paddingTop(`em(0.35)),
  paddingBottom(`em(0.35)),
  paddingLeft(`em(1.2)),
  paddingRight(`em(1.2)),
  border(`em(0.1), `solid, `hex(defaultBorderHex)),
  borderRadius(`em(0.12)),
  textAlign(`center),
  transitionDuration(200),
  hover([
    backgroundColor(`hex(defaultBorderHex)),
    color(`hex(defaultBackgroundHex)),
  ]),
  active([
    backgroundColor(`hex(defaultBorderHex)),
    color(`hex(defaultBackgroundHex)),
  ]),
]);

global("hr", [
  borderColor(`hex(defaultBorderHex)),
  width(`percent(100.)),
]);