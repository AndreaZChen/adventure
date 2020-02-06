let getSceneRendererById = id =>
  switch (id) {
  | id when id == InitialScene.id => InitialScene.renderer
  | id when id == ForestFire.id => ForestFire.renderer
  | _unknownId => InitialScene.renderer
  };